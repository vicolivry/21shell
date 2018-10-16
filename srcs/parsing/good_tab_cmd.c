/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   good_tab_cmd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/08 15:29:39 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:52:10 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  Search L'operateur (> ou >>)
*/

int				what_is_op(char *str, int i, int op)
{
	int		ret;

	ret = op;
	if (i + 1 > ft_strlen(str) || i == 0)
		return (ret);
	if (str[i] != '>')
		i--;
	if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '>' &&
	str[i - 1] == '>'))
		ret = 3;
	else if ((str[i] == '>' && (str[i - 1] != '>' && str[i + 1] != '>'))
			|| (str[i + 1] == '>' && str[i] != '>')
			|| (str[i - 1] == '>' && str[i] != '>'))
		ret = 2;
	return (ret);
}

/*
**	insert la commande a executer et search les redirections a faire
*/

static int		what_return(t_cmd **lst, char *str, int i, int ret)
{
	if ((*lst)->op_next == 2 || (*lst)->op_next == 3)
		ret = search_redirection(lst, str, i, i);
	else if ((*lst)->op_next == 9)
	{
		ret = search_redirection(lst, str, i, i);
		(*lst)->op_next = 0;
		if (ft_strstr(str + (i + 1), ">") != NULL)
			(*lst)->op_next = 2;
		else if (ft_strstr(str + (i + 1), "|") != NULL)
			(*lst)->op_next = 1;
	}
	else if ((*lst)->op_next == 4 || (*lst)->op_next == 5)
	{
		ret = search_heredoc(lst, str, i, i);
		(*lst)->heredoc_activ = 1;
		if (ret == -1)
			return (-1);
		else if (str[ret] == '>' || str[ret] == '|')
		{
			good_op_next(lst, str, ret);
			(*lst)->redir_heredoc = 1;
			ret = what_return(lst, str, ret, ret);
		}
	}
	return (ret);
}

/*
**  return 1 -> strdup
**  return 0 -> strsub
**  return (oher) -> strsub(., ., ret)
*/

static int		what_malloc(char *str, int i)
{
	if (i <= 0)
		return (0);
	if (i >= ft_strlen(str))
		return (1);
	if (str[i] == '>')
	{
		if (i > 1)
		{
			if (ft_isdigit(str[i - 1]))
				return (i - 1);
		}
		if (i < 1)
			return (1);
		return (0);
	}
	if (str[i] == '|')
		return (i);
	if (str[i] == '<')
		return (0);
	return (1);
}

static int		good_tab_norm(t_struct *data, t_cmd **lst, char **tmp)
{
	int			ret;

	ret = 0;
	insert_cmd_simple(data, lst, *tmp);
	ret = ft_strlen(*tmp);
	ft_strdel(tmp);
	return (ret);
}

int				good_tab_cmd(t_struct *data, t_cmd **lst, char *str, int i)
{
	char		*tmp;
	int			ret;
	int			start;

	tmp = NULL;
	ret = 0;
	start = 0;
	if (str == NULL)
		return (0);
	ret = what_malloc(str, i);
	if (ret == 1)
		tmp = ft_strdup(str);
	else if (ret == 0)
		tmp = ft_strsub(str, start, i);
	else
		tmp = ft_strsub(str, start, ret);
	if (tmp == NULL || ft_strlen(tmp) <= 1)
	{
		ft_strdel(&tmp);
		return (0);
	}
	ret = good_tab_norm(data, lst, &tmp);
	ret = what_return(lst, str, i, ret);
	return (ret);
}
