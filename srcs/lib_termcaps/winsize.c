/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   str_gestion.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 14:41:34 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 17:48:47 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Returns the number of characters to be possibly typed in the terminal
** in order to check if the window is big enough.
*/

int		remaining_chars(t_info *info, t_hist *hist)
{
	int	char_nb;
	int	hist_len;

	hist_len = hist->name ? ft_strlen(hist->name) : 0;
	char_nb = info->row_nb * info->col_nb;
	return (char_nb - (hist_len + ft_strlen(info->prmpt)) - 1);
}
