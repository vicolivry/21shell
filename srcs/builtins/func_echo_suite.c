/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_echo_suite.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 13:22:07 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:18:22 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	if option -n > print %\n
*/

void		option_echo(int j, t_struct *data)
{
	if (j == 0)
		ft_putchar('\n');
	else
	{
		if (data->option_echo == 0)
			ft_putendl("\033[7m%\033[0m");
	}
}

/*
**	Print special char
*/

int			ft_print_special(char *str, int i, int len)
{
	if (i >= len)
		return (0);
	if (str[i] == '\\' && (str[i + 1] == 'n' || str[i + 1] == 't' ||
				str[i + 1] == 'a' || str[i + 1] == 'v' || str[i + 1] == 'f'))
	{
		if (str[i + 1] == 'n')
			ft_putstr("\n");
		else if (str[i + 1] == 't')
			ft_putstr("\t");
		else if (str[i + 1] == 'a')
			ft_putstr("\a");
		else if (str[i + 1] == 'v')
			ft_putstr("\v");
		else if (str[i + 1] == 'f')
			ft_putstr("\f");
		return (2);
	}
	return (0);
}

/*
**	print good line in env if exist
*/

static int	ft_search_env_suite(char *str, int i)
{
	int quit;

	quit = 0;
	while (quit == 0)
	{
		if (str[i] == '\t' || str[i] == ' ' || str[i] == '\n' ||
	str[i] == '\r' || str[i] == '\f' || str[i] == '\v' ||
	str[i] == '\0' || str[i] == '\"' || str[i] == '\'')
			quit = 1;
		else
			i++;
	}
	return (i);
}

int			ft_search_env(char *str, int i, t_struct *data, int i2)
{
	char	*search;

	i2 = i;
	i = ft_search_env_suite(str, i);
	search = ft_strsub(str, i2 + 1, (i - i2 - 1));
	i2 = 0;
	if (data->env != NULL && search != NULL)
	{
		while (data->env[i2])
		{
			if (ft_strncmp(data->env[i2], search, ft_strlen(search)) == 0)
			{
				ft_putstr(data->env[i2] + (ft_strlen(search) + 1));
				i2 = ft_strlen(search);
				ft_strdel(&search);
				data->option_echo = 0;
				return (i2 + 1);
			}
			i2++;
		}
	}
	i2 = ft_strlen(search);
	ft_strdel(&search);
	data->option_echo = 1;
	return (i2 + 1);
}
