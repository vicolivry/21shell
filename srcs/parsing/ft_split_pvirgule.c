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

static int		ft_check_vir(t_ins **lst, char **line)
{
	if (ft_strstr(*line, ";") == NULL && ft_strstr(*line, "&&") == NULL
	&& ft_strstr(*line, "||") == NULL)
	{
		(*lst)->str = ft_strdup(*line);
		ft_strdel(line);
		return (0);
	}
	return (1);
}

static int		resize_line(char **str, int i, t_ins **lst)
{
	char	*tmp;

	(void)lst;
	tmp = NULL;
	if (!(*str))
		return (1);
	if (i == ft_strlen(*str))
	{
		ft_strdel(str);
		return (0);
	}
	tmp = ft_strdup(*str);
	ft_strdel(str);
	*str = ft_strsub(tmp, i + 1, ft_strlen(tmp) - (i + 1));
	ft_strdel(&tmp);
	return (0);
}

static int		add_code(t_ins *lst, char *str, int i)
{
	if (!lst || !str)
		return (1);
	if (str[i] == ';')
		lst->code = 0;
	if (str[i] == '&')
		lst->code = 7;
	if (str[i] == '|')
		lst->code = 8;
	return (0);
}

static int		ft_split_pvir_suite(char **line, int i, t_ins **lst)
{
	char	*tmp;

	tmp = NULL;
	if (i == -1 || !(*line))
		return (0);
	if ((*lst)->str != NULL)
	{
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = ft_init_ins();
		*lst = (*lst)->next;
	}
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
		else if (i == ft_strlen(tmp) || (quote == 0 && (tmp[i] == ';' ||
	(tmp[i] == '&' && tmp[i + 1] == '&') ||
	(tmp[i] == '|' && tmp[i + 1] == '|'))))
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
