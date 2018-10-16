/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signals2.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/06 14:04:31 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 17:48:16 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	ctrl_c2(t_hist *tmp, t_info *info)
{
	if (g_slct)
		info->out = 1;
	tmp = first_elem(info->history);
	while (tmp->name)
	{
		tmp->current = 0;
		tmp = tmp->next;
	}
	tmp = last_elem(info->history);
	if (tmp->name)
		ft_strdel(&tmp->name);
	if (info->line)
		ft_strdel(&info->line);
	tmp->current = 1;
	reinit_info(info);
	print_prompt(info);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
}

void		ctrl_c(int sig)
{
	t_info *info;
	t_hist *tmp;

	tmp = NULL;
	(void)sig;
	if (g_info.over)
		return ;
	info = &g_info;
	ft_putendl("");
	if (!g_data->is_executing)
		ctrl_c2(tmp, info);
}
