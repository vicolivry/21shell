/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute_commandes.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/11 09:36:12 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 19:14:59 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

//********************************************************************* A Delete !
#include <assert.h>
static void	debug(t_struct *data)
{
	t_cmd	*test;

	test = data->commandes;
	printf("***(%s)***\n", __func__);
	while (data->commandes)
	{
		printf("data->commandes->rep = %s\n", data->commandes->rep);
		printf("data->commandes->pathname = %s\n", data->commandes->pathname);
		if (data->commandes->tab_cmd != NULL)
		{
			printf("data->commandes->tab_cmd[0] = %s\n", data->commandes->tab_cmd[0]);
			printf("data->commandes->tab_cmd[1] = %s\n", data->commandes->tab_cmd[1]);
			printf("data->commandes->tab_cmd[2] = %s\n", data->commandes->tab_cmd[2]);
		}
		printf("data->commandes->stdin_cmd = %d\n", data->commandes->stdin_cmd);
		printf("data->commandes->stdout_cmd = %d\n", data->commandes->stdout_cmd);
		printf("data->commandes->stderr_cmd = %d\n", data->commandes->stderr_cmd);
		printf("data->commandes->op_redir = %d\n", data->commandes->op_redir);
		printf("data->commandes->op_next = %d\n", data->commandes->op_next);
		printf("next\n");
		data->commandes = data->commandes->next;
	}
	data->commandes = test;
	printf("End debug ******************************************\n\n");
}

static int			exec_pipe_child(t_cmd *commandes, int pipe_fd[2], int *fd_in)
{
	int		exec;
	int		fd;

	exec = 0;
	fd = 0;
	ft_putstr_fd("********************************** FONCTION\n", 2);
	ft_putstr_fd(commandes->rep, 2);
	ft_putstr_fd("\n\n", 2);
	if ((commandes->op_redir == 2 || commandes->op_redir == 3) && commandes->pathname != NULL)
	{
		if (commandes->op_redir == 2)
			fd = open(commandes->pathname, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (commandes->op_redir == 3)
			fd = open(commandes->pathname, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
			exit(EXIT_FAILURE);
		dup2(*fd_in, 0) == -1 ? ft_putstr_fd("error dup2\n", 2) : 0;
		dup2(fd, 1) == -1 ? ft_putstr_fd("error dup2\n", 2) : 0;
		close(pipe_fd[0]) == -1 ? ft_putstr_fd("error close\n", 2) : 0;
		close(fd) == -1 ? ft_putstr_fd("error close\n", 2) : 0;
		ft_putstr_fd("********************************** Here 1\n", 2);
		exec = execve(commandes->rep, commandes->tab_cmd, commandes->env);
		ft_putstr_fd("********************************** Here 1\n", 2);
		//if (exec == -1)
		//	exit(EXIT_FAILURE);
	}
	//if (commandes->op_next == 1)
	//{
		dup2(*fd_in, 0) == -1 ? ft_putstr_fd("error dup2\n", 2) : 0;
		dup2(pipe_fd[1], 1) == -1 ? ft_putstr_fd("error dup2\n", 2) : 0;
		close(pipe_fd[0]) == -1 ? ft_putstr_fd("error close\n", 2) : 0;
		ft_putstr_fd("********************************** Here 2\n", 2);
		exec = execve(commandes->rep, commandes->tab_cmd, commandes->env);
		ft_putstr_fd("********************************** Here 2\n", 2);
		//if (exec == -1)
		//	exit(EXIT_FAILURE);
	//}
	ft_putstr_fd("********************************** EXIT FONCTIONS\n", 2);
	return (EXIT_SUCCESS);
}

static int			exec_cmd_recur(t_struct *data)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		fd_in;
	int		status;
	int		ret;

	fd_in = 0;
	status = 0;
	while (data->commandes)
	{
		if (pipe(pipe_fd) == -1)
			exit(EXIT_FAILURE);
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			printf("%s ->DEBUG***** (child = %d) (getpid = %d)\n", __func__, pid, getpid());
			ret = exec_pipe_child(data->commandes, pipe_fd, &fd_in);
			if (ret == 1)
			{
				kill(pid, 0);
				exit(EXIT_FAILURE);
			}
			printf("%s ->Child End(child = %d) (getpid = %d)\n", __func__, pid, getpid());
		}
		else
		{
			printf("%s ->DEBUG***** (father = %d)\n", __func__, pid);
			waitpid(pid, &status, 0);
			close(pipe_fd[1]);
			fd_in = pipe_fd[0];
			printf("WEXITSTATUS = %d\n", WEXITSTATUS(status));
		}
		data->commandes = data->commandes->next;
	}
	data->ret_func = WEXITSTATUS(status);
	printf("END WEXITSTATUS = %d\n", data->ret_func = WEXITSTATUS(status));
	printf("%s ->Child End(child = %d) (getpid = %d)\n", __func__, pid, getpid());
	return (EXIT_SUCCESS);
}

int			execute_commandes(t_struct *data)
{
	int		ret;
	int		status;
	pid_t	pid_p;

	// A delete
	debug(data);
	// *******
	ret = 0;
	if (len_list(data->commandes) == 1)
		return (ft_process(data));
	if ((pid_p = fork()) == -1)
		ft_putstr_fd("Error Fork Father\n", 2);
	else if (pid_p == 0)
	{
		printf("%s ->DEBUG***** (child = %d) (getpid = %d)\n", __func__, pid_p, getpid());
		ret = exec_cmd_recur(data);
		if (ret == 1)
			exit(EXIT_FAILURE);
		printf("%s ->Child End(child = %d) (getpid = %d)\n", __func__, pid_p, getpid());
	}
	else
	{
		printf("%s ->DEBUG***** (father = %d)\n", __func__,pid_p);
		waitpid(pid_p, &status, 0);
		ft_putstr_fd("*********************************************************************************", 2);
	}
	ret == 1 ? ft_putstr_fd("Un erreur c'est produite\n", 2) : 0;
	printf("%s ->Father End(child = %d) (getpid = %d)\n", __func__, pid_p, getpid());
	return (EXIT_SUCCESS);
}
