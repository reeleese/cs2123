#include "stack.h"
#include <stdio.h>
#include <string.h>

#define TAG_CLOSE 1
#define TAG_OPEN 0;

char *readTag(FILE **infp);
int getType(char *tag);
void checkTag(stackADT openTags, char *tag);
void printTagsRemaining(stackADT openTags);
int endsComment(char *test);
void ClearStack(stackADT stack);

int main(int argc, char *argv[])
{
    /* Incorrect # of arguments */
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
	    if (tag) /* tag is not a comment */
		checkTag(openTags, tag);
	}
    }

    /* Still un-popped tags */
    if (!StackIsEmpty(openTags)) {
	printf("NO, there are unclosed tags.\n");
	printTagsRemaining(openTags);
	ClearStack(openTags);
	return 1;
    }

    /* Tags nested correctly at this point */
    printf("YES, all the tags are nested correctly.\n");
    FreeStack(openTags);
    return 0;
}

/* Calling this prgram immediately after *infp has read a '<' will return
 * the string of all characters up to the next '>'. Ignores comments. */
char *readTag(FILE **infp)
{
    /* Allocate string */
    char *string;
    if((string = (char *) malloc(250)) == NULL) {
	printf("big failure.\n");
	return NULL;
    }

    /* Read all chars into string until '>' */
    fscanf(*infp, "%[^>]", string);

    /* If tag starts a comment, read everything up to end of comment and
       throw away */
    if (strncmp("!--", string, 3) == 0) {
	while(fscanf(*infp, " %s", string) == 1) {
	    if (endsComment(string)) {
		free(string);
		return NULL;
	    }
	}
    }
    
    return string;
}

/* Given a tag,
 * -If it's closing: pops the opening tag, checks for a match, and ends the
 *  the program if the tags do not match.
 * -If it's a single-sided or !DOCTYPE, do nothing.
 * - If it's an opening tag, push it onto stack. */
void checkTag(stackADT openTags, char *tag)
{
    /* Ignore single-sided tags and <!DOCTYPE HTML> */
    int tag_len;
    tag_len = strlen(tag);
    if (tag[0] == '!' || tag[tag_len-1] == '/') {
	free(tag);
	return;
    }

    /* Tag is closing*/
    if (tag[0] == '/') {
	/* Closing tag, but no preceding opening tags */
	if (StackIsEmpty(openTags)) {
	    printf("NO, the tag <%s> has no matching tag to close.\n", tag);
	    free(tag);
	    exit(1);
	}
	/* get opening tag, removing attributes */
	char *pop, *ptr;
	pop = Pop(openTags);
	ptr = strchr(pop, ' ');
	if(ptr) *ptr = '\0';

	/* check opening tag with closer */
	if (strcmp(tag+1, pop) != 0) {
	    printf("NO, the tag <%s> and <%s> violates the proper nesting!\n",
		   pop, tag);
	    printTagsRemaining(openTags);
	    ClearStack(openTags);
	    free(tag);
	    free(pop);
	    exit(1);
	}
	
	/* Closing tag is nested properly */
	free(pop);
	free(tag);
	return;
    }

    /* Tag is opening */
    if (StackIsFull(openTags)) {
	printf("The stack is full! Exiting");
	ClearStack(openTags);
	free(tag);
	exit(1);
    }
    Push(openTags, tag);
}

/* Prints tags still on a stack */
void printTagsRemaining(stackADT openTags)
{
    printf("The tags that are currently in the stack are:\n");
    while(!StackIsEmpty(openTags)) {
	printf("<%s>\n", Pop(openTags));
    }
}

/* Determines if a string ends with "-->" */
int endsComment(char *test)
{
    const char *suffix = "-->";
    if (!test || !suffix)
        return 0;
    int len_test = strlen(test);
    int len_suffix = strlen(suffix);
    if (len_suffix > len_test)
        return 0;
    return strncmp(test + len_test - len_suffix, suffix, len_suffix) == 0;
}

/* Clears stack, freeing any elements remaining */
void ClearStack(stackADT stack)
{
    while(!StackIsEmpty(stack))
	free(Pop(stack));
}
