/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *tracks[] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};

/* Returns a heap-allocated string that contains the strings 
   from the given array, joined up with no spaces between.
*/
char *strjoin(char *array[], int n)
{
    int size = 0;
    for (int i = 0; i < n; ++i)
        size += strlen(array[i]);

    char* ret = malloc ((size + 1) * sizeof(char));

    int str_pos = 0;
    for (int i = 0; i < n; ++i) {
        strcpy(&ret[str_pos], array[i]);
        str_pos += strlen(array[i]);
    }

    return ret;
}


int main (int argc, char *argv[])
{
    char *s = strjoin(tracks, 5);
    printf("%s\n", s);
    return 0;
}
