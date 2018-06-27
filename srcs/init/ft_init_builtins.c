/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_builtins.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 13:00:14 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 12:22:32 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	initialise builtins in struct
*/

char		**ft_initialise_builtins(void)
{
	char	**tabl;

	if (!(tabl = (char**)malloc(sizeof(char *) * 6)))
		return (NULL);
	tabl[0] = ft_strdup("cd");
	tabl[1] = ft_strdup("echo");
	tabl[2] = ft_strdup("setenv");
	tabl[3] = ft_strdup("unsetenv");
	tabl[4] = ft_strdup("env");
	tabl[5] = NULL;
	return (tabl);
}
