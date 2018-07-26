/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_del_insert.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/27 10:51:34 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 11:30:50 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	insert_char(char c, t_info *info, t_hist *tmp)
{
	int		i;

	i = info->curs_in_str - 1;
	tputs(tgetstr("sc", NULL), 1, ft_putchar_err);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
	add_c_in_str(info, c, tmp);
	ft_putchar(c);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	while (i++ < info->s_len)
		ft_putchar(tmp->name[i]);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
	tputs(tgetstr("rc", NULL), 1, ft_putchar_err);
	right_key(info);
	info->s_len++;
	if ((info->s_len + ft_strlen(info->prmpt) - 1) % info->col_nb == 0 &&
			(info->orig_y + ((info->s_len + ft_strlen(info->prmpt) - 1) /
							info->col_nb) - 1 == info->row_nb))
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar_err);
		info->orig_y--;
	}
}

void	add_char(char c, t_info *info, t_hist *tmp)
{
	char	chr[2];

	chr[0] = c;
	chr[1] = '\0';
	tmp->name = !tmp->name ? ft_strdup(chr) : str_append(tmp->name, chr);
	ft_putchar(c);
	info->curs_x = CURS_X;
	info->curs_y = CURS_Y;
	info->curs_in_str++;
	info->s_len++;
	if (info->curs_y == info->row_nb && info->curs_x == 2)
		info->orig_y--;
}

void	del_char(t_info *info, t_hist *tmp)
{
	int	i;

	if (info->s_len && (info->curs_x > 1 || info->curs_y > info->orig_y))
	{
		left_key(info);
		i = info->curs_in_str - 2;
		tputs(tgetstr("sc", NULL), 1, ft_putchar_err);
		tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
		del_c_in_str(info, tmp);
		tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
		while (i++ < info->s_len - 1)
			ft_putchar(tmp->name[i]);
		tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
		tputs(tgetstr("rc", NULL), 1, ft_putchar_err);
		info->s_len--;
	}
}

void	add_c_in_str(t_info *info, char c, t_hist *tmp)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	str = NULL;
	if (!(str = (char*)malloc(info->s_len + 2)))
		return ;
	while (i++ < info->curs_in_str - 2)
		str[i] = tmp->name[i];
	str[i] = c;
	i++;
	j = i - 1;
	while (tmp->name[j])
	{
		str[i] = tmp->name[j];
		j++;
		i++;
	}
	str[i] = '\0';
	ft_strdel(&(tmp->name));
	tmp->name = ft_strdup(str);
	ft_strdel(&str);
}

void	del_c_in_str(t_info *info, t_hist *tmp)
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
		str[i] = tmp->name[i];
	j = i + 1;
	while (tmp->name[j])
	{
		str[i] = tmp->name[j];
		i++;
		j++;
	}
	str[i] = '\0';
	ft_strdel(&(tmp->name));
	tmp->name = ft_strdup(str);
	ft_strdel(&str);
}
