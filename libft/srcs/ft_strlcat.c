/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/03 12:01:01 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/03 12:01:05 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*dst_b;
	const char	*src_b;
	size_t		n;
	size_t		dst_len;

	dst_b = dst;
	src_b = src;
	n = size;
	while (n-- != 0 && *dst_b != '\0')
		dst_b++;
	dst_len = dst_b - dst;
	n = size - dst_len;
	if (n == 0)
		return (dst_len + ft_strlen(src_b));
	while (*src_b != '\0')
	{
		if (n != 1)
		{
			*dst_b++ = *src_b;
			n--;
		}
		src_b++;
	}
	*dst_b = '\0';
	return (dst_len + (src_b - src));
}
