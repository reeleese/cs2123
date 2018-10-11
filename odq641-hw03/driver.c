#include "stack.h"
#include <stdio.h>
#include <string.h>

#define TAG_CLOSE 1
#define TAG_OPEN 0;

typedef struct TagS {
    char *type;
    int opening;
} Tag;

char *readTag(FILE **infp);
int getType(char *tag);
int tagsMatch(char *open, char *close);

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

    stackADT openTags, closeTags;
    openTags = NewStack();
    closeTags = NewStack();

    /* Populate openTags and closeTags from infp */
    char x; char *tag;
    while((fscanf(infp, "%c", &x) == 1)) {
	if (x == '<') {
	    tag = readTag(&infp);
	    printf("%s\n", tag);
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

    /* Read all chars into string until '>' */
    fscanf(*infp, "%[^>]s", string);
    return string;
}
