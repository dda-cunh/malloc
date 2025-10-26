.SILENT:

HOSTTYPE	?=	$(shell uname -m)_$(shell uname -s)

BASENAME	:=	libft_malloc

NAME		:=	$(addprefix $(BASENAME)_, $(addsuffix .so, $(HOSTTYPE)))

LIBLINK		:=	$(BASENAME).so

ROOT_DIR	:=	$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

CC			:=	cc

CFLAGS		:=	-Wall -Wextra -Werror -fPIC -g #-fsanitize=address

LIBCFLAGS	:=	-shared

VAL_FLAGS	:=	--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

RM			:=	rm -rf

INC_DIR		:=	includes/

SRC_DIR		:=	sources/

OBJ_DIR		:=	temp/

LIBS_DIR	:=	lib/

LFT_PATH	:=	$(addprefix $(LIBS_DIR), libft/)

CSTACK_PATH	:=	$(addprefix $(LIBS_DIR), cstack/)

LINKS		:=	-L$(LFT_PATH) -lft # -L$(CSTACK_PATH) -lcstack

SRC			:=	$(addprefix $(SRC_DIR),	realloc.c \
										malloc.c \
										show_alloc_mem.c \
										free.c \
										globals.c \
										utils.c)

OBJ_DIRS	:=	$(OBJ_DIR)

OBJ			:=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

GREEN		:=	\033[0;32m

RESET		:=	\033[0m

SUS			:=	\U00000D9E

HAMMER		:=	\U0001F528

BROOM		:=	\U0001F9F9


$(NAME):		$(OBJ)
				printf '$(HAMMER)\n\t$(GREEN)Compiling $(NAME)$(RESET)\n'
				make dependencies
				$(CC) $(CFLAGS) $(LIBCFLAGS) $^ -o $@ $(LINKS)
				ln -s $(NAME) $(LIBLINK)
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
				make -C $(LFT_PATH) fclean
				$(RM) $(NAME)
				$(RM) $(LIBLINK)
				printf '$(BROOM)\t\t\t$(SUS)\n'

re:				fclean	all


dependencies:
					make -C $(LFT_PATH)
# 					make -C $(CSTACK_PATH)

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
