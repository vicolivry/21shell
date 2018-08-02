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

int		get_col_nb(t_info *info)
{
	int	cols;

	cols = info->nb_elem / (info->row_nb);
	cols = !cols ? 1 : cols;
	cols += cols * (info->row_nb) < info->nb_elem ? 1 : 0;
	return (cols);
}

void	free_slct(t_slct *lst)
{
	lst = lst->next;
	while (lst->next != lst)
	{
		ac_remove_elem(lst);
		lst = lst->next;
	}
	ft_memdel((void**)&lst);
}
