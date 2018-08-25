/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   autocomp.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 13:07:19 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/02 16:22:01 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"


static void	infinite_loop(t_info *info, t_slct *slct, t_hist *hist)
{
	int	loop;
//	int	size;

	loop = 1;
//	size = remaining_chars(info, hist);
	while (loop)
	{
		key_input(info, slct, &loop, hist);
		if (loop)
//			if (size > 0)
				display(info, slct);
	}
	free_slct(slct, info);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
}

char	*get_last_word(char	*line)
{
	char	**table;
	t_list	*lst;
	t_list	*tmp;

	if (line == NULL || !ft_strcmp(line, "") ||
			(table = ft_strsplit(line, ' ')) == NULL)
		return (NULL);
	lst = tab_to_lst(table);
	tmp = lst;
	while (tmp->next->next != NULL)
	tmp = tmp->next;
	ft_strdel(&line);
	line = ft_strdup(tmp->content);
	free_lst(lst);
	return (line);
}

void		autocomp(t_info *info, t_hist *hist)
{
	t_slct	*slct;
	char	*line;

	line = ft_strdup(hist->name);
	line = get_last_word(line);
	slct = init_slct(line);
	if (!slct)
	{
		tputs(tgetstr("be", NULL), 1, ft_putchar_err);
		return ;
	}
	ac_get_info(slct, info);
	update_index(slct);
	end_key(info);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	tputs(tgetstr("sf", NULL), 1, ft_putchar_err);
	get_x_back(info);
	display(info, slct);
	infinite_loop(info, slct, hist);
}
