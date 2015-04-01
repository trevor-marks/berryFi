CC=g++

FLAGS= -static 

_INCLUDE=

_LIB=

OBJECTS= menu.o \
		main.o

EXECUTABLE=PiPlayer.exe

PATH_OBJ=build/
PATH_SRC=src/

INCLUDE=$(addprefix -I, $(_INCLUDE))
LIB=$(addprefix -L, $(_LIB))


vpath %.o $(PATH_OBJ)
vpath %.h $(PATH_SRC)
vpath %.cpp $(PATH_SRC)

all: pre-build main-build

pre-build:
	cls
	-mkdir build


main-build: $(OBJECTS) $(EXECUTABLE)


%.o: %.cpp %.h
	$(CC) $(INCLUDE) -c $< -o $(PATH_OBJ)$@


$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ $(FLAGS) -o $@ $(LIB)


.PHONY: all


clean: 
	del build