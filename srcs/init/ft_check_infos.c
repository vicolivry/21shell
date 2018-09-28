/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_check_infos.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 12:57:34 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:59:31 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Take infos in Env
*/

char		*ft_check_infos(char **env, char *find)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	if (env == NULL || find == NULL)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], find, ft_strlen(find)) == 0)
		{
			path = ft_strdup(env[i]);
			return (path);
		}
		i++;
	}
	ft_strdel(&path);
	return (NULL);
}
