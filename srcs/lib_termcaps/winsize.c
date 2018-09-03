/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   str_gestion.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 14:41:34 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 13:33:17 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		remaining_chars(t_info *info, t_hist *hist)
{
	int	char_nb;
	int	hist_len;

	hist_len = hist->name ? ft_strlen(hist->name) : 0;
	char_nb = info->row_nb * info->col_nb;
	return (char_nb - (hist_len + ft_strlen(info->prmpt)) - 1);
}
