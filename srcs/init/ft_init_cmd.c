/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_cmd.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/14 15:37:03 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 14:35:52 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_cmd			*ft_init_cmd(void)
{
	t_cmd	*new;

	new = NULL;
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->rep = NULL;
	new->tab_cmd = NULL;
	new->pathname = NULL;
	new->heredoc = NULL;
	new->heredoc_str = NULL;
	new->op_next = 0;
	new->redir_heredoc = 0;
	new->heredoc_activ = 0;
	new->stdin_cmd = 0;
	new->stdout_cmd = 1;
	new->stderr_cmd = 2;
	new->bad_fd = 0;
	new->pid = 0;
	new->env = NULL;
	new->line = NULL;
	new->next = NULL;
	return (new);
}

t_cmd			*clear_cmd(t_cmd *start)
{
	t_cmd	*clear;
	t_cmd	*cpy;

	if (start == NULL)
		return (NULL);
	clear = start;
	cpy = NULL;
	while (clear)
	{
		ft_strdel(&clear->rep);
		ft_strdel(&clear->heredoc_str);
		clear->tab_cmd = ft_del_tab(clear->tab_cmd);
		clear->heredoc = ft_del_tab(clear->heredoc);
		clear_pathname(&clear->pathname);
		clear->env = ft_del_tab(clear->env);
		cpy = clear;
		clear = clear->next;
		free(cpy);
		cpy = NULL;
	}
	free(clear);
	clear = NULL;
	return (NULL);
}

t_path			*ft_init_path(void)
{
	t_path		*new;

	new = NULL;
	new = (t_path *)malloc(sizeof(t_path));
	if (new == NULL)
		return (NULL);
	new->name = NULL;
	new->s_or_d = 0;
	new->redir_fd = 0;
	new->fd = 0;
	new->pid = 0;
	new->next = NULL;
	return (new);
}

t_path			*clear_pathname(t_path **path)
{
	t_path		*clear;
	t_path		*cpy;

	if (*path == NULL)
		return (NULL);
	clear = *path;
	cpy = NULL;
	while (clear)
	{
		ft_strdel(&clear->name);
		cpy = clear;
		clear = clear->next;
		free(cpy);
		cpy = NULL;
	}
	free(clear);
	clear = NULL;
	return (NULL);
}
