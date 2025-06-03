#include "push_swap.h"

int ft_atoi_push_swap(const char *str, int *error_flag)
{
    long    result;
    int     sign;
    int     i;

    result = 0;
    sign = 1;
    i = 0;
    *error_flag = 0;

    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }

    while (str[i])
    {
        result = result * 10 + (str[i] - '0');
        if ((sign == 1 && result > INT_MAX) || (sign == -1 && -result < INT_MIN))
        {
            *error_flag = 1;
            return 0;
        }
        i++;
    }
    return ((int)(result *sign));
}
