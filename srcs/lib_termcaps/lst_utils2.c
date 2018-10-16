/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_utils2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 13:57:56 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/04 17:43:31 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Creates the neutral element of the
** linked list, that is its beginning and
** ending, and returns it.
*/

t_hist	*root_hist(void)
{
	t_hist	*lst;

	lst = NULL;
	if (!(lst = malloc(sizeof(*lst))))
		return (NULL);
	lst->name = NULL;
	lst->backup = NULL;
	lst->current = 0;
	lst->next = lst;
	lst->prev = lst;
	return (lst);
}

/*
** Returns the first element of the linked list.
*/

t_hist	*first_elem(t_hist *root)
{
	if (root->next != root)
		return (root->next);
	else
		return (NULL);
}

/*
** Returns the last element of the linked list.
*/

t_hist	*last_elem(t_hist *root)
{
	if (root->prev != root)
		return (root->prev);
	else
		return (NULL);
}

/*
** Reinits which element is the current one.
*/

void	init_current(t_hist *history)
{
	t_hist	*tmp;

	tmp = first_elem(history);
	while (tmp->next != history)
	{
		tmp->current = 0;
		tmp = tmp->next;
	}
	tmp->current = 1;
}

/*
** Frees the history linked list.
*/

void	free_hist(t_hist *lst)
{
	t_hist	*tmp;
	t_hist	*tmp2;

	tmp = lst->next;
	if (lst)
	{
		while (tmp != lst)
		{
			tmp2 = tmp->next;
			remove_elem(tmp);
			ft_memdel((void**)&tmp);
			tmp = tmp2;
		}
	}
	ft_memdel((void**)&lst);
}
