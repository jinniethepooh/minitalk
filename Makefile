# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchetana <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/24 18:15:35 by cchetana          #+#    #+#              #
#    Updated: 2022/06/25 14:20:55 by cchetana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= server client
SRCS_S		= srcs/server.c
SRCS_C		= srcs/client.c
B_SRCS_S	= srcs/server_bonus.c
B_SRCS_C	= srcs/client_bonus.c
OBJS_S		= $(SRCSs:.c=.o)
OBJS_C		= $(SRCSc:.c=.o)
B_OBJS_S	= $(B_SRCSs:.c=.o)
B_OBJS_C	= $(B_SRCSc:.c=.o)
INCS	= includes
CFLAGS	= gcc -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@$(CFLAGS) -I $(INCS) $(SRCS_C) -o client
	@$(CFLAGS) -I $(INCS) $(SRCS_S) -o server
	@echo "/// ----- minitalk is ready ----- ///"

bonus:
	@$(CFLAGS) -I $(INCS) $(B_SRCS_C) -o client
	@$(CFLAGS) -I $(INCS) $(B_SRCS_S) -o server
	@echo "/// ----- minitalk_bonus is ready ----- ///"

clean:
	@rm -rf $(OBJS_C)
	@rm -rf $(OBJS_S)
	@rm -rf $(B_OBJS_C)
	@rm -rf $(B_OBJS_S)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
