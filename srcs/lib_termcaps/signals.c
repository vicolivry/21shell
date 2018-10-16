/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signals.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 12:14:19 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 15:28:04 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void		resize2(t_info *info, int i)
{
	get_curs_pos(info);
	while (i > info->curs_in_str)
	{
		left_key(info);
		if (i != 1)
			info->curs_in_str++;
		i--;
	}
	get_curs_pos(info);
}

static void		resize(t_info *info, t_hist *tmp)
{
	int	i;

	print_prompt(info);
	if (info->curs_in_str == 1)
	{
		ft_putstr(tmp->name);
		tputs(tgoto(tgetstr("cm", NULL), ft_strlen(info->prmpt), 0),
		1, ft_putchar_err);
		home_key(info);
		return ;
	}
	ft_putstr(tmp->name);
	get_curs_pos(info);
	info->s_len = tmp->name ? ft_strlen(tmp->name) : 0;
	i = info->s_len ? info->s_len + 1 : 1;
	if ((info->s_len + ft_strlen(info->prmpt)) % info->col_nb == 0)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, info->curs_x == 1 ?
		info->curs_y + 1 : info->curs_y), 1, ft_putchar_err);
		get_curs_pos(info);
		return ;
	}
	resize2(info, i);
}

/*
** Handles the resizing of the terminal window.
*/

static void		resize_win(int sig)
{
	t_hist	*tmp;
	t_info	*info;

	(void)sig;
	if (g_data->is_executing)
		return ;
	info = &g_info;
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	tmp = first_elem(info->history);
	while (!tmp->current)
		tmp = tmp->next;
	if (info->line)
		ft_strdel(&(info->line));
	info->line = ft_strdup(tmp->name);
	ioctl(0, TIOCGWINSZ, &(info->wndw));
	info->row_nb = info->wndw.ws_row;
	info->col_nb = info->wndw.ws_col;
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar_err);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
	if (remaining_chars(info, tmp) < 0)
		ft_putstr("EXPAND WINDOW SIZE");
	else
		resize(info, tmp);
	info->orig_y = 0;
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
}

static void		stop(int sig)
{
	int		pid;

	pid = 0;
	if (g_data->is_executing)
	{
		pid = g_data->commandes->cmd->pid;
		kill(g_data->commandes->cmd->pid, 9);
		ft_putstr_fd("Process stopped : [", 2);
		ft_putnbr_fd(pid, 2);
		ft_putstr_fd("]\n", 2);
	}
	(void)sig;
}

void			get_signals(void)
{
	signal(SIGWINCH, resize_win);
	signal(SIGTSTP, stop);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGURG, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
}
