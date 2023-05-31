#include "cformat.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argv, char **argc)
{
    FILE *file = fopen("input.txt", "r");
    char fileText[65563] = "";
    char line[65563];
    while (fgets(line, 65563, file))
    {
        strcat(fileText, line);
        // strcat(fileText, "\n");
    }
    if (check_brackets(fileText, '{', '}') != 1)
        printf("Parentheses {} placed incorrectly\n");
    if (check_brackets(fileText, '(', ')') != 1)
        printf("Parentheses () placed incorrectly\n");
    if (check_brackets(fileText, '[', ']') != 1)
        printf("Parentheses [] placed incorrectly\n");
    fclose(file);

    char *result = formatFigureBrackets(fileText);

    FILE *file_res = fopen("output.txt", "w");
    fputs(result, file_res);
    printf("Complete\n");
    fclose(file_res);
}