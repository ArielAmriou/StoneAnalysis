##
## EPITECH PROJECT, 2026
## makefile
## File description:
## root makefile
##

CXX = clang++

MAIN = src/Main.cpp

SRC = 	$(addprefix ../src/, 					\
			Wav.cpp								\
			Riff.cpp							\
			Fmt.cpp								\
			Waves.cpp							\
			DFT.cpp								\
    	)

BONUS_SRC =	$(addprefix src/, 					\
			StoneAnalysis.cpp					\
			WaveForm.cpp 						\
			FrequencySpectrum.cpp				\
			ComplexSpectrum.cpp					\
			Loading.cpp 						\
			AButton.cpp 						\
    	)

OBJ = $(SRC:.cpp=.o) $(BONUS_SRC:.cpp=.o) $(MAIN:.cpp=.o)

CXXFLAGS = -Wall -Wextra --std=c++20 -lsfml-graphics -lsfml-window -lsfml-system $(shell pkg-config --cflags --libs gtk+-3.0)

CPPFLAGS = -iquote include -iquote ../include

NAME = bonus

all:	$(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(CPPFLAGS)

debug: CFLAGS += -g
debug: fclean $(OBJ) $(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(SERVER_NAME) $(NAME)

re: fclean all

.PHONY: all debug clean fclean re tests_run uni_clean
