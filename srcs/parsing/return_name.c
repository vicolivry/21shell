/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   return_name.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 11:41:42 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 14:56:45 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int			return_name_suite(t_cmd **lst, char **new, char **tab_tmp)
{
	char	*tmp;
	char	**tmp2;

	tmp2 = NULL;
	tmp = ft_strsub(*new, 0, ft_strlen(tab_tmp[0]));
	ft_strdel(new);
	*new = ft_strdup(tmp);
	ft_strdel(&tmp);
	if (!(tmp2 = insert_option_cmd((*lst)->tab_cmd, tab_tmp, 0, 0)))
		return (1);
	(*lst)->tab_cmd = ft_del_tab((*lst)->tab_cmd);
	(*lst)->tab_cmd = ft_duplicate_tab(tmp2);
	tmp2 = ft_del_tab(tmp2);
	ft_strdel(&tmp);
	return (0);
}

char				*return_name(t_cmd **lst, char *str, int start, int end)
{
	char	*new;
	char	**tab_tmp;

	new = NULL;
	tab_tmp = NULL;
	if (str[end + 1] == '&')
	{
		start += modifie_fd(lst, str, end + 1);
		return (NULL);
	}
	if (start > end)
		return (NULL);
	if (ft_strlen(str) == end + 1)
		new = ft_strsub(str, start, (end - start + 1));
	else if (str[end] == '>' && ft_isdigit(str[end - 1]) == 1)
		new = ft_strsub(str, start, (end - start - 2));
	else
		new = ft_strsub(str, start, (end - start));
	if (check_new(&new) == 1)
		return (NULL);
	tab_tmp = ft_strsplit(new, ' ');
	if (ft_len_tab(tab_tmp) > 1)
		return_name_suite(lst, &new, tab_tmp);
	tab_tmp = ft_del_tab(tab_tmp);
	return (new);
}
