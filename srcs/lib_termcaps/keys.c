/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   keys.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/12 14:39:02 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 18:12:49 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"


void	rc_key(t_info *info, int *loop)
{
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	while (info->curs_in_str < info->s_len)
		right_key(info);
	tputs(tgetstr("sf", NULL), 1, ft_putchar_err);
	while (info->curs_x > 1)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar_err);
		info->curs_x--;
	}
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
	*loop = 0;
}

void	up_key(t_info *info, t_hist *tmp)
{
/*	while (tmp->prev != info->history)
	{
		tmp = tmp->prev;
		ft_printf("current ? : %s, %s\n", tmp->current == 1 ? "oui" : "non", tmp->name);
	}*/
	if (tmp->prev != info->history)
	{
		while (info->curs_in_str > 1)
			left_key(info);
		tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
		while (!tmp->current)
			tmp = tmp->prev;
		ft_printf(tmp->name);
		info->s_len = ft_strlen(tmp->name);
		info->curs_in_str = info->s_len + 1;
	}
}

void	get_key(int *loop, t_info *info, t_hist *tmp)
{
	char	buff[5];

	ft_bzero(buff, 5);
	info->curs_x = CURS_X;
	info->curs_y = CURS_Y;
	if ((read(0, buff, 4) < 0))
		exit(1);
	ioctl(0, TIOCGWINSZ, info->wndw);
	if (KEY_CODE_UP)
		up_key(info, tmp);
	else if (KEY_CODE_DOWN)
		(void)buff;
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
	else if ((KEY_CODE_HOME) || (KEY_CODE_END))
		curs_extremity(info, buff);
	else if (KEY_CODE_RC)
		rc_key(info, loop);
	else if (KEY_CODE_CTRL_D)
	{
		tmp->current = 0;
		default_term_mode(info);
		exit(1);
	}
	else if (KEY_CODE_TAB)
		(void)buff;
	else if (ft_isprint(*buff))
		info->curs_in_str <= info->s_len ? insert_char(*buff, info, tmp)
			: add_char(*buff, info, tmp);

}
