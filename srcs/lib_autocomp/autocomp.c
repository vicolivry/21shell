/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   autocomp.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 13:07:19 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 11:45:29 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	win_big_enough(t_info *info, t_hist *hist)
{
	int		rows;
	int		line;

	line = (ft_strlen(info->prmpt) + ft_strlen(hist->name)) / info->col_nb;
	line += (ft_strlen(info->prmpt) + ft_strlen(hist->name)) % info->col_nb ?
		1 : 0;
	rows = get_row_number(info);
	if (info->row_nb - line - rows > 0)
		return (1);
	else
		return (0);
}

static void	infinite_loop(t_info *info, t_slct *slct, t_hist *hist)
{
	int	loop;

	loop = 1;
	while (loop)
	{
		key_input(info, slct, &loop, hist);
		if (loop && win_big_enough(info, hist))
			display(info, slct);
		else if (!win_big_enough(info, hist))
		{
			tputs(tgetstr("bl", NULL), 1, ft_putchar_err);
			free_slct(slct, info);
			return ;
		}
	}
	free_slct(slct, info);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
}

static int	ac_special_cases(t_slct *slct, t_info *info, t_hist *hist)
{
	if (!slct || !win_big_enough(info, hist))
	{
		tputs(tgetstr("bl", NULL), 1, ft_putchar_err);
		free_slct(slct, info);
		return (1);
	}
	if (slct->next->next == slct)
	{
		slct->current = 0;
		slct->next->current = 1;
		restore_curs(hist, info, slct);
		free_slct(slct, info);
		return (1);
	}
	return (0);
}

void		autocomp(t_info *info, t_hist *hist)
{
	t_slct	*slct;
	char	*line;

	line = ft_strdup(hist->name);
	line = get_last_word(line, info);
	slct = init_slct(line, info, hist);
	if (line != NULL)
		ft_strdel(&line);
	ac_get_info(slct, info);
	if (ac_special_cases(slct, info, hist))
		return ;
	update_index(slct);
	end_key(info);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	tputs(tgetstr("sf", NULL), 1, ft_putchar_err);
	get_x_back(info);
	display(info, slct);
	infinite_loop(info, slct, hist);
}
