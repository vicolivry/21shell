/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   search_redirection_suite.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 14:22:07 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 14:56:41 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	check_null_norm(t_path **lst, int j, char *str)
{
	if ((*lst)->s_or_d == 0)
		(*lst)->s_or_d = what_is_op(str, j - 1, (*lst)->s_or_d);
	if ((*lst)->redir_fd == 0)
		(*lst)->redir_fd = search_fd(str, j - 1);
	return (0);
}

static int	verif_name(char **str)
{
	char		**tmp;

	tmp = NULL;
	if (*str == NULL)
		return (0);
	if (!(tmp = ft_strsplit(*str, ' ')))
		return (1);
	if (ft_len_tab(tmp) > 1)
	{
		ft_strdel(str);
		if (!(*str = ft_strdup(tmp[0])))
			*str = NULL;
	}
	tmp = ft_del_tab(tmp);
	if (*str == NULL)
		return (1);
	return (0);
}

int			check_search_null(t_path **lst, char *str, int i, int j)
{
	if (*lst == NULL)
		return (i);
	if (str[i] == '|' || str[i] == '<' || i >= ft_strlen(str) - 1)
	{
		if ((*lst)->name != NULL)
		{
			(*lst)->next = ft_init_path();
			*lst = (*lst)->next;
		}
		(*lst)->name = ft_strsub(str, j, i - j);
		verif_name(&(*lst)->name);
		check_null_norm(lst, j, str);
		clear_line(&(*lst)->name);
		return (i);
	}
	else if (j < i)
	{
		(*lst)->next = ft_init_path();
		*lst = (*lst)->next;
		(*lst)->name = ft_strsub(str, j, i);
		(*lst)->s_or_d = 0;
	}
	return (i);
}

int			check_new(char **new)
{
	if (*new == NULL)
		return (1);
	clear_line(new);
	if (ft_strlen(*new) == 0)
	{
		ft_strdel(new);
		return (1);
	}
	return (0);
}
