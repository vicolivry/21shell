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

int		ft_check_vir(t_ins **lst, char **line)
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

int		resize_line(char **str, int i, t_ins **lst)
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

int		add_code(t_ins *lst, char *str, int i)
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
