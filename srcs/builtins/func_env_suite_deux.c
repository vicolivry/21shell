/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_env_suite_deux.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 15:31:53 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 11:17:44 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**      Check si str et hash son valide
*/

int				ft_is_func(t_struct *data, char *str, int hash)
{
	char	*tmp;

	tmp = NULL;
	if (!(data->tab_hash) || hash == 0 || !(str))
		return (1);
	if (data->tab_hash[hash] != 0)
	{
		tmp = ft_search_path(str, data);
		if (tmp == NULL)
		{
			ft_strdel(&tmp);
			return (1);
		}
		ft_strdel(&tmp);
		return (0);
	}
	return (1);
}

/*
**      Execute commande
*/

static int		execute_with_env_suite(t_cmd **lst, char ***new)
{
	(*lst)->tab_cmd = ft_del_tab((*lst)->tab_cmd);
	(*lst)->tab_cmd = ft_duplicate_tab((*new));
	(*new) = ft_del_tab((*new));
	ft_strdel(&(*lst)->rep);
	return (0);
}

int				execute_with_env(t_struct **data, t_cmd *lst, int i, int opt)
{
	char		**new;
	int			cpy;
	int			j;

	new = NULL;
	cpy = i;
	j = 0;
	while (lst->tab_cmd[cpy])
		cpy++;
	if (!(new = (char **)malloc(sizeof(char *) * (cpy - i + 1))))
		return (1);
	while (lst->tab_cmd[i])
	{
		new[j] = ft_strdup(lst->tab_cmd[i]);
		i++;
		j++;
	}
	new[j] = NULL;
	execute_with_env_suite(&lst, &new);
	chose_rep(*data, &lst, 1);
	if (opt == 1)
		lst->env = ft_del_tab(lst->env);
	if (ft_check_arg_invalid(*data, lst) == 1)
		return ((*data)->code_erreur);
	return (ft_process(lst));
}
