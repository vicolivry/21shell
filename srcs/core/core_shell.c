/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   core_shell.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 10:11:53 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:43:20 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

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

int					parse_line(t_struct *data, char **line, int ret)
{
	t_ins	*cpy;

	cpy = NULL;
	if (ft_check_line_vide(*line, &data) == 0)
		return (0);
	data->commandes = ft_split_commandes(line, data);
	cpy = data->commandes;
	while (cpy)
	{
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
		cpy = what_next_link(cpy, data->code_erreur);
	}
	data->commandes = clear_ins(data->commandes);
	if (*line != NULL)
		parse_line(data, line, 0);
	return (0);
}

/*
**	Boucle infini, Attend un retour different de zero pour exit
*/

static void			exit_core_shell(char *full_line)
{
	if (full_line)
		ft_strdel(&full_line);
	if (g_info.line)
		ft_strdel(&g_info.line);
	free_hist(g_info.history);
	if (g_info.copy)
		ft_strdel(&g_info.copy);
	ft_strdel(&g_info.prmpt);
	default_term_mode(&g_info);
	g_info.over = 1;
}

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
		if (quit == 0)
		{
			full_line = quoted_loops(full_line, data, &quit);
			if (g_info.line)
				ft_strdel(&(g_info.line));
		}
		reinit_info(&g_info);
	}
	exit_core_shell(full_line);
}
