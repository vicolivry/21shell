/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_access.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/16 11:47:26 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/21 16:36:48 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Check access or not (cmd cd)
*/

int		ft_access(char *path)
{
	if (access(path, F_OK))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file of directory\n", 2);
		return (-1);
	}
	if (access(path, R_OK))
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (0);
}

/*
**	mode = 0 -> F_OK
**	mode = 1 -> R_OK
**	mode = 2 -> W_OK
**	mode = 3 -> X_OK
*/

int		ft_access_rep(char *path, int mode)
{
	if (mode == 0)
	{
		if (access(path, F_OK) == 0)
			return (0);
	}
	else if (mode == 1)
	{
		if (access(path, R_OK) == 0)
			return (0);
	}
	else if (mode == 2)
	{
		if (access(path, W_OK) == 0)
			return (0);
	}
	else if (mode == 3)
	{
		if (access(path, X_OK) == 0)
			return (0);
	}
	return (1);
}
