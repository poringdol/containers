SHELL = /bin/sh

B&W = \033[0;0m
RED  = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m
	
CC = g++
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -rf

#-O3 -fsanitize=address

NAME = test

MAIN = main.cpp
SRC = test_runner.cpp list_tests.cpp
SRCDIR = ./sources/
INCLUDES = ./includes/

OBJS = $(SRC:.cpp=.o)
OBJDIR = ./objects/
OBJ = $(addprefix $(OBJDIR), $(OBJS))

DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ) $(MAIN)
	@$(CC) $(MAIN) $(OBJ) -o test -I$(INCLUDES) $(CFLAGS)
	@echo "$(GREEN) Tests created  $(B&W)\n For start tests:$(GREEN) ./test $(B&W)"

-include $(DEP)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@test -d $(OBJDIR) || mkdir $(OBJDIR)
	@$(CC) -I$(INCLUDES) -MMD -c $< -o $@ $(CFLAGS)

clean:
	@$(RM) $(OBJDIR)

fclean:
	@$(RM) $(OBJDIR) $(NAME)
	@echo "$(RED) All test deleted $(B&W)"

re: fclean all

.PHONY: all bonus clean fclean re