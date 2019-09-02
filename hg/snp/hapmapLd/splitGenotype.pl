#!/usr/bin/env perl
# DO NOT EDIT this file in any installed-bin location --
# edit kent/src/hg/snp/hapmapLd/splitGenotype.pl instead.

# $Id: splitGenotype.pl,v 1.2 2007/10/31 05:44:37 angie Exp $

use warnings;
use strict;
use Getopt::Long;

sub usage {
  die "usage: splitGenotype.pl chunkSize overlap outBase [f1 [f2...]]
options:
      -suffix [.]abc.xyz -- Append .abc.xyz to output file names.  If it ends
                            in .gz, output will be gzip-compressed.
      -verbose N         -- Print messages of level N or less to stderr
                            (default 1).
      -help              -- Show this message.
    Splits HapMap unphased genotypes_ download files into chunks of chunkSize
    plus overlap before and after, so that within the main part of the chunk,
    all neighbors will be present so computed LD scores will be correct.

    Also outputs a file outBase.map (-suffix doesn't affect this part) that
    specifies which SNPs in each output chunk file should have meaningful
    scores, i.e. are in the main part and not the overlap part where not all
    neighbors may be present.

    chunkSize must be *at least* twice as large as overlap -- for a reasonably
    efficient cluster run, more like at least 10x.\n\n";
}

use vars qw/
    $opt_suffix
    $opt_verbose
    $opt_help
    /;

my $ok = GetOptions('suffix=s',
		    'verbose=n',
		    'help',
		   );
&usage if (!$ok);
&usage if ($opt_help);
$opt_verbose = 1 if (! defined $opt_verbose);

my $chunkSize = shift || &usage;
my $overlap   = shift || &usage;
my $outBase   = shift || &usage;

sub verbose($$) {
  my ($level, $message) = @_;
  warn $message if ($level <= $opt_verbose);
}

&usage if ($chunkSize < ($overlap * 2));
&verbose(1, "Consider a larger chunkSize (like at least 10x overlap) for a " .
	 "more efficient cluster run.\n")
  if ($chunkSize < ($overlap * 10));

$outBase .= '.' if ($outBase !~ /[\.\/_-]$/);
my $suffix = $opt_suffix ? $opt_suffix : "";
$suffix = '.' . $suffix if ($suffix !~ /^\./);

sub outFileName($) {
  my ($chunk) = @_;
  sprintf "$outBase%03d%s", $chunk, $suffix;
}

my ($curChunk, $nextChunk) = (0, 1);
my ($curFile, $nextFile);
my @overlapSnps;

sub openChunk ($) {
  my ($chunk) = @_;
  my $outName = &outFileName($chunk);
  my $file;
  if ($outName =~ /\.gz$/) {
    open($file, "| gzip -c > $outName")
      || die ("Can't open pipe to gzip -c > $outName: $!\n");
  } else {
    open($file, ">$outName")
      || die ("Can't open $outName for writing: $!\n");
  }
  return $file;
}

sub closeNextFile () {
  if (defined $nextFile) {
    close($nextFile);
    # This is called only when we reach the end of a sequence.  If $nextFile
    # exists at that point, it is redundant, so remove it.
    unlink &outFileName($nextChunk);
    pop @overlapSnps;
    $nextFile = undef;
  }
}

sub mapHeader($) {
  my ($curChunk) = @_;
  my $fileName = &outFileName($curChunk);
  $fileName =~ s/^.+\///;
  return "# $fileName\n";
}

open(MAP, ">${outBase}map")
  || die "Can't open ${outBase}map for writing: $!\n";

$curFile = &openChunk($curChunk);
my ($prevChr, $prevPos);
my $fileHeader = <>;
print $curFile $fileHeader if ($fileHeader);
print MAP &mapHeader($curChunk);
my $nextMap = "";
while (<>) {
  if (! /^(rs\d+) \S+ (chr[0-9MXY]+) (\d+) /) {
    chomp;
    &verbose(1, "Skipping header line: " . substr($_, 0, 30) . "...\n");
    next;
  }
  my ($snp, $chr, $pos) = ($1, $2, $3);

  # Change of chromosome -- close books & reset.
  if ($prevChr && $chr ne $prevChr) {
    close($curFile);
    &closeNextFile($prevPos);
    print MAP $nextMap if ($nextMap);
    &verbose(2, "$prevChr " . &outFileName($curChunk) . " --> $chr " .
	     &outFileName($nextChunk) . "\n");
    $curChunk ++;  $nextChunk ++;
    if (@overlapSnps) {
      &verbose(1, "The LD for these $prevChr SNPs should agree if present " .
	       "in overlapping chunks: " . join(", ", @overlapSnps) . "\n");
    }
    $curFile = &openChunk($curChunk);
    print $curFile $fileHeader;
    print MAP &mapHeader($curChunk);
    ($prevChr, $prevPos) = ();
    @overlapSnps = ();
  }

  # Always print to $curFile.
  print $curFile $_;
  &verbose(3, "CUR  " . $_);;

  my $offset = $pos % $chunkSize;
  my $prevOffset;
  if ($prevPos) {
    $prevOffset = $prevPos % $chunkSize;
    if ($offset == 0 && defined $nextFile) {
      # This is the point of maximum overlap.  This snp should have enough
      # neighbors in both cur and next chunks.
      &verbose(2, "Noticed overlap $snp at pos $pos.\n");
      push @overlapSnps, $snp;
    }
  }

  # Open nextFile when we first get within $overlap of the next chunk:
  if ($offset >= ($chunkSize - $overlap) &&
      (!$prevOffset || $prevOffset < ($chunkSize - $overlap))) {
    if (!defined $nextFile) {
      &verbose(2, "Opening nextChunk $nextChunk at pos $pos.\n");
      $nextFile = &openChunk($nextChunk);
      print $nextFile $fileHeader;
    } else {
      &verbose(2, "Carrying nextChunk $nextChunk over at pos $pos.\n");
    }
  }

  # Print to $nextFile if it exists, and pass the baton from $curFile
  # to $nextFile when we get past $overlap;
  if (defined $nextFile) {
    print $nextFile $_;
    &verbose(3, "NEXT " . $_);
    if ($offset < $overlap) {
      $nextMap .= "$snp\n";
    } elsif ($offset >= $overlap && $offset < ($chunkSize - $overlap)) {
      &verbose(2, "Passing baton $curChunk --> $nextChunk at pos $pos.\n");
      close($curFile);
      $nextMap .= "$snp\n";
      $curChunk++;  $nextChunk++;
      $curFile = $nextFile;
      $nextFile = undef;
      print MAP &mapHeader($curChunk);
      print MAP $nextMap if ($nextMap);
      $nextMap = "";
    } else {
      print MAP "$snp\n";
    }
  } else {
    print MAP "$snp\n";
  }
  ($prevChr, $prevPos) = ($chr, $pos);
}
print MAP $nextMap if ($nextMap);
close($curFile);
&closeNextFile($prevPos);
close(MAP);

if (@overlapSnps) {
  &verbose(1, "The LD for these $prevChr SNPs should agree if present " .
	   "in overlapping chunks: " . join(", ", @overlapSnps) . "\n");
}

