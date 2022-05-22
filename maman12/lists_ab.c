#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define INCREASE_SIZE 100
#define MAX_CHAR_IN_ROW 50

void storageFailure();
char *getCharsInput(char *charArr, int *arrSize, int *totalChars, int *alphaChars);
void printAllChars(char *charArr, int charsCount, int charsInRow);
void printListInfo(int totalChars, int alphaChars);

int main()
{
    int listSize = INCREASE_SIZE;
    int totalChars = 0, alphaChars = 0;

    char *charsList = (char *)malloc(INCREASE_SIZE * sizeof(char));
    if (charsList == NULL)
        storageFailure();

    charsList = getCharsInput(charsList, &listSize, &totalChars, &alphaChars);

    printAllChars(charsList, totalChars, MAX_CHAR_IN_ROW);
    printListInfo(totalChars, alphaChars);

    free(charsList);

    return 0;
}

void storageFailure()
{
    printf("ERROR - not enough free storage");
    exit(1);
}

char *getCharsInput(char *charArr, int *arrSize, int *totalChars, int *alphaChars)
{
    char c;

    printf("Please enter a list of chars:\n");

    while ((c = getchar()) != EOF)
    {
        if (*totalChars == *arrSize)
        {
            *arrSize += INCREASE_SIZE;
            charArr = (char *)realloc(charArr, *arrSize * sizeof(char));
            if (charArr == NULL)
                storageFailure();
        }

        if (isalnum(c))
            (*alphaChars)++;

        *(charArr + (*totalChars)++) = c;
    }
    printf("\n");
    return charArr;
}

void printAllChars(char *charArr, int charsCount, int charsInRow)
{
    int i, curCharInRow;

    for (i = 0, curCharInRow = 0; i < charsCount; i++, curCharInRow++)
    {
        if (curCharInRow == charsInRow)
        {
            curCharInRow = 0;
            printf("\n");
        }
        printf("%c", *(charArr + i));
    }
}

void printListInfo(int totalChars, int alphaChars)
{
    printf("\nNumber of alphanumeric characters: %d\n", alphaChars);
    printf("Total number of characters: %d\n", totalChars);
}
