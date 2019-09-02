/* simpleRepeat.h was originally generated by the autoSql program, which also 
 * generated simpleRepeat.c and simpleRepeat.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2002 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef SIMPLEREPEAT_H
#define SIMPLEREPEAT_H

struct simpleRepeat
/* Describes the Simple Tandem Repeats */
    {
    struct simpleRepeat *next;  /* Next in singly linked list. */
    char *chrom;	/* Human chromosome or FPC contig */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Simple Repeats tag name */
    unsigned period;	/* Length of repeat unit */
    float copyNum;	/* Mean number of copies of repeat */
    unsigned consensusSize;	/* Length of consensus sequence */
    unsigned perMatch;	/* Percentage Match */
    unsigned perIndel;	/* Percentage Indel */
    unsigned score;	/* Score between  and .  Best is . */
    unsigned A;	/* Number of A's in repeat unit */
    unsigned C;	/* Number of C's in repeat unit */
    unsigned G;	/* Number of G's in repeat unit */
    unsigned T;	/* Number of T's in repeat unit */
    float entropy;	/* Entropy */
    char *sequence;	/* Sequence of repeat unit element */
    };

void simpleRepeatStaticLoad(char **row, struct simpleRepeat *ret);
/* Load a row from simpleRepeat table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct simpleRepeat *simpleRepeatLoad(char **row);
/* Load a simpleRepeat from row fetched with select * from simpleRepeat
 * from database.  Dispose of this with simpleRepeatFree(). */

struct simpleRepeat *simpleRepeatLoadAll(char *fileName);
/* Load all simpleRepeat from a tab-separated file.
 * Dispose of this with simpleRepeatFreeList(). */

struct simpleRepeat *simpleRepeatLoadWhere(struct sqlConnection *conn, char *table, char *where);
/* Load all simpleRepeat from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with simpleRepeatFreeList(). */

struct simpleRepeat *simpleRepeatCommaIn(char **pS, struct simpleRepeat *ret);
/* Create a simpleRepeat out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new simpleRepeat */

void simpleRepeatFree(struct simpleRepeat **pEl);
/* Free a single dynamically allocated simpleRepeat such as created
 * with simpleRepeatLoad(). */

void simpleRepeatFreeList(struct simpleRepeat **pList);
/* Free a list of dynamically allocated simpleRepeat's */

void simpleRepeatOutput(struct simpleRepeat *el, FILE *f, char sep, char lastSep);
/* Print out simpleRepeat.  Separate fields with sep. Follow last field with lastSep. */

#define simpleRepeatTabOut(el,f) simpleRepeatOutput(el,f,'\t','\n');
/* Print out simpleRepeat as a line in a tab-separated file. */

#define simpleRepeatCommaOut(el,f) simpleRepeatOutput(el,f,',',',');
/* Print out simpleRepeat as a comma separated list including final comma. */

#endif /* SIMPLEREPEAT_H */
