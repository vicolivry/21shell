/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_insert_dollar.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/22 11:56:35 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 11:58:36 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  replace $ for the path and return len var env
*/

static char		*ft_return_env_dollar(t_struct *data, char *tmp, int i, int j)
{
	char	*tmp2;
	int		x;

	tmp2 = NULL;
	x = 0;
	while (data->env[x] && tmp2 == NULL)
	{
		if (ft_strncmp(data->env[x], tmp + j + 1, i - j - 1) == 0)
			tmp2 = ft_strsub(data->env[x], i - j,
	ft_strlen(data->env[x]) - (i - j));
		x++;
	}
	return (tmp2);
}

static int		ft_suite(t_struct *data, char **str, int i, int j)
{
	char	*ttt;
	char	*tmp;
	char	*tmp2;

	ttt = NULL;
	tmp2 = NULL;
	tmp = ft_strdup(*str);
	*str = ft_strsub(tmp, 0, j);
	tmp2 = ft_return_env_dollar(data, tmp, i, j);
	if (tmp2 == NULL)
	{
		ft_strdel(str);
		*str = ft_strdup(tmp);
		ft_strdel(&tmp);
		return (1);
	}
	ttt = ft_strjoin(*str, tmp2);
	ft_strdel(str);
	*str = ft_strjoin(ttt, tmp + i);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	ft_strdel(&ttt);
	return (ft_strlen(*str));
}

int				ft_insert_dollar(t_struct *data, char **str, int i)
{
	char	*tmp;
	int		j;
	int		ret;

	tmp = ft_strdup(*str);
	ret = 1;
	j = i;
	while (tmp[i] || tmp[i] == ' ')
		i++;
	if (i - j > 1)
		ret = ft_suite(data, &tmp, i, j);
	ft_strdel(str);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (ret);
}
