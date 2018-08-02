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

void	key_input(t_info *info, t_slct *slct, int *loop)
{
	char	buff[5];
	int		nb_cols;

	nb_cols = get_col_nb(info);
	ft_bzero(buff, 5);
	if ((read(0, buff, 4) < 0))
		exit(0);
	if (KEY_CODE_UP)
		ac_up_key(slct);
	if (KEY_CODE_DOWN)
		ac_down_key(slct);
	if (KEY_CODE_RIGHT)
		nb_cols == 1 ? ac_down_key(slct) : ac_right_key(info, slct);
	if (KEY_CODE_LEFT)
		nb_cols == 1 ? ac_up_key(slct) : ac_left_key(info, slct);
	if (*(int*)buff == 10)
		ac_rc_key(info, slct, loop);
}

void	ac_rc_key(t_info *info, t_slct *slct, int *loop)
{
	t_slct	*tmp;

	//TO DO : concat info->line & slct->current
	tputs(tgetstr("rc", NULL), 1, ft_putchar_err);
	tmp = ac_first_elem(slct);
	while (tmp != slct)
	{
		ac_remove_elem(tmp);
		tmp = tmp->next;
	}
	info->max_len = 0;
	info->nb_elem = 0;
	*loop = 0;
	free_slct(slct);
}
