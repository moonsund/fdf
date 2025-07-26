#include "libft.h"

void ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *last_node;
    
    if (!lst || !new)
        return;
    if (*lst == NULL)
    {
        *lst = new;
        return;
    }
    last_node = *lst;
    while (last_node->next != NULL)
        last_node = last_node->next;
    last_node->next = new;
}