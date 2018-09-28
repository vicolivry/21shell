/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alt_keys.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/27 10:42:20 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 17:21:25 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void		alt_up_down(t_info *info, char *buff)
{
	if ((KEY_CODE_ALT_UP) && info->curs_y > info->orig_y)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar_err);
		get_curs_pos(info);
		info->curs_in_str -= info->col_nb;
	}
	else if ((KEY_CODE_ALT_DOWN) && info->s_len + ft_strlen(info->prmpt)
			> info->col_nb)
	{
		if (info->s_len - info->curs_in_str >= info->col_nb)
		{
			get_curs_pos(info);
			info->curs_y++;
			tputs(tgoto(tgetstr("cm", NULL), info->curs_x - 1,
						info->curs_y - 1), 1, ft_putchar_err);
			get_curs_pos(info);
			info->curs_in_str += info->col_nb;
		}
		else if (info->curs_y < info->row_nb)
			end_key(info);
	}
	if (info->curs_x <= ft_strlen(info->prmpt) && info->curs_y == info->orig_y)
		while (info->curs_x <= ft_strlen(info->prmpt))
			right_key(info);
	get_curs_pos(info);
}

void		alt_left(t_info *info, t_hist *tmp)
{
	if (!tmp->name)
		return ;
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	if (info->curs_in_str > 1 && !ft_iswhite(tmp->name[info->curs_in_str - 1])
			&& ft_iswhite(tmp->name[info->curs_in_str - 2]))
		left_key(info);
	if (!ft_iswhite(tmp->name[info->curs_in_str - 1]))
		while (info->curs_in_str > 1 &&
				!ft_iswhite(tmp->name[info->curs_in_str - 1]))
			left_key(info);
	else
	{
		while (info->curs_in_str > 1 &&
				ft_iswhite(tmp->name[info->curs_in_str - 1]))
			left_key(info);
		while (info->curs_in_str > 1 &&
				!ft_iswhite(tmp->name[info->curs_in_str - 1]))
			left_key(info);
	}
	if (info->curs_in_str > 1)
		right_key(info);
	get_curs_pos(info);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
}

void		alt_right(t_info *info, t_hist *tmp)
{
	if (!tmp->name)
		return ;
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	if (!ft_iswhite(tmp->name[info->curs_in_str - 1]) ||
			!ft_iswhite(tmp->name[info->curs_in_str]))
	{
		while (info->curs_in_str <= ft_strlen(tmp->name)
				&& !ft_iswhite(tmp->name[info->curs_in_str - 1]))
			right_key(info);
		while (info->curs_in_str <= ft_strlen(tmp->name)
				&& ft_iswhite(tmp->name[info->curs_in_str - 1]))
			right_key(info);
	}
	else
		while (info->curs_in_str <= ft_strlen(tmp->name)
				&& ft_iswhite(tmp->name[info->curs_in_str - 1]))
			right_key(info);
	get_curs_pos(info);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
}

void		ctrl_d(t_info *info, t_hist *tmp)
{
	if (tmp->name && ft_strcmp(tmp->name, ""))
		return ;
	else
	{
		info->line = ft_strdup("exit");
		info->loop = 0;
	}
}