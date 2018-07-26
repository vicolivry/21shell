/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_existe_in_path.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/25 13:41:48 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 11:58:14 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int			ft_existe_in_path(t_struct *data, char **path)
{
	char	*pat;
	int		i;

	pat = ft_return_path(*path);
	i = 0;
	while (data->tab_path[i])
	{
		if (ft_strcmp(data->tab_path[i], pat) == 0)
		{
			ft_strdel(&pat);
			return (1);
		}
		i++;
	}
	ft_strdel(&pat);
	return (0);
}
