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

void ctrl_c(int sig)
{
	t_info *info;
	t_hist *tmp;

	(void)sig;
	info = &g_info;
	tmp = info->history;
	while (!tmp->current)
		tmp = tmp->next;
/*	if (!g_data->is_executing)
		end_key(info);*/
	raw_term_mode(info);
	get_x_back(info);
	ft_putendl("");
	if (!g_data->is_executing)
	{
		if (tmp->name)
			ft_strdel(&tmp->name);
		if (info->line)
			ft_strdel(&info->line);
	//	fill_history(info, tmp);
		reinit_info(info);
		print_prompt(info);
	}
}
