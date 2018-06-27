/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_env.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 13:22:16 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:19:36 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Check if commande existe int dir data->tab_path and return index
*/

static int		ft_is_commande(t_struct *data, char *str)
{
	int		i;

	i = 0;
	while (data->tab_path[i])
	{
		if (good_path(data->tab_path[i], str, 0) == 1)
			return (i);
		i++;
	}
	return (-1);
}

/*
**	Call good func if cmd, rep, variable ... of print error
*/

static void		ft_env_suite(t_struct *data, char **tabl, int i, int x)
{
	while (tabl[i])
	{
		if ((x = ft_is_commande(data, tabl[i])) != -1)
		{
			ft_env_cmd(data, tabl, i, x);
			return ;
		}
		else if (tabl[i][0] == '/' || tabl[i][0] == '.')
		{
			ft_env_rep(data, tabl, i);
			return ;
		}
		else if (ft_strstr(tabl[i], "=") != NULL)
		{
			data->env_tmp = ft_insert_in_tab(data->env_tmp, tabl[i]);
		}
		else
		{
			ft_error_dir("env : ", tabl[i]);
			return ;
		}
		i++;
	}
	ft_print_tab(data->env_tmp);
}

/*
**	Check if tab[i] is NULL or if option -i is ok
**	if needed, print usage or go ft_env_suite
*/

static void		ft_env(t_struct *data, char **tabl, int i)
{
	while (tabl[i])
	{
		if (tabl[i] == NULL)
			return ;
		else if (ft_option_i(tabl[i]) == 1)
			data->option_i_env = 1;
		else if (ft_strcmp(tabl[i], "env") != 0)
		{
			if (tabl[i][0] == '-')
				ft_print_usage(tabl[i]);
			else
			{
				if (data->option_i_env == 0)
					data->env_tmp = ft_duplicate_tab(data->env);
				ft_env_suite(data, tabl, i, 0);
			}
			return ;
		}
		i++;
	}
}

/*
**	Core env
*/

void			func_env(char **line, t_struct *data)
{
	char	**tabl;
	int		i;

	tabl = NULL;
	i = 0;
	data->option_i_env = 0;
	data->env_tmp = ft_del_tab(data->env_tmp);
	ft_check_line(data, line, 0);
	tabl = ft_strsplit(*line, ' ');
	while (tabl[i] && (ft_strcmp(tabl[i], "env") == 0 ||
	ft_strcmp(tabl[i], "/usr/bin/env") == 0))
		i++;
	if (ft_len_tab(tabl) == i)
	{
		ft_del_tab(tabl);
		print_full_env(data);
		return ;
	}
	ft_env(data, tabl, i);
	tabl = ft_del_tab(tabl);
	data->env_tmp = ft_del_tab(data->env_tmp);
}
