/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_utils2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 13:57:56 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/09 14:39:36 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

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

t_hist	*first_elem(t_hist *root)
{
	if (root->next != root)
		return (root->next);
	else
		return (NULL);
}

t_hist	*last_elem(t_hist *root)
{
	if (root->prev != root)
		return (root->prev);
	else
		return (NULL);
}

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
