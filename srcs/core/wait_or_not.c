/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wait_or_not.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/23 13:09:39 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 13:47:26 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		wait_or_not(int *status, pid_t pid, t_cmd *start)
{
	waitpid(pid, status, WNOHANG);
	while (start)
	{
		if (ft_strcmp(start->tab_cmd[0], "top") != 0 &&
	ft_strcmp(start->tab_cmd[0], "yes") != 0 &&
	ft_strcmp(start->tab_cmd[0], "base64") != 0)
			waitpid(start->pid, NULL, 0);
		start = start->next;
	}
	return (0);
}
