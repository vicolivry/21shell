/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   str_gestion.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 14:41:34 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 14:40:27 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	end_position(t_info *info, t_hist *hist, int *x, int *y)
{
	int	i;

	i = 0;
	if (hist->name)
		while (i < ft_strlen(hist->name) + ft_strlen(info->prmpt))
		{
			if (*x != info->col_nb)
				*x = *x + 1;
			else
			{
				*x = 1;
				*y = *y + 1;
			}
			i++;
		}
	else
		*x = ft_strlen(info->prmpt) + 1;
}

int		remaining_chars(t_info *info, t_hist *hist)
{
	int	x;
	int	y;
	int	ret;

	x = 1;
	y = info->orig_y;
	ret = 0;
	end_position(info, hist, &x, &y);
/*	get_x_back(info);
	ft_printf("\nx : %d, y : %d\n", x, y);
	get_x_back(info);*/
	while (x != info->col_nb || y != info->row_nb)
	{
		if (x != info->col_nb)
			x++;
		else
		{
			x = 1;
			y++;
		}
		ret++;
	}
/*	get_x_back(info);
	ft_printf("remains %d chars\n", ret);
	get_x_back(info);*/
	if (y != 1)
		return (1);
	else
		return (ret);
}
