/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute_commandes.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/11 09:36:12 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 11:03:28 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	boucle sur la liste chainer des commandes et fork
*/

static int		pipe_child_norm(t_struct *mystruct, t_cmd *data, int pipe_fd[2],
		int *fd_in)
{
	int		ret;

	ret = exec_pipe_child(mystruct, data, pipe_fd, fd_in);
	if (ret == -1)
	{
		basic_error(data->tab_cmd[0], " : command not found");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

static int		exec_cmd_recur(t_struct *mystruct, t_cmd *data, int fd_in,
		t_cmd *start)
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
			pipe_child_norm(mystruct, data, pipe_fd, &fd_in);
		else
		{
			data->pid = pid;
			close(pipe_fd[1]);
			fd_in = pipe_fd[0];
		}
		data = data->next;
	}
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
	if (len_list(data) == 1 && data->op_next == 0)
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
