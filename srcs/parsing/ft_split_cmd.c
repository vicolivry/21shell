/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split_cmd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 11:08:13 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 16:12:06 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		ft_insert_cmd(t_cmd **new, t_struct *data, char **str, int i)
{
	char	*tmp;

	if ((*new)->op_redir == 2 || (*new)->op_redir == 3)
	{
		(*new)->pathname = ft_strdup(*str + 1);
		return (0);
	}
	if ((*new)->tab_cmd != NULL)
	{
		(*new)->next = ft_init_cmd();
		*new = (*new)->next;
	}
	tmp = ft_strsub(*str, 0, i);
	(*new)->tab_cmd = split_cmd(tmp, 0);
	chose_rep(data, new);
	if ((*new)->rep == NULL || (*new)->op_next == 2 || (*new)->op_next == 3)
	{
		if ((*new)->pathname != NULL)
			ft_strdel(&(*new)->pathname);
		(*new)->pathname = ft_strdup((*new)->tab_cmd[0]);
	}
	(*new)->env = ft_duplicate_tab(data->env);
	if (i == ft_strlen(*str))
		(*new)->op_next = 0;
	else
		(*new)->op_next = ft_search_opnext(*str, i);
	ft_strdel(&tmp);
	if ((*new)->op_next == 9)
		ft_redirection_avancees(new, str);
	return (0);
}

static void		ft_split_cmd_suite_deux(char **str, t_cmd **new, int i)
{
	char	*tmp2;

	tmp2 = NULL;
	tmp2 = ft_strdup(*str);
	if (tmp2[i] == '>')
		(*new)->op_redir = 2;
	if (tmp2[i + 1] == '>')
		(*new)->op_redir = 3;
	ft_strdel(str);
	if ((*new)->stdcmd != 0)
		*str = ft_strsub(tmp2, i + 3, ft_strlen(tmp2) - (i + 3));
	else
		*str = ft_strsub(tmp2, i + 1, ft_strlen(tmp2) - (i + 1));
	ft_strdel(&tmp2);
}

static int		ft_split_cmd_suite(t_cmd **new, t_struct *data, char **str)
{
	char	*tmp;
	int		i;

	tmp = ft_strdup(*str);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '|' || tmp[i] == '>')
		{
			ft_insert_cmd(new, data, &tmp, i);
			if (i < ft_strlen(tmp))
			{
				ft_split_cmd_suite_deux(&tmp, new, i);
				i = 0;
			}
		}
		i++;
	}
	ft_insert_cmd(new, data, &tmp, i);
	ft_strdel(&tmp);
	return (0);
}

t_cmd			*ft_split_cmd(char *str, t_struct *data)
{
	t_cmd	*new;
	t_cmd	*start;
	int		i;

	i = 0;
	new = NULL;
	start = NULL;
	if (!(new = ft_init_cmd()))
		return (NULL);
	start = new;
	clear_line(&str);
	if (str == NULL)
	{
		new = clear_cmd(new);
		return (NULL);
	}
	replace_in_line(data, &str);
	if (ft_strstr(str, "|") != NULL || ft_strstr(str, ">") != NULL ||
			ft_strstr(str, "<") != NULL)
		ft_split_cmd_suite(&new, data, &str);
	else
		ft_insert_cmd(&new, data, &str, ft_strlen(str));
	return (start);
}
