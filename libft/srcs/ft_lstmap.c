/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/03 11:39:02 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/03 11:43:51 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*first_link;
	t_list	*result;
	t_list	*elem;

	if (lst == NULL || f == NULL)
		return (NULL);
	elem = f(lst);
	result = ft_lstnew(elem->content, elem->content_size);
	if (result == NULL)
		return (NULL);
	lst = lst->next;
	first_link = result;
	while (lst != NULL)
	{
		elem = f(lst);
		result->next = ft_lstnew(elem->content, elem->content_size);
		if (result->next == NULL)
			return (NULL);
		result = result->next;
		lst = lst->next;
	}
	return (first_link);
}
