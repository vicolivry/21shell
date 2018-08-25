/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 13:55:04 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/02 16:10:13 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	free_slct(t_slct *lst, t_info *info)
{
	lst = lst->next;
	while (lst->next != lst)
	{
		ac_remove_elem(lst);
		lst = lst->next;
	}
	info->max_len = 0;
	info->nb_elem = 0;
	ft_memdel((void**)&lst);
}

int		is_exe(char *name)
{
	struct stat	st;

	lstat(name, &st);
	if ((st.st_mode & S_IXUSR || st.st_mode & S_IXGRP || st.st_mode & S_IXOTH)
				&& !S_ISDIR(st.st_mode))
		return (1);
	else
		return (0);
}
