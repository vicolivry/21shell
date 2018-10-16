/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split_cmd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 11:08:13 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:51:15 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Create chain list for exec cmd
*/

static int			check_split(t_struct *data, t_cmd **new, char *str)
{
	if (ft_strstr(str, ">") == NULL && ft_strstr(str, "|") == NULL
			&& ft_strstr(str, ">&") == NULL && ft_strstr(str, "<") == NULL)
	{
		insert_cmd_simple(data, new, str);
		return (1);
	}
	return (0);
}

static int			check_ft_split(char *tmp, int i)
{
	if (tmp[i] == '|' || tmp[i] == '>' || tmp[i] == '<' ||
	(tmp[i + 1] == '\0' || tmp[i] == '\0'))
		return (1);
	return (0);
}

static int			split_norm(t_cmd **new, char **tmp, int i)
{
	verifie_op(new, *tmp, i);
	if ((*new)->op_next == 5)
		i = i - 1;
	i = resize_str(tmp, i) - 1;
	return (i);
}

static int			ft_split_cmd_suite(t_cmd **new, t_struct *data,
		char *str, int i)
{
	char	*tmp;

	tmp = NULL;
	if (check_split(data, new, str) == 1)
		return (0);
	tmp = ft_strdup(str);
	while (tmp[i])
	{
		i = echap_quote(tmp, i, 0);
		if (check_ft_split(tmp, i) == 1)
		{
			good_op_next(new, tmp, i);
			i = good_tab_cmd(data, new, tmp, i);
			if (i == -1)
				return (1);
			i = split_norm(new, &tmp, i);
			if (tmp == NULL)
				return (0);
			(*new)->next = ft_init_cmd();
			*new = (*new)->next;
		}
		i++;
	}
	ft_strdel(&tmp);
	return (0);
}

t_cmd				*ft_split_cmd(char **str, t_struct *data)
{
	t_cmd	*new;
	t_cmd	*start;

	new = NULL;
	start = NULL;
	if (!(new = ft_init_cmd()) || str == NULL)
		return (NULL);
	start = new;
	clear_line(str);
	if (str == NULL || ft_split_cmd_suite(&new, data, *str, 0) == 1)
	{
		new = clear_cmd(new);
		return (NULL);
	}
	if (check_validity(&start, data) == 1)
	{
		new = clear_cmd(new);
		return (NULL);
	}
	return (start);
}
