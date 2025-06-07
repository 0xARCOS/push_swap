#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>

/* ===================== STRUCTS ===================== */
typedef struct s_node
{
    int             value;
    int             index;
    int             temp;
    struct s_node   *next;
} t_node;

/* ===================== PARSING ===================== */
t_node  *parse_input(int argc, char **argv);
char    **split_args(int argc, char **argv);
int     count_all_tokens(int argc, char **argv);
int     has_duplicates(t_node *stack);
char    **ft_split(const char *s, char c);
char    *ft_strdup(const char *s);
void    free_split(char **tokens);
int     ft_atoi_push_swap(const char *str, int *error_flag);
void    free_tokens(char **tokens, int count);
void    free_stack(t_node **stack);

/* ==================== MOVIMIENTOS ================== */
void sa(t_node **a); // swap a
void sb(t_node **b); // swap b
void ss(t_node **a, t_node **b); // swap a y b

void pa(t_node **a, t_node **b); // push a (b → a)
void pb(t_node **a, t_node **b); // push b (a → b)

void ra(t_node **a); // rotate a
void rb(t_node **b); // rotate b
void rr (t_node **a, t_node **b); //rotate a y b

void rra(t_node **a); // reverse rotate a
void rrb(t_node **b); // reverse rotate b
void rrr(t_node **a, t_node **b); // reverse rotate a y b

/* ==================== ALGORITMO ==================== */
int     is_sorted(t_node *stack);
void    sort_stack(t_node **a, t_node **b);

#endif
