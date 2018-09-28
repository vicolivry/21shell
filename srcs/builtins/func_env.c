/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_env.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 13:22:16 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 11:18:49 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Print env ou execute commande avec env modifier
*/

static int		print_env(t_struct *data, t_cmd *lst, int i, int opt)
{
	int		j;
	int		ret;

	j = i;
	ret = 0;
	while (lst->tab_cmd[j])
	{
		if (ft_strstr(lst->tab_cmd[j], "=") == NULL && lst->tab_cmd[j] != NULL)
		{
			ret = execute_var_modif(data, &lst, i, opt);
			return (ret);
		}
		j++;
	}
	if (opt == 0)
		ft_print_tab_spe(data->env, lst->tab_cmd, i);
	while (lst->tab_cmd[i])
	{
		ft_putendl(lst->tab_cmd[i]);
		i++;
	}
	return (0);
}

/*
**	Suite env
*/

static int		func_env_suite(t_struct **data, t_cmd *lst, int i, int opt)
{
	int		hash;
	int		ret;

	hash = 0;
	ret = 0;
	if (opt == 1 && lst->tab_cmd[i] == NULL)
		return (0);
	while (lst->tab_cmd[i])
	{
		hash = ft_calcul_hash(lst->tab_cmd[i], (*data)->sizemax);
		if (ft_is_func(*data, lst->tab_cmd[i], hash) == 0)
			return (execute_with_env(data, lst, i, opt));
		if (ft_strstr(lst->tab_cmd[i], "=") != NULL)
			return (print_env(*data, lst, i, opt));
		else
		{
			ft_error_dir("env: ", lst->tab_cmd[i], lst->stderr_cmd);
			return (1);
		}
		i++;
	}
	return (1);
}

/*
**	Core env
*/

static int		suite_func_env(char *str, int *i)
{
	int		option_i;

	option_i = 0;
	if (str == NULL)
		return (option_i);
	if (ft_strcmp(str, "-i") == 0)
	{
		option_i = 1;
		*i = *i + 1;
	}
	return (option_i);
}

int				func_env(t_struct *data, t_cmd **lst)
{
	int		i;
	int		ret;
	int		option_i;
	int		exit;

	i = 0;
	ret = 0;
	option_i = 0;
	exit = 0;
	while (exit == 0)
	{
		if ((*lst)->tab_cmd[i] == NULL)
		{
			ft_print_tab(data->env);
			return (0);
		}
		else if (ft_strcmp((*lst)->tab_cmd[i], "env") != 0)
			exit = 1;
		else
			i++;
	}
	if ((option_i = suite_func_env((*lst)->tab_cmd[i], &i)) == 1)
		(*lst)->env = ft_del_tab((*lst)->env);
	ret = func_env_suite(&data, *lst, i, option_i);
	return (ret);
}
