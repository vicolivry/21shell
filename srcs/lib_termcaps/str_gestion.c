/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   str_gestion.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 14:41:34 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 10:11:19 by volivry     ###    #+. /#+    ###.fr     */
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
				*x = 0;
				*y = *y + 1;
			}
			i++;
		}

}

int		remaining_chars(t_info *info, t_hist *hist)
{
	int	x;
	int	y;
	int	ret;

	x = 0;
	y = info->orig_y;
	ret = 0;
	end_position(info, hist, &x, &y);
	while (x != info->col_nb && y != info->row_nb)
	{
		if (x != info->col_nb)
			x++;
		else
		{
			x = 0;
			y++;
		}
		ret++;
	}
	ft_printf("\n\nremains %d chars\n", ret);
	return (0);
}
