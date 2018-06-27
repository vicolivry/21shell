/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 14:43:34 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 16:46:00 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <uuid/uuid.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <fcntl.h>
# include <term.h>

/*
** PRINT COLORS
*/

# define BLACK "\033[30m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"
# define GREEN "\033[32m"
# define MAGENTA "\033[35m"
# define WHITE "\033[37m"
# define YELLOW "\033[33m"

# define RESET "\033[00m"

/*
**	A Faire :
**	Si variable path suprimer, ne pas lancer de commande (sauf si chemin indiquer)
**	gestion des cotes et doubles code pour setenv et unsetenv
**
*/

/*
**	Source :
**	http://putaindecode.io/fr/articles/shell/redirections/
**	https://www.gnu.org/software/bash/manual/bashref.html#Redirections
**	https://abs.traduc.org/abs-5.3-fr/ch19.html
**	https://openclassrooms.com/forum/sujet/executer-fonctions-sur-pipes-successifs
**	https://stackoverflow.com/questions/17630247/coding-multiple-pipe-in-c/17631589
**	https://openclassrooms.com/forum/sujet/dup-dup2-et-close-12008
**
**
*/

/*
**	***	Structures ***
**
**	t_cmd -> liste chainer des commandes a executer
**
**	rep = Repertoire de commande
**	tab_cmd : commande et options sous forme de tableau
**	pathname : Si redirection dans un fichier, pathanme != NULL

**	Code operateur:
**	0 : NULL
**	1 : |
**	2 : >
**	3 : >>
**	4 : <
**	5 : <<
**	6 : &
**	7 : &&
**	8 : ||
**
**	env : Environnement a envoyer pour la commande
*/
typedef struct		s_cmd
{
	char			*rep;
	char			**tab_cmd;
	char			*pathname;

	int				op_redir;
	int				op_next;

	int				stdin_cmd;
	int				stdout_cmd;
	int				stderr_cmd;

	char			**env;
	struct s_cmd	*next;
}					t_cmd;
/*
**	t_struct -> On la ballade partout
*/
typedef struct		s_struct
{
	char			*path;
	char			*pwd;
	char			*oldpwd;
	char			*home;
	char			*charfound;
	char			*current_path;
	char			*prompt;
	char			*prompt_current;
	char			**tab_path;
	char			**env;
	char			**builtins;
	int				option_echo;
	int				option_i_env;
	char			**env_tmp;
	char			*char_echo;
	int				ret_func;
	int				stdin_shell;
	int				stdout_shell;
	int				stderr_shell;
	t_cmd			*commandes;
}					t_struct;
/*
**	***	Fonctions ***
**
**	CORE
*/
void				core_shell(char **line, t_struct *data);
int					execute_commandes(t_struct *data);
int					exec_pipe(t_struct *data);
int					exec_pipe_suite(t_struct *data);
int					ft_process(t_struct *data);
/*
**	PARSING
*/
t_cmd				*ft_split_commandes(char **line, t_struct **data);
/*
**	BUILTINS
*/
int					ft_builtins(char **line, t_struct *data);
int					func_cd(char **line, t_struct *data);
int					ft_error_cd(char *line);
void				ft_check_error_cd(t_struct **data);
int					func_echo(char **line, t_struct *data);
void				option_echo(int j, t_struct *data);
int					ft_search_env(char *str, int i, t_struct *data, int i2);
void				ft_print_echo(char *str, t_struct *data, size_t len);
int					ft_print_special(char *str, int i, int len);
char				**func_setenv(char **line, t_struct *data);
char				**func_unsetenv(char **line, t_struct *data);
void				func_env(char **line, t_struct *data);
void				print_full_env(t_struct *data);
void				ft_print_usage(char *str);
char				*ft_return_env(char *str, t_struct *data);
int					ft_option_i(char *str);
int					ft_env_cmd(t_struct *data, char **tmp, int i, int x);
int					ft_env_rep(t_struct *data, char **tmp, int i);
/*
**	INIT
*/
t_struct			*init_struct(char **env);
char				*ft_check_infos(char **env, char *find);
char				**ft_initialise_builtins(void);
void				ft_delete_struct(t_struct *data);
t_cmd				*clear_commandes(t_cmd *start);
t_cmd				*ft_init_commandes(void);
/*
**	LIB_SHELL
*/
char				**ft_del_tab(char **tabl);
int					ft_len_tab(char **tabl);
char				**ft_duplicate_tab(char **tabl);
char				**ft_insert_in_tab(char **tabl, char *str);
void				ft_print_tab(char **tabl);
char				**ft_del_tab_index(char **tabl, int max);
char				*ft_add_line(char *str, char **add, t_struct *data);
int					ft_dir_exist(char *path);
void				ft_display(t_struct *data);
int					ft_access(char *path);
void				basic_error(char *name, char *cmd);
int					ft_error(int cmd, char **line);
void				ft_error_dir(char *name, char *pre);
void				ft_error_unset(char *str, int what);
void				ft_error_fork(int father);
void				ft_check_path(t_struct *data, char **path);
int					good_path(char *target, char *cmd, int opt);
char				*ft_return_path(char *str);
int					ft_insert_tild(t_struct *data, char **str, int i);
int					ft_insert_dollar(t_struct *data, char **str, int i);
int					ft_existe_in_path(t_struct *data, char **path);
char				*ft_return_pwd(void);
void				ft_check_line(t_struct *data, char **line, int i);
int					len_list(t_cmd *lst);
/*
**	LIB_TERMCAPS
*/
# define KEY_CODE_NONE 0
# define KEY_CODE_UP buff[0] == 27 && buff[1] == 91 && buff[2] == 65
# define KEY_CODE_DOWN buff[0] == 27 && buff[1] == 91 && buff[2] == 66
# define KEY_CODE_RIGHT buff[0] == 27 && buff[1] == 91 && buff[2] == 67
# define KEY_CODE_LEFT buff[0] == 27 && buff[1] == 91 && buff[2] == 68
# define KEY_CODE_ALT_UP buff[0] == 27 && buff[1] == 27 && buff[2] == 91 && buff[3] == 65
# define KEY_CODE_ALT_DOWN buff[0] == 27 && buff[1] == 27 && buff[2] == 91 && buff[3] == 66
# define KEY_CODE_ALT_RIGHT buff[0] == 27 && buff[1] == 27 && buff[2] == 91 && buff[3] == 67
# define KEY_CODE_ALT_LEFT buff[0] == 27 && buff[1] == 27 && buff[2] == 91 && buff[3] == 68
# define KEY_CODE_BSP *(int*)buff == 127
# define KEY_CODE_RC *(int*)buff == 10
# define KEY_CODE_END buff[0] == 27 && buff[1] == 91 && buff[2] == 70
# define KEY_CODE_HOME buff[0] == 27 && buff[1] == 91 && buff[2] == 72
# define KEY_CODE_CTRL_A
# define KEY_CODE_CTRL_D *(int*)buff == 4
# define KEY_CODE_TAB *(int*)buff == 9

