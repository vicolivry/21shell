/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_cmd.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/14 15:37:03 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 15:04:11 by yoginet     ###    #+. /#+    ###.fr     */
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
	new->op_redir = 0;
	new->op_next = 0;
	new->stdcmd = 0;
	new->stdin_cmd = 0;
	new->stdout_cmd = 1;
	new->stderr_cmd = 2;
	new->pid = 0;
	new->env = NULL;
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
		clear->tab_cmd = ft_del_tab(clear->tab_cmd);
		ft_strdel(&clear->pathname);
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
