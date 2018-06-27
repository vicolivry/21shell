/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 09:20:56 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/14 09:13:58 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Print good prompt
*/

void		ft_display(t_struct *data)
{
	ft_putstr("\033[32m");
	if (data->prompt_current == NULL)
		ft_putstr(data->prompt);
	else
		ft_putstr(data->prompt_current);
	ft_putstr("\033[0m");
}
