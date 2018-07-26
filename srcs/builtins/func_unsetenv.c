/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_unsetenv.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 13:22:42 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:20:55 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	check_error(t_cmd *lst)
{
	int		i;

	i = 0;
	while (lst->tab_cmd[i])
		i++;
	if (i < 2 || i > 2)
	{
		ft_putstr_fd("21sh: unsetenv: Invalid format\n", 2);
		return (1);
	}
	return (0);
}

static int	delete_in_env(t_struct **data, int i)
{
	while ((*data)->env[i])
	{
		if ((*data)->env[i + 1] == NULL)
		{
			ft_strdel(&(*data)->env[i]);
			return (0);
		}
		ft_strdel(&(*data)->env[i]);
		(*data)->env[i] = ft_strdup((*data)->env[i + 1]);
		i++;
	}
	return (0);
}
static int	convertmaj(char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!(tmp = ft_strdup(*str)))
		return (1);
	while (tmp[i])
	{
		tmp[i] = ft_toupper(tmp[i]);
		i++;
	}
	ft_strdel(str);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (0);
}

int			func_unsetenv(t_struct **data, t_cmd *lst)
{
	int		i;
	int		len;

	i = 0;
	len = ft_len_tab((*data)->env);
	if (check_error(lst) == 1)
		return (1);
	convertmaj(&lst->tab_cmd[1]);
	while ((*data)->env[i])
	{
		if (ft_strncmp((*data)->env[i], lst->tab_cmd[1], ft_strlen(lst->tab_cmd[1])) == 0)
		{
			delete_in_env(data, i);
			return (0);
		}
		i++;
	}
	ft_putstr_fd("21sh: unsetenv: Pattern not found\n", 2);
	return (1);
}
