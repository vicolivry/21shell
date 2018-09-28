/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   split_cmd.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 12:12:16 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/27 10:55:09 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		clear_quote_deux(char *tmp, int i, int j)
{
	if (tmp[i] == '\"' && j > i)
	{
		while (tmp[j] && (tmp[j] != '\"' && tmp[j - 1] != '\\'))
			j++;
		if (tmp[j] != '\"')
			return (0);
		return (j);
	}
	else if (tmp[i] == '\'' && j > i)
	{
		while (tmp[j] && (tmp[j] != '\'' && tmp[j - 1] != '\\'))
			j++;
		if (tmp[j] != '\'')
			return (0);
		return (j);
	}
	return (0);
}

static int		clear_quote(char **str, int i)
{
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strdup(*str);
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
		{
			j = i + 1;
			j = clear_quote_deux(tmp, i, j);
			if (j != 0)
			{
				clear_string(str, i, 0);
				clear_string(str, j, 1);
				ft_strdel(&tmp);
				i = j - 2;
				tmp = ft_strdup(*str);
			}
		}
		i++;
	}
	ft_strdel(&tmp);
	return (0);
}

char			**split_cmd(char *str, int i)
{
	char		**new;

	new = ft_strsplit(str, ' ');
	while (new[i])
	{
		if (ft_strstr(new[i], "\"") != NULL || ft_strstr(new[i], "\'") != NULL)
			clear_quote(&new[i], 0);
		i++;
	}
	return (new);
}
