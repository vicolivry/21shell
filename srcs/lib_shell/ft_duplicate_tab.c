/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_duplicate_tab.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/26 11:24:31 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 16:23:33 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  Duplicate tab and return tab
*/

char		**ft_duplicate_tab(char **tabl)
{
	char	**new;
	int		len;
	int		i;

	new = NULL;
	if (tabl == NULL)
		return (NULL);
	len = ft_len_tab(tabl);
	i = 0;
	if (!(new = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (tabl[i])
	{
		new[i] = ft_strdup(tabl[i]);
		i++;
	}
	new[len] = NULL;
	return (new);
}
