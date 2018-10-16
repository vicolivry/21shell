/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_child.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 12:53:56 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:44:27 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Execution du fils (selon op_next (|, >, <, ...))
*/

static int		exec_pipe_child2(t_cmd *lst, int pipe_fd[2], int *fd_in)
{
	int		ret;

	ret = 0;
	redirection_fd(lst);
	if (lst->pathname != NULL)
		return (fork_redirection(lst));
	dup2(*fd_in, lst->stdin_cmd) == -1 ? basic_error("dup2", " failled") : 0;
	close(pipe_fd[1]) == -1 ? basic_error("close", " failled") : 0;
	close(pipe_fd[0]) == -1 ? basic_error("close", " failled") : 0;
	ret = execve(lst->rep, lst->tab_cmd, lst->env);
	if (ret == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

static int		redir_one(t_path *lst)
{
	t_path		*cpy;

	cpy = lst;
	while (cpy)
	{
		if (cpy->redir_fd == 1)
			return (1);
		cpy = cpy->next;
	}
	return (0);
}

static int		exec_pipe_op_1(t_cmd *lst, int pipe_fd[2], int *fd_in)
{
	int		ret;

	ret = 0;
	dup2(*fd_in, lst->stdin_cmd) == -1 ? basic_error("dup2", "failled") : 0;
	dup2(pipe_fd[1], lst->stdout_cmd) == -1 ?
		basic_error("dup2", " failled") : 0;
	redirection_fd(lst);
	close(pipe_fd[0]) == -1 ? basic_error("close", " failled") : 0;
	if (lst->pathname != NULL)
		duplique_process(lst, pipe_fd, fd_in);
	if (lst->redir_heredoc == 1)
		return (fork_heredoc(lst, 0));
	ret = execve(lst->rep, lst->tab_cmd, lst->env);
	if (ret == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int				exec_pipe_child(t_struct *mystruct, t_cmd *lst, int pipe_fd[2],
		int *fd_in)
{
	int		builtins;

	if ((builtins = execute_builtins(mystruct, lst, pipe_fd, fd_in)) != -1)
		return (builtins);
	if (lst->op_next == 1)
		return (exec_pipe_op_1(lst, pipe_fd, fd_in));
	if (lst->op_next == 2 || lst->op_next == 3)
	{
		if (redir_one(lst->pathname) == 1)
		{
			dup2(*fd_in, lst->stdin_cmd) == -1 ?
				basic_error("dup2", " failled") : 0;
			dup2(pipe_fd[0], lst->stdout_cmd) == -1 ?
				basic_error("dup2", " failled") : 0;
			close(pipe_fd[1]) == -1 ? basic_error("close", "failled") : 0;
		}
		return (fork_redirection(lst));
	}
	if (lst->op_next == 4 || lst->op_next == 5)
		return (fork_heredoc(lst, 0));
	return (exec_pipe_child2(lst, pipe_fd, fd_in));
}
