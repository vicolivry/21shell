/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arrows.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 17:44:23 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/02 16:10:57 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	ac_right_key(t_info *info, t_slct *slct)
{
	t_slct	*tmp;
	int		pos;

	tmp = ac_first_elem(slct);
	while (tmp != slct)
	{
		if (tmp->current)
		{
			tmp->current = 0;
			pos = (tmp->index % info->row_nb);
			tmp = tmp->next == slct ? tmp->next->next : tmp->next;
			while (tmp->index % info->row_nb != pos)
			{
				tmp = tmp->next == slct ? tmp->next : tmp;
				tmp = tmp->next;
			}
			tmp->current = 1;
			return ;
		}
		tmp = tmp->next;
	}
}

void	ac_left_key(t_info *info, t_slct *slct)
{
	t_slct	*tmp;
	int		pos;

	tmp = ac_last_elem(slct);
	while (tmp != slct)
	{
		if (tmp->current)
		{
			tmp->current = 0;
			pos = (tmp->index % info->row_nb);
			tmp = tmp->prev == slct ? tmp->prev->prev : tmp->prev;
			while (tmp->index % info->row_nb != pos)
			{
				tmp = tmp->prev == slct ? tmp->prev : tmp;
				tmp = tmp->prev;
			}
			tmp->current = 1;
			return ;
		}
		tmp = tmp->prev;
	}
}

void	ac_down_key(t_slct *slct)
{
	t_slct	*tmp;

	tmp = ac_first_elem(slct);
	while (tmp != slct)
	{
		if (tmp->current)
		{
			tmp->current = 0;
			if (tmp->next == slct)
				tmp->next->next->current = 1;
			else
				tmp->next->current = 1;
			return ;
		}
		tmp = tmp->next;
	}
}

void	ac_up_key(t_slct *slct)
{
	t_slct	*tmp;

	tmp = ac_last_elem(slct);
	while (tmp != slct)
	{
		if (tmp->current)
		{
			tmp->current = 0;
			if (tmp->prev == slct)
				tmp->prev->prev->current = 1;
			else
				tmp->prev->current = 1;
			return ;
		}
		tmp = tmp->prev;
	}
}
