/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/10 10:33:16 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/10 12:36:06 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	backing_up(t_hist *tmp)
{
	if (tmp->backup)
	{
		ft_strdel(&(tmp->name));
		tmp->name = ft_strdup(tmp->backup);
		ft_strdel(&(tmp->backup));
	}
}

void		up_key(t_info *info, t_hist *tmp)
{
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	backing_up(tmp);
	if (tmp->prev != info->history)
	{
		while (info->curs_in_str > 1)
			left_key(info);
		tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
		while (!tmp->next->current && tmp->prev != info->history)
			tmp = tmp->prev;
		tmp->next->current = 0;
		tmp->current = 1;
		ft_putstr(tmp->name);
		tmp->backup = ft_strdup(tmp->name);
		info->s_len = ft_strlen(tmp->name);
		info->curs_in_str = info->s_len + 1;
		info->curs_x = CURS_X;
		info->curs_y = CURS_Y;
	}
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
}

void		down_key(t_info *info, t_hist *tmp)
{
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	backing_up(tmp);
	if (tmp->next != info->history)
	{
		while (info->curs_in_str > 1)
			left_key(info);
		tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
		while (!tmp->prev->current && tmp->next != info->history)
			tmp = tmp->next;
		tmp->prev->current = 0;
		tmp->current = 1;
		if (tmp->name)
		{
			ft_putstr(tmp->name);
			tmp->backup = ft_strdup(tmp->name);
		}
		info->s_len = tmp->name ? ft_strlen(tmp->name) : 0;
		info->curs_in_str = info->s_len + 1;
		info->curs_x = CURS_X;
		info->curs_y = CURS_Y;
	}
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
}
