/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_return_path.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 13:15:04 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/28 13:14:54 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  Return path in str
*/

char		*ft_return_path(char *str)
{
	char	*new;
	size_t	i;

	new = NULL;
	i = ft_strlen(str);
	while ((int)i >= 0)
	{
		if (str[i] == '/')
		{
			new = ft_strsub(str, 0, i);
			return (new);
		}
		i--;
	}
	new = ft_strdup(str);
	return (new);
}
