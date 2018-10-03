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

void	add_c_in_str(t_info *info, char c)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	str = NULL;
	if (!(str = (char*)malloc(info->s_len + 2)))
		return ;
	while (i++ < info->curs_in_str - 2)
		str[i] = info->line[i];
	str[i] = c;
	i++;
	j = i - 1;
	while (info->line[j])
	{
		str[i] = info->line[j];
		j++;
		i++;
	}
	str[i] = '\0';
	ft_strdel(&(info->line));
	info->line = ft_strdup(str);
	ft_strdel(&str);
}

void	del_c(t_info *info)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	i = -1;
	str = NULL;
	if (!(str = (char*)malloc(info->s_len)))
		return ;
	while (i++ < info->curs_in_str - 2)
		str[i] = info->line[i];
	j = i + 1;
	while (info->line[j])
	{
		str[i] = info->line[j];
		i++;
		j++;
	}
	str[i] = '\0';
	ft_strdel(&(info->line));
	info->line = ft_strdup(str);
	ft_strdel(&str);
}
