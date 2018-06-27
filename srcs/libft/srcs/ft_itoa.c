/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/03 11:38:05 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 16:34:36 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_countchar(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n /= 10)
		count++;
	return (count);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_countchar(n);
	if ((str = malloc(len + 1)) == NULL)
		return (NULL);
	str[len] = '\0';
	len--;
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	while (n > 0)
	{
		str[len] = '0' + (n % 10);
		len--;
		n /= 10;
	}
	return (str);
}
