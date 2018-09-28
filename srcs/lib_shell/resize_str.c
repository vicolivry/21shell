/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resize_str.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/08 09:48:23 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/17 15:48:04 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	check_len(char *str, int len)
{
	if (!str)
		return (0);
	if (len + 1 == ft_strlen(str))
		return (ft_strlen(str));
	if ((str[len] == '|' || str[len] == '>' || str[len] == '<') &&
	(str[len + 1] == ' ' || str[len + 1] == '\t'))
		return (len + 1);
	return (len);
}

static char	*check_tmp(char *tmp)
{
	char	*new;

	new = NULL;
	if (tmp != NULL)
	{
		if (tmp[0] == '|' || tmp[0] == '>' || tmp[0] == '<')
			new = ft_strsub(tmp, 1, ft_strlen(tmp) - 1);
		else
			new = ft_strdup(tmp);
		return (new);
	}
	return (NULL);
}

int			resize_str(char **str, int len)
{
	char		*tmp;

	tmp = NULL;
	if (*str == NULL)
		return (1);
	len = check_len(*str, len);
	if (len >= ft_strlen(*str) || len == 0)
	{
		ft_strdel(str);
		return (0);
	}
	tmp = ft_strsub(*str, len, (ft_strlen(*str) - len));
	if (tmp == NULL)
		return (0);
	ft_strdel(str);
	*str = check_tmp(tmp);
	if (*str == NULL || ft_strlen(*str) == 0)
	{
		ft_strdel(str);
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	return (0);
}
