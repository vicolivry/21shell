/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   split_echo.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/17 14:38:34 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 15:16:55 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		return_i(int i, char *str, char c)
{
	if (!(str))
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

static char		*split_echo_suite(char *str, int i)
{
	char	*tmp;

	tmp = NULL;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			tmp = ft_strsub(str, 0, i);
			return (tmp);
		}
		else if (str[i] == '\'')
		{
			i = return_i(i + 1, str, '\'');
			tmp = ft_strsub(str, 0, i + 1);
			return (tmp);
		}
		else if (str[i] == '\"')
		{
			i = return_i(i + 1, str, '\"');
			if (i == ft_strlen(str))
				tmp = ft_strdup(str);
			else
				tmp = ft_strsub(str, 0, i + 1);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

static char		*clear_quote_echo(char **str)
{
	int		i;
	char	**tmp;
	char	*cpy;

	i = 0;
	tmp = NULL;
	cpy = NULL;
	if (*str == NULL)
		return (NULL);
	if (ft_strlen(*str) == 0)
	{
		ft_strdel(str);
		return (NULL);
	}
	if (ft_strstr(*str, "\'") == NULL && ft_strstr(*str, "\"") == NULL)
	{
		tmp = ft_strsplit(*str, ' ');
		cpy = ft_strdup(tmp[0]);
		resize_str_echo(str, ft_strlen(cpy), ft_strlen(*str) - ft_strlen(cpy));
		tmp = ft_del_tab(tmp);
		return (cpy);
	}
	cpy = split_echo_suite(*str, i);
	resize_str_echo(str, ft_strlen(cpy), ft_strlen(*str) - ft_strlen(cpy));
	return (cpy);
}

static int		check_split_echo(char ***tabl, char *str, int len)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 1;
	(*tabl)[0] = ft_strdup("echo");
	(*tabl)[1] = ft_strsub(str, 5, ft_strlen(str) - 5);
	tmp = NULL;
	tmp2 = NULL;
	while ((*tabl)[i] && i < len)
	{
		clear_line(&(*tabl)[i]);
		tmp = clear_quote_echo(&(*tabl)[i]);
		tmp2 = ft_strdup((*tabl)[i]);
		if (tmp != NULL)
		{
			ft_strdel(&(*tabl)[i]);
			(*tabl)[i] = ft_strdup(tmp);
			(*tabl)[i + 1] = ft_strdup(tmp2);
		}
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
		i++;
	}
	return (0);
}

/*
**	Appleler via insert_cmd_simple.c
*/

// segfault quand echo"test"
char			**split_echo(char *str)
{
	int		i;
	int		j;
	char	**new;
	char	**tmp;

	i = 0;
	j = 0;
	new = NULL;
	tmp = NULL;
	if (ft_strstr(str, "\"") == NULL && ft_strstr(str, "\'") == NULL)
	{
		new = ft_strsplit(str, ' ');
		return (new);
	}
	tmp = ft_strsplit(str, ' ');
	i = ft_len_tab(tmp);
	tmp = ft_del_tab(tmp);
	if (!(new = (char **)malloc(sizeof(char *) * i)))
		return (NULL);
	while (j < i)
		new[j++] = NULL;
	check_split_echo(&new, str, i);
	return (new);
}
