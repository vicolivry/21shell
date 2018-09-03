/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/10 10:33:16 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 12:03:39 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void		fill_history(t_info *info, t_hist *tmp)
{
	t_hist	*last;

	last = last_elem(info->history);
	if (tmp->current && tmp->next != info->history)
	{
		if (last->name)
			ft_strdel(&(last->name));
		last->name = ft_strdup(tmp->name);
		if (info->line)
			ft_strdel(&(info->line));
		info->line = ft_strdup(tmp->name);
		ft_strdel(&(tmp->name));
		tmp->name = ft_strdup(tmp->backup);
		ft_strdel(&(tmp->backup));
	}
	while (tmp->next != info->history)
		tmp = tmp->next;
	if (!last->name ||
			(last->prev->name && !ft_strcmp(last->name, last->prev->name)))
		remove_elem(last);
}

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
	if (tmp->prev != info->history /*&& remaining_chars(info, tmp->prev) >
			ft_strlen(tmp->prev->name)*/)
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
		tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
	}
	else
		tputs(tgetstr("bl", NULL), 1, ft_putchar_err);
}

void		down_key(t_info *info, t_hist *tmp)
{
	if (tmp->next != info->history/* && remaining_chars(info, tmp->next) >
			ft_strlen(tmp->next->name)*/)
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
		ft_putstr(tmp->name);
		if (tmp->next != info->history)
			tmp->backup = ft_strdup(tmp->name);
		info->s_len = tmp->name ? ft_strlen(tmp->name) : 0;
		info->curs_in_str = info->s_len + 1;
		get_curs_pos(info);
		tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
	}
	else
		tputs(tgetstr("bl", NULL), 1, ft_putchar_err);

}
