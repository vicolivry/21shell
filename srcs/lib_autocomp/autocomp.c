/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   autocomp.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 13:07:19 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 17:50:05 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	infinite_loop(t_info *info, t_slct *slct, t_hist *hist)
{
	int	loop;

	loop = 1;
	while (loop)
	{
		key_input(info, slct, &loop, hist);
		if (loop)
			display(info, slct);
	}
	free_slct(slct, info);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
}

static int	ac_special_cases(t_slct *slct, t_info *info, t_hist *hist)
{
	if (!slct)
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
	if (ac_special_cases(slct, info, hist))
		return ;
	ac_get_info(slct, info);
	update_index(slct);
	end_key(info);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	tputs(tgetstr("sf", NULL), 1, ft_putchar_err);
	get_x_back(info);
	display(info, slct);
	infinite_loop(info, slct, hist);
}
