########################################
##
## Makefile
## LINUX compilation 
##
##############################################

#FLAGS
C++FLAG = -g  

MATH_LIBS = -lm

EXEC_DIR=.

.cpp.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@

#Including
INCLUDES=  -I. 

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 

#All Programs (ListTest)

Cpp_OBJ1=Image.o 	Pgm.o 	BinaryImage.o 		    				           Program1.o 
Cpp_OBJ2=Image.o 	Pgm.o 	ObjectInfo.o   DisjSets.o  Line.o  LabeledImage.o  Program2.o
Cpp_OBJ3=Image.o 	Pgm.o 	ObjectInfo.o   DisjSets.o  Line.o  LabeledImage.o  Program3.o
Cpp_OBJ4=Image.o 	Pgm.o 	ObjectInfo.o   DisjSets.o  Line.o  LabeledImage.o   Program4.o

PROGRAM_NAME1=Program1
PROGRAM_NAME2=Program2
PROGRAM_NAME3=Program3
PROGRAM_NAME4=Program4

$(PROGRAM_NAME1): $(Cpp_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ1) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM_NAME2): $(Cpp_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ2) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM_NAME3): $(Cpp_OBJ3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ3) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM_NAME4): $(Cpp_OBJ4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ4) $(INCLUDES) $(LIBS_ALL)

all: 
	make $(PROGRAM_NAME1)
	make $(PROGRAM_NAME2)
	make $(PROGRAM_NAME3)
	make $(PROGRAM_NAME4)

clean:
	(rm -f *.o;)

(:
