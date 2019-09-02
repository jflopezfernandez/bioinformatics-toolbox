/* bgiGeneSnp.c was originally generated by the autoSql program, which also 
 * generated bgiGeneSnp.h and bgiGeneSnp.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "bgiGeneSnp.h"


void bgiGeneSnpStaticLoad(char **row, struct bgiGeneSnp *ret)
/* Load a row from bgiGeneSnp table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{
ret->geneName = row[0];
ret->snpName = row[1];
ret->geneAssoc = row[2];
ret->effect = row[3];
strcpy(ret->phase, row[4]);
ret->siftComment = row[5];
}

struct bgiGeneSnp *bgiGeneSnpLoad(char **row)
/* Load a bgiGeneSnp from row fetched with select * from bgiGeneSnp
 * from database.  Dispose of this with bgiGeneSnpFree(). */
{
struct bgiGeneSnp *ret;

AllocVar(ret);
ret->geneName = cloneString(row[0]);
ret->snpName = cloneString(row[1]);
ret->geneAssoc = cloneString(row[2]);
ret->effect = cloneString(row[3]);
strcpy(ret->phase, row[4]);
ret->siftComment = cloneString(row[5]);
return ret;
}

struct bgiGeneSnp *bgiGeneSnpLoadAll(char *fileName) 
/* Load all bgiGeneSnp from a whitespace-separated file.
 * Dispose of this with bgiGeneSnpFreeList(). */
{
struct bgiGeneSnp *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[6];

while (lineFileRow(lf, row))
    {
    el = bgiGeneSnpLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct bgiGeneSnp *bgiGeneSnpLoadAllByChar(char *fileName, char chopper) 
/* Load all bgiGeneSnp from a chopper separated file.
 * Dispose of this with bgiGeneSnpFreeList(). */
{
struct bgiGeneSnp *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[6];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = bgiGeneSnpLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct bgiGeneSnp *bgiGeneSnpCommaIn(char **pS, struct bgiGeneSnp *ret)
/* Create a bgiGeneSnp out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new bgiGeneSnp */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->geneName = sqlStringComma(&s);
ret->snpName = sqlStringComma(&s);
ret->geneAssoc = sqlStringComma(&s);
ret->effect = sqlStringComma(&s);
sqlFixedStringComma(&s, ret->phase, sizeof(ret->phase));
ret->siftComment = sqlStringComma(&s);
*pS = s;
return ret;
}

void bgiGeneSnpFree(struct bgiGeneSnp **pEl)
/* Free a single dynamically allocated bgiGeneSnp such as created
 * with bgiGeneSnpLoad(). */
{
struct bgiGeneSnp *el;

if ((el = *pEl) == NULL) return;
freeMem(el->geneName);
freeMem(el->snpName);
freeMem(el->geneAssoc);
freeMem(el->effect);
freeMem(el->siftComment);
freez(pEl);
}

void bgiGeneSnpFreeList(struct bgiGeneSnp **pList)
/* Free a list of dynamically allocated bgiGeneSnp's */
{
struct bgiGeneSnp *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    bgiGeneSnpFree(&el);
    }
*pList = NULL;
}

void bgiGeneSnpOutput(struct bgiGeneSnp *el, FILE *f, char sep, char lastSep) 
/* Print out bgiGeneSnp.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->snpName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneAssoc);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->effect);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->phase);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->siftComment);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

