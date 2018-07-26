/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   epur_line_suite.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 11:14:22 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 11:21:15 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Supprime les espaces avant
*/

char		*clean_before(char *str)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	new = ft_strsub(str, i, ft_strlen(str) - i);
	return (new);
}

/*
**	Supprime les espaces apres
*/

char		*clean_next(char *str)
{
	int		i;
	char	*new;

	i = ft_strlen(str) - 1;
	new = NULL;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	new = ft_strsub(str, 0, i + 1);
	return (new);
}
