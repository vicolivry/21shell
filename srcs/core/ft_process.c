/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_process.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/13 15:38:15 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:46:01 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Fonction pour une execution simple d'une commande
**	return : Valeur de retour de la commande
*/

static int		check_process(t_cmd *data)
{
	if (data->heredoc_activ == 1 || data->heredoc_str != NULL ||
	data->heredoc != NULL)
		return (1);
	return (0);
}

int				ft_process(t_cmd *data)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (check_process(data))
		return (fork_heredoc(data, 0));
	pid = fork();
	if (pid < 0)
	{
		ft_error_fork(pid);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		redirection_fd(data);
		if (execve(data->rep, data->tab_cmd, data->env) == -1)
			basic_error(data->tab_cmd[0], "command not found");
		kill(getpid(), SIGTERM);
	}
	else
	{
		data->pid = pid;
		waitpid(pid, &status, WUNTRACED);
	}
	return (exit_status(status));
}
