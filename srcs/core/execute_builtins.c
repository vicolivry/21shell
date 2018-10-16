/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute_builtins.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/11 09:36:12 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:45:05 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Execution des builtins piper ou rediriger
*/

static int	ft_dup(int *fd_in, int pipe_fd[2], t_cmd *lst)
{
	dup2(*fd_in, lst->stdin_cmd) == -1 ? basic_error("dup2", "failled") : 0;
	dup2(pipe_fd[1], lst->stdout_cmd) == -1 ?
	basic_error("dup2", "failled") : 0;
	close(pipe_fd[0]) == -1 ? basic_error("close", "failled") : 0;
	return (0);
}

int			execute_builtins(t_struct *mystruct, t_cmd *lst, int pipe_fd[2],
	int *fd_in)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (mystruct->builtins[i])
	{
		if (ft_strcmp(lst->tab_cmd[0], mystruct->builtins[i]) == 0)
		{
			if (lst->pathname != NULL)
			{
				clear_tab(&lst->tab_cmd);
				return (fork_redirection(lst));
			}
			if (lst->heredoc_activ == 1)
				exit(ft_search_func(mystruct, lst, i));
			ft_dup(fd_in, pipe_fd, lst);
			ret = ft_search_func(mystruct, lst, i);
			exit(ret);
		}
		i++;
	}
	return (-1);
}

/*
**	Execution des builtins sans fork
*/

int			execute_builtins_light(t_struct *mystruct, t_cmd *lst)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (mystruct->builtins[i])
	{
		if (ft_strcmp(lst->tab_cmd[0], mystruct->builtins[i]) == 0)
		{
			ret = ft_search_func(mystruct, lst, i);
			return (ret);
		}
		i++;
	}
	return (-2);
}
