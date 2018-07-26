/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   func_setenv.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/15 13:22:35 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:20:46 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int				func_setenv(t_struct **data, t_cmd *lst)
{
	/*
	int		i;
	char	**tmp;
	char	*str;

	i = 0;
	if ((str = ft_valid_env(*line)) == NULL)
		return (data->env);
	data->env = ft_existe_or_not(data, &str);
	if (str == NULL || data->env == NULL)
		return (data->env);
	while (data->env[i])
		i++;
	if (!(tmp = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = 0;
	while (data->env[i])
	{
		tmp[i] = ft_strdup(data->env[i]);
		i++;
	}
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = NULL;
	ft_del_tab(data->env);
	ft_strdel(&str);
	return (tmp);
	*/
	(void)data;
	(void)lst;
	return (0);
}
