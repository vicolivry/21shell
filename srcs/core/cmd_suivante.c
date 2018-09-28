/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cmd_suivante.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/11 11:32:20 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/27 14:55:19 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int			cmd_suivante(t_ins *cpy, int code)
{
	if (!cpy)
		return (1);
	if (cpy->next == NULL)
		return (0);
	if (cpy->code == 0)
		return (0);
	if (cpy->code == 7)
	{
		if (code == 0)
			return (0);
		return (1);
	}
	if (cpy->code == 8)
	{
		if (code != 0)
			return (0);
		return (1);
	}
	return (0);
}
