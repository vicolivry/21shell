/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/10 10:33:16 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 13:52:46 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Fills history with the lat command line.
** Handles the backup of a modified history element.
*/

void		fill_history(t_info *info, t_hist *tmp)
{
	t_hist	*last;

	last = last_elem(info->history);
	if (tmp->current && tmp->next != info->history)
	{
		if (last->name)
			ft_strdel(&(last->name));
		last->name = ft_strdup(tmp->name);
		if (info->line)
			ft_strdel(&(info->line));
		info->line = ft_strdup(tmp->name);
		ft_strdel(&(tmp->name));
		tmp->name = ft_strdup(tmp->backup);
		ft_strdel(&(tmp->backup));
	}
	while (tmp->next != info->history)
		tmp = tmp->next;
	if ((!last->name || str_iswhite(last->name)) ||
			(last->prev->name && !ft_strcmp(last->name, last->prev->name)))
		remove_this_elem(last);
}
