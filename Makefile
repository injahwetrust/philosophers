# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 11:16:05 by bvaujour          #+#    #+#              #
#    Updated: 2023/05/24 17:44:17 by bvaujour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES = inc/philo.h
INCLUDES_B = inc/philo_bonus.h

FILES = philo.c init.c life.c philo_utils.c
FILES_B = philo_bonus.c check_bonus.c life_bonus.c time_utils_bonus.c utils_bonus.c

DIRPATH = 		$(sh pwd)
SRCPATH =		$(DIRPATH)src/
SRCPATH_B =		$(DIRPATH)src_bonus/
SRC		=		$(addprefix $(SRCPATH), $(FILES))
SRC_B		=		$(addprefix $(SRCPATH_B), $(FILES_B))

NAME 	= philo
NAME_B 	= philo_bonus
CC = gcc
CFLAGS = -g3 -Wall -Werror -Wextra

OBJ	= $(SRC:.c=.o)
OBJ_B	= $(SRC_B:.c=.o)



all	: $(NAME)

$(NAME)	: $(OBJ) $(INCLUDES) Makefile
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus : $(NAME_B)

$(NAME_B)	: $(OBJ_B) $(INCLUDES_B) Makefile
	$(CC) $(CFLAGS) $(OBJ_B) -o $(NAME_B)
	
clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_B)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_B)
	
re: fclean all

.PHONY: clean fclean re