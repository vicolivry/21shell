/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   core_shell_termcaps.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/11 13:27:58 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/20 10:32:44 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void			init_info(t_info *info)
{
	raw_term_mode(info);
	info->s_len = 0;
	info->orig_y = CURS_Y;
	info->curs_x = CURS_X;
	info->curs_y = CURS_Y;
	info->line = NULL;
	info->curs_in_str = 1;
	ioctl(0, TIOCGWINSZ, &(info->wndw));
	info->row_nb = info->wndw.ws_row;
	info->col_nb = info->wndw.ws_col;
	info->prmpt = NULL;
	info->prmpt = ft_strdup("$> ");
	info->history = root_hist();
}

void			reinit_info(t_info *info)
{
	raw_term_mode(info);
	info->s_len = 0;
	info->orig_y = CURS_Y;
	info->curs_x = CURS_X;
	info->curs_y = CURS_Y;
	info->curs_in_str = 1;
	ft_strdel(&(info->line));
}

void			line_edit(t_info *info, t_hist *tmp)
{
	int loop;

	raw_term_mode(info);
	add_head(info->history);
	tmp = last_elem(info->history);
	init_current(info->history);
	loop = 1;
	print_prompt(info);
	get_signals();
	while (loop)
		get_key(&loop, info, tmp);
}
