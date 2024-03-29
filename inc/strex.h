/* strex.h - interface to string expression language,  currently used in tabToTabDir
 * to describe how the output fields are filled in from input fields. */

#ifndef STREX_H
#define STREX_H

/* Parsing out something into strex */
struct strexParse;    /* A parser generated tree */

struct strexParse *strexParseString(char *s, char *fileName, int fileLineNumber);
/* Parse out string expression in s and return root of tree. The fileName and 
 * fileLineNumber are just used in the error message.  Ideally they should help 
 * the user navigate to where the problem was. */

void strexParseDump(struct strexParse *p, int depth, FILE *f);
/* Dump out strexParse tree and children for debugging.  Usual depth is 0. */



/* Evaluating a parsed out strex expression */

typedef char* (*StrexEvalLookup)(void *symbols, char *key);
/* Callback to lookup value of key in a symbol table. */

char *strexEvalAsString(struct strexParse *p, void *symbols, StrexEvalLookup lookup);
/* Evaluating a strex expression on a symbol table with a lookup function for variables and
 * return result as a string value. */

#endif /* STREX_H */

