.SILENT:
HOSTTYPE	?=	$(shell uname -m)_$(shell uname -s)

NAME		:=	$(addprefix libft_malloc_, $(addsuffix .so, $(HOSTTYPE)))

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address

LIBCFLAGS	=	-fPIC

VAL_FLAGS	=	--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

RM			=	rm -rf

INC_DIR		=	includes/

SRC_DIR		=	sources/

OBJ_DIR		=	temp/

SRC			=	$(addprefix $(SRC_DIR),	realloc.c \
										malloc.c \
										show_alloc_mem.c \
										free.c)

OBJ_DIRS	=	$(OBJ_DIR)

OBJ			=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

GREEN		=	\033[0;32m

RESET		=	\033[0m

SUS			=	\U00000D9E

HAMMER		=	\U0001F528

BROOM		=	\U0001F9F9

$(NAME):		$(OBJ)
				printf '$(HAMMER)\n\t$(GREEN)Compiling $(NAME)$(RESET)\n'
				$(CC) $(CFLAGS) $(LIBCFLAGS) -shared $^ -o $@
				make compiled

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_DIRS)
				printf '$(HAMMER)\n\t'
				printf "$(GREEN)Compiling $(NAME) object $(RED)%-33.33s\r" $(notdir $@)
				$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

$(OBJ_DIRS):
				mkdir -p $@


all:			$(NAME)

clean:
				$(RM) $(OBJ_DIR)

fclean:			clean
				printf '$(BROOM)\n$(BROOM)\t$(GREEN)Cleaning project$(RESET)\n'
				$(RM) $(NAME)
				printf '$(BROOM)\t\t\t$(SUS)\n'

re:				fclean	all

compiled:
				printf "															 	\n"
				printf "$(GREEN)	$(NAME)							 			$(RESET)\n"
				printf "$(GREEN)                             _  _             _ $(RESET)\n"
				printf "$(GREEN)                            (_)| |           | |$(RESET)\n"
				printf "$(GREEN)  ____   ___   ____   ____   _ | |  ____   _ | |$(RESET)\n"
				printf "$(GREEN) / ___) / _ \ |    \ |  _ \ | || | / _  ) / || |$(RESET)\n"
				printf "$(GREEN)( (___ | |_| || | | || | | || || |( (/ / ( (_| |$(RESET)\n"
				printf "$(GREEN) \____) \___/ |_|_|_|| ||_/ |_||_| \____) \____|$(RESET)\n"
				printf "$(GREEN)                     |_|                        $(RESET)\n"
				printf "																\n"

.PHONY: 		all fclean re compiled
