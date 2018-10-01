/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   info_init_edit.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 13:53:18 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 14:13:37 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void			init_info(t_info *info)
{
	raw_term_mode(info);
	info->s_len = 0;
	get_curs_pos(info);
	info->orig_y = info->curs_y;
	info->line = NULL;
	info->curs_in_str = 1;
	ioctl(0, TIOCGWINSZ, &(info->wndw));
	info->row_nb = info->wndw.ws_row;
	info->col_nb = info->wndw.ws_col;
	info->prmpt = NULL;
	info->copy = NULL;
	info->prmpt = ft_strdup("$> ");
	info->history = root_hist();
	info->letters = NULL;
	info->loop = 1;
	info->max_len = 0;
	info->nb_elem = 0;
	info->h_d.cmd =  NULL;
	info->h_d.trigger =  NULL;
	info->h_d.fill =  NULL;
}

void			reinit_info(t_info *info)
{
	raw_term_mode(info);
	info->s_len = 0;
	ioctl(0, TIOCGWINSZ, &(info->wndw));
	info->row_nb = info->wndw.ws_row;
	info->col_nb = info->wndw.ws_col;
	get_curs_pos(info);
	info->orig_y = info->curs_y;
	info->curs_in_str = 1;
	ft_strdel(&(info->line));
	info->loop = 1;
}

void			line_edit(t_info *info, t_hist *tmp)
{
	g_data->is_executing = 0;
	raw_term_mode(info);
	add_head(info->history);
	tmp = last_elem(info->history);
	init_current(info->history);
	get_curs_pos(info);
	tputs(tgoto(tgetstr("cm", NULL), info->curs_x - 1, info->curs_y - 1),
	1, ft_putchar_err);
	print_prompt(info);
	get_signals();
	while (info->loop)
		get_key(info, tmp);
}

char			*hd_case(int *quit, char *full_line, t_struct *data)
{
	if (heredoc() == NULL || !g_info.h_d.fill ||
	!ft_strcmp(g_info.h_d.fill, ""))
		return (full_line);
	g_info.h_d.cmd = str_append(g_info.h_d.cmd, " ");
	g_info.h_d.cmd = str_append(g_info.h_d.cmd, g_info.h_d.fill);
	full_line = ft_strdup(g_info.h_d.cmd);
	ft_strdel(&g_info.h_d.fill);
	ft_strdel(&g_info.h_d.cmd);
	default_term_mode(&g_info);
	g_data->is_executing = 1;
	*quit = parse_line(data, &(full_line));
	return (full_line);
}

char			*quoted_loops(char *full_line, t_struct *data, int *quit)
{
	if (g_info.quoted == 1 || g_info.quoted == 2)
	{
		full_line = str_append(full_line, g_info.line);
		full_line = str_append(full_line, "\n");
	}
	else if (g_info.quoted == 3)
	{
		g_info.line[ft_strlen(g_info.line) - 1] = 0;
		full_line = str_append(full_line, g_info.line);
		g_info.quoted = 0;
	}
	else if (g_info.quoted == 4)
		full_line = hd_case(quit, full_line, data);
	else
	{
		full_line = str_append(full_line, g_info.line);
		default_term_mode(&g_info);
		g_data->is_executing = 1;
		*quit = parse_line(data, &(full_line));
	}
	return (full_line);
}
