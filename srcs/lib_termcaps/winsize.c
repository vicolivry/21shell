/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   str_gestion.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 14:41:34 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 16:40:37 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"
/*
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
*/
int		remaining_chars(t_info *info, t_hist *hist)
{
	int	char_nb;
	int	hist_len;

	hist_len = hist->name ? ft_strlen(hist->name) : 0;
	char_nb = info->row_nb * info->col_nb;
	return (char_nb - (hist_len + ft_strlen(info->prmpt)));
}
