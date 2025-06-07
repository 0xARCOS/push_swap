#include "push_swap.h"

static int word_count(const char *s, char c)
{
    int     count;
    int     in_word;
    count = 0;
    in_word = 0;

    while (*s)
    {
        if (*s != c && in_word == 0)
        {
            in_word = 1;
            count++;
        }
        else if (*s == c)
            in_word = 0;
        s++;
    }
    return count;
}

static char *word_dup(const char *start, int len)
{
    char    *word;
    int     i;
    i = 0;

    word = malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    while (i < len)
    {
        word[i] = start[i];
        i++;
    }
    word[i] = '\0';
    return (word);
}

static void free_all(char **result, int i)
{
    while (i--)
        free(result[i]);
    free(result);
}


char    **ft_split(const char *s, char c)
{
    char    **result;
    int     i = 0;
    int     start = -1;
    int     k = 0;
    int     len;

    if (!s)
        return NULL;
    result = malloc(sizeof(char *) * (word_count(s, c) + 1));
    if (!result)
        return (NULL);
    while (s[i])
    {
        if (s[i] != c && start < 0)
            start = i;
        else if (s[i] == c && start >= 0)
        {
            len = i - start;
            result[k] = word_dup(s + start, len);
            if (!result[k])
            {
                free_all(result, k);
                return NULL;
            }
            k++;
            start = -1;
        }
        i++;
    }
    if (start >= 0)
    {
        len = i - start;
        result[k] = word_dup(s + start, len);
        if (!result[k])
        {
            free_all(result, k);
            return NULL;
        }
        k++;
    }
    result[k] = NULL;
    return result;
}

