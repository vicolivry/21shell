/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/19 14:32:59 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 11:47:54 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	print_prompt(t_info *info)
{
	ft_putstr(CYAN);
	ft_putstr(info->prmpt);
	ft_putstr(RESET);
}

void	change_prompt(t_info *info, int mode)
{
	if (!mode && ft_strcmp(info->prmpt, "$> "))
	{
		ft_strdel(&info->prmpt);
		info->prmpt = ft_strdup("$> ");
	}
	else if (mode == 1 && ft_strcmp(info->prmpt, "quote> "))
	{
		ft_strdel(&info->prmpt);
		info->prmpt = ft_strdup("quote> ");
	}
	else if (mode == 2 && ft_strcmp(info->prmpt, "dquote> "))
	{
		ft_strdel(&info->prmpt);
		info->prmpt = ft_strdup("dquote> ");
	}
}
