SHELL = /bin/sh

B&W = \033[0;0m
RED  = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m
	
CC = g++
STD = -std=c++98
CFLAGS = -Wall -Werror -Wextra -g
CFLAGS += $(STD)
RM = rm -rf

#-O3 -fsanitize=address

NAME = test

SRC = main.cpp \
	  test_runner.cpp \
	  vector_tests.cpp \
	  list_tests.cpp \
	  stack_tests.cpp \
	  queue_tests.cpp  \
	  map_tests.cpp
SRCDIR = ./tests/
INCLUDES = ./containers/
MAIN = $(SRCDIR)main.cpp

OBJS = $(SRC:.cpp=.o)
OBJDIR = ./objects/
OBJ = $(addprefix $(OBJDIR), $(OBJS))

DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ) $(MAIN)
	@$(CC) $(OBJ) -o test -I$(INCLUDES) $(CFLAGS)
	@echo ""
	@echo "$(GREEN)~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~$(B&W)"
	@echo "$(GREEN)^						^$(B&W)"
	@echo "$(GREEN)^	 $(B&W)Project: ft_services by $(GREEN)pdemocri	^$(B&W)"
	@echo "$(GREEN)^						^$(B&W)"
	@echo "$(GREEN)^						^$(B&W)"
	@echo "$(GREEN)^ [Tests created]				^$(B&W)"
	@echo "$(GREEN)^ $(RED)[For start tests]:$(B&W) $(GREEN)./test$(B&W)$(GREEN)			^$(B&W)"
	@echo "$(GREEN)~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~$(B&W)"
	@echo ""

-include $(DEP)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@test -d $(OBJDIR) || mkdir $(OBJDIR)
	@$(CC) -I$(INCLUDES) -MMD -c $< -o $@ $(CFLAGS)

clean:
	@$(RM) $(OBJDIR)

fclean:
	@$(RM) $(OBJDIR) $(NAME) test_c98 a.out
	@echo "$(RED) All test deleted $(B&W)"

re: fclean all

.PHONY: all bonus clean fclean re