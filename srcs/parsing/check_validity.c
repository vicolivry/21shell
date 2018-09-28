/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_validity.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/11 09:42:47 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 15:58:10 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		replace_order(char ***tabl, int i)
{
	ft_strdel(&(*tabl)[i]);
	if ((*tabl)[i + 1] != NULL)
		(*tabl)[i] = ft_strdup((*tabl)[i + 1]);
	i++;
	while ((*tabl)[i])
	{
		if ((*tabl)[i + 1] != NULL)
		{
			ft_strdel(&(*tabl)[i]);
			(*tabl)[i] = ft_strdup((*tabl)[i + 1]);
		}
		else
		{
			ft_strdel(&(*tabl)[i]);
			return (0);
		}
		i++;
	}
	return (0);
}

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
	int		quit;
	t_path	*start;

	start = NULL;
	while (*lst)
	{
		i = 0;
		quit = 0;
		while ((*lst)->tab_cmd[i] && quit == 0)
		{
			quit = replace_in_line(data, &(*lst)->tab_cmd[i]);
			if (quit == -1)
			{
				replace_order(&(*lst)->tab_cmd, i);
				i = 0;
				quit = 0;
			}
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
	if (lst->op_next == 2 && lst->pathname == NULL)
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
	return (0);
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
