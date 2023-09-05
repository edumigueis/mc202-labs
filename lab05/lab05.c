#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strLen(char str[])
{
    int count;
    for (count = 0; str[count] != '\0'; ++count)
        ;
    return count;
}

char *toUpperCase(const char *input)
{
    if (input == NULL)
    {
        return NULL; // Return NULL if the input string is NULL.
    }

    size_t length = strlen(input);
    char *result = (char *)malloc(length + 1); // +1 for the null terminator

    if (result == NULL)
    {
        return NULL; // Return NULL if memory allocation fails.
    }

    for (size_t i = 0; i < length; i++)
    {
        if (input[i] >= 'a' && input[i] <= 'z')
        {
            // If the character is a lowercase letter, convert it to uppercase.
            result[i] = input[i] - 'a' + 'A';
        }
        else
        {
            // Otherwise, keep the character unchanged.
            result[i] = input[i];
        }
    }

    result[length] = '\0'; // Null-terminate the new string.

    return result;
}

char *substring(char string[], int start, int end)
{
    int length = end - start + 1;

    if (start < 0 || end >= strLen(string) || length <= 0)
    {
        return NULL; // Invalid indices or length
    }

    char *substring = (char *)malloc((length + 1) * sizeof(char));

    if (substring == NULL)
    {
        return NULL; // Memory allocation failed
    }

    for (int i = 0; i < length; i++)
    {
        substring[i] = string[start + i];
    }
    substring[length] = '\0'; // Null-terminate the substring

    return substring;
}

short isPalindromic(char *s, int i, int j)
{
    if (i >= j)
        return 1;

    if (s[i] != s[j])
        return 0;

    return isPalindromic(s, i + 1, j - 1);
}

short isDistinct(char *stringArray[], int arraySize, const char *newString)
{
    for (int i = 0; i < arraySize; i++)
    {
        if (strcmp(stringArray[i], newString) == 0 || strstr(stringArray[i], newString) != NULL)
        {
            return 0;
        }
    }
    return 1;
}

/*for (int i = 0; i < n; i++)
    {
        for (int j = i + 2; j < n; j++)
        {
            if (isPalindromic(str, i, j) && isDistinct(palindromes, count, substring(str, i, j)))
            {
                count++;
                if (count >= 2)
                {
                    return 1; // At least two distinct non-contained palindromic substrings found
                }
            }
        }
    }*/

short is2Palindrome(char *str)
{
    int n = strLen(str);

    if (n < 3)
        return 0;
    char *palindromes[250];
    int count = 0;

    for (int len = n; len >= 3; len--) {
        for (int start = 0; start <= n - len; start++) {
            int end = start + len;
            char* curr = substring(str, start, end - 1);
            if (isPalindromic(str, start, end - 1) && isDistinct(palindromes, count, curr))
            {
                palindromes[count] = curr;
                count++;
                if (count >= 2)
                {
                    return 1; // At least two distinct non-contained palindromic substrings found
                }
            }
        }
    }

    return 0;
}

int main(void)
{
    char word[] = "";
    while (scanf("%s", word) == 1)
        if (is2Palindrome(toUpperCase(word)) != 0)
            printf("%s", word);
    printf("\n");
    return 0;
}