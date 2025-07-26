#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list *new_node;
    t_list *new_lst;

    if (!lst || !f || !del)
        return (NULL);
    new_lst = NULL;
    while (lst != NULL)
    {
        new_node = ft_lstnew(f(lst->content));
        if (!new_node)
        {
            ft_lstdelone(new_node, del);
            return (NULL);
        }
        ft_lstadd_back(&new_lst, new_node);
        lst = lst->next;
    }
    return (new_lst);
}