/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_info.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/30 12:07:02 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/02 16:10:25 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	ac_get_info(t_slct *slct, t_info *info)
{
	t_slct	*tmp;

	tmp = ac_first_elem(slct);
	while (tmp != slct)
	{
		if (tmp->len > info->max_len)
			info->max_len = tmp->len;
		info->nb_elem++;
		tmp = tmp->next;
	}
}
