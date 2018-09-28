/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_unsetenv.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 13:22:42 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/28 13:29:56 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		ft_check_error_unsetenv(t_cmd **lst)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*lst)->tab_cmd[i])
		i++;
	if (i != 2)
	{
		ft_putstr_fd("unsetenv: Invalid format\n", (*lst)->stderr_cmd);
		return (1);
	}
	while ((*lst)->tab_cmd[1][j])
	{
		(*lst)->tab_cmd[1][j] = ft_toupper((*lst)->tab_cmd[1][j]);
		j++;
	}
	return (0);
}

static int		delete_in_env(t_struct **data, int i, int j)
{
	int		x;
	char	**new;

	j = 0;
	x = 0;
	new = NULL;
	while ((*data)->env[j])
		j++;
	if (!(new = (char **)malloc(sizeof(char *) * (j))))
		return (1);
	new[j - 1] = NULL;
	j = 0;
	while ((*data)->env[j])
	{
		if (j != i)
		{
			new[x] = ft_strdup((*data)->env[j]);
			x++;
		}
		j++;
	}
	(*data)->env = ft_del_tab((*data)->env);
	(*data)->env = ft_duplicate_tab(new);
	new = ft_del_tab(new);
	return (0);
}

static int		verif_unset(t_struct *data, char *str, int i)
{
	int		len;
	int		len2;

	len = ft_strlen(data->env[i]);
	len2 = ft_strlen(str);
	if (len > len2)
	{
		if (data->env[i][len2] == '=')
			return (0);
	}
	return (1);
}

int				func_unsetenv(t_struct **data, t_cmd *lst)
{
	int		i;

	i = 0;
	if (ft_check_error_unsetenv(&lst) == 1)
		return (1);
	while ((*data)->env[i])
	{
		if ((ft_strncmp((*data)->env[i], lst->tab_cmd[1],
	ft_strlen(lst->tab_cmd[1])) == 0) &&
	verif_unset(*data, lst->tab_cmd[1], i) == 0)
		{
			delete_in_env(data, i, 0);
			if (ft_strncmp(lst->tab_cmd[1], "PATH", 4) == 0)
			{
				(*data)->tab_hash = delete_tab_hash((*data)->tab_hash,
	(*data)->sizemax);
				(*data)->sizemax = 0;
			}
			return (0);
		}
		i++;
	}
	ft_putstr_fd("unsetenv: pattern not found\n", lst->stderr_cmd);
	return (1);
}
