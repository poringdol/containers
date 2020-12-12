SHELL = /bin/sh

B&W = \033[0;0m
RED  = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m
	
CC = g++
CFLAGS = -Wall -Werror -Wextra -g
STD = -std=c++98
RM = rm -rf

#-O3 -fsanitize=address

NAME = test

SRC = main.cpp test_runner.cpp list_tests.cpp
SRCDIR = ./tests/
INCLUDES = ./containers/
MAIN = $(SRCDIR)main.cpp
MAIN98 = $(SRCDIR)main_c98.cpp

OBJS = $(SRC:.cpp=.o)
OBJDIR = ./objects/
OBJ = $(addprefix $(OBJDIR), $(OBJS))

DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ) $(MAIN)
	@$(CC) $(OBJ) -o test -I$(INCLUDES) $(CFLAGS)
	@echo "$(GREEN) Tests created  $(B&W)\n For start tests:$(GREEN) ./test $(B&W)"

c98:
	$(CC) $(MAIN98) -o test_c98 -I$(INCLUDES) $(CFLAGS) $(STD)
	@echo "$(GREEN) Tests with c++98 standart created  $(B&W)\n For start tests:$(GREEN) ./test_c98 $(B&W)"

-include $(DEP)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@test -d $(OBJDIR) || mkdir $(OBJDIR)
	@$(CC) -I$(INCLUDES) -MMD -c $< -o $@ $(CFLAGS)

clean:
	@$(RM) $(OBJDIR)

fclean:
	@$(RM) $(OBJDIR) $(NAME) test_c98
	@echo "$(RED) All test deleted $(B&W)"

re: fclean all

.PHONY: all bonus clean fclean re