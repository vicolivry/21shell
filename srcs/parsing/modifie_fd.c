/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   modifie_fd.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/08 15:29:39 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 10:42:35 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**  Check if fd valid or print error
*/

static int		valid_fd(int fd)
{
	if (fd == 0)
		return (1);
	if (ttyname(fd) != NULL)
		return (0);
	ft_putstr_fd("21sh: ", 2);
	ft_putnbr_fd(fd, 2);
	ft_putstr_fd(": bad file descriptor\n", 2);
	return (-1);
}

/*
**  Return fd before >&
*/

static int		ft_fd_before(char *str, int i)
{
	int		fd_before;

	fd_before = 1;
	if (!(str))
		return (-1);
	if (i < 3)
		return (0);
	if (ft_isdigit(str[i - 2]) == 1)
	{
		fd_before = ft_atoi(str + (i - 2));
	}
	if (valid_fd(fd_before) == -1)
		return (-1);
	return (fd_before);
}

/*
**  Return fd next >&
*/

static int		fd_next_suite(char *str, int i, int add, int *fd_next)
{
	char	*tmp;

	tmp = NULL;
	// add gestion chemin a faire
	while (ft_isalpha(str[i + add]) == 1 || str[i + add] == '/')
		add++;
	tmp = ft_strsub(str, i + 1, add);
	basic_error(tmp, ": ambigous redirect");
	*fd_next = -1;
	ft_strdel(&tmp);
	return (-2);
}

static int		ft_fd_next(char *str, int i, int *fd_next)
{
	int		add;

	add = 1;
	*fd_next = 1;
	if (!(str) || i > ft_strlen(str))
		return (-2);
	if (str[i + 1] == '-')
	{
		*fd_next = open("/dev/null", O_RDWR);
		return (2);
	}
	while(str[i + 1] == ' ' || str[i + 1] == '\t')
	{
		i++;
		add++;
	}
	if (ft_isdigit(str[i + add]) == 1)
		*fd_next = ft_atoi(str + (i + add));
	else if (ft_isalpha(str[i + add] == 1) || str[i + add] == '/')
		return (fd_next_suite(str, i, add, fd_next));
	if (valid_fd(*fd_next) == -1)
		return (-2);
	return (add + 1);
}

/*
**	verifie que l'on est bien sur un >& et modifie les fd
*/

int				modifie_fd(t_cmd **lst, char *str, int start)
{
	int		fd_before;
	int		fd_next;
	int		len_next;

	fd_before = 1;
	fd_next = 1;
	len_next = 1;
	if (!(str) || !(lst))
		return (0);
	if (str[start] != '&')
		return (0);
	fd_before = ft_fd_before(str, start);
	len_next = ft_fd_next(str, start, &fd_next);
	if (fd_before == fd_next && fd_before > 0 && fd_next > 0)
		return (len_next);
	if (fd_before == -1 || fd_next == -2 || len_next == -2)
	{
		(*lst)->stdout_cmd = -1;
		return (ft_strlen(str));
	}
	if (fd_before == 1)
		(*lst)->stdout_cmd = fd_next;
	else if (fd_before == 2)
		(*lst)->stderr_cmd = fd_next;
	return (len_next);
}
