/* wgEncodeGencodePubMed.c was originally generated by the autoSql program, which also 
 * generated wgEncodeGencodePubMed.h and wgEncodeGencodePubMed.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2011 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "encode/wgEncodeGencodePubMed.h"


void wgEncodeGencodePubMedStaticLoad(char **row, struct wgEncodeGencodePubMed *ret)
/* Load a row from wgEncodeGencodePubMed table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->transcriptId = row[0];
ret->pubMedId = sqlSigned(row[1]);
}

struct wgEncodeGencodePubMed *wgEncodeGencodePubMedLoad(char **row)
/* Load a wgEncodeGencodePubMed from row fetched with select * from wgEncodeGencodePubMed
 * from database.  Dispose of this with wgEncodeGencodePubMedFree(). */
{
struct wgEncodeGencodePubMed *ret;

AllocVar(ret);
ret->transcriptId = cloneString(row[0]);
ret->pubMedId = sqlSigned(row[1]);
return ret;
}

struct wgEncodeGencodePubMed *wgEncodeGencodePubMedLoadAll(char *fileName) 
/* Load all wgEncodeGencodePubMed from a whitespace-separated file.
 * Dispose of this with wgEncodeGencodePubMedFreeList(). */
{
struct wgEncodeGencodePubMed *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[2];

while (lineFileRow(lf, row))
    {
    el = wgEncodeGencodePubMedLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct wgEncodeGencodePubMed *wgEncodeGencodePubMedLoadAllByChar(char *fileName, char chopper) 
/* Load all wgEncodeGencodePubMed from a chopper separated file.
 * Dispose of this with wgEncodeGencodePubMedFreeList(). */
{
struct wgEncodeGencodePubMed *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[2];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = wgEncodeGencodePubMedLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct wgEncodeGencodePubMed *wgEncodeGencodePubMedCommaIn(char **pS, struct wgEncodeGencodePubMed *ret)
/* Create a wgEncodeGencodePubMed out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new wgEncodeGencodePubMed */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->transcriptId = sqlStringComma(&s);
ret->pubMedId = sqlSignedComma(&s);
*pS = s;
return ret;
}

void wgEncodeGencodePubMedFree(struct wgEncodeGencodePubMed **pEl)
/* Free a single dynamically allocated wgEncodeGencodePubMed such as created
 * with wgEncodeGencodePubMedLoad(). */
{
struct wgEncodeGencodePubMed *el;

if ((el = *pEl) == NULL) return;
freeMem(el->transcriptId);
freez(pEl);
}

void wgEncodeGencodePubMedFreeList(struct wgEncodeGencodePubMed **pList)
/* Free a list of dynamically allocated wgEncodeGencodePubMed's */
{
struct wgEncodeGencodePubMed *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    wgEncodeGencodePubMedFree(&el);
    }
*pList = NULL;
}

void wgEncodeGencodePubMedOutput(struct wgEncodeGencodePubMed *el, FILE *f, char sep, char lastSep) 
/* Print out wgEncodeGencodePubMed.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->transcriptId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->pubMedId);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

