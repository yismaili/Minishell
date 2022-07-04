# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souchen <souchen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 11:28:16 by souchen           #+#    #+#              #
#    Updated: 2022/06/22 18:23:36 by souchen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m
CC = gcc
FLAGS = -Wall -Werror -Wextra 

RM = rm -rf

FILES =builtins.c create_env.c  ft_exit.c  ft_unset.c \
       initial_path.c  main.c  run_commande.c \
       divise_commande.c arguments.c arguments_utils.c ft_env.c ft_export.c ft_cd.c ft_pwd.c \
       ft_echo.c output_input.c


OBJ_FILES= $(FILES:.c=.o)

HEADER = includes/minishell.h
LIBFT = libft/libft.a
NAME = minishell
# LINK=-L/goinfre/readline/a.out.dSYM

all : $(NAME)

$(NAME) : $(OBJ_FILES) $(LIBFT)
	$(CC) $(OBJ_FILES) -lreadline $(LIBFT) $(FLAGS) -o $(NAME)
# $(CC) $(OBJ_FILES) $(LIBFT) $(FLAGS) -o $(NAME)

%.o : %.c $(HEADER)
	@echo "$(RED)COMPILING$(RESET) $<"
	$(CC)  $(FLAGS)  -c $< -o $@
$(LIBFT):
	make -C libft
	make clean -C libft
clean:
	$(RM) $(OBJ_FILES)

fclean: clean
	$(RM) $(NAME)
	$(RM) libft/libft.a

re: fclean clean all


    
