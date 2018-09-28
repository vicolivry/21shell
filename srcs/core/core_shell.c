/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   core_shell.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 10:11:53 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 14:40:04 by yoginet     ###    #+. /#+    ###.fr     */
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
	get_curs_pos(info);
	tputs(tgoto(tgetstr("cm", NULL), info->curs_x - 1, info->curs_y - 1), 1, ft_putchar_err);
	print_prompt(info);
	get_signals();
	while (info->loop)
		get_key(info, tmp);
}

static char*	quoted_loops(char *full_line, t_struct *data, int *quit)
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
	else if (ft_strstr(g_info.line, "<<"))
	{
		if (heredoc() == NULL || !g_info.h_d.fill || !ft_strcmp(g_info.h_d.fill, ""))
			return (full_line);
		g_info.h_d.cmd = str_append(g_info.h_d.cmd, " ");
		g_info.h_d.cmd = str_append(g_info.h_d.cmd, g_info.h_d.fill);
		full_line = ft_strdup(g_info.h_d.cmd);
		ft_strdel(&g_info.h_d.fill);
		ft_strdel(&g_info.h_d.cmd);
		default_term_mode(&g_info);
		*quit = parse_line(data, &(full_line));
	}
	else
	{
		full_line = str_append(full_line, g_info.line);
		default_term_mode(&g_info);
		*quit = parse_line(data, &(full_line));
	}
	return (full_line);
}



/*
**	parse_line : Parse la line et la convertit en liste chainer
**	Execute la / les commandes
*/

static t_ins		*what_next_link(t_ins *lst, int code)
{
	if (cmd_suivante(lst, code) == 0)
		return (lst->next);
	else
	{
		while (lst)
		{
			if (lst->code == 0)
				return (lst->next);
			lst = lst->next;
		}
	}
	return (NULL);
}

int					parse_line(t_struct *data, char **line)
{
	int		ret;
	t_ins	*cpy;

	ret = 0;
	if (ft_check_line_vide(*line, &data) == 0)
		return (0);
	data->commandes = ft_split_commandes(line, data);
	cpy = data->commandes;
	while (cpy)
	{
		// a delete (print_debug)
		print_debug(&cpy->cmd, cpy->code);
		if (ft_check_arg_invalid(data, cpy->cmd) == 0)
		{
			ret = execute_commandes(data, cpy->cmd);
			if (ret == -1)
			{
				data->commandes = clear_ins(data->commandes);
				return (1);
			}
			data->code_erreur = ret;
		}
		// A DETETE **********************************************************
		//ft_putstr_fd(GREEN, 2);
		//ft_printf("******* repertoire = %s\n", data->pwd);
		//ft_printf("******* Valeur de retour (data->code_erreur) = %d\n", data->code_erreur);
		//ft_putstr_fd(RESET, 2);
		// *******************************************************************
		cpy = what_next_link(cpy, data->code_erreur);
	}
	data->commandes = clear_ins(data->commandes);
	if (*line != NULL)
		parse_line(data, line);
	return (0);
}

/*
**	Boucle infini, Attend un retour different de zero pour exit
*/

void				core_shell(t_struct *data)
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
		if (g_info.line != NULL && quit == 0)
		{
			full_line = quoted_loops(full_line, data, &quit);
			ft_strdel(&(g_info.line));
		}
		reinit_info(&g_info);
	}
	if (full_line)
		ft_strdel(&full_line);
	if (g_info.line)
		ft_strdel(&g_info.line);
	free_hist(g_info.history);
	if (g_info.copy)
		ft_strdel(&g_info.copy);
	ft_strdel(&g_info.prmpt);
	default_term_mode(&g_info);
}
