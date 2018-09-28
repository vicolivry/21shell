# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/24 10:04:43 by yoginet      #+#   ##    ##    #+#        #
#    Updated: 2018/09/05 13:22:59 by yoginet     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NOCOLOR=\033[0m
VERT=\033[32;05m
JAUNE=\033[33m

NAME =		21sh
CC = 		gcc
FLAGS = 	-Wall -Werror -Wextra
DEL =		rm -rf

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/
LIB_PATH = ./libft/

SRC = $(addprefix $(SRC_PATH),$(N_SRCS))
OBJ = $(addprefix $(OBJ_PATH), $(N_SRCS:.c=.o))
INC = -I $(INC_PATH) -I $(LIB_PATH)includes/

N_SRCS = 	main.c\
			core/core_shell.c\
			core/ft_process.c\
			core/execute_commandes.c\
			core/redirection.c\
			core/execute_builtins.c\
			core/ft_check_arg_invalid.c\
			core/heredoc.c\
			core/hd_exec.c\
			core/info_init_edit.c\
			core/kill_process.c\
			core/cmd_suivante.c\
			core/exit_status.c\
			core/wait_or_not.c\
			core/redirection_fd.c\
			init/ft_check_infos.c\
			init/ft_delete_struct.c\
			init/ft_init_builtins.c\
			init/ft_init_cmd.c\
			init/ft_init_ins.c\
			init/init_struct.c\
			init/ft_load_path.c\
			init/hash_path.c\
			init/hash_path_suite.c\
			init/init_infos.c\
			lib_termcaps/term.c\
			lib_termcaps/keys.c\
			lib_termcaps/move_cursor.c\
			lib_termcaps/signals.c\
			lib_termcaps/get_cursor_position.c\
			lib_termcaps/lst_utils.c\
			lib_termcaps/lst_utils2.c\
			lib_termcaps/alt_keys.c\
			lib_termcaps/add_del_insert.c\
			lib_termcaps/add_del_insert2.c\
			lib_termcaps/history.c\
			lib_termcaps/end_quote.c\
			lib_termcaps/prompt.c\
			lib_termcaps/history2.c\
			lib_termcaps/cut_copy_paste.c\
			lib_termcaps/signals2.c\
			lib_termcaps/winsize.c\
			lib_autocomp/arrows.c\
			lib_autocomp/arrows2.c\
			lib_autocomp/autocomp.c\
			lib_autocomp/display.c\
			lib_autocomp/get_info.c\
			lib_autocomp/key_func.c\
			lib_autocomp/ac_lst_utils.c\
			lib_autocomp/ac_lst_utils2.c\
			lib_autocomp/utils.c\
			lib_autocomp/ac_parse_line.c\
			lib_autocomp/ac_init_slct.c\
			lib_autocomp/ac_init_slct2.c\
			lib_shell/ascii_art.c\
			lib_shell/ft_add_line.c\
			lib_shell/ft_check_path.c\
			lib_shell/ft_del_tab.c\
			lib_shell/ft_dir_exist.c\
			lib_shell/ft_duplicate_tab.c\
			lib_shell/ft_error.c\
			lib_shell/ft_existe_in_path.c\
			lib_shell/ft_good_path.c\
			lib_shell/ft_insert_dollar.c\
			lib_shell/ft_insert_in_tab.c\
			lib_shell/ft_len_tab.c\
			lib_shell/ft_print_tab.c\
			lib_shell/ft_return_path.c\
			lib_shell/ft_return_pwd.c\
			lib_shell/func_access.c\
			lib_shell/len_list.c\
			lib_shell/resize_str.c\
			lib_shell/ft_replace_word.c\
			lib_shell/replace_line.c\
			builtins/good_func.c\
			builtins/func_cd.c\
			builtins/func_echo.c\
			builtins/func_env.c\
			builtins/func_env_suite.c\
			builtins/func_env_suite_deux.c\
			builtins/malloc_for_env.c\
			builtins/func_setenv.c\
			builtins/func_setenv_suite.c\
			builtins/func_unsetenv.c\
			builtins/func_exit.c\
			builtins/func_history.c\
			parsing/ft_split_commandes.c\
			parsing/ft_split_pvirgule.c\
			parsing/ft_split_cmd.c\
			parsing/chose_rep.c\
			parsing/epur_line.c\
			parsing/epur_line_suite.c\
			parsing/ft_search_path.c\
			parsing/replace_in_line.c\
			parsing/ft_error_parsing.c\
			parsing/split_echo.c\
			parsing/split_echo_suite.c\
			parsing/split_cmd.c\
			parsing/split_cmd_suite.c\
			parsing/check_error.c\
			parsing/check_line_vide.c\
			parsing/insert_cmd_simple.c\
			parsing/good_tab_cmd.c\
			parsing/search_heredoc.c\
			parsing/search_redirection.c\
			parsing/search_redirection_suite.c\
			parsing/search_redirection_fd.c\
			parsing/check_validity.c\
			parsing/print_msg_error.c\
			parsing/modifie_fd.c\
			parsing/check_regex_classic.c\
			parsing/good_op_next.c\
			parsing/delete_bs.c\
			debug.c\

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_PATH)
	@$(CC) $(FLAGS) $(OBJ) $(INC) -L$(LIB_PATH) -ltermcap -lft -o $(NAME)
	@echo "$(VERT)$(NAME): compilation success!$(NOCOLOR)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo "$(VERT)\c"
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/core
	@mkdir -p $(OBJ_PATH)/init
	@mkdir -p $(OBJ_PATH)/lib_shell
	@mkdir -p $(OBJ_PATH)/lib_termcaps
	@mkdir -p $(OBJ_PATH)/builtins
	@mkdir -p $(OBJ_PATH)/lib_autocomp
	@mkdir -p $(OBJ_PATH)/parsing
	@$(CC) -c $(FLAGS) $(INC) -o $@ $<
	@echo -n █
	@echo "$(NOCOLOR)\c"

clean:
	@make -C $(LIB_PATH) clean
	@$(DEL) $(OBJ_PATH)
	@echo "$(JAUNE)$(NAME): Removing $(NAME) ./obj/$(NOCOLOR)"

fclean: clean
	@make -C $(LIB_PATH) fclean
	@$(DEL) $(NAME)
	@echo "$(JAUNE)$(NAME): Removing executable$(NOC)"

re: fclean all
