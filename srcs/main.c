/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/29 15:00:57 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 17:50:03 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/shell.h"

/*
**	Main 42sh
**	Ignore argc et argv
**	Retourne la valeur de exit
*/

static void		print_ascii_art_start(void)
{
	ft_putstr(L_BLUE);
	ft_printf("       ::::::::    :::   ::::::::  :::    ::: \n");
	ft_printf("     :+:    :+: :+:+:  :+:    :+: :+:    :+:  \n");
	ft_printf("          +:+    +:+  +:+        +:+    +:+   \n");
	ft_printf("       +#+      +#+  +#++:++#++ +#++:++#++    \n");
	ft_printf("    +#+        +#+         +#+ +#+    +#+     \n");
	ft_printf("  #+#         #+#  #+#    #+# #+#    #+#      \n");
	ft_printf("########## ####### ########  ###    ###       \n");
	ft_printf("\n");
	ft_printf("© - volivry\n");
	ft_printf("© - yoginet\n");
	ft_putstr(RESET);
}

static void		print_ascii_art_end(void)
{
	ft_putstr(L_BLUE);
	ft_printf(" _________\n");
	ft_printf("< goodbye >\n");
	ft_printf(" ---------\n");
	ft_printf("        \\   ^__^\n");
	ft_printf("         \\  (oo)\\_______\n");
	ft_printf("            (__)\\       )\\/\\\n");
	ft_printf("                ||----w |\n");
	ft_printf("                ||     ||\n");
	ft_putstr(RESET);
}

static int      ft_test_system(void)
{
    int     i;
    char    *test;

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

static int		help_bash(int ac, char **av)
{
	if (ac == 1)
		return (0);
	if (ac > 1)
	{
		if (ft_strcmp(av[1], "--help") == 0)
		{
			ft_putstr("GNU bash, version 1.0.0-(yoginet - volivry)\n");
			ft_putstr("Usage : ./21sh\n");
			return (1);
		}
	}
	return (0);
}

int				main(int argc, char **argv, char **env)
{
	t_struct	*data;
	int			code_exit;

	if (help_bash(argc, argv) == 1)
		return (0);
    if (ft_test_system() == 1)
        return (1);
	print_ascii_art_start();
	code_exit = 0;
	data = NULL;
	if (!(data = init_struct(env)))
		return (EXIT_FAILURE);
	core_shell(data);
	code_exit = ft_delete_struct(&data);
	print_ascii_art_end();
	ft_printf("SLEEP\n");
	sleep(150);
	return (code_exit);
}
