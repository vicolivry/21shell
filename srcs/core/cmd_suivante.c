/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cmd_suivante.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/11 11:32:20 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 14:43:08 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Check la commande suivante a executer (selon code erreur)
*/

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
