#include "utils.h"

int	lst_add_back(t_list **lst, char *line)
{
	t_list	*tail;
	t_list	*new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (-1);
	new->content = line;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	tail = *lst;
	while (tail->next)
		tail = tail->next;
	tail->next = new;
	return (1);
}
