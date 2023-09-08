#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUBPALINDROMES 1000 // Maximum number of subpalindromes

// Function to check if a string is a palindrome
short isPalindrome(const char *str)
{
    short leftPointer = 0;
    short rightPointer = strlen(str) - 1;

    while (leftPointer < rightPointer)
    {
        if (str[leftPointer] != str[rightPointer]) // must be symmetrical
            return 0;
        leftPointer++;
        rightPointer--;
    }
    return 1;
}

// Function to convert characters to lowercase
char *toLowerCase(char *input)
{
    char *lower = (char *)malloc((strlen(input) + 1) * sizeof(char));
    strcpy(lower, input); // copying string for return statement
    for (char *p = lower; *p; ++p)
        *p = *p > 0x40 && *p < 0x5b ? *p | 0x60 : *p;

    return lower;
}

// if one string is contained entirely inside the other or vice versa
short areCrossContained(char first[], char second[])
{
    return strstr(first, second) != NULL || strstr(second, first) != NULL;
}

char *substring(const char string[], int start, int end)
{
    short length = end - start + 1;

    if (start < 0 || end >= (int)strlen(string) || length <= 0 || (length + 1) <= 0)
    {
        return NULL; // Invalid indices, length, or potential overflow
    }

    char *substring = (char *)malloc((length + 1) * sizeof(char));

    if (substring == NULL)
    {
        return NULL; // Memory allocation failed
    }

    for (short i = 0; i < length; i++)
    {
        substring[i] = string[start + i];
    }
    substring[length] = '\0'; // Null-terminate the substring

    return substring;
}

// Responsible for freeing all strings allocated with malloc
void freeStringArray(char **array, short size)
{
    for (short i = 0; i < size; i++)
    {
        free(array[i]); // Free each individual string
    }
}

short is2Palindrome(char *str)
{
    short n = strlen(str);
    if (n <= 3)
        return 0;
    short count = 0;
    // Use fixed-size arrays for subpalindromes
    char *subpalindromes[MAX_SUBPALINDROMES];

    for (short len = n - 1; len >= 3; len--)
    {
        for (short start = 0; start <= n - len; start++)
        {
            short end = start + len;
            char *curr = substring(str, start, end - 1);
            if (isPalindrome(curr))
            {
                subpalindromes[count] = curr;
                count++;
            }
            else
            {
                free(curr);
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (!areCrossContained(subpalindromes[j], subpalindromes[i]) && strcmp(subpalindromes[j], subpalindromes[i]) != 0)
            {
                freeStringArray(subpalindromes, count);
                return 1;
            }
        }
    }
    freeStringArray(subpalindromes, count);
    return 0;
}

int main()
{
    char word[257];                   // 256 + /0
    while (scanf("%256s", word) == 1) // scan words(divided by space)
    {
        char *lower = toLowerCase(word);
        if (is2Palindrome(lower))
            printf("%s\n", word);
        free(lower);
    }

    return 0;
}
