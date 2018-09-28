/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   split_echo_suite.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/21 10:49:44 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 11:05:07 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int			resize_str_echo(char **str, int start, int len)
{
	char	*tmp;

	tmp = NULL;
	if (!(tmp = ft_strdup(*str)))
		return (1);
	ft_strdel(str);
	*str = ft_strsub(tmp, start, len);
	ft_strdel(&tmp);
	return (0);
}

static int	check_line_echo(char **str)
{
	char	*tmp;
	char	*cpy;

	tmp = NULL;
	cpy = NULL;
	cpy = ft_strdup(*str);
	if (cpy[0] == '\"' && cpy[ft_strlen(*str) - 1] == '\"')
	{
		tmp = ft_strsub(*str, 1, ft_strlen(*str) - 2);
		ft_strdel(str);
		*str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	ft_strdel(&cpy);
	return (0);
}

int			clear_echo(char ***tabl)
{
	int		i;

	i = 0;
	if (!(*tabl))
		return (1);
	while ((*tabl)[i])
	{
		if ((*tabl)[i] != NULL)
			check_line_echo(&(*tabl)[i]);
		i++;
	}
	return (0);
}