# define CURS_X get_curs_pos(0, info)
# define CURS_Y get_curs_pos(1, info)


typedef struct winsize t_wndw;
typedef struct termios t_termios;

typedef struct		s_hist
{
	char			*name;
	int				current;
	struct s_hist	*next;
	struct s_hist	*prev;
}					t_hist;

typedef struct		s_info
{
	int				s_len;
	int				orig_y;
	int				curs_x;
	int				curs_y;
	int				row_nb;
	int				col_nb;
	int				curs_in_str;
	char			*line;
	char			*prmpt;
	t_hist			*history;
	t_wndw			wndw;
	t_termios		term;
}					t_info;


void				default_term_mode(t_info *info);
void				raw_term_mode(t_info *info);
void				get_key(int *loop, t_info *info, t_hist *tmp);
t_info				*memo_info(t_info *info, int mode);
int					get_curs_pos(int mode, t_info *info);
void				get_signals(void);
void				left_key(t_info *info);
void				right_key(t_info *info);
void				add_c_in_str(t_info *info, char c, t_hist *tmp);
void				del_c_in_str(t_info *info, t_hist *tmp);
void				del_char(t_info *info, t_hist *tmp);
void				add_char(char c, t_info *info, t_hist *tmp);
void				insert_char(char c, t_info *info, t_hist *tmp);
void				curs_extremity(t_info *info, char *buff);
void				add_queue(t_hist *root);
void				add_head(t_hist *root);
void				remove_elem(t_hist *elem);
t_hist				*root_hist(void);
t_hist				*first_elem(t_hist *root);
t_hist				*last_elem(t_hist *root);
void				alt_up_down(t_info *info, char *buff);
void				init_current(t_hist *history);
void				alt_right(t_info *info, t_hist *tmp);
void				alt_left(t_info *info, t_hist *tmp);
/*
**	END
*/
#endif
