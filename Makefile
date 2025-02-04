# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 16:11:30 by jmakkone          #+#    #+#              #
#    Updated: 2024/06/07 10:30:48 by jmakkone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
SRC			= pipex.c \
			  pipex_utils.c \
			  error_handler.c \
			  parse_cmd.c \
			  add_argument.c \
			  append_char.c \
			  check_cmd.c \
			  check_path.c \
			  execute.c \
			  open_file.c \
			  check_status.c \
			  exit_handler.c \
			  last_process.c \
			  libft/libft.a

SRC_BONUS	= pipex_bonus.c \
			  pipex_utils.c \
			  error_handler.c \
			  parse_cmd.c \
			  add_argument.c \
			  append_char.c \
			  check_cmd.c \
			  check_path.c \
			  execute.c \
			  open_file.c \
			  check_status.c \
			  exit_handler.c \
			  last_process.c \
			  here_doc_bonus.c \
			  libft/libft.a

RM 			= rm -f         
CC 			= cc        
LIBFTD		= ./libft

CFLAGS 		= -Wall -Wextra -Werror

${NAME}:
				@make -C ${LIBFTD}
				${CC} ${CFLAGS} ${SRC} -o ${NAME}

all:		${NAME}

bonus:		.bonus

.bonus:		
			@make -C ${LIBFTD}
			${CC} ${CFLAGS} ${SRC_BONUS} -o ${NAME}
			@touch .bonus

clean: 
			@make clean -C ${LIBFTD}
			@${RM} .bonus

fclean: 	clean
			${RM} ${NAME}
			@make fclean -C ${LIBFTD}
		
re:			fclean all

			
.PHONY:		all clean fclean re bonus
