#####################################################################################
#                                                                                   #
#                            Compiling Makefile for core                            #
#                                                                                   #
#####################################################################################


#----------------------- Initialisation of misc. variables --------------------------
include ../Makefile.common
COMMON_MAKEFILE = ../Makefile.common
OUTPUT_DIR      = ../lib
CXX             = gcc
CXXFLAGS        = -O3 -Wall -g -fPIC
LDFLAGS         = -shared

INC_DIR         = include
INCS            = -I$(INC_DIR) -I/usr/include/libxml2
LIBS            = -lxml2

SRC_DIR         = src
OBJ_DIR         = ../obj
BIN_DIR         = ../bin

COLOR_BIN       = $(BIN_DIR)/color

FILES_EXT       = c
SRC             = $(notdir $(wildcard $(SRC_DIR)/*.$(FILES_EXT)))
OBJ             = $(SRC:%.$(FILES_EXT)=$(OBJ_DIR)/%.o)


#---------------------------------- Makefile core -----------------------------------
all: header depend $(OUTPUT_DIR)/lib$(GLOBAL_TARGET).a $(OUTPUT_DIR)/lib$(GLOBAL_TARGET).so footer

header:
	@echo "`$(COLOR_BIN) ltwhite`[ Core ]`$(COLOR_BIN) off`"

depend:
	@echo -n "`$(COLOR_BIN) ltyellow`+ Generate dependencies`$(COLOR_BIN) off` : "
ifneq ($(strip $(SRC)),)
	@$(CXX) $(INCS) -MM $(SRC:%=$(SRC_DIR)/%) \
	| sed -e 's:^[^ ]:$(OBJ_DIR)/&:' > Makefile.depend
endif
	@echo "`$(COLOR_BIN) ltred`OK`$(COLOR_BIN) off`"

$(OUTPUT_DIR)/lib$(GLOBAL_TARGET).a: $(OBJ)
	@echo -n "`$(COLOR_BIN) ltyellow`+ Build $(notdir $@)`$(COLOR_BIN) off` : "
	@\rm -rf $@
	@ar rc $@ $(OBJ)
	@echo "`$(COLOR_BIN) ltred`OK`$(COLOR_BIN) off`"

$(OUTPUT_DIR)/lib$(GLOBAL_TARGET).so: $(OBJ)
	@echo -n "`$(COLOR_BIN) ltyellow`+ Build $(notdir $@)`$(COLOR_BIN) off` : "
	@\rm -rf $@
	@$(CXX) $(LDFLAGS) $(OBJ) $(LIBS) -o $@
	@echo "`$(COLOR_BIN) ltred`OK`$(COLOR_BIN) off`"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(FILES_EXT)
	@echo -n "`$(COLOR_BIN) ltyellow`+ Compile $(notdir $@)`$(COLOR_BIN) off` : "
	@$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@
	@echo "`$(COLOR_BIN) ltred`OK`$(COLOR_BIN) off`"

clean: header
	@echo -n "`$(COLOR_BIN) ltyellow`+ Delete objects and libraries`$(COLOR_BIN) off` : "
	@\rm -rf $(OBJ) $(OUTPUT_DIR)/lib$(GLOBAL_TARGET).*
	@echo "`$(COLOR_BIN) ltred`OK`$(COLOR_BIN) off`"

footer:

.PHONY: clean

include Makefile.depend
