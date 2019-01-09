####################################################
###################### MAKE ########################
####################################################

PATHBUF= ./src/buffers
PATHTAB= ./src/tables
PATHSRC= ./src

PATHTEMP = ./.temp
PATHEXEC = ./bin
EXECUTAVEL = Table_Utils.run

all:
	mkdir -p $(PATHEXEC)
	mkdir -p $(PATHTEMP)
	make $(EXECUTAVEL)

#Juntando todos os objetos e gerando o programa

$(EXECUTAVEL): $(PATHTEMP)/AeternalBuffer.o $(PATHTEMP)/SmallText.o $(PATHTEMP)/Converter.o $(PATHTEMP)/Table.o $(PATHTEMP)/TableLine.o $(PATHTEMP)/TableCell.o $(PATHTEMP)/TextPart.o $(PATHTEMP)/Coordenate.o $(PATHTEMP)/Rule.o $(PATHTEMP)/main.o
	$(CPP) $(CCFLAGS) $(PATHTEMP)/AeternalBuffer.o $(PATHTEMP)/SmallText.o $(PATHTEMP)/Converter.o $(PATHTEMP)/Table.o $(PATHTEMP)/TableLine.o $(PATHTEMP)/TableCell.o $(PATHTEMP)/TextPart.o $(PATHTEMP)/Coordenate.o $(PATHTEMP)/Rule.o $(PATHTEMP)/main.o -o $(PATHEXEC)/$(EXECUTAVEL)

#Compiling main file:

$(PATHTEMP)/main.o: $(PATHSRC)/main.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/main.cpp -o $(PATHTEMP)/main.o


#Compiling buffer package:

$(PATHTEMP)/AeternalBuffer.o: $(PATHBUF)/AeternalBuffer.cpp
	$(CPP) $(CCFLAGS) -c $(PATHBUF)/AeternalBuffer.cpp -o $(PATHTEMP)/AeternalBuffer.o


#Compiling table package:

$(PATHTEMP)/Table.o: $(PATHTAB)/Table.cpp
	$(CPP) $(CCFLAGS) -c $(PATHTAB)/Table.cpp -o $(PATHTEMP)/Table.o

$(PATHTEMP)/TableLine.o: $(PATHTAB)/TableLine.cpp
	$(CPP) $(CCFLAGS) -c $(PATHTAB)/TableLine.cpp -o $(PATHTEMP)/TableLine.o

$(PATHTEMP)/TableCell.o: $(PATHTAB)/TableCell.cpp
	$(CPP) $(CCFLAGS) -c $(PATHTAB)/TableCell.cpp -o $(PATHTEMP)/TableCell.o

$(PATHTEMP)/TextPart.o: $(PATHTAB)/TextPart.cpp
	$(CPP) $(CCFLAGS) -c $(PATHTAB)/TextPart.cpp -o $(PATHTEMP)/TextPart.o

$(PATHTEMP)/Coordenate.o: $(PATHTAB)/Coordenate.cpp
	$(CPP) $(CCFLAGS) -c $(PATHTAB)/Coordenate.cpp -o $(PATHTEMP)/Coordenate.o

$(PATHTEMP)/Converter.o: $(PATHTAB)/Converter.cpp
	$(CPP) $(CCFLAGS) -c $(PATHTAB)/Converter.cpp -o $(PATHTEMP)/Converter.o

$(PATHTEMP)/SmallText.o: $(PATHTAB)/SmallText.cpp
	$(CPP) $(CCFLAGS) -c $(PATHTAB)/SmallText.cpp -o $(PATHTEMP)/SmallText.o

$(PATHTEMP)/Rule.o: $(PATHTAB)/Rule.cpp
	$(CPP) $(CCFLAGS) -c $(PATHTAB)/Rule.cpp -o $(PATHTEMP)/Rule.o


####################################################
###################### CLEAN #######################
####################################################

clean:
	/bin/rm -rf $(PATHEXEC)
	/bin/rm -rf $(PATHTEMP)

####################################################
##################### COMPILER #####################
####################################################

##### COMPILER CONFIGURATION's
# Compiler
CPP = g++ -std=c++14

# Compilation parameters
CCOPT = -m64 -O3 -g -fPIC -fexceptions -DIL_STD

# Header's include path
CCFLAGS = $(CCOPT)
