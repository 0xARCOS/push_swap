#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>

/* Minimal implementation of split_args for testing */
char **split_args(int argc, char **argv)
{
    int count = count_all_tokens(argc, argv);
    char **tokens = malloc(sizeof(char *) * (count + 1));
    if (!tokens)
        return NULL;
    int idx = 0;
    for (int i = 1; i < argc; i++)
    {
        char **split = ft_split(argv[i], ' ');
        if (!split)
        {
            free_tokens(tokens, idx);
            return NULL;
        }
        for (int j = 0; split[j]; j++)
            tokens[idx++] = ft_strdup(split[j]);
        free_split(split);
    }
    tokens[idx] = NULL;
    return tokens;
}

int main(int argc, char **argv)
{
    t_node *stack = parse_input(argc, argv);
    if (!stack)
    {
        printf("ERROR\n");
        return 1;
    }
    printf("OK\n");
    free_stack(&stack);
    return 0;
}
