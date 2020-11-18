################################################
##	MACROS
################################################

# $(1) : Compiler
# $(2) : Object file to generate
# $(3) : Source file
# $(4) : Additional dependencies
# $(5) : Compiler flags
define COMPILE
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5)
endef

# $(1) : Source file
define C2O
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

# $(1) : Source file
define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(1)))
endef


################################################
##	CONFIG
################################################
APP 		:= game
SFML		:= SFML

CCFLAGS 	:= -Wall -pedantic -fdiagnostics-color=always -std=c++17 -I./SFML -I./src

CFLAGS 		:= $(CCFLAGS)
CC 			:= x86_64-w64-mingw32-g++#ccache g++
C			:= x86_64-w64-mingw32-gcc#ccache gcc
MKDIR 		:= mkdir -p
SRC			:= src
OBJ			:= obj
BIN 		:= bin

LIBPATHS	:= -L./SFML
LIBS		:= -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2

ifdef DEBUG
	CCFLAGS += -g
else
	CCFLAGS += -O3
endif

ifdef NOCCACHE
	CC := g++
endif

ALLCPPS		:= $(shell find $(SRC)/ -type f -iname *.cpp)
ALLCS		:= $(shell find $(SRC)/ -type f -iname *.c)
ALLOBJ	 	:= $(foreach F,$(ALLCPPS) $(ALLCS),$(call C2O,$(F)))
SUBDIRS 	:= $(shell find $(SRC)/ -type d)
OBJSUBDIRS 	:= $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))


################################################
##	RULES
################################################
.PHONY: info clean cleanall

$(APP): $(OBJSUBDIRS) $(BIN) $(ALLOBJ)
	$(info --------- Compilando app ----------)
	$(CC) $(LIBPATHS) -o $(BIN)/$(APP) $(ALLOBJ) $(LIBS)

$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CCFLAGS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS))))


$(OBJSUBDIRS) :
	$(info --------- Creando /$(OBJ) ----------)
	$(MKDIR) $(OBJSUBDIRS)

$(BIN) : 
	$(info --------- Creando /$(BIN) ----------)
	$(MKDIR) $(BIN)

info:
	$(info --------- Informacion ----------)
	$(info Subdirs: $(SUBDIRS))
	$(info Objsubdirs: $(OBJSUBDIRS))
	$(info Bin: $(BIN)/)
	$(info AllCpps: $(ALLCPPS))
	$(info AllObj: $(ALLOBJ))

clean:
	$(info --------- Borrando /$(OBJ) ----------)
	$(shell rm -f -r "./$(OBJ)")

cleanall: clean
	$(info --------- Borrando /$(BIN) ----------)
	$(shell rm -f -r "./$(BIN)")

