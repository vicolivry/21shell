/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   split_cmd_suite.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/11 14:02:55 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/20 16:11:51 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		clear_suite(char **tmp1, char **tmp2, char **str, int d)
{
	*tmp1 = ft_strsub(*str, 0, d);
	*tmp2 = ft_strsub(*str, d + 1, ft_strlen(*str) - (d + 1));
	return (0);
}

static int		clear_suite_opt(char **tmp1, char **tmp2, char **str, int d)
{
	*tmp1 = ft_strsub(*str, 0, d - 1);
	*tmp2 = ft_strsub(*str, d, ft_strlen(*str) - (d));
	return (0);
}

static int		clear_string_suite(char **str, char **tmp)
{
	*tmp = ft_strsub(*str, 1, ft_strlen(*str) - 1);
	ft_strdel(str);
	*str = ft_strdup(*tmp);
	ft_strdel(tmp);
	return (0);
}

void			clear_string(char **str, int deleted, int opt)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	if (deleted == 0)
		clear_string_suite(str, &tmp1);
	else if (deleted == ft_strlen(*str) || deleted == ft_strlen(*str) - 1)
	{
		tmp1 = ft_strsub(*str, 0, ft_strlen(*str) - 1);
		ft_strdel(str);
		*str = ft_strdup(tmp1);
	}
	else
	{
		opt == 1 ? clear_suite_opt(&tmp1, &tmp2, str, deleted) :
			clear_suite(&tmp1, &tmp2, str, deleted);
		ft_strdel(str);
		*str = ft_strjoin(tmp1, tmp2);
	}
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
}
