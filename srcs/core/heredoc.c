/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   heredoc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/26 16:51:46 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 18:43:10 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char		*get_hd_cmd2(char *str, char *remain, int i)
{
	int	j;

	i += 2;
	j = 0;
	while (str[i] && str[i] != '>' && str[i] != '|')
	{
		remain[j] = str[i];
		i++;
		j++;
	}
	remain[j] = 0;
	if (ft_strstr(remain, "<<"))
		return (NULL);
	return (remain);
}

static char		*get_hd_cmd(char *str)
{
	int		len;
	int		i;
	char	*remain;

	i = 0;
	len = 0;
	while (str[len] != '<' && str[len + 1] != '<')
		len++;
	if (last_char(str) == '<')
		return (NULL);
	if (!(g_info.h_d.cmd = malloc(len + 2)))
		return (NULL);
	while (i <= len)
	{
		g_info.h_d.cmd[i] = str[i];
		i++;
	}
	g_info.h_d.cmd[i] = 0;
	clear_line(&g_info.h_d.cmd);
	if (!(remain = malloc(ft_strlen(str) - len + 2)))
		return (NULL);
	remain = remain ? get_hd_cmd2(str, remain, i) : NULL;
	if (remain)
		remain = get_hd_trigger(remain);
	return (remain);
}

static int		hd_err(char *remain, char *str, int *err)
{
	if (!g_info.h_d.trigger || !ft_strcmp(g_info.h_d.trigger, "") ||
	(str[0] == '<' && str[1] == '<') || ft_strstr(str, "<<<"))
	{
		ft_putstr("21sh: parse error near \\n\n");
		change_prompt(&g_info, 0);
		g_info.quoted = 0;
		*err = 1;
		return (1);
	}
	if (ft_strstr(remain, "<<"))
	{
		ft_putstr("Parse error: multiple heredocs in the same command\n");
		change_prompt(&g_info, 0);
		g_info.quoted = 0;
		*err = 1;
		return (1);
	}
	return (0);
}

static char		*quit_hd(void)
{
	t_hist *tmp;

	tmp = last_elem(g_info.history);
	ft_strdel(&g_info.h_d.cmd);
	ft_strdel(&g_info.h_d.trigger);
	if (g_info.line)
		ft_strdel(&g_info.line);
	g_info.loop = 0;
	change_prompt(&g_info, 0);
	g_info.quoted = 0;
	remove_this_elem(tmp);
	if (g_info.h_d.fill)
		g_info.h_d.fill[ft_strlen(g_info.h_d.fill) - 1] = 0;
	return (g_info.h_d.fill);
}

char			*heredoc(char *str, int *err)
{
	char	*remain;
	t_hist	*tmp;
	int		first_round;

	tmp = last_elem(g_info.history);
	first_round = 1;
	remain = get_hd_cmd(str);
	if (hd_err(remain, str, err))
		return (NULL);
	change_prompt(&g_info, 4);
	g_info.h_d.fill = NULL;
	ft_strdel(&remain);
	while (g_info.h_d.trigger && (!tmp->name ||
		ft_strcmp(tmp->name, g_info.h_d.trigger)))
	{
		if (g_info.line && !first_round)
			g_info.h_d.fill = str_append(g_info.h_d.fill, g_info.line);
		if (!first_round)
			g_info.h_d.fill = str_append(g_info.h_d.fill, "\n");
		reinit_info(&g_info);
		line_edit(&g_info, tmp);
		tmp = last_elem(g_info.history);
		first_round = 0;
	}
	return (quit_hd());
}
