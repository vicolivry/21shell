/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hd_exec.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 14:42:03 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 11:36:15 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char	*path_heredoc(char *name, int i)
{
	char	*path;
	char	*tmp;

	path = NULL;
	tmp = NULL;
	if (!name)
		return (NULL);
	while (name[i] && (name[i] == ' ' || name[i] == '\t'))
		i++;
	if (name[i] == '/')
	{
		path = ft_strdup(name + i);
		return (path);
	}
	if (name[i] == '~')
	{
		if (g_data->home == NULL)
			return (NULL);
		tmp = ft_strdup(g_data->home);
		path = ft_strjoin(tmp, name + (i + 1));
		ft_strdel(&tmp);
		return (path);
	}
	return (NULL);
}

char		*return_path_heredoc(char *name)
{
	char	*path;
	char	*tmp;
	char	*cpy;

	path = NULL;
	tmp = NULL;
	cpy = NULL;
	if (!name)
		return (NULL);
	if ((path = path_heredoc(name, 0)) != NULL)
		return (path);
	if (!(path = ft_strnew(255)))
		return (NULL);
	getcwd(path, 255);
	if (!(tmp = ft_strjoin(path, "/")))
		return (NULL);
	ft_strdel(&path);
	cpy = ft_strdup(name);
	clear_line(&cpy);
	if (!(path = ft_strjoin(tmp, cpy)))
		return (NULL);
	ft_strdel(&cpy);
	ft_strdel(&tmp);
	return (path);
}
