/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoui_base.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 18:31:13 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/22 18:42:02 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(base) < 2)
		return (0);
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int		ft_check_str(char *str, char *base)
{
	while (*str)
	{
		if (ft_strchr(base, *str) == NULL)
			return (0);
		str++;
	}
	return (1);
}

static int		ft_value(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i] != c)
		i++;
	return (i);
}

unsigned int	ft_atoui_base(char *str, char *base)
{
	unsigned int	nb;
	int				pwr;
	int				b;

	nb = 0;
	b = ft_strlen(base);
	if (!ft_check_base(base) || !ft_check_str(str, base))
		return (0);
	pwr = ft_strlen(str) - 1;
	while (*str)
	{
		nb += ft_value(base, *str) * ft_power(b, pwr);
		pwr--;
		str++;
	}
	return (nb);
}
