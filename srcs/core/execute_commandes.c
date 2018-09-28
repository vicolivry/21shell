/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute_commandes.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/11 09:36:12 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 11:03:39 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		exec_pipe_child(t_struct *mystruct, t_cmd *lst, int pipe_fd[2],
	int *fd_in)
{
	int		builtins;

	if ((builtins = execute_builtins(mystruct, lst, pipe_fd, fd_in)) != -1)
		return (builtins);
	if (lst->pathname != NULL)
		return (fork_redirection(lst));
	if (lst->op_next == 4 || lst->op_next == 5)
		return (fork_heredoc(lst, 0));
	if (lst->op_next == 1)
	{
		dup2(*fd_in, lst->stdin_cmd) == -1 ? basic_error("dup2", "failled") : 0;
		dup2(pipe_fd[1], lst->stdout_cmd) == -1 ?
	basic_error("dup2", "failled") : 0;
		close(pipe_fd[0]) == -1 ? basic_error("close", "failled") : 0;
		return (execve(lst->rep, lst->tab_cmd, lst->env));
	}
	dup2(*fd_in, lst->stdin_cmd) == -1 ? basic_error("dup2", "failled") : 0;
	close(pipe_fd[1]) == -1 ? basic_error("close", "failled") : 0;
	close(pipe_fd[0]) == -1 ? basic_error("close", "failled") : 0;
	return (execve(lst->rep, lst->tab_cmd, lst->env));
}

/*
**	boucle sur la liste chainer des commandes et fork
*/

static int		exec_cmd_recur(t_struct *mystruct, t_cmd *data, int fd_in, t_cmd *start)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	while (data)
	{
		if (pipe(pipe_fd) == -1)
			exit(EXIT_FAILURE);
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			if (exec_pipe_child(mystruct, data, pipe_fd, &fd_in) == -1)
			{
				basic_error(data->tab_cmd[0], ": command not found");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			data->pid = pid;
			close(pipe_fd[1]);
			fd_in = pipe_fd[0];
		}
		data = data->next;
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait_or_not(&status, pid, start);
	return (exit_status(status));
}

/*
**	On envoie la liste chainee a exec_cmd_recur
*/

int				execute_commandes(t_struct *mystruct, t_cmd *data)
{
	int		ret;
	int		fd_in;
	t_cmd	*start;

	ret = 0;
	fd_in = 0;
	start = NULL;
	if (!data)
		return (-1);
	if (len_list(data) == 1 && (data)->op_next == 0)
	{
		if ((ret = execute_builtins_light(mystruct, data)) == -2)
			return (ft_process(data));
		else
			return (ret);
	}
	start = data;
	ret = exec_cmd_recur(mystruct, data, fd_in, data);
	ft_kill_process(start, mystruct->pid);
	return (ret);
}
