#include <libft.h>

t_list	*ft_lstpop_front(t_list **alst)
{
	t_list *head;

	head = *alst;
	(*alst) = (*alst)->next;
	free(head);
	return (head);
}
