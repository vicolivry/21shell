/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   good_func.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 11:20:03 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:21:19 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	start good function (for builtins)
*/

int		ft_search_func(t_struct *mystruct, t_cmd *lst, int i)
{
	int		ret;

	ret = 0;
	if (i == 0)
		ret = func_cd(mystruct, lst);
	else if (i == 1)
		ret = func_echo(mystruct, lst);
	else if (i == 2)
		ret = func_setenv(&mystruct, lst);
	else if (i == 3)
		ret = func_unsetenv(&mystruct, lst);
	else if (i == 4)
		ret = func_env(mystruct, lst);
	else if (i == 5)
		ret = func_exit(mystruct, lst);
	return (ret);
}
