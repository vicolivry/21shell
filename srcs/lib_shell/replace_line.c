/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   replace_line.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 10:35:11 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/23 10:57:37 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Remplace line par str
*/

int		replace_line(char **line, char *str)
{
	if (*line == NULL || str == NULL)
		return (0);
	ft_strdel(line);
	if (!(*line = ft_strdup(str)))
		return (1);
	return (0);
}
