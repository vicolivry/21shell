/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signals.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 12:14:19 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/10 18:57:22 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void		resize_win(int sig)
{
	t_info	*info;
	int		i;

	i = -1;
	(void)sig;
	info = NULL;
	info = memo_info(info, 101);
	ioctl(0, TIOCGWINSZ, &(info->wndw));

	info->row_nb = info->wndw.ws_row;
	info->col_nb = info->wndw.ws_col;
	info->curs_x = CURS_X;
	info->curs_y = CURS_Y;
	while (i++ <= info->s_len)
		left_key(info);
	i = -1;
	while (i++ <= info->curs_in_str)
		right_key(info);
}

void			get_signals(void)
{
	signal(SIGWINCH, resize_win);
}
