/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split_cmd_suite.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 10:59:09 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 17:11:55 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int				ft_search_opnext(char *str, int i)
{
	int		len;

	len = ft_strlen(str);
	if (i < len)
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (5);
		if (str[i] == '>' && str[i + 1] == '>')
			return (3);
		if (str[i] == '>' && str[i + 1] == '&')
			return (9);
	}
	if (str[i] == '|')
		return (1);
	else if (str[i] == '>')
		return (2);
	else if (str[i] == '<')
		return (4);
	else if (str[i] == '&')
		return (4);
	return (0);
}

int				chose_rep(t_struct *data, t_cmd **new)
{
	if (ft_strstr((*new)->tab_cmd[0], "./") != NULL)
		(*new)->rep = ft_strdup((*new)->tab_cmd[0]);
	else
		(*new)->rep = ft_search_path((*new)->tab_cmd[0], data);
	return (0);
}
