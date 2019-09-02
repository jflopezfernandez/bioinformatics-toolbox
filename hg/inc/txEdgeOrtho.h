/* txEdgeOrtho.h was originally generated by the autoSql program, which also 
 * generated txEdgeOrtho.c and txEdgeOrtho.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2007 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef TXEDGEORTHO_H
#define TXEDGEORTHO_H

#define TXEDGEORTHO_NUM_COLS 19

enum txEdgeOrthoType
    {
    txEdgeOrthoExon = 0,
    txEdgeOrthoIntron = 1,
    };
struct txEdgeOrtho
/* A transcription edge with additional orthology information. */
    {
    struct txEdgeOrtho *next;  /* Next in singly linked list. */
    char *chrom;	/* Chromosome or contig name */
    int chromStart;	/* Start position, zero-based */
    int chromEnd;	/* End position, non-inclusive */
    char *name;	/* Name of txGraph in other organism */
    int score;	/* Parts per thousand of edge that align */
    char strand[2];	/* Strand - either plus or minus */
    char startType[2];	/* [ or ( for hard or soft */
    enum txEdgeOrthoType type;	/* edge type */
    char endType[2];	/* ] or ) for hard or soft */
    char *mappedChrom;	/* Chromosome in other organism */
    int mappedStart;	/* ChromStart mapped to other organism */
    int mappedEnd;	/* ChromEnd mapped to other organism */
    char *txGraph;	/* Transcription graph name in this organism */
    int overlapScore;	/* Parts per thousand of mapped/ortho overlap */
    char orthoStrand[2];	/* Strand of orthologous txGraph */
    char orthoStartType[2];	/* Is orthologous start hard/soft? */
    char orthoEndType[2];	/* Is orthologous end hard/soft? */
    int orthoStart;	/* Start of orthologous edge (based on RNA in other species) */
    int orthoEnd;	/* End of orthologous edge (based on RNA in other species) */
    };

void txEdgeOrthoStaticLoad(char **row, struct txEdgeOrtho *ret);
/* Load a row from txEdgeOrtho table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct txEdgeOrtho *txEdgeOrthoLoad(char **row);
/* Load a txEdgeOrtho from row fetched with select * from txEdgeOrtho
 * from database.  Dispose of this with txEdgeOrthoFree(). */

struct txEdgeOrtho *txEdgeOrthoLoadAll(char *fileName);
/* Load all txEdgeOrtho from whitespace-separated file.
 * Dispose of this with txEdgeOrthoFreeList(). */

struct txEdgeOrtho *txEdgeOrthoLoadAllByChar(char *fileName, char chopper);
/* Load all txEdgeOrtho from chopper separated file.
 * Dispose of this with txEdgeOrthoFreeList(). */

#define txEdgeOrthoLoadAllByTab(a) txEdgeOrthoLoadAllByChar(a, '\t');
/* Load all txEdgeOrtho from tab separated file.
 * Dispose of this with txEdgeOrthoFreeList(). */

struct txEdgeOrtho *txEdgeOrthoCommaIn(char **pS, struct txEdgeOrtho *ret);
/* Create a txEdgeOrtho out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new txEdgeOrtho */

void txEdgeOrthoFree(struct txEdgeOrtho **pEl);
/* Free a single dynamically allocated txEdgeOrtho such as created
 * with txEdgeOrthoLoad(). */

void txEdgeOrthoFreeList(struct txEdgeOrtho **pList);
/* Free a list of dynamically allocated txEdgeOrtho's */

void txEdgeOrthoOutput(struct txEdgeOrtho *el, FILE *f, char sep, char lastSep);
/* Print out txEdgeOrtho.  Separate fields with sep. Follow last field with lastSep. */

#define txEdgeOrthoTabOut(el,f) txEdgeOrthoOutput(el,f,'\t','\n');
/* Print out txEdgeOrtho as a line in a tab-separated file. */

#define txEdgeOrthoCommaOut(el,f) txEdgeOrthoOutput(el,f,',',',');
/* Print out txEdgeOrtho as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* TXEDGEORTHO_H */

