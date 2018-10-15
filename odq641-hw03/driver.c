#include "stack.h"
#include <stdio.h>
#include <string.h>

#define TAG_CLOSE 1
#define TAG_OPEN 0;

char *readTag(FILE **infp);
int getType(char *tag);
void checkTag(stackADT openTags, char *tag);
void printTagsRemaining(stackADT openTags);

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

    stackADT openTags;
    openTags = NewStack();

    /* Populate openTags and closeTags from infp */
    char x; char *tag;
    while((fscanf(infp, "%c", &x) == 1)) {
	if (x == '<') {
	    tag = readTag(&infp);
	    printf("%s\n", tag);
	    checkTag(openTags, tag);
	}
    }

    if (!StackIsEmpty(openTags)) {
	printf("NO, there are unclosed tags.\n");
	printTagsRemaining(openTags);
	return 1;
    }
    printf("YES, all the tags are nested correctly.\n");
    
    return 0;
}

char *readTag(FILE **infp)
{
    /* Allocate string */
    char *string;
    if((string = (char *) calloc(250, sizeof(char))) == NULL) {
	printf("big failure.\n");
	return NULL;
    }

    /* Read all chars into string until '>' */
    int i=0; char x;
    while (fscanf(*infp, "%c", &x) == 1) {
	
    }
    return string;
}

void checkTag(stackADT openTags, char *tag)
{
    /* Ignore single-sided tags and comments */
    int tag_len;
    tag_len = strlen(tag);
    if (tag[0] == '!' || tag[tag_len-1] == '/')
	return;

    /* Tag is closing*/
    if (tag[0] == '/') {
	/* Closing tag, but no preceding opening tags */
	if (StackIsEmpty(openTags)) {
	    printf("NO, the tag <%s> has no matching tag to close.\n", tag);
	    exit(1);
	}
	/* get opening tag, removing attributes */
	char *tmp, *ptr;
	tmp = Pop(openTags);
	ptr = strchr(tmp, ' ');
	if(ptr) *ptr = '\0';

	/* check opening tag with closer */
	if (strcmp(tag+1, tmp) != 0) {
	    printf("NO, the tag <%s> and <%s> violates the proper nesting!\n",
		   tag, tmp);
	    printTagsRemaining(openTags);
	    exit(1);
	}
	/* Closing tag is nested properly */
	printf("<%s> pops <%s>\n", tag, tmp);
	free(tmp);
	return;
    }

    /* Tag is opening */
    if (StackIsFull(openTags)) {
	printf("The stack is full! Exiting");
	exit(1);
    }
    Push(openTags, tag);
}

void printTagsRemaining(stackADT openTags)
{
    printf("The tags that are currently in the stack are:\n");
    while(!StackIsEmpty(openTags)) {
	printf("<%s>\n", Pop(openTags));
    }
}
