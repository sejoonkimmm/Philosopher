# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejokim <sejokim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 19:00:15 by sejokim           #+#    #+#              #
#    Updated: 2023/05/30 23:38:14 by sejokim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

HEADER		=	philo.h

CC			=	cc

CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER)

SRCS		=	main.c \
			init.c     \
			init_2.c	\
			action.c   \
			utils.c    \
			thread.c 	\
			death.c 	\

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:	fclean all
