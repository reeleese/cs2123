#include "stack.h"
#include <stdio.h>
#include <string.h>

#define TAG_CLOSING 1
#define TAG_OPENING -1

char *readTag(FILE **infp);
int getType(char *tag);

int main(int argc, char *argv[])
{
    if (argc != 2) {
	printf("Invalid input. Please enter the name of the HTML file to evaluate>\n");
	return 1;
    }

    /* File can either be .html or .htm */
    char *fileExt = strrchr(argv[1], '.');
    if (!fileExt || (strcmp(fileExt, ".html") && strcmp(fileExt, ".htm"))) {
	printf("File must have a .html extension.\n");
	return 1;
    }

    /* Open file */
    FILE *infp;
    if ((infp = fopen(argv[1], "r")) == NULL) {
	printf("File could not be opened.\n");
	return -1;
    }

    char x; char *string;
    while(fscanf(infp, "%c", &x) == 1) {
	if (x == '<') {
	    string = readTag(&infp);
	    printf("%2ld: %s\n", ftell(infp), string);
	}
	
    }
    
    return 0;
}

char *readTag(FILE **infp)
{
    /* Allocate string */
    char *string;
    if((string = (char *) malloc(250)) == NULL) {
	printf("big failure.\n");
	return NULL;
    }

    /* Read all characters into string from infp until '>'*/
    char c; char *str = string;
    while(fscanf(*infp, "%c", &c) == 1) {
	if (c == '>') {
	    *str = '\0';
	    break;
	}
	*str = c;
	++str;
    }
    return string;
}

int getType(char *tag)
{
    /* if tag is single-sided or comment, return -1 */
    int tag_len = strlen(tag);
    if (tag[0] == '!' || tag[tag_len-1] == '/')
	return 0;
    if (tag[0] == '/')
	return 1;
    return -1;
}


