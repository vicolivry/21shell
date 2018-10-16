/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split_pvirgule.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/14 14:38:25 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 09:55:39 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static t_ins	*return_good_chain(t_ins **lst)
{
	if (!(*lst))
		return (NULL);
	if ((*lst)->str != NULL)
	{
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = ft_init_ins();
		*lst = (*lst)->next;
	}
	return (*lst);
}

static int		ft_split_pvir_suite(char **line, int i, t_ins **lst)
{
	char	*tmp;

	tmp = NULL;
	if (i == -1 || !(*line))
		return (0);
	*lst = return_good_chain(lst);
	add_code(*lst, *line, i);
	if (i == ft_strlen(*line))
	{
		(*lst)->str = ft_strdup(*line);
		ft_strdel(line);
		return (-2);
	}
	tmp = ft_strdup(*line);
	(*lst)->str = ft_strsub(*line, 0, i);
	while (tmp[i] == '&')
		i++;
	while (tmp[i] == '|')
		i++;
	ft_strdel(&tmp);
	resize_line(line, i, lst);
	if ((*lst)->code == 0)
		return (-2);
	return (-1);
}

static int		check_tmp(char *tmp, int i)
{
	if (!tmp)
		return (-1);
	if (tmp[i] == ';' || (tmp[i] == '&' && tmp[i + 1] == '&') ||
		(tmp[i] == '|' && tmp[i + 1] == '|'))
		return (1);
	return (0);
}

t_ins			*ft_split_pvirgule(char **line, t_ins *lst, int i, int quote)
{
	t_ins	*start;
	char	*tmp;

	tmp = NULL;
	start = lst;
	if (ft_check_vir(&lst, line) == 0)
		return (start);
	tmp = ft_strdup(*line);
	while (i != -1 && i < ft_strlen(tmp))
	{
		if ((tmp[i] == '\'' || tmp[i] == '\"') && quote == 0)
			quote = 1;
		else if ((tmp[i] == '\'' || tmp[i] == '\"') && quote == 1)
			quote = 0;
		else if (i == ft_strlen(tmp) || (quote == 0 && check_tmp(tmp, i) == 1))
			i = ft_split_pvir_suite(&tmp, i, &lst);
		i++;
	}
	ft_split_pvir_suite(&tmp, i, &lst);
	ft_strdel(line);
	if (tmp != NULL && ft_strlen(tmp) > 0)
		*line = ft_strdup(tmp);
	ft_strdel(&tmp);
	lst = start;
	return (lst);
}
