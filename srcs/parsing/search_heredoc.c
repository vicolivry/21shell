/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   search_heredoc.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 11:34:39 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 15:14:26 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	ft_return_heredoc(char *str, char **tmp, int i)
{
	int		j;
	int		len;

	j = i;
	len = ft_strlen(str) - 1;
	while (str[i] == ' ' || str[i] == '<')
		i++;
	i += 2;
	while (str[i])
	{
		if (i == len || (str[i] == '|' ||
	str[i] == '>' || str[i] == '<'))
		{
			*tmp = ft_strsub(str, j, i - j + 1);
			return (i);
		}
		i++;
	}
	return (len + 1);
}

static char	**heredoc_simple(char *str, int i, int *j)
{
	char	*tmp;
	char	**new;

	tmp = NULL;
	new = NULL;
	*j = ft_return_heredoc(str, &tmp, i + 1);
	if (tmp == NULL)
		return (NULL);
	if (!(new = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	new[0] = ft_strdup(tmp);
	new[1] = NULL;
	ft_strdel(&tmp);
	return (new);
}

static int	add_params(t_cmd **lst, char *str, int j, int end)
{
	char	*tmp;
	char	**tabl;
	int		i;

	tmp = NULL;
	tabl = NULL;
	i = 0;
	if (end <= j)
		return (0);
	tmp = ft_strsub(str, j, end - j);
	if (tmp == NULL)
		return (0);
	tabl = ft_strsplit(tmp, ' ');
	if (tabl == NULL)
		return (0);
	while (tabl[i])
	{
		increase_tab(&(*lst)->tab_cmd);
		(*lst)->tab_cmd[i + 1] = ft_strdup(tabl[i]);
		clear_line(&(*lst)->tab_cmd[i + 1]);
		i++;
	}
	ft_strdel(&tmp);
	tabl = ft_del_tab(tabl);
	return (0);
}

int			clear_tab_heredoc(t_cmd **lst)
{
	int		len;
	char	*tmp;

	tmp = NULL;
	if ((*lst)->heredoc == NULL)
		return (0);
	len = ft_strlen((*lst)->heredoc[0]);
	if (!(tmp = ft_strdup((*lst)->heredoc[0])))
		return (1);
	if (tmp[len - 1] == '>' || tmp[len - 1] == '|')
	{
		ft_strdel(&(*lst)->heredoc[0]);
		(*lst)->heredoc[0] = ft_strsub(tmp, 0, len - 1);
	}
	ft_strdel(&tmp);
	return (0);
}

int			search_heredoc(t_cmd **lst, char *str, int i, int j)
{
	int		end;
	int		err;

	err = 0;
	end = 0;
	if (!lst || !str)
		return (-1);
	if ((*lst)->op_next == 4)
	{
		(*lst)->heredoc = heredoc_simple(str, i, &j);
		clear_tab_heredoc(lst);
		end = j;
	}
	else if ((*lst)->op_next == 5)
	{
		(*lst)->heredoc_str = heredoc(str, &err);
		if (err)
			return (-1);
		j = start_heredoc_opt(str, 0);
		end = end_heredoc_opt(str, j);
		if (j < ft_strlen(str) && j != end)
			add_params(lst, str, j, end);
	}
	change_prompt(&g_info, 0);
	return (end);
}
