#include "stack.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
	printf("Invalid input. Please enter the name of the HTML file to evaluate>\n");
	return 1;
    }

    /* File can either be .html or .htm */
    char *fileExt = strrchr(argv[1], '.'); printf("%s\n", fileExt);
    if (!fileExt || (strcmp(fileExt, ".html") && strcmp(fileExt, ".htm"))) {
	printf("File must have a .html extension.\n");
	return 1;
    }
    
    return 0;
}
