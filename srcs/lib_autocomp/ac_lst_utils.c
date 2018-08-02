/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/28 14:10:10 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/02 16:10:18 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	ac_add_after_lst(t_slct *elem, const char *name)
{
	t_slct	*new_elem;

	new_elem = NULL;
	if ((new_elem = (t_slct*)malloc(sizeof(*new_elem))))
	{
		new_elem->name = ft_strdup(name);
		new_elem->len = ft_strlen(name);
		new_elem->current = 0;
		new_elem->index = 0;
		new_elem->prev = elem;
		new_elem->next = elem->next;
		elem->next->prev = new_elem;
		elem->next = new_elem;
	}
}

void	ac_add_before_lst(t_slct *elem, const char *name)
{
	t_slct	*new_elem;

	new_elem = NULL;
	if ((new_elem = (t_slct*)malloc(sizeof(*new_elem))))
	{
		new_elem->name = ft_strdup(name);
		new_elem->len = ft_strlen(name);
		new_elem->current = 0;
		new_elem->index = 0;
		new_elem->prev = elem->prev;
		new_elem->next = elem;
		elem->prev->next = new_elem;
		elem->prev = new_elem;
	}
}

void	ac_add_queue(t_slct *root, const char *name)
{
	ac_add_before_lst(root, name);
}

void	ac_add_head(t_slct *root, const char *name)
{
	ac_add_after_lst(root, name);
}

void	ac_remove_elem(t_slct *elem)
{
	elem->prev->next = elem->next;
	elem->next->prev = elem->prev;
	ft_strdel(&elem->name);
	ft_memdel((void**)&elem);
}
