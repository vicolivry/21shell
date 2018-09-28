/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   search_redirection.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/10 14:27:41 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 10:38:31 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char			**insert_option_cmd(char **tab_cmd, char **new_tab,
		int len_1, int len_2)
{
	char	**new;

	new = NULL;
	if (tab_cmd == NULL || new_tab == NULL)
		return (NULL);
	len_1 = ft_len_tab(tab_cmd);
	len_2 = ft_len_tab(new_tab);
	if (!(new = (char **)malloc(sizeof(char *) * (len_1 + len_2 + 1))))
		return (NULL);
	new[len_1 + len_2] = NULL;
	len_1 = 0;
	len_2 = 1;
	while (tab_cmd[len_1])
	{
		new[len_1] = ft_strdup(tab_cmd[len_1]);
		len_1++;
	}
	while (new_tab[len_2])
	{
		new[len_1] = ft_strdup(new_tab[len_2]);
		len_1++;
		len_2++;
	}
	return (new);
}

static int			return_name_suite(t_cmd **lst, char **new, char **tmp,
		char **tab_tmp)
{
	char **tmp2;

	tmp2 = NULL;
	*tmp = ft_strsub(*new, 0, ft_strlen(tab_tmp[0]));
	ft_strdel(new);
	*new = ft_strdup(*tmp);
	ft_strdel(tmp);
	if (!(tmp2 = insert_option_cmd((*lst)->tab_cmd, tab_tmp, 0, 0)))
		return (1);
	(*lst)->tab_cmd = ft_del_tab((*lst)->tab_cmd);
	(*lst)->tab_cmd = ft_duplicate_tab(tmp2);
	tmp2 = ft_del_tab(tmp2);
	return (0);
}

static char			*return_name(t_cmd **lst, char *str, int start, int end)
{
	char	*new;
	char	*tmp;
	char	**tab_tmp;

	new = NULL;
	tmp = NULL;
	tab_tmp = NULL;
	if (str[start] == '&')
		start += modifie_fd(lst, str, start);
	if (start > end)
		return (NULL);
	if (ft_strlen(str) == end + 1)
		new = ft_strsub(str, start, (end - start + 1));
	else if (str[end] == '>' && ft_isdigit(str[end - 1]) == 1)
		new = ft_strsub(str, start, (end - start - 2));
	else
		new = ft_strsub(str, start, (end - start));
	if (new == NULL)
		return (NULL);
	clear_line(&new);
	if (ft_strlen(new) == 0)
	{
		ft_strdel(&new);
		return (NULL);
	}
	tab_tmp = ft_strsplit(new, ' ');
	if (ft_len_tab(tab_tmp) > 1)
		return_name_suite(lst, &new, &tmp, tab_tmp);
	tab_tmp = ft_del_tab(tab_tmp);
	return (new);
}

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

int					search_redirection(t_cmd **lst, char *str, int i, int j)
{
	t_path		*new;
	int			val;

	new = NULL;
	val = 0;
	while (str[i] && str[i] != '|' && str[i] != '<')
	{
		if (str[i] == '>' || str[i + 1] == '\0')
		{
			new = search_suite(&new, lst);
			new->name = return_name(lst, str, j, i);
			new->s_or_d = what_is_op(str, i);
			new->redir_fd = search_fd(str, j - 1);
			j = i + 1;
		}
		i++;
	}
	if (new == NULL)
	{
		val = check_search_null(&new, str, i, j);
		(*lst)->pathname = new;
		return (val);
	}
	val = check_search_null(&new, str, i, j);
	return (val);
}
