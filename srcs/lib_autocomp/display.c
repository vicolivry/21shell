/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/30 18:56:33 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/02 17:33:17 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		set_cols(t_info *info, int col_pos, int i)
{
	int	j;

	j = 0;
	if (i != 0 && (i % (info->row_nb) == 0))
	{
		col_pos += (info->max_len + 2);
		tputs(tgetstr("rc", NULL), 1, ft_putchar_err);
	}
	while (j < col_pos)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar_err);
		j++;
	}
	return (col_pos);
}

static void		display2(t_info *info, int col_pos, t_slct *tmp, t_slct *slct)
{
	int	i;

	i = 0;
	while (tmp != slct)
	{
		col_pos = set_cols(info, col_pos, i);
		ac_print_arg(tmp);
		if ((i + 1) % (info->row_nb) || !i)
			ft_putchar(10);
		tmp = tmp->next;
		i++;
	}
}

void			display(t_info *info, t_slct *slct)
{
	int		i;
	int		cols;
	int		col_pos;
	t_slct	*tmp;

	i = 0;
	cols = get_col_nb(info);
	col_pos = 0;
	tmp = ac_first_elem(slct);
	tputs(tgetstr("cl", NULL), 1, ft_putchar_err);
	if (cols * info->max_len > info->col_nb - 1)
	{
		ft_putstr("Window size too small");
		return ;
	}
	else
		display2(info, col_pos, tmp, slct);
}

void		ac_print_arg(t_slct *slct)
{
	if (slct->current)
	{
		tputs(tgetstr("so", NULL), 1, ft_putchar_err);
		ft_putstr(L_BLUE);
		ft_putstr(slct->name);
		ft_putstr(RESET);
		tputs(tgetstr("se", NULL), 1, ft_putchar_err);
	}
	else
		ft_putstr(slct->name);
}
