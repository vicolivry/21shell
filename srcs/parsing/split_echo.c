/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   split_echo.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/17 14:38:34 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:54:08 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Split echo
*/

static int	echap_word(char *str, int i)
{
	if (str[i] == ' ' || str[i] == '\t')
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
	}
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (i);
		i++;
	}
	return (i);
}

static int	check_split_echo(char ***tabl, int index)
{
	int		i;
	int		t;
	int		len;
	char	*tmp;

	i = 0;
	t = index + 1;
	len = 0;
	tmp = NULL;
	i = echap_quote((*tabl)[index], i, 0);
	if (i == 0)
		i = echap_word((*tabl)[index], i);
	if (i + 1 < ft_strlen((*tabl)[index]))
	{
		increase_tab(tabl);
		tmp = ft_strsub((*tabl)[index], 0, i);
		len = ft_strlen((*tabl)[index]);
		(*tabl)[t] = ft_strsub((*tabl)[index], i + 1, len - (i + 1));
		clear_line(&(*tabl)[t]);
		ft_strdel(&(*tabl)[index]);
		(*tabl)[index] = ft_strdup(tmp);
		ft_strdel(&tmp);
		check_split_echo(tabl, index + 1);
	}
	return (0);
}

static int	return_start_echo(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (-1);
	if (ft_strstr(str, "echo") == NULL)
		return (-1);
	if (ft_strncmp(str, "echo ", 5) == 0)
		return (5);
	if (ft_strncmp(str, "echo\"", 5) == 0)
	{
		basic_error(str, " : command not found");
		return (-2);
	}
	while (str[i])
	{
		if (ft_strncmp(str + i, "echo ", 5) == 0)
			return (i + 5);
		i++;
	}
	return (-2);
}

/*
**	Appleler via insert_cmd_simple.c
*/

char		**split_echo(char *str)
{
	int		ret;
	int		j;
	char	**new;

	new = NULL;
	ret = 0;
	j = return_start_echo(str);
	if (ft_strstr(str, "\"") == NULL && ft_strstr(str, "\'") == NULL)
	{
		new = ft_strsplit(str, ' ');
		return (new);
	}
	if (j == -2)
		return (NULL);
	if (!(new = (char **)malloc(sizeof(char *) * 3)))
		return (NULL);
	new[0] = ft_strdup("echo");
	if (j != -1 && j != -2)
		new[1] = ft_strsub(str, j, ft_strlen(str) - j);
	else
		new[1] = ft_strsub(str, 5, ft_strlen(str) - 5);
	new[2] = NULL;
	if ((ret = check_split_echo(&new, 1)) == 1)
		return (NULL);
	return (new);
}
