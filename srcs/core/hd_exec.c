/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hd_exec.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 14:42:03 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:46:22 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Execution heredoc
*/

int				check_validity_heredoc(t_cmd *lst)
{
	char	*path;
	int		ret;

	path = NULL;
	ret = 0;
	if (lst->redir_heredoc == 0 || lst->heredoc == NULL)
		return (0);
	path = return_path_heredoc(lst->heredoc[0]);
	if (open(path, O_RDONLY) < 0)
	{
		ret = 1;
		basic_error(lst->heredoc[0], ": No such file or directory");
	}
	ft_strdel(&path);
	return (ret);
}

int				delete_tmp(char **file)
{
	int		fd;
	int		pid;

	fd = 0;
	pid = 0;
	if ((fd = open(file[1], O_RDONLY)) < 0)
		return (0);
	close(fd);
	if ((pid = fork()) < 0)
		return (1);
	if (pid == 0)
		execve("/bin/rm", file, NULL);
	else
		wait(&pid);
	return (0);
}

static int		heredoc_simple_exec(t_cmd *lst, int i)
{
	int		fd;
	int		status;
	char	*path;

	path = NULL;
	if (!(path = return_path_heredoc(lst->heredoc[i])))
		return (1);
	if ((fd = open(path, O_RDONLY)) < 0)
	{
		basic_error(lst->heredoc[i], ": No such file or directory");
		ft_strdel(&path);
		return (1);
	}
	ft_strdel(&path);
	dup2(fd, lst->stdin_cmd);
	close(fd);
	status = execve(lst->rep, lst->tab_cmd, lst->env);
	exit(status);
}

static int		heredoc_exec(t_cmd *lst, char *file)
{
	int		i;
	int		fd;
	int		status;

	i = 0;
	status = 0;
	if ((fd = open(file, O_CREAT | O_WRONLY | O_WRONLY, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		return (1);
	if (lst->heredoc_str != NULL)
	{
		write(fd, lst->heredoc_str, ft_strlen(lst->heredoc_str));
		write(fd, "\n", ft_strlen("\n"));
	}
	close(fd);
	if ((fd = open(file, O_RDONLY)) < 0)
		return (1);
	dup2(fd, lst->stdin_cmd);
	close(fd);
	status = execve(lst->rep, lst->tab_cmd, lst->env);
	return (status);
}

int				fork_heredoc(t_cmd *lst, int code)
{
	int		ret;
	char	**delete;

	delete = NULL;
	ret = 0;
	if (code == 1)
	{
		if (!(delete = (char **)malloc(sizeof(char *) * 3)))
			return (1);
		delete[0] = ft_strdup("rm");
		delete[1] = ft_strdup("./.heredoc_42sh_tmp");
		delete[2] = NULL;
		delete_tmp(delete);
		delete = ft_del_tab(delete);
		return (0);
	}
	if (!(lst))
		return (1);
	if (lst->op_next == 4 || lst->heredoc != NULL)
		ret = heredoc_simple_exec(lst, 0);
	else
		ret = heredoc_exec(lst, "./.heredoc_42sh_tmp");
	exit(ret);
}
