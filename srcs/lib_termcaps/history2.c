/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history2.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/06 13:51:05 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 13:58:27 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Creates a back up of a history element if this one
** is modified.
*/

static void	backing_up(t_hist *tmp)
{
	if (tmp->backup)
	{
		ft_strdel(&(tmp->name));
		tmp->name = ft_strdup(tmp->backup);
		ft_strdel(&(tmp->backup));
	}
}

static void	down_key2(t_info *info, t_hist *tmp)
{
	backing_up(tmp);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	while (info->curs_in_str > 1)
		left_key(info);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
	while (!tmp->prev->current)
		tmp = tmp->next;
	tmp->prev->current = 0;
	tmp->current = 1;
	get_curs_pos(info);
	info->orig_y = info->curs_y;
	ft_putstr(tmp->name);
	if (tmp->next != info->history)
		tmp->backup = ft_strdup(tmp->name);
	info->s_len = tmp->name ? ft_strlen(tmp->name) : 0;
	info->curs_in_str = info->s_len + 1;
	get_curs_pos(info);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
}

/*
** Command line becomes the next element in the
** history if there is one.
*/

void		down_key(t_info *info, t_hist *tmp)
{
	if (tmp->next->name && ft_strlen(tmp->next->name) + ft_strlen(info->prmpt)
			> info->col_nb * info->row_nb)
	{
		tputs(tgetstr("bl", NULL), 1, ft_putchar_err);
		return ;
	}
	if (tmp->next != info->history)
		down_key2(info, tmp);
	else
		tputs(tgetstr("bl", NULL), 1, ft_putchar_err);
}

static void	up_key2(t_info *info, t_hist *tmp)
{
	backing_up(tmp);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	while (info->curs_in_str > 1)
		left_key(info);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
	while (!tmp->next->current)
		tmp = tmp->prev;
	tmp->next->current = 0;
	tmp->current = 1;
	tmp->backup = ft_strdup(tmp->name);
	info->s_len = ft_strlen(tmp->name);
	info->curs_in_str = info->s_len + 1;
	ft_putstr(tmp->name);
	get_curs_pos(info);
	info->orig_y = info->curs_y - ((ft_strlen(tmp->name)
				+ ft_strlen(info->prmpt)) / info->col_nb) + 1;
	if ((ft_strlen(tmp->name) + ft_strlen(info->prmpt)) % info->col_nb != 0)
		info->orig_y--;
	else
	{
		tputs(tgetstr("sf", NULL), 1, ft_putchar_err);
		get_x_back(info);
		info->orig_y--;
	}
}

/*
** Command line becomes the last element in the
** history if there is one.
*/

void		up_key(t_info *info, t_hist *tmp)
{
	if (tmp->prev->name && ft_strlen(tmp->prev->name) + ft_strlen(info->prmpt)
			> info->col_nb * info->row_nb)
	{
		tputs(tgetstr("bl", NULL), 1, ft_putchar_err);
		return ;
	}
	if (tmp->prev != info->history)
		up_key2(info, tmp);
	else
		tputs(tgetstr("bl", NULL), 1, ft_putchar_err);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
}
