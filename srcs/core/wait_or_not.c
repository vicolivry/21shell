/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wait_or_not.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 13:09:39 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:46:52 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Wait et kill les processus
*/

static int	kill_all(t_cmd *cpy)
{
	while (cpy)
	{
		kill(cpy->pid, SIGPIPE);
		cpy = cpy->next;
	}
	return (0);
}

int			wait_or_not(int *status, pid_t pid, t_cmd *start)
{
	int		stat;
	t_cmd	*cpy;

	stat = 0;
	cpy = start;
	waitpid(pid, status, WUNTRACED);
	while (start)
	{
		waitpid(start->pid, &stat, WNOHANG);
		if (ft_strcmp(start->tab_cmd[0], "top") != 0 &&
	ft_strcmp(start->tab_cmd[0], "yes") != 0 &&
	ft_strcmp(start->tab_cmd[0], "base64") != 0 &&
	ft_strcmp(start->tab_cmd[0], "cat") != 0)
		{
			waitpid(start->pid, NULL, 0);
		}
		start = start->next;
	}
	kill_all(cpy);
	return (0);
}
