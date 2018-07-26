/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_env.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 13:22:16 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:19:36 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Core env
*/

int			func_env(t_struct *data, t_cmd *lst)
{
	/*
	char	**tabl;
	char	*line;
	int		i;

	line = ft_strdup(lst->tab_cmd[0]);
	tabl = NULL;
	i = 0;
	data->option_i_env = 0;
	data->env_tmp = ft_del_tab(data->env_tmp);
	ft_check_line(data, line, 0);
	tabl = ft_strsplit(*line, ' ');
	while (tabl[i] && (ft_strcmp(tabl[i], "env") == 0 ||
	ft_strcmp(tabl[i], "/usr/bin/env") == 0))
		i++;
	if (ft_len_tab(tabl) == i)
	{
		ft_del_tab(tabl);
		print_full_env(data);
		return ;
	}
	ft_env(data, tabl, i);
	tabl = ft_del_tab(tabl);
	data->env_tmp = ft_del_tab(data->env_tmp);
	*/
	int i = 0;
	printf("BUILTINS ENV\n");
	while (data->env[i])
	{
		ft_putendl(data->env[i]);
		i++;
	}
	(void)lst;
	return (0);
}
