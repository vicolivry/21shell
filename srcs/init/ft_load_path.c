/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_load_path.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 13:59:22 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/25 12:02:28 by yoginet     ###    #+. /#+    ###.fr     */
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

	tmp = ft_check_infos((*data)->env, "PATH=");
	if (tmp == NULL)
	{
		(*data)->path = NULL;
		(*data)->tab_path = NULL;
		(*data)->home = NULL;
	}
	else
	{
		(*data)->path = ft_strsub(tmp, 5, ft_strlen(tmp) - 5);
		ft_strdel(&tmp);
		(*data)->tab_path = ft_strsplit((*data)->path, ':');
		tmp = ft_check_infos((*data)->env, "PWD=");
		ft_strdel(&tmp);
	}
	ret = ft_create_table_hash(data);
	if (ret == -1)
    {
		ft_putstr_fd("Erreur table hashage\n", 2);
        exit(EXIT_FAILURE);
    }
	return (ret);
}
