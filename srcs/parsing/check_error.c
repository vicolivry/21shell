/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_error.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 09:43:18 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 12:53:27 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"


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
		printf("cpy->str = %s\n", cpy->str);
		if (print_error(cpy->str) == 1)
			return (1);
		cpy = cpy->next;
	}
	return (0);
}
