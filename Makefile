
NAME = zappy

FLAGS = -Wfatal-errors -std=c++14

SRC =  ./src/*.cpp

INC = -I ./src -I ~/.brew/include

all:
	@g++ $(FLAGS) -o $(NAME) $(SRC) $(INC)

fclean:
	rm $(NAME)
