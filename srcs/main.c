/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/29 15:00:57 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/04 13:58:26 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/shell.h"

/*
**	Test si on peux malloc correctement en lancant le programme, sinon on quite
**	le shell.
*/

static int		ft_test_system(void)
{
	int		i;
	char	*test;

	i = 0;
	test = NULL;
	while (i < 10)
	{
		if (!(test = ft_strnew(2000000)))
			return (EXIT_FAILURE);
		ft_strdel(&test);
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
**	Usage 21sh
*/

static int		help_bash(int ac, char **av)
{
	if (ac == 1)
		return (0);
	if (ac > 1)
	{
		if (ft_strcmp(av[1], "--help") == 0)
		{
			ft_putstr("Based on GNU bash, version 1.0.0-(yoginet - volivry)\n");
			ft_putstr("Usage : ./21sh\n");
			return (1);
		}
	}
	return (0);
}

static int		env_incompleted(char **env)
{
	if (ft_len_tab(env) < 20)
	{
		ft_putstr_fd("21sh: Environnment incomplet 🖕\n", 2);
		return (1);
	}
	return (0);
}

/*
**	Main 42sh
**	Retourne la valeur de exit
*/

int				main(int argc, char **argv, char **env)
{
	int			code_exit;

	if (help_bash(argc, argv) == 1 || !isatty(0) || env_incompleted(env) == 1)
		return (0);
	if (ft_test_system() == 1)
		return (1);
	print_ascii_art_start();
	code_exit = 0;
	g_data = NULL;
	if (!(g_data = init_struct(env)))
		return (EXIT_FAILURE);
	core_shell(g_data);
	code_exit = ft_delete_struct(&g_data);
	print_ascii_art_end();
	//ft_printf("SLEEP\n");
	//sleep(150);
	return (code_exit);
}
