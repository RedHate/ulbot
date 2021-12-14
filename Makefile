#############################
# redhate (ultros)
#############################

TARGET		=  ulbot
OBJ		    =  ulbot.o
LDLIBS		=  -pthread
TEXTURES 	=  textures
MODELS		=  models
ASSETS		=  
			  
CC		    =  $(PREFIX)gcc
CXX		    =  $(PREFIX)g++
LD		    =  $(PREFIX)gcc
MV		    =  mv
CP		    =  cp
ECHO		=  echo
RM 		    =  rm
AR		    =  $(PREFIX)ar
RANLIB   	=  $(PREFIX)ranlib
STRIP		=  $(PREFIX)strip

INCLUDES	?= -I/usr/include
LIBS		?= -L/usr/lib
LDFLAGS		?= -B/usr/lib
CFLAGS   	?= -Wall -g -O2 $(INCLUDES) $(LIBS) -fPIC -no-pie
CXXFLAGS 	?= -Wall -g -O2 $(INCLUDES) $(LIBS) -fPIC -no-pie
WARNINGS	:= -w

## colors for fun
BLACK1		= \033[1;30m
BLACK2		= \033[0;30m
RED1		= \033[1;31m
RED2		= \033[0;31m
GREEN1		= \033[1;32m
GREEN2		= \033[0;32m
YELLOW1		= \033[1;33m
YELLOW		= \033[0;33m
BLUE1		= \033[1;34m
BLUE2		= \033[0;34m
PURPLE1		= \033[1;35m
PURPLE2		= \033[0;35m
CYAN1		= \033[1;36m
CYAN2		= \033[0;36m
WHITE1		= \033[1;37m
WHITE2		= \033[0;37m
NOCOLOR		= \033[0m

.PHONY: all run clean

all: $(ASSETS) $(OBJ) $(RES) $(TARGET) $(TARGET_LIB)

run:  $(ASSETS) $(OBJ) $(RES) $(TARGET) $(TARGET_LIB) 
	@./$(TARGET) localhost 6667 chat ultbot_

clean: 
	@printf "$(RED1)[CLEANING]$(NOCOLOR)\n" 
	@rm $(OBJ) $(RES) $(TARGET) $(TARGET_LIB) $(ASSETS)

%.o: %.cpp
	@printf "$(RED1)[CXX]$(NOCOLOR) $(notdir $(basename $<)).o\n" 
	@$(CXX) $(WARNINGS) -c $< $(CXXFLAGS) -o $(basename $<).o 

%.o: %.cxx
	@printf "$(RED1)[CXX]$(NOCOLOR) $(notdir $(basename $<)).o\n" 
	@$(CXX) $(WARNINGS) -c $< $(CFLAGS) -o $(basename $<).o 

%.o: %.c
	@printf "$(RED1)[CC]$(NOCOLOR) $(notdir $(basename $<)).o\n" 
	@$(CC) $(WARNINGS) -c $< $(CFLAGS) -o $(basename $<).o 

%.a:
	@printf "$(RED1)[CC]$(NOCOLOR) $(basename $(TARGET_LIB)).a\n" 
	@$(AR) -cru $(basename $(TARGET_LIB)).a $(OBJ)

$(TARGET): $(ASSETS) $(OBJ)
	@printf "$(RED1)[CC]$(NOCOLOR) $(TARGET)\n" 
	@$(CC) $(OBJ) -shared $(LDLIBS) $(LDFLAGS) $(CXXFLAGS) -o $(TARGET)
	@$(STRIP) -s $(TARGET)
