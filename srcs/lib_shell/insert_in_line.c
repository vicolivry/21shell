/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   insert_in_line.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 11:18:47 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 11:18:53 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

char	*insert_in_line(char *str, int i, char *insert)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	if (!(str))
		return (NULL);
	if (!(tmp = ft_strsub(str, 0, i)))
		return (NULL);
	if (!(tmp2 = ft_strsub(str, i + 1, ft_strlen(str) - (i + 1))))
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	tmp3 = ft_strjoin(tmp, insert);
	ft_strdel(&tmp);
	tmp = ft_strjoin(tmp3, tmp2);
	ft_strdel(&tmp2);
	ft_strdel(&tmp3);
	return (tmp);
}
