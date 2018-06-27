/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_env_print.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/11 15:17:53 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:20:21 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Print all env
*/

void		print_full_env(t_struct *data)
{
	int		i;

	i = 0;
	if (data->env == NULL)
		return ;
	while (data->env[i])
	{
		ft_putendl(data->env[i]);
		i++;
	}
}

/*
**	Print usage
*/

void		ft_print_usage(char *str)
{
	ft_putstr("env: illegal option -- ");
	ft_putendl(ft_strstr(str, "-i") + 1);
	ft_putstr("env [-i] [name=value]... [utility [argument...]]\n");
}

/*
**	return 0 if option -i illiegal
*/

int			ft_option_i(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == 'i')
			i++;
		else
			return (0);
	}
	return (1);
}

/*
**	Execute commande env
*/

int			ft_env_cmd(t_struct *data, char **tabl, int i, int x)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	tmp = ft_strjoin(data->tab_path[x], "/");
	tmp2 = ft_strjoin(tmp, tabl[i]);
	tabl = ft_del_tab_index(tabl, i);
	//ft_process(tmp2, tab, data->env_tmp);
	execute_commandes(data);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	data->env_tmp = ft_del_tab(data->env_tmp);
	return (0);
}

/*
**	Execute rep
*/

int			ft_env_rep(t_struct *data, char **tabl, int i)
{
	char	*path;
	char	*cmd;

	path = ft_return_path(tabl[i]);
	cmd = ft_strdup(tabl[i] + ft_strlen(path) + 1);
	ft_del_tab_index(tabl, i);
	i = 0;
	if (good_path(tabl[0], cmd, 1) == 1)
	{
		ft_strdel(&path);
		path = ft_strdup(tabl[0]);
		ft_strdel(&tabl[0]);
		tabl[0] = ft_strdup(cmd);
		//ft_process(path, tab, data->env_tmp);
		execute_commandes(data);
	}
	ft_strdel(&path);
	ft_strdel(&cmd);
	return (0);
}
