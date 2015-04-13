CC=arm-linux-gnueabihf-gcc

FLAGS= -static 

_INCLUDE=

_LIB=

OBJECTS= main.o menu.o screen.o i2c.o
		

EXECUTABLE=berryFi.out

PATH_OBJ=build/
PATH_SRC=src/

INCLUDE=$(addprefix -I, $(_INCLUDE))
LIB=$(addprefix -L, $(_LIB))


vpath %.o $(PATH_OBJ)
vpath %.h $(PATH_SRC)
vpath %.cpp $(PATH_SRC)

all: pre-build main-build

pre-build:
	clear
	-mkdir -p build


main-build: $(EXECUTABLE) $(OBJECTS) 


%.o: %.cpp %.h
	$(CC) $(INCLUDE) -c $< -o $(PATH_OBJ)$@


$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ $(FLAGS) -o $@ $(LIB)


.PHONY: all


clean: 
	del build
