/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_setenv_suite.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/28 13:44:18 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/28 14:07:35 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char				*return_line(char *str1, char *str2)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	tmp = ft_strjoin(str1, "=");
	tmp2 = ft_strjoin(tmp, str2);
	ft_strdel(&tmp);
	return (tmp2);
}

int						modifie_env(t_struct **data, t_cmd *lst, int i)
{
	char	*tmp;
	int		ret;

	ret = 0;
	tmp = return_line(lst->tab_cmd[1], lst->tab_cmd[2]);
	ft_strdel(&(*data)->env[i]);
	(*data)->env[i] = ft_strdup(tmp);
	ft_strdel(&tmp);
	ret = check_if_path_modif(data, lst);
	return (ret);
}

int						check_if_path_modif(t_struct **data, t_cmd *lst)
{
	if (ft_strcmp(lst->tab_cmd[1], "PATH") == 0)
	{
		(*data)->tab_hash = delete_tab_hash((*data)->tab_hash,
				(*data)->sizemax);
		(*data)->sizemax = ft_load_path(data);
		if ((*data)->sizemax == -1)
		{
			ft_putstr_fd("Error creation  table de hashage\n",
		lst->stderr_cmd);
			return (1);
		}
	}
	return (0);
}
