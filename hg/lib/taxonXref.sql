# taxonXref.sql was originally generated by the autoSql program, which also 
# generated taxonXref.c and taxonXref.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#mapping from ucsc organism name to ncbi tax id/name
CREATE TABLE taxonXref (
    organism varchar(255) not null,	# UCSC organism name
    taxon int unsigned not null,	# NCBI taxon ID
    name varchar(255) not null,	# NCBI taxon name Binomial format 
    toGenus varchar(255) not null,	# NCBI tree down to Genus
              #Indices
    PRIMARY KEY(organism),
    INDEX(taxon),
    INDEX(name)
);
