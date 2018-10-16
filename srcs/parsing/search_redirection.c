/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   search_redirection.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/10 14:27:41 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:53:24 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Fonction appeler par good_tab_cmd
**	Insert dans une liste chainer toutes les redirections a faire
**	Retourne la longueur de str a resize, exemple :
**	ls > test1 > test2 | grep auteur
**					  |-> i
*/

static t_path		*search_suite(t_path **new, t_cmd **lst)
{
	if (*new == NULL)
	{
		*new = ft_init_path();
		(*lst)->pathname = *new;
	}
	else if ((*new)->name != NULL)
	{
		(*new)->next = ft_init_path();
		*new = (*new)->next;
	}
	return (*new);
}

static int			search_redir_norm(t_path **new, char *str, int j)
{
	if ((*new)->s_or_d == 0)
		(*new)->s_or_d = what_is_op(str, j, (*new)->s_or_d);
	if ((*new)->redir_fd == 0)
		(*new)->redir_fd = search_fd(str, j);
	return (0);
}

static int			search_redir_norm2(t_cmd **lst, char *str, int *i, int j)
{
	int		cpy_i;

	cpy_i = *i;
	*i += modifie_fd(lst, str, cpy_i + 1);
	j = *i + 1;
	return (j);
}

int					search_redirection(t_cmd **lst, char *str, int i, int j)
{
	t_path		*new;
	int			val;

	new = NULL;
	while (str[i] && str[i] != '|' && str[i] != '<')
	{
		if (str[i] == '>' && str[i + 1] != '&')
		{
			new = search_suite(&new, lst);
			new->name = return_name(lst, str, j, i);
			search_redir_norm(&new, str, j);
			new->s_or_d == 3 ? i += 1 : 0;
			j = i + 1;
		}
		else if (str[i] == '>' && str[i + 1] == '&')
			j = search_redir_norm2(lst, str, &i, j);
		i++;
	}
	if (new == NULL)
	{
		val = check_search_null(&new, str, i, j);
		(*lst)->pathname = new;
		return (val);
	}
	return ((val = check_search_null(&new, str, i, j)));
}
