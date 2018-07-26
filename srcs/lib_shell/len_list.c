/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   len_list.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/12 07:25:56 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 11:49:17 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int			len_list(t_cmd *lst)
{
	t_cmd	*cpy;
	int		i;

	if (lst == NULL)
		return (0);
	cpy = lst;
	i = 0;
	while (cpy)
	{
		i++;
		cpy = cpy->next;
	}
	return (i);
}
