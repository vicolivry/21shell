/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   insert_cmd_simple.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/08 15:04:18 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 10:50:02 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Split and chose rep
*/

int			insert_cmd_simple(t_struct *data, t_cmd **lst, char *str)
{
	if (str == NULL)
		return (1);
	if (ft_strstr(str, "echo"))
		(*lst)->tab_cmd = split_echo(str);
	else
		(*lst)->tab_cmd = split_cmd(str, 0);
	if ((*lst)->tab_cmd == NULL)
		return (1);
	chose_rep(data, lst, 0);
	(*lst)->env = ft_duplicate_tab(data->env);
	return (0);
}
