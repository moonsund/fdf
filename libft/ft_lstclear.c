#include "libft.h"

void ft_lstclear(t_list **lst, void (*del)(void*))
{
    t_list *current;

    current = *lst;
    while (*lst != NULL)
    {
        current = (*lst)->next;
        del((*lst)->content);
        free(*lst);
        *lst = current;
    }
}