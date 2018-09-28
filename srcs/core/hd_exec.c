/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hd_exec.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 14:42:03 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 10:02:01 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

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

static char		*return_path_heredoc(char *name)
{
	char	*path;
	char	*tmp;

	path = NULL;
	tmp = NULL;
	if (!(path = ft_strnew(255)))
		return (NULL);
	getcwd(path, 255);
	if (!(tmp = ft_strjoin(path, "/")))
		return (NULL);
	ft_strdel(&path);
	clear_line(&name);
	if (!(path = ft_strjoin(tmp, name)))
		return (NULL);
	return (name);
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
		return (1);
	ft_strdel(&path);
	dup2(fd, lst->stdin_cmd);
	close(fd);
	status = execve(lst->rep, lst->tab_cmd, lst->env);
	return (status);
}

static int		heredoc_exec(t_cmd *lst, char *file)
{
	int		i;
	int		fd;
	int		status;

	i = 0;
	status = 0;
	if (file == NULL)
		return (1);
	if ((fd = open(file, O_CREAT | O_WRONLY | O_WRONLY, S_IRUSR
	| S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		return (1);
	while (lst->heredoc[i])
	{
		write(fd, lst->heredoc[i], ft_strlen(lst->heredoc[i]));
		write(fd, "\n", 2);
		i++;
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
	if (lst->op_next == 4)
		ret = heredoc_simple_exec(lst, 0);
	else
		ret = heredoc_exec(lst, "./.heredoc_42sh_tmp");
	return (ret);
}
