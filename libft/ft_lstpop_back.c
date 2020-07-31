#include <libft.h>

t_list	*ft_lstpop_back(t_list **alst)
{
	size_t	size;
	t_list	*tail;
	t_list	*tmp;

	if (*alst == NULL)
		return (NULL);
	if ((*alst)->next == NULL)
	{
		tail = *alst;
		*alst = NULL;
		free(tail);
		return (tail);
	}
	size = ft_lstsize(*alst);
	tail = ft_lstat(*alst, size - 1);
	tmp = ft_lstat(*alst, size - 2);
	tmp->next = NULL;
	free(tail);
	return (tail);
}
