/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/03 12:04:15 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/17 14:32:31 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char			**output;
	size_t			count;
	unsigned int	i;
	size_t			j;

	count = ft_wordcount(s, c);
	if (!s || !(output = (char**)malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (j < count && s[i])
	{
		if ((i == 0 && s[i] != c) || (i > 0 && (s[i] != c && s[i - 1] == c)))
		{
			output[j] = ft_strsub(s, i, word_length(s + i, c));
			j++;
		}
		i++;
	}
	output[j] = NULL;
	return (output);
}
