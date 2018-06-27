/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_power.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/08 15:51:10 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/22 18:41:35 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_power(int nb, int pwr)
{
	int	tmp;

	tmp = nb;
	if (pwr == 0)
		return (1);
	if (pwr < 0)
		return (0);
	while (pwr > 1)
	{
		nb = nb * tmp;
		pwr--;
	}
	return (nb);
}
