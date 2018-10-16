/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_validity.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/11 09:42:47 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 10:30:04 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Replace special char in tab and check access for redirection
*/

static int		check_file_redir(t_struct *data, t_path *start)
{
	if (start == NULL)
		return (0);
	while (start)
	{
		if (ft_access_rep(start->name, 0) == 0)
		{
			if (ft_access_rep(start->name, 2) == 1)
			{
				ft_putstr_fd("21sh: ", 2);
				ft_putstr_fd(start->name, 2);
				ft_putstr_fd(" : Permission denied\n", 2);
				data->code_erreur = 1;
				return (1);
			}
		}
		start = start->next;
	}
	return (0);
}

static int		check_lst_special(t_struct *data, t_cmd **lst, int i)
{
	t_path	*start;

	start = NULL;
	if ((*lst)->tab_cmd == NULL)
		return (1);
	while (*lst)
	{
		i = 0;
		if ((*lst)->tab_cmd == NULL)
			return (0);
		while ((*lst)->tab_cmd[i])
		{
			replace_in_line(data, &(*lst)->tab_cmd[i]);
			i++;
		}
		start = (*lst)->pathname;
		if (check_file_redir(data, start) == 1)
			return (1);
		*lst = (*lst)->next;
	}
	return (0);
}

/*
**	Replace special char in tab and check access for redirection
*/

int				check_link(t_cmd *lst)
{
	if (lst->op_next == 1 && lst->next->rep == NULL)
		return (1);
	if ((lst->op_next == 2 || lst->op_next == 3) && lst->pathname == NULL)
		return (1);
	return (0);
}

/*
**	Check validity of lst && replace $ and ~
*/

int				check_validity(t_cmd **lst, t_struct *data)
{
	t_cmd	*start;

	if (!(*lst))
		return (1);
	start = *lst;
	if (check_lst_special(data, &start, 0) == 1)
		return (1);
	start = *lst;
	while (start)
	{
		if (check_link(start) != 0)
		{
			ft_putstr_fd("21sh: invalid command\n", 2);
			data->code_erreur = 1;
			return (1);
		}
		start = start->next;
	}
	return (0);
}
