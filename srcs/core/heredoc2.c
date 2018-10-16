/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   heredoc2.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 18:43:18 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 18:46:00 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char		*get_hd_trigger2(int i, char *tmp, char *str)
{
	int	len;

	len = 0;
	while (tmp[i])
	{
		str[len] = tmp[i];
		i++;
		len++;
	}
	str[len] = 0;
	ft_strdel(&tmp);
	return (str);
}

char			*get_hd_trigger(char *str)
{
	int		len;
	int		i;
	char	*tmp;

	i = 0;
	len = 0;
	tmp = clean_before(str);
	while (tmp[len] && tmp[len] != ' ')
		len++;
	if (!(g_info.h_d.trigger = malloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		g_info.h_d.trigger[i] = tmp[i];
		i++;
	}
	g_info.h_d.trigger[i] = 0;
	clear_line(&g_info.h_d.trigger);
	while (tmp[i] && tmp[i] == ' ')
		i++;
	ft_strdel(&str);
	if (!(str = malloc(ft_strlen(tmp) - len + 1)))
		return (NULL);
	return (get_hd_trigger2(i, tmp, str));
}
