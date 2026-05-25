##
## EPITECH PROJECT, 2026
## makefile
## File description:
## root makefile
##

CXX = clang++

MAIN = src/Main.cpp

SRC = 	$(addprefix src/, 						\
			StoneAnalysis.cpp 					\
			Wav.cpp								\
			Riff.cpp							\
			Fmt.cpp								\
			Waves.cpp							\
			DFT.cpp								\
    	)

PATH_UNI = 	$(addprefix tests/, 				\
				tests_parsing.cpp 				\
			)

OBJ = $(SRC:.cpp=.o) $(MAIN:.cpp=.o)

TESTS = tests_run

CXXFLAGS = -Wall -Wextra --std=c++20

CPPFLAGS = -iquote include

NAME = stone_analysis

all:	$(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CPPFLAGS)

debug: CFLAGS += -g
debug: fclean $(OBJ) $(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

$(TESTS): LDFLAGS += --coverage -lcriterion
$(TESTS):
	$(CXX) -o $(TESTS) $(SRC) $(PATH_UNI) \
		$(LDLIBS) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS)
	./$(TESTS)

uni_clean:
	$(RM) $(TESTS)*

clean: uni_clean
	$(RM) $(OBJ)

fclean:	clean
	$(RM) *.html coverage coverage.css
	$(RM) $(SERVER_NAME) $(NAME)

re: fclean all

.PHONY: all debug clean fclean re tests_run uni_clean
