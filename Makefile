# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 11:28:16 by souchen           #+#    #+#              #
#    Updated: 2022/08/15 15:05:24 by yismaili         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m
BBlue=\033[1;34m
BYellow=\033[1;33m
CC = gcc
FLAGS = -Wall -Werror -Wextra -g
#-fsanitize=address
RM = rm -rf
LIB = /Users/yismaili/goinfre/.brew/opt/readline/lib
INCL = /Users/yismaili/goinfre/.brew/opt/readline/include/readline/


FILES =builtins.c create_env.c  ft_exit.c  ft_unset.c \
       initial_path.c  main.c  run_commande.c \
       divise_commande.c arguments.c arguments_utils.c ft_env.c ft_export.c ft_cd.c ft_pwd.c \
       ft_echo.c output_input.c leaks.c execution.c tools.c split_arg.c creat_env_fun.c  export_tools.c  herDoc_tools.c 
 

OBJ_FILES= $(FILES:.c=.o)

HEADER = includes/minishell.h
LIBFT = libft/libft.a
NAME = minishell

all : $(NAME)

		@echo "$(RESET)"
		@echo "███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░"
		@echo "████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░"
		@echo "██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░"
		@echo "██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░"
		@echo "██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗"
		@echo "╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝ BY yismaili && souchen"

$(NAME) : $(OBJ_FILES) $(LIBFT)
	$(CC) $(OBJ_FILES) -lreadline  -L $(LIB)  -I $(INCL) $(LIBFT) $(FLAGS) -o $(NAME)

%.o : %.c $(HEADER)
	@echo $(HOME)
	@echo "$(GREEN)COMPILING$(RESET) $<"
	$(CC)  $(FLAGS)  -c $< -o $@
$(LIBFT):
	make -C libft

clean:
	$(RM) $(OBJ_FILES)
	@make fclean -C libft

fclean: clean
	$(RM) $(NAME)
	@make fclean -C libft
	@echo "$(RED)Everything is fcleaned in minishell!$(RESET)"

re: fclean clean all
