/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_access.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/16 11:47:26 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:01:26 by volivry     ###    #+. /#+    ###.fr     */
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
