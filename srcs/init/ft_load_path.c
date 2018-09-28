/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_load_path.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 13:59:22 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/10 13:02:50 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Creation d‘une table de hashage
*/

int			ft_load_path(t_struct **data)
{
	char	*tmp;
	int		ret;

	tmp = NULL;
	tmp = ft_check_infos((*data)->env, "PATH=");
	if (tmp == NULL)
		return (1);
	else
	{
		ft_strdel(&(*data)->path);
		(*data)->path = ft_strsub(tmp, 5, ft_strlen(tmp) - 5);
		ft_strdel(&tmp);
		(*data)->tab_path = ft_del_tab((*data)->tab_path);
		(*data)->tab_path = ft_strsplit((*data)->path, ':');
	}
	ret = ft_create_table_hash(data);
	if (ret == -1)
	{
		ft_putstr_fd("Erreur table hashage\n", 2);
		exit(EXIT_FAILURE);
	}
	return (ret);
}
