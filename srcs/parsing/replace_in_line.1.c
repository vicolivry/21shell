/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   replace_in_line.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 11:40:00 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 16:11:52 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  remplace ~ et $ dans line
**	Appeler dans check_validity
*/

static char		*replace_suite(t_struct *data, char *line)
{
	return (NULL);
}

int				replace_in_line(t_struct *data, char **line)
{
	char	*tmp;

	tmp = NULL;
	if (*line == NULL || ft_strlen(*line) < 1)
		return (1);
	if (ft_strstr(*line, "~") == NULL || ft_strstr(*line, "$") == NULL)
		return (0);
	if (!(tmp = ft_strdup(*line)))
		return (1);
	tmp = replace_suite(data, *line);
	if (tmp != NULL)
	{
		ft_strdel(line);
		*line = ft_strdup(tmp);
	}
	ft_strdel(&tmp);
	return (0);
}
