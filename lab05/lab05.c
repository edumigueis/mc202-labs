#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if a string is a palindrome
short isPalindrome(const char *str)
{
    int len = strlen(str);
    if (len < 3)
    {
        return 0; // Palindromes must be at least 3 characters long
    }
    for (int i = 0; i < len / 2; i++)
    {
        if (str[i] != str[len - i - 1])
        {
            return 0;
        }
    }
    return 1;
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

short isContained(char container[], char candidate[])
{
    char *result = strstr(container, candidate);

    if (result != NULL)
    {
        // Check if str2 is in the middle of str1
        if (result > container && result + strlen(candidate) < container + strlen(container))
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

char *substring(const char string[], int start, int end)
{
    int length = end - start + 1;

    if (start < 0 || end >= (int)strlen(string) || length <= 0)
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

char **getAllSubpalindromes(const char *str)
{
    int n = strlen(str);
    int count = 0;
    char **subpalindromes = malloc(sizeof(char *) * n * n);
    char **uniquePalindromes = malloc(sizeof(char *) * n * n);

    for (int len = n; len >= 3; len--)
    {
        for (int start = 0; start <= n - len; start++)
        {
            int end = start + len;
            char *curr = substring(str, start, end - 1);
            if (isPalindrome(curr))
            {
                int isDuplicate = 0;

                // Check for duplicates
                for (int i = 0; i < count; i++)
                {
                    if (strcmp(curr, uniquePalindromes[i]) == 0)
                    {
                        isDuplicate = 1;
                        break;
                    }
                }

                if (!isDuplicate)
                {
                    uniquePalindromes[count] = curr;
                    count++;
                }
                else
                {
                    free(curr); // Free memory for duplicates
                }
            }
            else
            {
                free(curr); // Free memory for non-palindromic substrings
            }
        }
    }

    char **res = malloc(sizeof(char *) * (count + 1)); // Allocate memory for the result
    for (int i = 0; i < count; i++)
    {
        res[i] = uniquePalindromes[i];
    }
    res[count] = NULL; // Null-terminate the array

    // Free memory
    free(subpalindromes);
    free(uniquePalindromes);

    return res;
}

short is2Palindrome(char *subpalindromes[])
{
    short count = 0;
    short n = 0;
    while (subpalindromes[n] != NULL)
    {
        //printf("%s|", subpalindromes[n]);
        n++;
    }
    short isDistinct = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isContained(subpalindromes[j], subpalindromes[i]))
                isDistinct = 0;
        }
        if (isDistinct)
            count++;
        if (count >= 2)
            return 1;
        isDistinct = 1;
    }
    return 0;
}

int main()
{
    char word[256];
    while (scanf("%s", word) == 1)
        if (is2Palindrome(getAllSubpalindromes(toUpperCase(word))))
            printf("%s\n", word);
    printf("\n");

    return 0;
}
