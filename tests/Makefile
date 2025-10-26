.SILENT:

MALLOC_LIB_NAME	:=	libft_malloc.so

MALLOC_LIB_PATH	:=	../$(MALLOC_LIB_NAME)

LIBS_DIR		:=	../lib/
LFT_PATH		:=	$(addprefix $(LIBS_DIR), libft/)

LINKS			:=	-L$(LFT_PATH) -lft -L.. -lft_malloc

VAL_FLAGS		:= --leak-check=full --show-leak-kinds=all --track-origins=yes

NAME			:= test_malloc
CC		  		:= cc
CFLAGS	  		:= -g #-fsanitize=address #-Wall -Wextra -Werror 
RM		  		:= rm -rf

SRC		 		:= main.c
OBJ		 		:= $(SRC:.c=.o)

all: $(NAME)
	@echo "Running $(NAME)... LIB: $(MALLOC_LIB_PATH)"
	LD_LIBRARY_PATH=../ LD_PRELOAD=$(MALLOC_LIB_PATH) ./$(NAME)

$(NAME): $(OBJ) $(MALLOC_LIB_PATH)
		make build_dep
		$(CC) $(CFLAGS) -o $@ $(OBJ) $(LINKS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

build_dep:
	make -C $(LFT_PATH)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
