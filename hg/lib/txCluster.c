/* txCluster.c was originally generated by the autoSql program, which also 
 * generated txCluster.h and txCluster.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "txCluster.h"


struct txCluster *txClusterLoad(char **row)
/* Load a txCluster from row fetched with select * from txCluster
 * from database.  Dispose of this with txClusterFree(). */
{
struct txCluster *ret;

AllocVar(ret);
ret->txCount = sqlSigned(row[6]);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlSigned(row[1]);
ret->chromEnd = sqlSigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = sqlSigned(row[4]);
safecpy(ret->strand, sizeof(ret->strand), row[5]);
{
int sizeOne;
sqlStringDynamicArray(row[7], &ret->txArray, &sizeOne);
assert(sizeOne == ret->txCount);
}
return ret;
}

struct txCluster *txClusterLoadAll(char *fileName) 
/* Load all txCluster from a whitespace-separated file.
 * Dispose of this with txClusterFreeList(). */
{
struct txCluster *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[8];

while (lineFileRow(lf, row))
    {
    el = txClusterLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct txCluster *txClusterLoadAllByChar(char *fileName, char chopper) 
/* Load all txCluster from a chopper separated file.
 * Dispose of this with txClusterFreeList(). */
{
struct txCluster *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[8];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = txClusterLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct txCluster *txClusterCommaIn(char **pS, struct txCluster *ret)
/* Create a txCluster out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new txCluster */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlSignedComma(&s);
ret->chromEnd = sqlSignedComma(&s);
ret->name = sqlStringComma(&s);
ret->score = sqlSignedComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
ret->txCount = sqlSignedComma(&s);
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->txArray, ret->txCount);
for (i=0; i<ret->txCount; ++i)
    {
    ret->txArray[i] = sqlStringComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
*pS = s;
return ret;
}

void txClusterFree(struct txCluster **pEl)
/* Free a single dynamically allocated txCluster such as created
 * with txClusterLoad(). */
{
struct txCluster *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
/* All strings in txArray are allocated at once, so only need to free first. */
if (el->txArray != NULL)
    freeMem(el->txArray[0]);
freeMem(el->txArray);
freez(pEl);
}

void txClusterFreeList(struct txCluster **pList)
/* Free a list of dynamically allocated txCluster's */
{
struct txCluster *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    txClusterFree(&el);
    }
*pList = NULL;
}

void txClusterOutput(struct txCluster *el, FILE *f, char sep, char lastSep) 
/* Print out txCluster.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->chromStart);
fputc(sep,f);
fprintf(f, "%d", el->chromEnd);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->score);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strand);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->txCount);
fputc(sep,f);
{
int i;
if (sep == ',') fputc('{',f);
for (i=0; i<el->txCount; ++i)
    {
    if (sep == ',') fputc('"',f);
    fprintf(f, "%s", el->txArray[i]);
    if (sep == ',') fputc('"',f);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
}
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

