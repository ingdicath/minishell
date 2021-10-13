# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dsalaman <dsalaman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/06 13:42:00 by dsalaman      #+#    #+#                  #
#    Updated: 2021/10/12 16:29:22 by hlin          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

GREEN	=	\033[38;5;10m
WHITE	=	\033[0m

NAME	=	minishell

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

SRC_DIR =	srcs/
OBJ_DIR =	objs/

SRCS =  minishell.c

SRC 	=	$(addprefix $(SRC_DIR), $(SRCS))
OBJS	=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

INCS	=	-I includes -I libft

LIBFT	=	libft/libft.a

LFT		=	-L libft -lft -lncurses

# for readline lib
RL = -lreadline
RL_FLAGS = "-L$(HOME)/.brew/opt/readline/lib"
RL_INCS = "-I$(HOME)/.brew/opt/readline/include"

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFT) $(INCS) $(RL) $(RL_FLAGS)
	@echo "$(GREEN)minishell created successfully $(WHITE)"

$(LIBFT) :
	@make -C libft/

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCS) $(RL_INCS)

clean :
	@make clean -C libft/
	@rm -rf $(OBJ_DIR)
	@echo "Objects were removed - clean."

fclean : clean
	@make fclean -C libft/
	@rm -rf $(NAME)
	@echo "Name was removed - fclean."

re : fclean all

.PHONY: all clean fclean re
