/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_regex_classic.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 10:18:35 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/23 10:25:02 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		check_regex_classic(t_struct *data, char **line)
{
	if (ft_strcmp(*line, "$$") == 0)
	{
		ft_strdel(line);
		*line = ft_itoa_base(data->pid, 10);
		return (0);
	}
	else if (ft_strcmp(*line, "$?") == 0)
	{
		ft_strdel(line);
		*line = ft_itoa_base(data->code_erreur, 10);
		return (0);
	}
	else if (ft_strcmp(*line, "~") == 0 || ft_strcmp(*line, "~-") == 0)
	{
		ft_strdel(line);
		*line = ft_return_home(data);
		return (0);
	}
	else if (ft_strcmp(*line, "-") == 0)
	{
		ft_strdel(line);
		*line = ft_return_moins(data);
		return (0);
	}
	return (1);
}
