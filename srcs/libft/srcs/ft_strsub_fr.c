/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub_fr.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/16 12:00:31 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/16 12:20:12 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strsub_fr(char const *s, unsigned int start, size_t len)
{
	char			*newstr;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(newstr = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
		newstr[i++] = s[start++];
	newstr[i] = '\0';
	ft_strdel((char**)&s);
	s = ft_strdup(newstr);
	ft_strdel(&newstr);
	return ((char*)s);
}
