/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   core_shell.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 10:11:53 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 14:27:57 by volivry     ###    #+. /#+    ###.fr     */
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
	info->copy = NULL;
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
	// A DETETE **********************************************************
	ft_putstr_fd(GREEN, 2);
	ft_printf("Parsing ok\n");
	ft_putstr_fd(RESET, 2);
	// *******************************************************************
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
		// A DETETE **********************************************************
		ft_putstr_fd(GREEN, 2);
		ft_printf("******* Valeur de retour (data->code_erreur) = %d\n", data->code_erreur);
		ft_putstr_fd(RESET, 2);
		// *******************************************************************
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
		if (g_info.line != NULL && quit == 0)
		{
			if (g_info.quoted)
			{
				full_line = str_append(full_line, g_info.line);
				full_line = str_append(full_line, "\n");
				ft_strdel(&(g_info.line));
			}
			else
			{
				full_line = str_append(full_line, g_info.line);
				ft_strdel(&(g_info.line));
				default_term_mode(&g_info);
				quit = parse_line(data, &(full_line));
				if (full_line)
					ft_strdel(&full_line);
			}
		}
		reinit_info(&g_info);
	}
	default_term_mode(&g_info);
}
