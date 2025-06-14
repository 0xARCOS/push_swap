/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2024/06/06 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>

typedef struct s_node
{
	int		value;
	int		index;
	struct s_node		*next;
} t_node;

t_node  *parse_input(int argc, char **argv);
char    **split_args(int argc, char **argv);
int     count_all_tokens(int argc, char **argv);
int is_valid_number(const char *str);
int add_node(t_node **stack, const char *str);
char    **ft_split(const char *s, char c);
char    *ft_strdup(const char *s);
void    free_split(char **tokens);
int     ft_atoi_push_swap(const char *str, int *error_flag);
void    free_tokens(char **tokens, int count);
void    free_stack(t_node **stack);

void    sa(t_node **a); /* swap a */
void    sb(t_node **b); /* swap b */
void    ss(t_node **a, t_node **b); /* swap a and b */

void    pa(t_node **a, t_node **b); /* push b to a */
void    pb(t_node **a, t_node **b); /* push a to b */

void    ra(t_node **a); /* rotate a */
void    rb(t_node **b); /* rotate b */
void    rr(t_node **a, t_node **b); /* rotate a and b */

void    rra(t_node **a); /* reverse rotate a */
void    rrb(t_node **b); /* reverse rotate b */
void    rrr(t_node **a, t_node **b); /* reverse rotate a and b */

void    swap_nodes(t_node **stack);
void    push_node(t_node **dst, t_node **src);
void    rotate_nodes(t_node **stack);
void    reverse_rotate_nodes(t_node **stack);

int     stack_size(t_node *stack);
void    assign_indexes(t_node *stack);
void    sort_three(t_node **a);
void    sort_five(t_node **a, t_node **b);
void    chunk_sort(t_node **a, t_node **b, int chunks);

int     is_sorted(t_node *stack);
void    sort_stack(t_node **a, t_node **b);

#endif
