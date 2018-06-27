/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_insert_tild.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/22 11:48:06 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 11:59:44 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  replace ~ for the path and return len path
*/

int		ft_insert_tild(t_struct *data, char **str, int i)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = i;
	tmp = ft_strsub(*str, 0, i);
	tmp2 = ft_strsub(*str, i + 1, ft_strlen(*str) - i - 1);
	ft_strdel(str);
	*str = ft_strjoin(tmp, data->home);
	ft_strdel(&tmp);
	tmp = ft_strjoin(*str, tmp2);
	ft_strdel(&tmp2);
	ft_strdel(str);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (ft_strlen(data->home));
}
