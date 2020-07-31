#include <libft.h>

/*
** null not included
*/

size_t	ft_lstsize(t_list *lst)
{
	size_t	i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	if (lst == NULL)
		return (0);
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
