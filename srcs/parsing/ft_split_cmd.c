/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split_cmd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 11:08:13 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 15:41:03 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

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

static int			return_val_i(char *str, int i)
{
	if (str[i] == '\"')
	{
		i++;
		while (str[i] != '\"')
		{
			if (str[i] == '\0')
				return (1);
			i++;
		}
	}
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
		{
			if (str[i] == '\0')
				return (1);
			i++;
		}
	}
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
	while (tmp[i] && i < ft_strlen(tmp))
	{
		i = return_val_i(tmp, i);
		if (tmp[i] == '|' || tmp[i] == '>' ||
	tmp[i] == '<' || i == ft_strlen(tmp) - 1)
		{
			i += good_op_next(new, tmp, i);
			i = good_tab_cmd(data, new, tmp, i);
			verifie_op(new, tmp, i);
			i = resize_str(&tmp, i) - 1;
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

t_cmd				*ft_split_cmd(char *str, t_struct *data)
{
	t_cmd	*new;
	t_cmd	*start;
	int		i;

	i = 0;
	new = NULL;
	start = NULL;
	if (!(new = ft_init_cmd()) || str == NULL)
		return (NULL);
	start = new;
	clear_line(&str);
	if (str == NULL || ft_split_cmd_suite(&new, data, str, 0) == 1)
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
