/* taxonDivision.c was originally generated by the autoSql program, which also 
 * generated taxonDivision.h and taxonDivision.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "taxonDivision.h"


void taxonDivisionStaticLoad(char **row, struct taxonDivision *ret)
/* Load a row from taxonDivision table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->id = sqlUnsigned(row[0]);
strcpy(ret->code, row[1]);
ret->name = row[2];
ret->comments = row[3];
}

struct taxonDivision *taxonDivisionLoad(char **row)
/* Load a taxonDivision from row fetched with select * from taxonDivision
 * from database.  Dispose of this with taxonDivisionFree(). */
{
struct taxonDivision *ret;

AllocVar(ret);
ret->id = sqlUnsigned(row[0]);
strcpy(ret->code, row[1]);
ret->name = cloneString(row[2]);
ret->comments = cloneString(row[3]);
return ret;
}

struct taxonDivision *taxonDivisionLoadAll(char *fileName) 
/* Load all taxonDivision from a whitespace-separated file.
 * Dispose of this with taxonDivisionFreeList(). */
{
struct taxonDivision *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileRow(lf, row))
    {
    el = taxonDivisionLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct taxonDivision *taxonDivisionLoadAllByChar(char *fileName, char chopper) 
/* Load all taxonDivision from a chopper separated file.
 * Dispose of this with taxonDivisionFreeList(). */
{
struct taxonDivision *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = taxonDivisionLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct taxonDivision *taxonDivisionLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all taxonDivision from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with taxonDivisionFreeList(). */
{
struct taxonDivision *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = taxonDivisionLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void taxonDivisionSaveToDb(struct sqlConnection *conn, struct taxonDivision *el, char *tableName, int updateSize)
/* Save taxonDivision as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Strings are automatically escaped to allow insertion into the database. */
{
struct dyString *update = newDyString(updateSize);
sqlDyStringPrintf(update, "insert into %s values ( %u,'%s','%s','%s')", 
	tableName,  el->id,  el->code,  el->name,  el->comments);
sqlUpdate(conn, update->string);
freeDyString(&update);
}


struct taxonDivision *taxonDivisionCommaIn(char **pS, struct taxonDivision *ret)
/* Create a taxonDivision out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new taxonDivision */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->id = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->code, sizeof(ret->code));
ret->name = sqlStringComma(&s);
ret->comments = sqlStringComma(&s);
*pS = s;
return ret;
}

void taxonDivisionFree(struct taxonDivision **pEl)
/* Free a single dynamically allocated taxonDivision such as created
 * with taxonDivisionLoad(). */
{
struct taxonDivision *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->comments);
freez(pEl);
}

void taxonDivisionFreeList(struct taxonDivision **pList)
/* Free a list of dynamically allocated taxonDivision's */
{
struct taxonDivision *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    taxonDivisionFree(&el);
    }
*pList = NULL;
}

void taxonDivisionOutput(struct taxonDivision *el, FILE *f, char sep, char lastSep) 
/* Print out taxonDivision.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->id);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->code);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->comments);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

