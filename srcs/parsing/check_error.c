/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_error.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 09:43:18 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/27 14:11:12 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Check si on a des regex d'erreur
*/

static int	print_error(char *str)
{
	if (ft_strstr(str, "\"") == NULL && ft_strstr(str, "><"))
		return (1);
	return (0);
}

int			check_error_inlinesplit(t_ins **lst)
{
	t_ins	*cpy;

	cpy = *lst;
	while (cpy)
	{
		if (print_error(cpy->str) == 1)
			return (1);
		cpy = cpy->next;
	}
	return (0);
}
