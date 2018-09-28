/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_exit.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 13:22:16 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/10 12:43:14 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int			test_arg_exit(char *str, t_struct *data)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
		{
			ft_putstr_fd("21sh: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			data->code_erreur = 255;
			return (1);
		}
		i++;
	}
	return (0);
}

int			func_exit(t_struct *data, t_cmd *lst)
{
	int		ret;
	int		test;

	ret = 0;
	test = 0;
	if (ft_len_tab(lst->tab_cmd) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		data->code_erreur = 1;
		return (1);
	}
	test = test_arg_exit(lst->tab_cmd[1], data);
	if (lst->tab_cmd[1] == NULL)
		ret = 0;
	else
		ret = ft_atoi(lst->tab_cmd[1]);
	if (test == 0)
		data->code_erreur = ret;
	default_term_mode(&g_info);
	return (-1);
}
