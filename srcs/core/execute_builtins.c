/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute_builtins.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/11 09:36:12 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 12:13:20 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

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
			(void)pipe_fd;
			(void)fd_in;
			// Gestion des pipes et redirection a faire
			ret = ft_search_func(mystruct, lst, i);
			return (ret);
		}
		i++;
	}
	return (-1);
}

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
