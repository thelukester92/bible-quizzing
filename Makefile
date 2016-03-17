OUTFILE	= bible_quizzing
BIN		= ./bin
OBJ		= ./obj
SRC		= ./src
DEP		= ./dependencies

CPP_FILES =\
	Bible.cpp\
	Database.cpp\
	Player.cpp\
	QuizSet.cpp\
	Quiz.cpp\
	Random.cpp\
	main.cpp\

DEP_FILES =\
	sqlite3.c\

OBJ_FILES = $(DEP_FILES:%.c=$(OBJ)/%.o) $(CPP_FILES:%.cpp=$(OBJ)/%.o)

all: dirs $(OBJ_FILES)
	g++ $(OBJ_FILES) -Wall -o $(BIN)/$(OUTFILE)

$(OBJ)/%.o: $(SRC)/%.cpp
	g++ $< -c -o $@

$(OBJ)/%.o: $(DEP)/%.c
	gcc $< -c -o $@

dirs:
	mkdir -p $(BIN)
	mkdir -p $(OBJ)

clean:
	rm -rf $(BIN)
	rm -rf $(OBJ)
