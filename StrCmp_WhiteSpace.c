#include <stdio.h>
#include <ctype.h>

/** string compare ignoring whitespace.
 *  if both strings are NULL, they are equal (same as strcmp).
 *  scans both strings to determine if non-whitespace characters are
 *  present. sets flag 'anws = 1' if 'a' contains non-whitespace,
 *  and 'bnws = 1' if 'b' contains non-whitespace chars. a character
 *  by character comparison is then performed skipping whitespace. if
 *  both contain non-whitespace, returns result of *a - *b, otherwise
 *  if neither contain non-whitespace, zero (equal) is returned. if
 *  'a' contains non-whitespace and 'b' has none, returns 1 (a > b), or
 *  if 'b' contains non-whitespace and 'a' has none, returns -1 (b > a).
 */
 
int strcmp_nows (char *a, char *b)
{
    int anws = 0, bnws = 0;   /* flags for a, b contains non-whitespace */

    if (!a && !b) return 0;             /* if both NULL - equal */

    /* scan both strings and set anws, bnws flags */
    for (char *pa = a; *pa; pa++)           /* check each char in a */
        if (' ' < *pa && *pa <= '~') {      /* check/set anws flag */
            anws = 1;
            break;
        }
    for (char *pb = b; *pb; pb++)           /* check each char in b */
        if (' ' < *pb && *pb <= '~') {      /* check/set bnws flag */
            bnws = 1;
            break;
        }

    while (*a && *b)        /* compare characters in each skipping ws */
        if (isspace (*a))       /* if *a points to whitespace -- skip */
            a++;
        else if (isspace (*b))  /* if *b points to whitespace -- skip */
            b++;
        else if (*a == *b)      /* if equal, advance both pointers */
            a++, b++;
        else                    /* if differ, strings differ, bail */
            break;

    if (anws && bnws)               /* if both contain non-whitespace */
        return *a - *b;             /* return comparison */
    else {
        if (!anws && !bnws)         /* if neither contian non-whitespace */
            return 0;               /*   equal */
        else if (anws)              /* if only a contians non-whitespace */
            return 1;               /*   a > b */
        else                        /* if only b contains non-whitespace */
            return -1;              /*   b > a */
    }
}

int main (int argc, char **argv) {
    char *a = argc > 1 ? argv[1] : "test",
         *b = argc > 2 ? argv[2] : " test";

    if (strcmp_nows (a, b) == 0)
        printf ("a: %s\nb: %s  (have equal non-whitespace chars)\n", a, b);
    else
        printf ("a: %s\nb: %s  (differ in non-whitespace chars)\n", a, b);    

    return 0;
}
