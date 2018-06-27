/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_cd_suite.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/16 09:12:25 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:16:50 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	For builtins/func_cd.c
**	Check data in t_struct *data
*/

void		ft_check_error_cd(t_struct **data)
{
	char	*buf;

	buf = NULL;
	if ((*data)->home == NULL)
		(*data)->home = ft_strdup("/");
	if ((*data)->pwd == NULL)
	{
		buf = ft_strnew(512);
		buf = getcwd(buf, 512);
		(*data)->pwd = ft_strdup(buf);
		ft_strdel(&buf);
	}
	if ((*data)->oldpwd == NULL)
		(*data)->oldpwd = ft_strdup((*data)->pwd);
}

int			ft_error_cd(char *line)
{
	char	**tabl;

	tabl = ft_strsplit(line, ' ');
	if (ft_len_tab(tabl) > 3)
	{
		tabl = ft_del_tab(tabl);
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else
		tabl = ft_del_tab(tabl);
	return (0);
}
