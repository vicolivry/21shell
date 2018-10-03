/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signals.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 12:14:19 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 14:13:39 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void		resize(t_info *info, t_hist *tmp)
{
	int	i;

	print_prompt(info);
	ft_putstr(tmp->name);
	info->s_len = tmp->name ? ft_strlen(tmp->name) : 0;
	i = info->s_len ? info->s_len + 1 : 1;
	i -= (info->s_len + ft_strlen(info->prmpt)) % info->col_nb == 0 ? 1 : 0;
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

static void		resize_win(int sig)
{
	t_hist	*tmp;
	t_info	*info;

	(void)sig;
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
	t_info	*info;
	char	s[2];

	info = &g_info;
	s[0] = info->term.c_cc[VSUSP];
	s[1] = 0;
	(void)sig;
	default_term_mode(info);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, s);
}

static void		restart(int sig)
{
	t_info	*info;

	info = &g_info;
	(void)sig;
	raw_term_mode(info);
	resize_win(sig);
}

void			get_signals(void)
{
	signal(SIGWINCH, resize_win);
	signal(SIGTSTP, stop);
	signal(SIGCONT, restart);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
