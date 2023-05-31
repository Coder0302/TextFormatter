#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

int check_brackets(char *text, char open_bracket, char close_bracket)
{
    int len_text = strlen(text);
    Stack bracket_stack = Stack_default;
    for (int i = 0; i < len_text; i++)
    {
        if (text[i] == open_bracket)
        {
            push(&bracket_stack, open_bracket);
        }
        else if (text[i] == close_bracket)
        {
            if (pop(&bracket_stack) == -1)
            {
                return 0;
            }
        }
    }
    if (bracket_stack.countInStack != 0)
    {
        return 0;
    }
    return 1;
}

void strcut(char s[], int c)
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}

int checkToOneWord(char *text, char *word)
{
    return isalpha(*(strstr(text, word) - 1)) != 1 && isalpha(*(strstr(text, word) + strlen(word))) != 1;
}

void cutFromAndTo(char *text, int from, int to)
{
    // char result[strlen(*text) + 1];
    int index = 0;
    for (int i = 0; i <= strlen(text); i++)
    {
        if (!(i >= from && i < to))
        {
            text[index++] = text[i];
        }
    }
    // strcpy(*text, result);
}

char *formatFigureBrackets(char *text)
{
    int len_text = strlen(text);
    char *result = (char *)malloc(sizeof(char) * len_text * 3);
    strcpy(result, text);
    // strcut(text, '\t');
    char *find = (char *)malloc(sizeof(char) * len_text * 3);
    for (int i = 0; i < strlen(result); i++)
    {
        if (result[i] == '{')
        {
            // Вырезаем все пустые поля около скобочки
            int indexOperator = i - 1;
            while (isspace(result[indexOperator--]))
                ;
            cutFromAndTo(result, indexOperator + 2, i);
            while (result[i] != '{')
                i--;

            // Проверяем есть ли перед нами операторы
            indexOperator = i;
            strcpy(find, result);
            find[indexOperator] = 0;
            while (find[indexOperator] != '\n')
                indexOperator--;
            if (strstr(&find[indexOperator], "for") != NULL || strstr(&find[indexOperator], "if") != NULL || strstr(&find[indexOperator], "while") != NULL)
            {
            }
            else
            {
                strcpy(find, result);
                result[i] = '\n';
                result[i + 1] = 0;
                strcat(result, &find[i]);
                i++;
            }
            if (result[i + 1] != '\n')
            {
                strcpy(find, result);
                result[i + 1] = '\n';
                result[i + 2] = 0;
                strcat(result, &find[i + 1]);
            }
        }
    }
    // Убераем всё что может быть в начале новой строки
    for (int i = 0; i < strlen(result); i++)
    {
        if (result[i] == '\n')
        {
            int indexSpace = i;
            while (isspace(result[indexSpace]))
                indexSpace++;
            cutFromAndTo(result, i + 1, indexSpace);
        }
    }
    // Расставляем табы
    int countBrackets = 0;
    for (int i = 0; i < strlen(result); i++)
    {
        if (result[i] == '{')
            countBrackets++;
        else if (result[i + 1] == '}')
            countBrackets--;
        if (result[i] == '\n')
        {
            for (int j = 0; j < countBrackets; j++)
            {
                strcpy(find, result);
                result[i + 1] = '\t';
                result[i + 2] = 0;
                strcat(result, &find[i + 1]);
                i += 1;
            }
        }
    }
    free(find);
    char *res = (char *)malloc(sizeof(char) * strlen(result) + 2);
    strcpy(res, result);
    return res;
}