/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   autocomp.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 13:07:19 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/02 16:22:01 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"


static void	infinite_loop(t_info *info, t_slct *slct)
{
	int	loop;

	loop = 1;
	while (loop)
	{
		update_index(slct);
		ac_get_info(slct, info);
		key_input(info, slct, &loop);
		display(info, slct);
	}
}

void		autocomp(t_info *info)
{
	t_slct	*slct;

	slct = init_slct();
	ac_get_info(slct, info);
	slct->next->current = 1;
	update_index(slct);
	display(info, slct);
	infinite_loop(info, slct);
}
