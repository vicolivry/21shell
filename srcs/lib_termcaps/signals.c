/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signals.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 12:14:19 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/11 13:47:59 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void		resize_win(int sig)
{
	t_info	*info;
	int		i;

	(void)sig;
	info = NULL;
	info = memo_info(info, 101);
	ioctl(0, TIOCGWINSZ, &(info->wndw));
	info->row_nb = info->wndw.ws_row;
	info->col_nb = info->wndw.ws_col;
	while (info->curs_y-- > info->s_len)
		tputs(tgetstr("up", NULL), 1, ft_putchar_err);
	while (info->curs_x-- > 1)
		tputs(tgetstr("le", NULL), 1, ft_putchar_err);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
	ft_putstr(GREEN);
	ft_putstr(info->prmpt);
	ft_putstr(RESET);
	ft_putstr(info->line);
	i = info->s_len;
	while (i-- >= info->curs_in_str)
		left_key(info);
	info->curs_x = CURS_X;
	info->curs_y = CURS_Y;
}

void			get_signals(void)
{
	signal(SIGWINCH, resize_win);
}
