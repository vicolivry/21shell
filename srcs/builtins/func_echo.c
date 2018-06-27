/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_echo.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 13:22:07 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:18:01 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Special cmd echo
*/

static int		ft_echo_path(char *line, t_struct *data)
{
	if (ft_strcmp(line, "echo ~") == 0)
	{
		ft_putendl(data->home);
		return (1);
	}
	if (ft_strcmp(line, "echo ~+") == 0)
	{
		ft_putendl(data->pwd);
		return (1);
	}
	if (ft_strcmp(line, "echo ~-") == 0)
	{
		ft_putendl(data->oldpwd);
		return (1);
	}
	if (ft_strcmp(line, "echo -n") == 0)
		return (1);
	return (0);
}

/*
**	Check options -n/-e/-ne/-en in line
*/

static int		ft_check_option(char *line, int n_or_e)
{
	char	**tabl;
	int		ret;

	ret = 0;
	tabl = ft_strsplit(line, ' ');
	if (ft_len_tab(tabl) >= 2)
	{
		if (ft_strcmp(tabl[1], "-n") == 0 && n_or_e == 0)
			ret = 1;
		else if (ft_strcmp(tabl[1], "-ne") == 0 && n_or_e == 0)
			ret = 2;
		else if (ft_strcmp(tabl[1], "-en") == 0 && n_or_e == 0)
			ret = 2;
		else if (ft_strcmp(tabl[1], "-e") == 0 && n_or_e == 1)
			ret = 1;
	}
	ft_del_tab(tabl);
	return (ret);
}

/*
**	Core echo
*/

int				func_echo(char **line, t_struct *data)
{
	char	*str;
	int		i;
	int		tiret_n;
	int		tiret_e;

	str = NULL;
	i = 0;
	if (ft_echo_path(*line, data) == 1)
		return (0);
	tiret_n = ft_check_option(*line, 0);
	tiret_e = ft_check_option(*line, 1);
	if (tiret_n == 0 && tiret_e == 0)
		str = ft_strsub(*line, 5, ft_strlen(*line) - 5);
	else
	{
		if (tiret_n == 1 || tiret_e == 1)
			str = ft_strsub(*line, 8, ft_strlen(*line) - 8);
		else if (tiret_n == 2)
			str = ft_strsub(*line, 9, ft_strlen(*line) - 9);
	}
	if (str)
		ft_print_echo(str, data, 0);
	option_echo(tiret_n, data);
	ft_strdel(&str);
	return (0);
}
