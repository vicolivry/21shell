/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 11:18:44 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 17:48:25 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** LEFT KEY
** le : move cursor left
** up : move cursor up
** vi / ve : init/end cursor invisibility
*/

void	left_key(t_info *info)
{
	if (info->s_len)
	{
		if (info->curs_x == 1 && info->curs_y > info->orig_y)
		{
			tputs(tgetstr("up", NULL), 1, ft_putchar_err);
			while (info->curs_x <= info->col_nb)
			{
				tputs(tgetstr("nd", NULL), 0, ft_putchar_err);
				info->curs_x++;
			}
			info->curs_in_str--;
		}
		else if (info->curs_in_str > 1)
		{
			tputs(tgetstr("le", NULL), 1, ft_putchar_err);
			info->curs_in_str--;
		}
	}
	get_curs_pos(info);
}

/*
** RIGHT KEY
** nd : move cursor right
** le : move cursor left
** sr : scroll the screen one line down
** sf : scroll one line up
*/

void	right_key(t_info *info)
{
	get_curs_pos(info);
	if (info->curs_in_str <= info->s_len)
	{
		if (info->curs_x < info->col_nb)
		{
			info->curs_in_str++;
			tputs(tgetstr("nd", NULL), 0, ft_putchar_err);
		}
		else if (info->curs_x == info->col_nb)
		{
			if (info->curs_y == info->row_nb)
				info->orig_y--;
			tputs(tgetstr("sf", NULL), 1, ft_putchar_err);
			get_x_back(info);
			info->curs_in_str++;
		}
	}
	get_curs_pos(info);
}

/*
** Put cursor at first (HOME) or last (END) position
*/

void	home_key(t_info *info)
{
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	while (info->curs_in_str > 1)
		left_key(info);
	get_curs_pos(info);
	info->curs_in_str = 1;
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
}

void	end_key(t_info *info)
{
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	while (info->curs_in_str <= info->s_len)
		right_key(info);
	get_curs_pos(info);
	info->curs_in_str = info->s_len + 1;
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
}

void	get_x_back(t_info *info)
{
	int	i;

	get_curs_pos(info);
	i = info->curs_x;
	while (i > 1)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar_err);
		i--;
	}
}
