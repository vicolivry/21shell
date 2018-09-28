/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   good_tab_cmd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/08 15:29:39 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 10:42:33 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  Search L'operateur (> ou >>)
**	inutile ?
*/

int				what_is_op(char *str, int i)
{
	int		ret;

	ret = 0;
	if (i + 1 > ft_strlen(str) || i == 0)
		return (0);
	if (str[i - 1] == '>' && str[i] == '>')
		ret = 3;
	else
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
		ret = search_redirection(lst, str, i - 1, i - 1);
		if (ft_strstr(str + i, ">") == NULL)
			(*lst)->op_next = 0;
	}
	else if ((*lst)->op_next == 4 || (*lst)->op_next == 5)
	{
		ret += search_heredoc(lst, str, i, i);
	}
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
	if ((*lst)->op_next != 1 && (*lst)->op_next != 2 && (*lst)->op_next != 4)
		i--;
	if ((i >= ft_strlen(str) && (*lst)->op_next != 9))
		tmp = ft_strdup(str);
	else if (str[i - 1] == '>' && (ft_isdigit(str[i - 2]) || str[i - 2] == '&'))
		tmp = ft_strsub(str, start, i - 3);
	else if ((*lst)->op_next == 9)
		tmp = ft_strsub(str, start, i - 3);
	else
		tmp = ft_strsub(str, start, i - 1);
	insert_cmd_simple(data, lst, tmp);
	ret = ft_strlen(tmp);
	ft_strdel(&tmp);
	ret = what_return(lst, str, i, ret);
	return (ret);
}
