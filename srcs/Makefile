# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: yoginet <yoginet@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/24 10:04:43 by yoginet      #+#   ##    ##    #+#        #
#    Updated: 2018/06/27 11:04:20 by volivry     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NOCOLOR=\033[0m
VERT=\033[32;05m
JAUNE=\033[33m

NAME =		21sh
CC = 		gcc
FLAGS = 	-Wall -Werror -Wextra -g
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
			init/ft_check_infos.c\
			init/ft_delete_struct.c\
			init/ft_init_builtins.c\
			init/ft_init_commandes.c\
			init/clear_commandes.c\
			init/init_struct.c\
			lib_termcaps/term.c\
			lib_termcaps/keys.c\
			lib_termcaps/keys2.c\
			lib_termcaps/signals.c\
			lib_termcaps/cursor_position.c\
			lib_termcaps/lst_utils.c\
			lib_termcaps/lst_utils2.c\
			lib_termcaps/alt_keys.c\
			lib_termcaps/add_del_insert.c\
			lib_shell/display.c\
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
			lib_shell/ft_insert_tild.c\
			lib_shell/ft_len_tab.c\
			lib_shell/ft_print_tab.c\
			lib_shell/ft_return_path.c\
			lib_shell/ft_return_pwd.c\
			lib_shell/func_access.c\
			lib_shell/format_line.c\
			lib_shell/len_list.c\
			builtins/good_func.c\
			builtins/func_cd.c\
			builtins/func_cd_suite.c\
			builtins/func_echo.c\
			builtins/func_echo_suite.c\
			builtins/func_echo_print.c\
			builtins/func_env.c\
			builtins/func_env_suite.c\
			builtins/func_setenv.c\
			builtins/func_unsetenv.c\
			parsing/ft_split_commandes.c\

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
