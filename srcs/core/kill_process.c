/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   kill_process.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/26 13:22:36 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/04 11:19:05 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int				ft_kill_process(t_cmd *start, int pid)
{
	while (start)
	{
		if (start->pid != pid && start->pid != 0)
			kill(start->pid, SIGTERM);
		if (start->stdout_cmd != 1 && start->stdout_cmd != 2)
			close(start->stdout_cmd);
		if (start->stderr_cmd != 2 && start->stdout_cmd != 1)
			close(start->stderr_cmd);
		start = start->next;
	}
	fork_heredoc(NULL, 1);
	return (0);
}
