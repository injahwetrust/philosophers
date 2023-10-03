# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 11:16:05 by bvaujour          #+#    #+#              #
#    Updated: 2023/08/28 16:21:21 by bvaujour         ###   ########.fr        #
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
FFLAGS = -Wall -Werror -Wextra
OBJ	= $(SRC:.c=.o)
OBJ_B	= $(SRC_B:.c=.o)

all	: $(NAME)

$(NAME)	: $(OBJ) $(INCLUDES) Makefile
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus : $(NAME_B)

$(NAME_B): $(OBJ_B) $(INCLUDES_B) Makefile
	$(CC) $(CFLAGS) $(OBJ_B) -o $(NAME_B)
	
sanitize :  $(OBJ) $(INCLUDES) $(OBJ_B) $(INCLUDES_B) Makefile 
	$(CC) $(FFLAGS) $(OBJ_B) -o philosan_bonus
	$(CC) $(FFLAGS) $(OBJ) -o philosan
clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_B)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_B)
	rm -rf philosan
	rm -rf philosan_bonus
re: fclean all

.PHONY: clean fclean re
