/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   good_func.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 11:20:03 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:21:19 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	start good function (for builtins)
*/

static int		ft_search_func(char **line, t_struct *data, int i)
{
	if (i == 0)
		func_cd(line, data);
	else if (i == 1)
		func_echo(line, data);
	else if (i == 2)
		data->env = func_setenv(line, data);
	else if (i == 3)
		data->env = func_unsetenv(line, data);
	else if (i == 4)
		func_env(line, data);
	return (0);
}

/*
**	Search if commande is a builtins
*/

int				ft_builtins(char **line, t_struct *data)
{
	char	**tabl;
	int		i;
	int		ret;

	tabl = ft_strsplit(*line, ' ');
	i = 0;
	ret = 1;
	while (data->builtins[i])
	{
		if (ft_strcmp(tabl[0], data->builtins[i]) == 0)
		{
			ft_search_func(line, data, i);
			ret = 0;
		}
		i++;
	}
	ft_del_tab(tabl);
	if (data->tab_path == NULL && ret == 1)
	{
		ft_error(1, line);
		return (0);
	}
	return (ret);
}
