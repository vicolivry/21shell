/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/29 15:00:57 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/14 09:04:45 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int				main(int argc, char **argv, char **env)
{
	char		*line;
	t_struct	*data;

	(void)argc;
	(void)argv;
	line = NULL;
	data = init_struct(env);
	core_shell(&line, data);
	ft_strdel(&line);
	ft_delete_struct(data);
	return (0);
}
