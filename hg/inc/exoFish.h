/* exoFish.h was originally generated by the autoSql program, which also 
 * generated exoFish.c and exoFish.sql.  This header links the database and the RAM 
 * representation of objects. */

#ifndef EXOFISH_H
#define EXOFISH_H

struct exoFish
/* An evolutionarily conserved region (ecore) with Tetroadon */
    {
    struct exoFish *next;  /* Next in singly linked list. */
    char *chrom;	/* Human chromosome or FPC contig */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Just a dummy dot */
    unsigned score;	/* Score from 0 to 1000 */
    };

void exoFishStaticLoad(char **row, struct exoFish *ret);
/* Load a row from exoFish table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct exoFish *exoFishLoad(char **row);
/* Load a exoFish from row fetched with select * from exoFish
 * from database.  Dispose of this with exoFishFree(). */

struct exoFish *exoFishCommaIn(char **pS, struct exoFish *ret);
/* Create a exoFish out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new exoFish */

void exoFishFree(struct exoFish **pEl);
/* Free a single dynamically allocated exoFish such as created
 * with exoFishLoad(). */

void exoFishFreeList(struct exoFish **pList);
/* Free a list of dynamically allocated exoFish's */

void exoFishOutput(struct exoFish *el, FILE *f, char sep, char lastSep);
/* Print out exoFish.  Separate fields with sep. Follow last field with lastSep. */

#define exoFishTabOut(el,f) exoFishOutput(el,f,'\t','\n');
/* Print out exoFish as a line in a tab-separated file. */

#define exoFishCommaOut(el,f) exoFishOutput(el,f,',',',');
/* Print out exoFish as a comma separated list including final comma. */

#endif /* EXOFISH_H */
