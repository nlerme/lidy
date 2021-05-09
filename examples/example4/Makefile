#####################################################################################
#                                                                                   #
#                          Compiling Makefile for example4                          #
#                                                                                   #
#####################################################################################


#----------------------- Initialisation of misc. variables --------------------------
include ../../Makefile.common
CXX          = gcc
CXXFLAGS     = -O3 -Wall -g
BIN_DIR      = ../../bin
OBJ_DIR      = ../../obj
SRC_DIR      = .
COLOR_BIN    = $(BIN_DIR)/color
INC_DIR      = ../../core/include
LIB_DIR      = ../../lib
INCS         = -I$(INC_DIR)
LIBS         = -L$(LIB_DIR) -l$(GLOBAL_TARGET)
FILES_EXT    = c
SRC          = $(notdir $(wildcard $(SRC_DIR)/*.$(FILES_EXT)))
OBJ          = $(SRC:%.$(FILES_EXT)=$(OBJ_DIR)/%.o)
DESCRIPTION  = Example 4 - Multiplication of sparse matrices
LOCAL_TARGET = example4


#---------------------------------- Makefile core -----------------------------------
all: header depend $(LOCAL_TARGET) footer

header:
	@echo "`$(COLOR_BIN) ltwhite`[ $(DESCRIPTION) ]`$(COLOR_BIN) off`"

depend:
	@echo -n "`$(COLOR_BIN) ltyellow`+ Generate dependencies`$(COLOR_BIN) off` : "
ifneq ($(strip $(SRC)),)
	@$(CXX) $(INCS) -MM $(SRC:%=$(SRC_DIR)/%) \
	| sed -e 's:^[^ ]:$(OBJ_DIR)/&:' > Makefile.depend
endif
	@echo "`$(COLOR_BIN) ltred`OK`$(COLOR_BIN) off`"

$(LOCAL_TARGET): $(OBJ)
	@echo -n "`$(COLOR_BIN) ltyellow`+ Build $@ `$(COLOR_BIN) off`: "
	@$(CXX) $(CXXFLAGS) $(INCS) $^ $(LIBS) -o $@
	@echo "`$(COLOR_BIN) ltred`OK`$(COLOR_BIN) off`"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(FILES_EXT)
	@echo -n "`$(COLOR_BIN) ltyellow`+ Compile $(notdir $@)`$(COLOR_BIN) off` : "
	@$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@
	@echo "`$(COLOR_BIN) ltred`OK`$(COLOR_BIN) off`"

clean: header
	@echo -n "`$(COLOR_BIN) ltyellow`+ Delete objects and bin`$(COLOR_BIN) off` : "
	@\rm -rf $(LOCAL_TARGET) $(OBJ)
	@echo "`$(COLOR_BIN) ltred`OK`$(COLOR_BIN) off`"

footer:

.PHONY: clean

include Makefile.depend
