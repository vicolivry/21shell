/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_dir_exist.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 09:38:58 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 16:31:44 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Directory exist of not
*/

int			ft_stat(char *path)
{
	struct stat		buff;

	if (lstat(path, &buff) == -1)
	{
		return (1);
	}
	return (0);
}

int			ft_dir_exist(char *path)
{
	DIR		*dir;

	dir = opendir(path);
	if (dir == NULL)
		return (0);
	closedir(dir);
	return (1);
}
