/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   search_redirection_suite.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 14:22:07 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/27 14:40:31 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		check_search_null(t_path **lst, char *str, int i, int j)
{
	if (str[i] == '|' || str[i] == '<')
	{
		*lst = ft_init_path();
		(*lst)->name = ft_strsub(str, j, i - j);
		(*lst)->s_or_d = what_is_op(str, j);
		clear_line(&(*lst)->name);
		return (i);
	}
	if (lst == NULL)
	{
		*lst = ft_init_path();
		(*lst)->name = ft_strdup(str);
		(*lst)->s_or_d = what_is_op(str, i);
		clear_line(&(*lst)->name);
		return (ft_strlen(str));
	}
	else if (j < i)
	{
		(*lst)->next = ft_init_path();
		*lst = (*lst)->next;
		(*lst)->name = ft_strsub(str, j, i);
		(*lst)->s_or_d = 0;
	}
	return (i);
}
