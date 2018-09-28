/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ascii_art.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/28 11:11:45 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/28 14:12:19 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void		print_ascii_art_start(void)
{
	ft_putstr(BLUE);
	ft_printf("       ::::::::    :::   ::::::::  :::    ::: \n");
	ft_putstr(BLUE);
	ft_printf("     :+:    :+: :+:+:  :+:    :+: :+:    :+:  \n");
	ft_putstr(BLUE);
	ft_printf("          +:+    +:+  +:+        +:+    +:+   \n");
	ft_putstr(BLUE);
	ft_printf("       +#+      +#+  +#++:++#++ +#++:++#++    \n");
	ft_putstr(BLUE);
	ft_printf("    +#+        +#+         +#+ +#+    +#+     \n");
	ft_putstr(BLUE);
	ft_printf("  #+#         #+#  #+#    #+# #+#    #+#      \n");
	ft_putstr(BLUE);
	ft_printf("########## ####### ########  ###    ###       \n");
	ft_putstr(RESET);
	ft_printf("\n");
	ft_printf("© - volivry\n");
	ft_printf("© - yoginet\n");
}

void		print_ascii_art_end(void)
{
	ft_putstr(BLUE);
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
