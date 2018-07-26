/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split_pvirgule.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/14 14:38:25 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 16:05:11 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		ft_check_vir(t_ins **lst, char *line)
{
	if (ft_strstr(line, ";") == NULL)
	{
		(*lst)->str = ft_strdup(line);
		return (0);
	}
	return (1);
}

static int		resize_line(char **str, int i, t_ins **lst)
{
	char	*tmp;

	(void)lst;
	tmp = NULL;
	tmp = ft_strdup(*str);
	ft_strdel(str);
	*str = ft_strsub(tmp, i + 1, ft_strlen(tmp) - (i + 1));
	ft_strdel(&tmp);
	return (0);
}

static int		ft_split_pvir_suite(char **line, int i, t_ins **lst)
{
	char	*tmp;

	tmp = NULL;
	if ((*lst)->str != NULL)
	{
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = ft_init_ins();
		*lst = (*lst)->next;
	}
	if (i == ft_strlen(*line))
	{
		(*lst)->str = ft_strdup(*line);
		return (-2);
	}
	(*lst)->str = ft_strsub(*line, 0, i);
	resize_line(line, i, lst);
	return (-1);
}

t_ins			*ft_split_pvirgule(char *line, t_ins *lst)
{
	t_ins	*start;
	int		i;
	int		quote;
	char	*tmp;

	i = 0;
	quote = 0;
	tmp = NULL;
	start = lst;
	if (ft_check_vir(&lst, line) == 0)
		return (start);
	tmp = ft_strdup(line);
	while (i != -1)
	{
		if ((tmp[i] == '\'' || tmp[i] == '\"') && quote == 0)
			quote = 1;
		else if ((tmp[i] == '\'' || tmp[i] == '\"') && quote == 1)
			quote = 0;
		if ((quote == 0 && tmp[i] == ';') || i == ft_strlen(tmp))
			i = ft_split_pvir_suite(&tmp, i, &lst);
		i++;
	}
	ft_strdel(&tmp);
	return (start);
}
