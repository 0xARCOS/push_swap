#include "push_swap.h"
#include <unistd.h>

/* ========== silent operations (no output) ========== */
static void swap_nodes(t_node **stack)
{
    t_node  *first;
    t_node  *second;

    if (!stack || !*stack || !(*stack)->next)
        return;
    first = *stack;
    second = first->next;
    first->next = second->next;
    second->next = first;
    *stack = second;
}

static void push_node(t_node **dst, t_node **src)
{
    t_node  *tmp;

    if (!src || !*src)
        return;
    tmp = *src;
    *src = (*src)->next;
    tmp->next = *dst;
    *dst = tmp;
}

static void rotate_nodes(t_node **stack)
{
    t_node  *first;
    t_node  *last;

    if (!stack || !*stack || !(*stack)->next)
        return;
    first = *stack;
    *stack = first->next;
    last = *stack;
    while (last->next)
        last = last->next;
    last->next = first;
    first->next = NULL;
}

static void reverse_rotate_nodes(t_node **stack)
{
    t_node  *prev;
    t_node  *last;

    if (!stack || !*stack || !(*stack)->next)
        return;
    prev = NULL;
    last = *stack;
    while (last->next)
    {
        prev = last;
        last = last->next;
    }
    prev->next = NULL;
    last->next = *stack;
    *stack = last;
}

static void sa_chk(t_node **a) { if (a && *a && (*a)->next) swap_nodes(a); }
static void sb_chk(t_node **b) { if (b && *b && (*b)->next) swap_nodes(b); }
static void ss_chk(t_node **a, t_node **b)
{
    if (a && *a && (*a)->next)
        swap_nodes(a);
    if (b && *b && (*b)->next)
        swap_nodes(b);
}
static void pa_chk(t_node **a, t_node **b) { if (b && *b) push_node(a, b); }
static void pb_chk(t_node **a, t_node **b) { if (a && *a) push_node(b, a); }
static void ra_chk(t_node **a) { if (a && *a && (*a)->next) rotate_nodes(a); }
static void rb_chk(t_node **b) { if (b && *b && (*b)->next) rotate_nodes(b); }
static void rr_chk(t_node **a, t_node **b)
{
    if (a && *a && (*a)->next)
        rotate_nodes(a);
    if (b && *b && (*b)->next)
        rotate_nodes(b);
}
static void rra_chk(t_node **a) { if (a && *a && (*a)->next) reverse_rotate_nodes(a); }
static void rrb_chk(t_node **b) { if (b && *b && (*b)->next) reverse_rotate_nodes(b); }
static void rrr_chk(t_node **a, t_node **b)
{
    if (a && *a && (*a)->next)
        reverse_rotate_nodes(a);
    if (b && *b && (*b)->next)
        reverse_rotate_nodes(b);
}

/* ========== utils ========== */
static int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;
    while (s1[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int apply_instruction(const char *instr, t_node **a, t_node **b)
{
    if (ft_strcmp(instr, "sa") == 0)
        sa_chk(a);
    else if (ft_strcmp(instr, "sb") == 0)
        sb_chk(b);
    else if (ft_strcmp(instr, "ss") == 0)
        ss_chk(a, b);
    else if (ft_strcmp(instr, "pa") == 0)
        pa_chk(a, b);
    else if (ft_strcmp(instr, "pb") == 0)
        pb_chk(a, b);
    else if (ft_strcmp(instr, "ra") == 0)
        ra_chk(a);
    else if (ft_strcmp(instr, "rb") == 0)
        rb_chk(b);
    else if (ft_strcmp(instr, "rr") == 0)
        rr_chk(a, b);
    else if (ft_strcmp(instr, "rra") == 0)
        rra_chk(a);
    else if (ft_strcmp(instr, "rrb") == 0)
        rrb_chk(b);
    else if (ft_strcmp(instr, "rrr") == 0)
        rrr_chk(a, b);
    else
        return 0;
    return 1;
}

static int read_instruction(char *buf)
{
    char    c;
    int     i = 0;
    ssize_t r;

    while ((r = read(0, &c, 1)) > 0)
    {
        if (c == '\n')
            break;
        if (i >= 3)
            return -1; /* instruction too long */
        buf[i++] = c;
    }
    if (r == 0 && i == 0)
        return 0; /* EOF */
    if (r < 0)
        return -1;
    buf[i] = '\0';
    return 1;
}

int main(int argc, char **argv)
{
    t_node  *a = NULL;
    t_node  *b = NULL;
    char    instr[4];
    int     ret;

    if (argc < 2)
        return 0;
    a = parse_input(argc, argv);
    if (!a)
    {
        write(2, "Error\n", 6);
        return 1;
    }
    while ((ret = read_instruction(instr)) > 0)
    {
        if (!apply_instruction(instr, &a, &b))
        {
            write(2, "Error\n", 6);
            free_stack(&a);
            free_stack(&b);
            return 1;
        }
    }
    if (ret == -1)
    {
        write(2, "Error\n", 6);
        free_stack(&a);
        free_stack(&b);
        return 1;
    }
    if (is_sorted(a) && b == NULL)
        write(1, "OK\n", 3);
    else
        write(1, "KO\n", 3);
    free_stack(&a);
    free_stack(&b);
    return 0;
}

