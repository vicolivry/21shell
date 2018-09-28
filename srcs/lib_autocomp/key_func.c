/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_func.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 17:49:20 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 14:26:00 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void		key_input(t_info *info, t_slct *slct, int *loop, t_hist *hist)
{
	char	buff[5];

	ft_bzero(buff, 5);
	read(0, buff, 4);
	if (KEY_CODE_RIGHT)
		ac_right_key(info, slct, hist);
	else if (KEY_CODE_LEFT)
		ac_left_key(info, slct, hist);
	else if (KEY_CODE_UP)
		ac_up_key(info, slct, hist);
	else if (KEY_CODE_DOWN)
		ac_down_key(info, slct, hist);
	else if (KEY_CODE_TAB)
		ac_tab_key(info, slct, hist);
	else if (KEY_CODE_CTRL_D)
		ctrl_d(info, hist);
	else if (*(int*)buff == 10 || (KEY_CODE_BSP) || ft_isprint(*buff))
	{
		restore_curs(hist, info, slct);
		if (ft_isprint(*buff))
			add_char(*buff, info, hist);
		*loop = 0;
	}
	else
		reset_screen(info);
}

void		add_slct(t_slct *slct, t_info *info)
{
	int	i;

	i = 0;
	if (info->letters)
		while (info->letters[i])
			i++;
	if (slct->name)
		while (slct->name[i])
		{
			ft_putchar(slct->name[i]);
			i++;
		}
	if (slct->is_dir)
		ft_putchar('/');
	tputs(tgetstr("sf", NULL), 1, ft_putchar_err);
	get_x_back(info);
}

void		erase_prev(t_info *info, t_hist *hist)
{
	reset_screen(info);
	tputs(tgetstr("up", NULL), 1, ft_putchar_err);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
	print_prompt(info);
	if (hist->name)
		ft_putstr(hist->name);
}

static void	restore2(t_info *info, t_hist *hist, t_slct *tmp)
{
	int	i;

	i = 0;
	if (info->letters)
		while (info->letters[i])
			i++;
	while (tmp->name[i])
	{
		add_char(tmp->name[i], info, hist);
		i++;
	}
}

void		restore_curs(t_hist *hist, t_info *info, t_slct *slct)
{
	t_slct	*tmp;

	tmp = ac_first_elem(slct);
	reset_screen(info);
	if (slct->next->next != slct)
		tputs(tgetstr("up", NULL), 1, ft_putchar_err);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
	print_prompt(info);
	if (hist->name)
		ft_putstr(hist->name);
	while (!tmp->current)
		tmp = tmp->next;
	if (tmp->name)
		restore2(info, hist, tmp);
	if (tmp->is_dir)
		add_char('/', info, hist);
	get_curs_pos(info);
}
