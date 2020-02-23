# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/09 23:21:55 by psprawka          #+#    #+#              #
#    Updated: 2020/02/21 22:34:57 by psprawka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
FLAGS = -g -Wall -Wextra -Werror

HEADERS = includes/
SRCS_DIR = srcs/

SRCS =	$(SRCS_DIR)ft_ls.c \
		$(SRCS_DIR)ft_ls_print.c \
		$(SRCS_DIR)ft_ls_parse.c \
		$(SRCS_DIR)ft_ls_tools.c \
		$(SRCS_DIR)ft_ls_list.c \
		$(SRCS_DIR)ft_ls_sort.c \
		$(SRCS_DIR)ft_ls_help.c \
		$(SRCS_DIR)ft_ls_print_long.c \

OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

BUILD_PRINT = @echo "\r\033[K\033[0;38;5;27m[FT_LS] \033[38;5;45mBuilding $<\x1B[0m"
DONE = @echo "\033[K\033[1;38;5;200mFT_LS ready to use!\x1B[0m"
CLEAN_O = @echo "\033[38;5;246mObject files removed! [FT_LS]\x1B[0m"
CLEAN_A = @echo "\033[38;5;246mExecutable removed! [FT_LS]\x1B[0m"

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJS) $(HEADERS)
	@gcc $(FLAGS) -I $(HEADERS) $(OBJS) $(LIBFT) -lncurses -o $(NAME)
	$(DONE)

$(LIBFT):
	@make -C libft

%.o: %.c
	$(BUILD_PRINT)
	@gcc $(CFLAGS) -I $(HEADERS) -c $< -o $@

clean:
	@$(MAKE) -C libft/ clean
	@rm -f $(OBJS)
	$(CLEAN_O)

fclean: clean
	@$(MAKE) -C libft/ fclean
	@rm -f $(NAME)
	$(CLEAN_A)

re: fclean all
