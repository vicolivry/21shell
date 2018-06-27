/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/27 10:25:07 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 16:11:15 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	add_queue(t_hist *elem)
{
	t_hist	*new_elem;

	new_elem = NULL;
	if ((new_elem = (t_hist*)malloc(sizeof(*new_elem))))
	{
		new_elem->name = NULL;
		new_elem->current = 0;
		new_elem->prev = elem;
		new_elem->next = elem->next;
		elem->next->prev = new_elem;
		elem->next = new_elem;
	}
}

void	add_head(t_hist *elem)
{
	t_hist	*new_elem;

	new_elem = NULL;
	if ((new_elem = (t_hist*)malloc(sizeof(*new_elem))))
	{
		new_elem->name = NULL;
		new_elem->current = 0;
		new_elem->prev = elem->prev;
		new_elem->next = elem;
		elem->prev->next = new_elem;
		elem->prev = new_elem;
	}
}

void	remove_elem(t_hist *elem)
{
	elem->prev->next = elem->next;
	elem->next->prev = elem->prev;
	ft_strdel(&elem->name);
	ft_memdel((void**)&elem);
}
