/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   format_line.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/21 10:09:53 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:12:19 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	incremente i de la bonne valeur
*/

static int		ft_incremente_i(char *str, int i)
{
	int j;

	j = 0;
	if (str[i] == '\'')
	{
		while (str[i] != '\'')
		{
			if (i == ft_strlen(str))
				return (j);
			i++;
			j++;
		}
	}
	else if (str[i] == '\"')
	{
		while (str[i] != '\"')
		{
			if (i == ft_strlen(str))
				return (j);
			i++;
			j++;
		}
	}
	return (j);
}

/*
**	If epur = 1 -> no epur and return tab
**	Epur string ' or "
*/

char			**epur_tab(char *line, int epur)
{
	int		i;
	char	**tabl;
	char	*tmp;

	i = 0;
	tmp = NULL;
	tabl = ft_strsplit(line, ' ');
	if (epur == 1)
		return (tabl);
	while (tabl[i])
	{
		if ((tabl[i][0] == '\'' && tabl[i][ft_strlen(tabl[i]) - 1] == '\'') ||
	(tabl[i][0] == '\"' && tabl[i][ft_strlen(tabl[i]) - 1] == '\"'))
		{
			tmp = ft_strdup(tabl[i]);
			ft_strdel(&tabl[i]);
			tabl[i] = ft_strsub(tmp, 1, ft_strlen(tmp) - 2);
			ft_strdel(&tmp);
		}
		i++;
	}
	return (tabl);
}

/*
**	Insert good valeur (replace ~ or $)
*/

void			ft_check_line(t_struct *data, char **line, int i)
{
	char	*str;

	str = ft_strdup(*line);
	i = 0;
	while (str[i])
	{
		if (str[i] == '~')
			i += ft_insert_tild(data, &str, i);
		else if (str[i] == '$')
			i += ft_insert_dollar(data, &str, i);
		else if (str[i] == '\'' || str[i] == '\"')
			i += ft_incremente_i(str, i);
		i++;
	}
	ft_strdel(line);
	*line = ft_strdup(str);
	ft_strdel(&str);
}
