/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_add_line.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 09:30:03 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 11:43:07 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Add commande in end of path
*/

static char		*ft_cmp_path(char *str, char **add, t_struct *data)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = ft_strlen(*add);
	tmp = ft_strdup(*add);
	tmp2 = NULL;
	while (i > 0 && tmp[i] != '/')
		i--;
	ft_strdel(&tmp);
	tmp = ft_strsub(*add, 0, i);
	if (ft_strcmp(tmp, str) == 0)
	{
		ft_strdel(&tmp);
		tmp = ft_strdup(*add);
		ft_strdel(add);
		*add = ft_strsub(tmp, i + 1, (ft_strlen(tmp) - i - 1));
		return (tmp);
	}
	ft_strdel(&tmp);
	tmp = ft_strjoin(data->pwd, "/");
	tmp2 = ft_strjoin(tmp, *add);
	ft_strdel(&tmp);
	return (tmp2);
}

char			*ft_add_line(char *str, char **add, t_struct *data)
{
	char	*tmp;
	char	*new;

	tmp = NULL;
	new = NULL;
	if (ft_strstr(*add, "/") != NULL)
	{
		new = ft_cmp_path(str, add, data);
		if (new == NULL)
			new = ft_strjoin(str, *add);
		return (new);
	}
	tmp = ft_strjoin(str, "/");
	new = ft_strjoin(tmp, *add);
	ft_strdel(&tmp);
	return (new);
}
