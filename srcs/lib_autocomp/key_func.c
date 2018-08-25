/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_func.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 17:49:20 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/02 16:22:43 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	key_input(t_info *info, t_slct *slct, int *loop, t_hist *hist)
{
	char	buff[5];

	ft_bzero(buff, 5);
	if ((read(0, buff, 4) < 0))
		exit(0);
	else if (KEY_CODE_RIGHT)
		ac_right_key(info, slct, hist);
	else if (KEY_CODE_LEFT)
		ac_left_key(info, slct, hist);
	else if (KEY_CODE_UP)
		ac_up_key(info, slct, hist);
	else if (KEY_CODE_DOWN)
		ac_down_key(info, slct, hist);
	else if (KEY_CODE_TAB)
		ac_tab_key(info, slct, hist);
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

void	add_slct(t_slct *slct, t_info *info)
{
	int	i;

	i = 0;
	if (slct->name)
		ft_putstr(slct->name);
	if (slct->is_dir)
		ft_putchar('/');
	tputs(tgetstr("sf", NULL), 1, ft_putchar_err);
	get_x_back(info);
}

void	erase_prev(t_info *info, t_hist *hist)
{
	reset_screen(info);
	tputs(tgetstr("up", NULL), 1, ft_putchar_err);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
	print_prompt(info);
	if (hist->name)
		ft_putstr(hist->name);
}

void	restore_curs(t_hist *hist, t_info *info, t_slct *slct)
{
	int		i;
	t_slct	*tmp;

	i = 0;
	tmp = ac_first_elem(slct);
	reset_screen(info);	
	tputs(tgetstr("up", NULL), 1, ft_putchar_err);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
	print_prompt(info);
	if (hist->name)
		ft_putstr(hist->name);
	info->curs_x = CURS_X;
	info->curs_y = CURS_Y;
	while (!tmp->current)
		tmp = tmp->next;
	if (tmp->name)
		while (tmp->name[i])
		{
			add_char(tmp->name[i], info, hist);
			i++;
		}
	if (tmp->is_dir)
		add_char('/', info, hist);
	info->curs_x = CURS_X;
	info->curs_y = CURS_Y;
}
