/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   heredoc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/26 16:51:46 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/26 16:51:48 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char	*get_hd_trigger(char *str)
{
	int		len;
	int		i;
	char	*tmp;

	i =  0;
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
	ft_strdel (&str);
	if (!(str = malloc(ft_strlen(tmp) - len + 1)))
		return (NULL);
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

static char *get_hd_cmd()
{
	int		len;
	int		i;
	int		j;
	char	*remain;

	i = 0;
	len = 0;
	while (g_info.line[len] != '<' && g_info.line[len + 1] != '<')
		len++;
	if (last_char(g_info.line) == '<')
	return (NULL);
	if (!(g_info.h_d.cmd = malloc(len + 2)))
		return (NULL);
	while (i <= len)
	{
		g_info.h_d.cmd[i] = g_info.line[i];
		i++;
	}
	g_info.h_d.cmd[i] = 0;
	clear_line(&g_info.h_d.cmd);
	if (!(remain = malloc(ft_strlen(g_info.line) - len + 2)))
		return (NULL);
	i += 2;
	j = 0;
	while (g_info.line[i])
	{
		remain[j] = g_info.line[i];
		i++;
		j++;
	}
	remain[j] = 0;
	remain = ft_strdup(get_hd_trigger(remain));
	return (remain);	
}

static int	hd_err(char *remain)
{
	if (!g_info.h_d.trigger || !ft_strcmp(g_info.h_d.trigger, "") ||
	(g_info.line[0] == '<' && g_info.line[1] == '<'))
	{
		ft_putstr("21sh: parse error near \\n\n");	
		ft_strdel(&g_info.line);
		return (1);
	}
	if (ft_strstr(remain, "<<"))
	{
		ft_putstr("Parse error: multiple heredocs in the same command\n");
		ft_strdel(&g_info.line);
		return (1);
	}
	return (0);
}

static void	quit_hd(void)
{
	t_hist *tmp;

	tmp = last_elem(g_info.history);
	ft_strdel(&g_info.h_d.cmd);
	ft_strdel(&g_info.h_d.trigger);
	ft_strdel(&g_info.line);
	g_info.loop = 0;
	change_prompt(&g_info, 0);
	g_info.quoted = 0;
	remove_elem(tmp);
}

char *heredoc(void)
{
	char	*remain;
	t_hist	*tmp;
	int		first_round;

	first_round = 1;
	tmp = last_elem(g_info.history);
	remain = get_hd_cmd();
	if (hd_err(remain))
	{
		change_prompt(&g_info, 0);
		g_info.quoted = 0;
		return (NULL);
	}
	change_prompt(&g_info, 4);
	g_info.quoted = 4;
	g_info.h_d.fill = remain ? ft_strdup(remain) : NULL;
	ft_strdel(&remain);
	fill_history(&g_info, tmp);
	while (g_info.h_d.trigger && ft_strcmp(g_info.line, g_info.h_d.trigger))
	{
		if (g_info.line && !first_round)
		{
			g_info.h_d.fill = str_append(g_info.h_d.fill, "\n");
			g_info.h_d.fill = str_append(g_info.h_d.fill, g_info.line);
		}
		first_round = 0;
		reinit_info(&g_info);
		line_edit(&g_info, tmp);
	}
	quit_hd();
	return (g_info.h_d.fill);
}