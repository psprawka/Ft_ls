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
		$(SRCS_DIR)ft_ls_sort.c \
		$(SRCS_DIR)ft_ls_help.c \
		$(SRCS_DIR)ft_ls_print_long.c \

OBJS = $(SRCS:.c=.o)
LIBFT = Libft/libft.a

BUILD_PRINT = @echo "\r\033[K\033[0;38;5;27m[FT_LS] \033[38;5;45mBuilding $<\e[0m"
DONE = @echo "\033[K\033[1;38;5;200mFT_LS ready to use!\e[0m"
CLEAN_O = @echo "\033[38;5;246mObject files removed! [FT_LS]\e[0m"
CLEAN_A = @echo "\033[38;5;246mExecutable removed! [FT_LS]\e[0m"

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJS) $(HEADERS)
	@gcc $(FLAGS) -I $(HEADERS) $(OBJS) $(LIBFT) -lncurses -o $(NAME)
	$(DONE)

$(LIBFT):
	@make -s -C Libft

%.o: %.c
	$(BUILD_PRINT)
	@gcc $(CFLAGS) -I $(HEADERS) -c $< -o $@

clean:
	@$(MAKE) -s -C Libft/ clean
	@rm -f $(OBJS)
	$(CLEAN_O)

fclean: clean
	@$(MAKE) -s  -C Libft/ fclean
	@rm -f $(NAME)
	$(CLEAN_A)

re: fclean all
