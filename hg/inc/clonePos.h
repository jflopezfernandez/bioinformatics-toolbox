/* clonePos.h was originally generated by the autoSql program, which also 
 * generated clonePos.c and clonePos.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2010 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef CLONEPOS_H
#define CLONEPOS_H

#define CLONEPOS_NUM_COLS 8

struct clonePos
/* A clone's position and other info. */
    {
    struct clonePos *next;  /* Next in singly linked list. */
    char *name;	/* Name of clone including version */
    unsigned seqSize;	/* base count not including gaps */
    unsigned char phase;	/* htg phase */
    char *chrom;	/* Reference sequence chromosome or scaffold */
    unsigned chromStart;	/* Start in chromosome */
    unsigned chromEnd;	/* End in chromosome */
    char stage[2];	/* F/D/P for finished/draft/predraft */
    char *faFile;	/* File with sequence. */
    };

void clonePosStaticLoad(char **row, struct clonePos *ret);
/* Load a row from clonePos table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct clonePos *clonePosLoad(char **row);
/* Load a clonePos from row fetched with select * from clonePos
 * from database.  Dispose of this with clonePosFree(). */

struct clonePos *clonePosLoadAll(char *fileName);
/* Load all clonePos from whitespace-separated file.
 * Dispose of this with clonePosFreeList(). */

struct clonePos *clonePosLoadAllByChar(char *fileName, char chopper);
/* Load all clonePos from chopper separated file.
 * Dispose of this with clonePosFreeList(). */

#define clonePosLoadAllByTab(a) clonePosLoadAllByChar(a, '\t');
/* Load all clonePos from tab separated file.
 * Dispose of this with clonePosFreeList(). */

struct clonePos *clonePosCommaIn(char **pS, struct clonePos *ret);
/* Create a clonePos out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new clonePos */

void clonePosFree(struct clonePos **pEl);
/* Free a single dynamically allocated clonePos such as created
 * with clonePosLoad(). */

void clonePosFreeList(struct clonePos **pList);
/* Free a list of dynamically allocated clonePos's */

void clonePosOutput(struct clonePos *el, FILE *f, char sep, char lastSep);
/* Print out clonePos.  Separate fields with sep. Follow last field with lastSep. */

#define clonePosTabOut(el,f) clonePosOutput(el,f,'\t','\n');
/* Print out clonePos as a line in a tab-separated file. */

#define clonePosCommaOut(el,f) clonePosOutput(el,f,',',',');
/* Print out clonePos as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* CLONEPOS_H */

