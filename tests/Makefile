.SILENT:

LIB_NAME	:=	libft_malloc.so

LIB_PATH	:= ../$(LIB_NAME)

VAL_FLAGS	:= --leak-check=full --show-leak-kinds=all --track-origins=yes

NAME		:= test_malloc
CC		  	:= cc
CFLAGS	  	:= -g #-fsanitize=address #-Wall -Wextra -Werror 
RM		  	:= rm -rf

SRC		 	:= main.c
OBJ		 	:= $(SRC:.c=.o)

all: $(NAME)
	@echo "Running $(NAME)... LIB: $(LIB_PATH)"
	LD_LIBRARY_PATH=../ LD_PRELOAD=$(LIB_PATH) ./$(NAME)

$(NAME): $(OBJ) $(LIB_PATH)
		$(CC) $(CFLAGS) -o $@ $(OBJ) -L.. -lft_malloc
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
