/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirections_avancees.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 10:54:14 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 17:10:27 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		insert_next(t_cmd **new, char *str, int i)
{
	if (str[i] == ' ')
		return (0);
	if (str[i] == '1')
	{
		(*new)->stdout_cmd = 1;
		return (0);
	}
	if (str[i] == '2')
	{
		(*new)->stdout_cmd = 2;
		return (0);
	}
	else
	{
		ft_putstr_fd("21sh :", 2);
		write(1, &str[i], 2);
		ft_putstr_fd(": bad file descriptor\n", 2);
	}
	return (1);
}

static int		insert_before(t_cmd **new, char *str, int i)
{
	if (str[i] == ' ')
		return (0);
	if (str[i] == '1')
	{
		(*new)->stdin_cmd = 1;
		return (0);
	}
	else if (str[i] == '2')
	{
		(*new)->stdin_cmd = 2;
		return (0);
	}
	else
	{
		ft_putstr_fd("21sh :", 2);
		write(1, &str[i], 2);
		ft_putstr_fd(": bad file descriptor\n", 2);
	}
	return (1);
}

static int		insert_redir(t_cmd **new, char *str, int i)
{
	int		len;
	int		ret;

	ret = 0;
	len = ft_strlen(str);
	if (i < len - 1)
	{
		if (ft_isdigit(str[i + 2]) || str[i + 2] == ' ')
			ret = insert_next(new, str, i + 2);
		if (ret == 1)
			return (1);
	}
	if (i > 0)
	{
		if (ft_isdigit(str[i - 1]))
			ret = insert_before(new, str, i - 1);
		if (ret == 1)
			return (1);
	}
	return (0);
}

int				ft_redirection_avancees(t_cmd **new, char **str)
{
	char	*tmp;
	int		i;
	int		ret;

	ret = 0;
	if (!(tmp = ft_strdup(*str)))
		return (1);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '>')
		{
			if (i < ft_strlen(*str))
			{
				if (tmp[i + 1] == '&')
				{
					ret = insert_redir(new, tmp, i);
					(*new)->stdcmd = 1;
				}
				if (ret == 1)
					return (1);
			}
		}
		i++;
	}
	return (0);
}
