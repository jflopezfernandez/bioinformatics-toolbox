/* gtexTissueData.h was originally generated by the autoSql program, which also 
 * generated gtexTissueData.c and gtexTissueData.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef GTEXTISSUEDATA_H
#define GTEXTISSUEDATA_H

#include "jksql.h"
#define GTEXTISSUEDATA_NUM_COLS 7

extern char *gtexTissueDataCommaSepFieldNames;

struct gtexTissueData
/* GTEX Expression data summarized by tissue (RPKM) */
    {
    struct gtexTissueData *next;  /* Next in singly linked list. */
    char *geneId;	/* Gene identifier (ensembl) */
    char *tissue;	/* Tissue short name */
    double min;	/* Minimum expression level */
    double q1;	/* 1st quartile expression level */
    double median;	/* Median expression level */
    double q3;	/* 3rd quartile expression level */
    double max;	/* Maximum expression level */
    };

void gtexTissueDataStaticLoad(char **row, struct gtexTissueData *ret);
/* Load a row from gtexTissueData table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct gtexTissueData *gtexTissueDataLoadByQuery(struct sqlConnection *conn, char *query);
/* Load all gtexTissueData from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with gtexTissueDataFreeList(). */

void gtexTissueDataSaveToDb(struct sqlConnection *conn, struct gtexTissueData *el, char *tableName, int updateSize);
/* Save gtexTissueData as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. This function automatically escapes quoted strings for mysql. */

struct gtexTissueData *gtexTissueDataLoad(char **row);
/* Load a gtexTissueData from row fetched with select * from gtexTissueData
 * from database.  Dispose of this with gtexTissueDataFree(). */

struct gtexTissueData *gtexTissueDataLoadAll(char *fileName);
/* Load all gtexTissueData from whitespace-separated file.
 * Dispose of this with gtexTissueDataFreeList(). */

struct gtexTissueData *gtexTissueDataLoadAllByChar(char *fileName, char chopper);
/* Load all gtexTissueData from chopper separated file.
 * Dispose of this with gtexTissueDataFreeList(). */

#define gtexTissueDataLoadAllByTab(a) gtexTissueDataLoadAllByChar(a, '\t');
/* Load all gtexTissueData from tab separated file.
 * Dispose of this with gtexTissueDataFreeList(). */

struct gtexTissueData *gtexTissueDataCommaIn(char **pS, struct gtexTissueData *ret);
/* Create a gtexTissueData out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new gtexTissueData */

void gtexTissueDataFree(struct gtexTissueData **pEl);
/* Free a single dynamically allocated gtexTissueData such as created
 * with gtexTissueDataLoad(). */

void gtexTissueDataFreeList(struct gtexTissueData **pList);
/* Free a list of dynamically allocated gtexTissueData's */

void gtexTissueDataOutput(struct gtexTissueData *el, FILE *f, char sep, char lastSep);
/* Print out gtexTissueData.  Separate fields with sep. Follow last field with lastSep. */

#define gtexTissueDataTabOut(el,f) gtexTissueDataOutput(el,f,'\t','\n');
/* Print out gtexTissueData as a line in a tab-separated file. */

#define gtexTissueDataCommaOut(el,f) gtexTissueDataOutput(el,f,',',',');
/* Print out gtexTissueData as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* GTEXTISSUEDATA_H */

