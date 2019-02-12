CC = g++
CFLAGS = `pkg-config --libs --cflags gtkmm-3.0` -Wall
EXEC_NAME = balltrapp
LIBS = -L/usr/lib/ -lboost_serialization -lcurl -ljsoncpp
OBJ_FILES = ./Model/Channel.o ./Model/Parameter.o ./Model/User.o ./Model/UserAuthentification.o ./Model/UserCredit.o ./Model/UserInfo.o ./Model/Database.o ./Model/Game.o ./View/ViewConsole.o ./View/ViewMotion.o ./Controller/ControllerConsole.o ./Controller/ControllerMotion.o main.o

all : $(EXEC_NAME)

clean :
	rm $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS) $(CFLAGS)
	
%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<