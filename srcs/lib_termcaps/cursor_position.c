/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_position.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 15:03:27 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/19 15:46:58 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		get_row(char *curs_pos)
{
	int		i;
	char	tmp[ft_strlen(curs_pos) + 1];

	i = 0;
	while (curs_pos[i] != ':')
	{
		tmp[i] = curs_pos[i];
		i++;
	}
	tmp[i] = 0;
	ft_strdel(&curs_pos);
	return (ft_atoi(tmp));
}

static int		get_col(char *curs_pos)
{
	int		i;
	char	tmp[ft_strlen(curs_pos) + 1];

	i = 0;
	while (curs_pos[i])
	{
		if (i > 0 && curs_pos[i - 1] == ':')
		{
			ft_strcpy(tmp, curs_pos + i);
			break ;
		}
		i++;
	}
	ft_strdel(&curs_pos);
	return (ft_atoi(tmp));
}

int				get_curs_pos(int mode, t_info *info)
{
	char	buf[2];
	int		ret;
	char	*curs_pos;

	curs_pos = NULL;
	write(1, "\E[6n", 4);
	ioctl(0, TIOCGWINSZ, &(info->wndw));
	while ((ret = read(0, buf, 1)) > 0)
	{
		buf[ret] = 0;
		if ((buf[0] >= '0' && buf[0] <= '9') || (buf[0] == ';'))
			curs_pos = str_append(curs_pos, buf[0] == ';' ? ":" : buf);
		if (ft_strchr(buf, 'R'))
			break ;
	}
	return (mode ? get_row(curs_pos) : get_col(curs_pos));
}
