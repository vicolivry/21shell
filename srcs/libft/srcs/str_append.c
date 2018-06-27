/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   str_append.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/03 16:09:17 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/16 12:33:55 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./libft.h"

char	*str_append(char *s1, char *s2)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(s1, s2);
	ft_strdel(&s1);
	s1 = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (s1);
}
