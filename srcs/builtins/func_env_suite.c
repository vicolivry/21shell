/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_env_suite.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/25 13:36:26 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 10:54:14 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Execute une commande avec env modifier
*/

static int	ft_existe_in_env(char *str, char **env, int mode)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!(str) || !(env))
		return (1);
	while (str[len] && str[len] != '=')
		len++;
	if (mode == 0)
		len--;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, len) == 0)
		{
			if (mode == 1)
				return (i);
			return (0);
		}
		i++;
	}
	if (mode == 1)
		return (0);
	return (1);
}

static int	return_i_env(t_cmd *lst)
{
	int		i;

	i = 0;
	while (lst->tab_cmd[i] && (ft_strcmp(lst->tab_cmd[i], "env") == 0 ||
	ft_strcmp(lst->tab_cmd[i], "-i") == 0))
	{
		if (lst->tab_cmd[i] == NULL)
			return (i);
		i++;
	}
	return (i);
}

static int	cpy_env(t_struct *data, char ***str)
{
	int		j;

	j = 0;
	if (!(data->env) || !(*str))
		return (-1);
	while (data->env[j])
	{
		if (!((*str)[j] = ft_strdup(data->env[j])))
			return (-1);
		j++;
	}
	return (j);
}

int			malloc_for_env_suite(char ***str, t_struct *data, t_cmd *lst, int i)
{
	int		j;
	int		ret;

	ret = 0;
	if ((j = cpy_env(data, str)) == -1)
		return (1);
	i = return_i_env(lst);
	while (lst->tab_cmd[i] && ft_strstr(lst->tab_cmd[i], "=") != NULL)
	{
		if ((ret = ft_existe_in_env(lst->tab_cmd[i], data->env, 1)) != 0)
		{
			ft_strdel(&(*str)[ret]);
			if (!((*str)[ret] = ft_strdup(lst->tab_cmd[i])))
				return (1);
		}
		else
		{
			if (!((*str)[j] = ft_strdup(lst->tab_cmd[i])))
				return (1);
		}
		i++;
		j++;
	}
	return (0);
}

int			execute_var_modif(t_struct *data, t_cmd **lst, int i, int opt)
{
	int		j;
	int		backup_i;
	int		ret;
	char	**new;

	backup_i = i;
	ret = 0;
	j = 0;
	new = NULL;
	while ((*lst)->tab_cmd[i] && ft_strstr((*lst)->tab_cmd[i], "=") != NULL)
	{
		if (ft_existe_in_env((*lst)->tab_cmd[i], data->env, 0) == 1)
			j++;
		i++;
	}
	if (!(new = malloc_for_env(&data, lst, j, opt)))
		return (1);
	if (new != NULL)
	{
		(*lst)->env = ft_del_tab((*lst)->env);
		(*lst)->env = ft_duplicate_tab(new);
	}
	new = ft_del_tab(new);
	ret = execute_with_env(&data, *lst, i, 0);
	return (ret);
}
