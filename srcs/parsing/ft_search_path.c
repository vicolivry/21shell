/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_search_path.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 11:18:28 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/25 14:32:32 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	On cherche l'executable dans la table de hashage
*/

static int			return_hash(char *str, int max)
{
	int		hash;
	int		len;
	char	*tmp;

	tmp = NULL;
	len = ft_strlen(str);
	if (ft_strstr(str, "/") != NULL)
	{
		while (str[len] != '/')
			len--;
		tmp = ft_strsub(str, len + 1, ft_strlen(str) - (len + 1));
		hash = ft_calcul_hash(tmp, max);
		ft_strdel(&tmp);
	}
	else
		hash = ft_calcul_hash(str, max);
	return (hash);
}

static int			ft_cmpforhash(char *rep, char *str)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = 0;
	if (ft_strcmp(rep, str) == 0)
		return (0);
	else if (ft_strstr(str, "/") != NULL)
	{
		len = ft_strlen(str);
		while (str[len] != '/' && len > 0)
			len--;
		tmp = ft_strsub(str, len + 1, ft_strlen(str) - (len + 1));
		if (ft_strcmp(rep, tmp) == 0)
		{
			ft_strdel(&tmp);
			return (0);
		}
		ft_strdel(&tmp);
	}
	return (1);
}

char				*ft_search_path(char *str, t_struct *data)
{
	int			hash;
	char		*retour;
	t_infos		*rep;

	rep = NULL;
	retour = NULL;
	hash = return_hash(str, data->sizemax);
	if (data->tab_hash[hash][0] == 0)
		return (NULL);
	else
	{
		rep = (t_infos *)data->tab_hash[hash][1];
		while (rep)
		{
			if (ft_cmpforhash(rep->name, str) == 0)
			{
				retour = ft_strdup(rep->repname);
				return (retour);
			}
			rep = rep->next;
		}
	}
	return (NULL);
}
