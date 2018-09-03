/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   keys.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/12 14:39:02 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:15:51 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	cursor_start(t_info *info)
{
	while (info->curs_x > 1)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar_err);
		get_curs_pos(info);
	}
}

void		rc_key(t_info *info, int *loop, t_hist *tmp)
{
	fill_history(info, tmp);
	toggle_quote(info);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	while (info->curs_in_str < info->s_len)
		right_key(info);
	tputs(tgetstr("sf", NULL), 1, ft_putchar_err);
	cursor_start(info);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
	*loop = 0;
}

void		get_key(int *loop, t_info *info, t_hist *tmp)
{
	char	buff[5];

	if (info->line)
		ft_strdel(&(info->line));
	info->line = ft_strdup(tmp->name);
	ft_bzero(buff, 5);
	get_curs_pos(info);
	while (!tmp->current)
		tmp = tmp->next;
	if ((read(0, buff, 4) < 0))
		exit(1);
	ioctl(0, TIOCGWINSZ, info->wndw);
	if (KEY_CODE_UP)
		up_key(info, tmp);
	else if (KEY_CODE_DOWN)
		down_key(info, tmp);
	else if (KEY_CODE_RIGHT)
		right_key(info);
	else if (KEY_CODE_LEFT)
		left_key(info);
	else if ((KEY_CODE_ALT_UP) || (KEY_CODE_ALT_DOWN))
		alt_up_down(info, buff);
	else if (KEY_CODE_ALT_RIGHT)
		alt_right(info, tmp);
	else if (KEY_CODE_ALT_LEFT)
		alt_left(info, tmp);
	else if (KEY_CODE_BSP)
		del_char(info, tmp);
	else if (KEY_CODE_HOME)
		home_key(info);
	else if (KEY_CODE_END)
		end_key(info);
	else if (KEY_CODE_RC)
		rc_key(info, loop, tmp);
	else if (KEY_CODE_CTRL_E || KEY_CODE_CTRL_B ||
			KEY_CODE_CTRL_X || KEY_CODE_CTRL_A || KEY_CODE_CTRL_P)
		cut_n_cpy(info, buff, tmp);
	else if (KEY_CODE_CTRL_D)
		ctrl_d(info);
	else if (KEY_CODE_TAB)
		autocomp(info, tmp);
	else if (ft_isprint(*buff))
		info->curs_in_str <= info->s_len ? insert_char(*buff, info, tmp)
			: add_char(*buff, info, tmp);
}
