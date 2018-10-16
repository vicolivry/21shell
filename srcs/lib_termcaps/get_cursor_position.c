/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_cursor_position.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 11:18:28 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/04 11:28:22 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Gets x and y coordinates of the cursor position
*/

void	get_curs_pos(t_info *info)
{
	char	pos[20];
	char	*str;
	int		i;

	i = 0;
	str = "\033[6n";
	ft_bzero(pos, 20);
	ft_printf("%s", str);
	read(0, pos, 20);
	info->curs_y = ft_atoi(pos + 2);
	while (pos[i] && pos[i] != 59)
		i++;
	info->curs_x = ft_atoi(pos + i + 1);
}
