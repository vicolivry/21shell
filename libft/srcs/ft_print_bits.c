/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print_bits.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 10:10:37 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/14 09:13:10 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_print_bits(unsigned char oct)
{
	int i;

	i = 128;
	while (i > 0)
	{
		if (i & oct)
			ft_putchar('1');
		else
			ft_putchar('0');
		i /= 2;
	}
}
