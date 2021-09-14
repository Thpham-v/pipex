NAME			=	pipex
SRC_DIR			=	./
INC_DIR			=	./
SRCS			=	


					
SRC_BASENAME	=	$(addprefix $(SRC_DIR), $(SRCS))		
OBJS			=	$(SRC_BASENAME:.c=.o)
CC				=	clang 
FLAGS			=	-Wall -Wextra -Werror -I $(INC_DIR)

.c.o		:
				$(CC) $(FLAGS) -c $< -o $@

all			:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS)
			@echo [$(NAME)] : Created !

clean		:
			rm -rf $(OBJS)
			@echo "[OBJS] Deleted"

fclean		:	clean
			rm -f $(NAME)
			@echo "[$(NAME)]: Deleted"

re			:	fclean all