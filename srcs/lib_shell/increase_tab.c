/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   increase_tab.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 15:19:04 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 15:19:32 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  Augmente de 1 la taille du tableau
*/

int			increase_tab(char ***tabl)
{
	char	**cpy;
	int		size;
	int		i;

	cpy = NULL;
	size = ft_len_tab((*tabl));
	i = 0;
	cpy = ft_duplicate_tab((*tabl));
	(*tabl) = ft_del_tab(*tabl);
	(*tabl) = (char **)malloc(sizeof(char *) * (size + 2));
	while (i != (size + 1))
	{
		if (cpy[i] != NULL)
			(*tabl)[i] = ft_strdup(cpy[i]);
		else
			(*tabl)[i] = NULL;
		i++;
	}
	(*tabl)[size + 1] = NULL;
	cpy = ft_del_tab(cpy);
	return (0);
}
