#include "libft.h"

void	ft_dellast(t_oken **lst, void (*del)(void *))
{
	t_oken	*current;
	t_oken	*prev;

	if (lst && *lst && del)
	{
		if (!(*lst)->next)
		{
			ft_lstdelone(*lst, del);
			*lst = NULL;
			return ;
		}
		current = *lst;
		prev = NULL;
		while (current->next)
		{
			prev = current;
			current = current->next;
		}
		prev->next = NULL;
		ft_lstdelone(current, del);
	}
}
