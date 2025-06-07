#include "push_swap.h"

char    *ft_strdup(const char *s)
{
    char    *dup;
    int     len;
    int     i;

    len = 0;
    while (s[len])
        len++;
    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        return NULL;
    i = 0;
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}
