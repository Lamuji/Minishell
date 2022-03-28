# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edalmis <edalmis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 20:42:53 by edalmis           #+#    #+#              #
#    Updated: 2022/03/28 15:20:54 by edalmis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= clang

CFLAGS		= -Wall -Werror -Wextra -g
CPPFLAGS	:= -I.incl -I.libft -I${HOME}/.brew/opt/readline/include
LDFLAGS		:= -L./libft/  -L${HOME}/.brew/opt/readline/lib
LDLIBS		:= -lft -lreadline -lncurses
AR			:= ar -rcs

SRCS		:= src/main.c \
			utils/ft_util_libft.c \
			utils/ft_util_libft2.c \
			utils/ft_util_libft3.c \
			utils/ft_util_libft4.c \
			src/ft_exit.c \
			src/ft_get_args.c \
			src/ft_str_split.c \
			src/parse.c \
			src/parse2.c \
			src/list_utils.c \
			src/list_utils2.c \
			src/tk_var_ops.c \
			src/substitute_vartok.c \
			src/substitute_vartok2.c \
			src/substitute_vartok3.c \
			src/handle_qt.c \
			src/rm_qt.c \
			src/tokenize_var.c \
			src/execution.c \
			src/cmd.c \
			src/cmd_1.c \
			src/pipe.c \
			src/env_list.c \
			builtins/bultins.c \
			builtins/ft_cd.c \
			builtins/ft_cd2.c \
			builtins/ft_cd3.c \
			builtins/ft_cd4.c \
			builtins/ft_echo.c \
			builtins/ft_exec_env.c \
			builtins/ft_exec_env2.c \
			builtins/ft_export.c \
			builtins/ft_export2.c \
			builtins/ft_export3.c \
			builtins/ft_pwd.c \
			src/signals.c \
			src/var_cmd.c \

OBJS	:= $(SRCS:.c=.o)

TEXT = " Time to run minishell!\n"

TEXT2 = " created!\n"

TEXT3 = " deleted!\n"

TEXT4 = "Objects"

.PHONY: all clean fclean re

all: $(NAME)
	@printf "\033[32m"$(TEXT)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@make -C libft/
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@
	@printf "\n"
	@printf "\033[21m"$(NAME)$(TEXT2)

clean:
	@make -C libft/ clean
	rm -f $(OBJS)
	@printf "\033[0;31m"$(TEXT4)$(TEXT3)

fclean: clean
	@make -C libft/ fclean
	rm -f $(NAME)
	@printf "\033[0;23m"$(TEXT4)$(TEXT3)

re:     fclean all

