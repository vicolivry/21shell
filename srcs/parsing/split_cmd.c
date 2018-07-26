/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   split_cmd.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 12:12:16 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 15:52:12 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		clear_string(char **str, int delete, int opt)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	if (delete == 0)
	{
		tmp1 = ft_strsub(*str, 1, ft_strlen(*str) - 1);
		ft_strdel(str);
		*str = ft_strdup(tmp1);
	}
	else if (delete == ft_strlen(*str) || delete == ft_strlen(*str) - 1)
	{
		tmp1 = ft_strsub(*str, 0, ft_strlen(*str) - 1);
		ft_strdel(str);
		*str = ft_strdup(tmp1);
	}
	else
	{
		if (opt == 1)
		{
			tmp1 = ft_strsub(*str, 0, delete - 1);
			tmp2 = ft_strsub(*str, delete, ft_strlen(*str) - (delete));
		}
		else
		{
			tmp1 = ft_strsub(*str, 0, delete);
			tmp2 = ft_strsub(*str, delete + 1, ft_strlen(*str) - (delete + 1));
		}
		ft_strdel(str);
		*str = ft_strjoin(tmp1, tmp2);
	}
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (0);
}

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

static int		clear_quote(char **str)
{
	int		i;
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
        	clear_quote(&new[i]);
		i++;
	}
	return (new);
}
