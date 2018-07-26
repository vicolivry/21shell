/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   end_quote.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 13:43:07 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 11:29:57 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	single_toggle(t_info *info)
{
	if (!(info->quoted))
		info->quoted = 1;
	else
		info->quoted = 0;
}

static void	double_toggle(t_info *info)
{
	if (!(info->quoted))
		info->quoted = 2;
	else
		info->quoted = 0;
}

void		toggle_quote(t_info *info)
{
	int	i;

	i = 0;
	if (info->line)
		while (i <= info->s_len)
		{
			if (((i == 0 && info->line[i] == '"') || (i > 0
							&& info->line[i] == '"'
							&& info->line[i - 1] != '\\')) && info->quoted != 1)
				double_toggle(info);
			if (((i == 0 && info->line[i] == 39) || (i > 0
							&& info->line[i] == 39
							&& info->line[i - 1] != '\\')) && info->quoted != 2)
				single_toggle(info);
			i++;
		}
	if (!info->quoted)
		change_prompt(info, 0);
	else
		info->quoted == 1 ? change_prompt(info, 1) : change_prompt(info, 2);
}
