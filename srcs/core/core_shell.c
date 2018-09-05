/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   core_shell.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 10:11:53 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 18:08:40 by volivry     ###    #+. /#+    ###.fr     */
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
	print_prompt(info);
	get_signals();
	while (info->loop)
		get_key(info, tmp);
}

/*
 **	parse_line : Parse la line et la convertit en liste chainer
 **	Execute la / les commandes
 */

static int		parse_line(t_struct *data, char **line)
{
	int ret;
	t_ins *cpy;

	ret = 0;
	data->commandes = ft_split_commandes(line, data);
	cpy = data->commandes;
	while (cpy)
	{
		if (ft_check_arg_invalid(data, cpy->cmd) == 0)
		{
			ret = execute_commandes(data, cpy->cmd);
			if (ret == -1)
			{
				ft_putstr_fd("--> exit 21sh <--\n", 2);
				data->commandes = clear_ins(data->commandes);
				return (1);
			}
			data->code_erreur = ret;
		}
		cpy = cpy->next;
	}
	data->commandes = clear_ins(data->commandes);
	return (0);
}

/*
 **	Boucle infini, Attend un retour different de zero pour exit
*/

void			core_shell(t_struct *data)
{
	int		quit;
	t_hist	*tmp;
	char	*full_line;

	quit = 0;
	tmp = NULL;
	full_line = NULL;
	init_info(&g_info);
	while (quit == 0)
	{
		line_edit(&g_info, tmp);
		g_data->is_executing = 1;
		dprintf(2, "g_info.line: %s\n", g_info.line);
		if (g_info.line != NULL && quit == 0)
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
			else
			{
				full_line = str_append(full_line, g_info.line);
				default_term_mode(&g_info);
				quit = parse_line(data, &(full_line));
			}
				ft_strdel(&(g_info.line));
		}
		reinit_info(&g_info);
	}
		if (full_line)
			ft_strdel(&full_line);
	free_hist(g_info.history);
	if (g_info.copy)
		ft_strdel(&g_info.copy);
	ft_strdel(&g_info.prmpt);
	default_term_mode(&g_info);
}
