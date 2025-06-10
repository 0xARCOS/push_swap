#include "push_swap.h"

static int has_duplicates(t_node *stack)
{
    t_node  *current;
    t_node  *runner;

    current = stack;
    while (current)
    {
        runner = current->next;
        while (runner)
        {
            if (current->value == runner->value)
                return 1;
            runner = runner->next;
        }
        current = current->next;
    }
    return 0;
}

char    **split_args(int argc, char **argv)
{
    char    **tokens;
    char    **split;
    int     total;
    int     i;
    int     j;
    int     k;

    total = count_all_tokens(argc, argv);
    tokens = malloc(sizeof(char *) * (total + 1));
    if (!tokens)
        return (NULL);
    i = 1;
    k = 0;
    while (i < argc)
    {
        split = ft_split(argv[i], ' ');
        if (!split)
        {
            free_tokens(tokens, k);
            return (NULL);
        }
        j = 0;
        while (split[j])
        {
            tokens[k] = ft_strdup(split[j]);
            if (!tokens[k])
            {
                free_split(split);
                free_tokens(tokens, k);
                return (NULL);
            }
            k++;
            j++;
        }
        free_split(split);
        i++;
    }
    tokens[k] = NULL;
    return (tokens);
}

t_node *parse_input(int argc, char **argv)
{
    char    **tokens;
    int     i;
    t_node  *stack;

    tokens = split_args(argc, argv);
    i = 0;
    stack = NULL;
    if (!tokens)
        return NULL;
    while (tokens[i])
    {
        if (!is_valid_number(tokens[i]) || !add_node(&stack, tokens[i]))
        {
            free_split(tokens);
            free_stack(&stack);
            return NULL;
        }
        i++;
    }
    free_split(tokens);
    if (has_duplicates(stack))
    {
        free_stack(&stack);
        return NULL;
    }
    return stack;
}
