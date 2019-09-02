/* recombRateRat.h was originally generated by the autoSql program, which also 
 * generated recombRateRat.c and recombRateRat.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2003 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef RECOMBRATERAT_H
#define RECOMBRATERAT_H

#define RECOMBRATERAT_NUM_COLS 6

struct recombRateRat
/* Describes the recombination rate in 5Mb intervals based on genetic maps */
    {
    struct recombRateRat *next;  /* Next in singly linked list. */
    char *chrom;	/* chromosome number */
    unsigned chromStart;	/* Start position in genoSeq */
    unsigned chromEnd;	/* End position in genoSeq */
    char *name;	/* Constant string recombRate */
    float shrspAvg;	/* Calculated SHRSPxBN recombination rate */
    float fhhAvg;	/* Calculated FHHxACI recombination rate */
    };

void recombRateRatStaticLoad(char **row, struct recombRateRat *ret);
/* Load a row from recombRateRat table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct recombRateRat *recombRateRatLoad(char **row);
/* Load a recombRateRat from row fetched with select * from recombRateRat
 * from database.  Dispose of this with recombRateRatFree(). */

struct recombRateRat *recombRateRatLoadAll(char *fileName);
/* Load all recombRateRat from whitespace-separated file.
 * Dispose of this with recombRateRatFreeList(). */

struct recombRateRat *recombRateRatLoadAllByChar(char *fileName, char chopper);
/* Load all recombRateRat from chopper separated file.
 * Dispose of this with recombRateRatFreeList(). */

#define recombRateRatLoadAllByTab(a) recombRateRatLoadAllByChar(a, '\t');
/* Load all recombRateRat from tab separated file.
 * Dispose of this with recombRateRatFreeList(). */

struct recombRateRat *recombRateRatCommaIn(char **pS, struct recombRateRat *ret);
/* Create a recombRateRat out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new recombRateRat */

void recombRateRatFree(struct recombRateRat **pEl);
/* Free a single dynamically allocated recombRateRat such as created
 * with recombRateRatLoad(). */

void recombRateRatFreeList(struct recombRateRat **pList);
/* Free a list of dynamically allocated recombRateRat's */

void recombRateRatOutput(struct recombRateRat *el, FILE *f, char sep, char lastSep);
/* Print out recombRateRat.  Separate fields with sep. Follow last field with lastSep. */

#define recombRateRatTabOut(el,f) recombRateRatOutput(el,f,'\t','\n');
/* Print out recombRateRat as a line in a tab-separated file. */

#define recombRateRatCommaOut(el,f) recombRateRatOutput(el,f,',',',');
/* Print out recombRateRat as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* RECOMBRATERAT_H */
