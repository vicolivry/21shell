/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_del_tab.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 09:38:44 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 11:54:54 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Delete tab and return NULL
*/

char		**ft_del_tab(char **tabl)
{
	int		i;

	i = 0;
	if (tabl == NULL)
		return (NULL);
	while (tabl[i])
	{
		ft_strdel(&tabl[i]);
		i++;
	}
	free(tabl);
	tabl = NULL;
	return (NULL);
}

/*
**	Clean tab until int max and reposition tab
*/

char		**ft_del_tab_index(char **tabl, int max)
{
	int		i;
	int		len;

	if (tabl == NULL)
		return (NULL);
	i = 0;
	len = ft_len_tab(tabl);
	while (i <= len)
	{
		if (max < len)
		{
			ft_strdel(&tabl[i]);
			tabl[i] = ft_strdup(tabl[max]);
			ft_strdel(&tabl[max]);
			max++;
		}
		else
			ft_strdel(&tabl[i]);
		i++;
	}
	return (tabl);
}
