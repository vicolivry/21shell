/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_del_insert2.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/06 14:11:26 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 16:40:03 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	if_end(t_info *info, t_hist *tmp)
{
	if (tmp->name)
		if (!((ft_strlen(tmp->name) + ft_strlen(info->prmpt)) % info->col_nb))
		{
			if (info->curs_y == info->row_nb)
				info->orig_y--;
			tputs(tgetstr("sf", NULL), 1, ft_putchar_err);
			if (info->curs_in_str >= info->s_len)
				get_x_back(info);
		}
}
