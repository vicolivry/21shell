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

/*
** Sends to up, down, right and left arrow functions.
*/

static void	arrow_cmds(t_info *info, t_slct *slct, char *buff, t_hist *hist)
{
	if (!info->out)
	{
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
	}
}

/*
** Gets the key that is typed.
*/

int			key_input(t_info *info, t_slct *slct, int *loop, t_hist *hist)
{
	char	buff[50];

	ft_bzero(buff, 50);
	if (info->out)
	{
		restore_curs(hist, info, slct);
		return ((*loop = 0));
	}
	read(0, buff, 49);
	if (buff[3] || buff[0] > 127)
		return (0);
	if ((KEY_CODE_RIGHT) || (KEY_CODE_LEFT) || (KEY_CODE_UP)
	|| (KEY_CODE_DOWN) || (KEY_CODE_TAB))
		arrow_cmds(info, slct, buff, hist);
	else if ((buff[0] == 10 && buff[1] == 0) || (KEY_CODE_BSP)
	|| ft_isprint(*buff))
	{
		restore_curs(hist, info, slct);
		if (ft_isprint(*buff))
			add_char(*buff, info, hist);
		return ((*loop = 0));
	}
	else
		reset_screen(info);
	return (1);
}

/*
** Erases the display of the list so that only the command line remains.
*/

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
	if (!info->out)
		while (tmp->name[i])
		{
			add_char(tmp->name[i], info, hist);
			i++;
		}
}

/*
** Puts back th cursor in the command line after displaying
** the list.
*/

void		restore_curs(t_hist *hist, t_info *info, t_slct *slct)
{
	t_slct	*tmp;

	tmp = ac_first_elem(slct);
	reset_screen(info);
	if (slct->next->next != slct && !info->out)
		tputs(tgetstr("up", NULL), 1, ft_putchar_err);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
	print_prompt(info);
	if (!info->out && hist->name)
		ft_putstr(hist->name);
	while (!tmp->current)
		tmp = tmp->next;
	if (tmp->name)
		restore2(info, hist, tmp);
	if (!info->out && tmp->is_dir)
		add_char('/', info, hist);
	get_curs_pos(info);
}
