/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_echo.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 13:22:07 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 10:07:34 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Func echo provisoire
** 	reste option a gerer
*/

static void		option_n(int n)
{
	if (n == 0)
		ft_putstr("\n");
	else
		ft_putstr("\033[7m%\033[0m\n");
}

int				func_echo(t_struct *data, t_cmd *lst)
{
	int		i;
	int		no_return;

	i = 1;
	no_return = 0;
	(void)data;
	while (lst->tab_cmd[i])
	{
		if (lst->tab_cmd[i] != NULL && i == 1)
		{
			if (ft_strcmp(lst->tab_cmd[i], "-n") == 0)
				no_return = 1;
			else
				ft_putstr(lst->tab_cmd[i]);
		}
		else
			ft_putstr(lst->tab_cmd[i]);
		if (lst->tab_cmd[i + 1] != NULL)
			ft_putstr(" ");
		i++;
	}
	option_n(no_return);
	return (0);
}
