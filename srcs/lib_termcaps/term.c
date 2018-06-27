/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/12 12:15:32 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 10:12:44 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	raw_term_mode(t_info *info)
{
	char			*term_name;

	term_name = getenv("TERM");
	tcgetattr(STDIN_FILENO, &(info->term));
	if (tgetent(NULL, term_name) < 1)
		exit(1);
	info->term.c_lflag &= ~(ECHO | ICANON);
	info->term.c_oflag &= ~(OPOST);
	info->term.c_cc[VMIN] = 1;
	info->term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &(info->term));
	tputs(tgetstr("sc", NULL), 0, ft_putchar_err);
}

t_info	*memo_info(t_info *info, int mode)
{
	static t_info	*tmp = NULL;

	if (!mode)
		tmp = info;
	return (tmp);
}

void	default_term_mode(t_info *info)
{
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	while (info->curs_y > info->orig_y)
	{
		tputs(tgetstr("up", NULL), 0, ft_putchar_err);
		info->curs_y = CURS_Y;
	}
	while (info->curs_x > 1)
	{
		tputs(tgetstr("le", NULL), 0, ft_putchar_err);
		info->curs_x = CURS_X;
	}
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
	tcgetattr(STDIN_FILENO, &(info->term));
	info->term.c_lflag |= (ECHO | ICANON);
	info->term.c_oflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &(info->term));
}
