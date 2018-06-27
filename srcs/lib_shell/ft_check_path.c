/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_check_path.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 10:42:59 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 11:56:11 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  ft_check_path : check on string if ./ or ~/ and replace
*/

static void		ft_replace_tild(t_struct *data, char **path)
{
	char	*tmp;

	tmp = ft_strdup(*path);
	ft_strdel(path);
	*path = ft_strjoin(data->home, tmp + 2);
	ft_strdel(&tmp);
}

static void		ft_replace_path(t_struct *data, char **path)
{
	char	*tmp;

	tmp = ft_strdup(*path);
	ft_strdel(path);
	*path = ft_strjoin(data->pwd, "/");
	tmp = ft_strjoin(*path, tmp);
	ft_strdel(path);
	*path = ft_strdup(tmp);
	ft_strdel(&tmp);
}

void			ft_check_path(t_struct *data, char **path)
{
	if (ft_strncmp(*path, "~/", 2) == 0)
		ft_replace_tild(data, path);
	else if (ft_strncmp(*path, "./", 2) == 0)
		ft_replace_path(data, path);
}
