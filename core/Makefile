#--- Variables --------------------------------------------------------------------------------------
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
FILES_EXT       = c
SRC             = $(notdir $(wildcard $(SRC_DIR)/*.$(FILES_EXT)))
OBJ             = $(SRC:%.$(FILES_EXT)=$(OBJ_DIR)/%.o)

#--- Rules ------------------------------------------------------------------------------------------
all: header depend $(OUTPUT_DIR)/lib$(GLOBAL_TARGET).a $(OUTPUT_DIR)/lib$(GLOBAL_TARGET).so footer

header:
	@echo "[ Core ]"

depend:
ifeq ("$(wildcard $(OBJ_DIR))","")
	@mkdir $(OBJ_DIR) $(OUTPUT_DIR)
endif
	@echo -n "  + Generate dependencies : "
ifneq ($(strip $(SRC)),)
	@$(CXX) $(INCS) -MM $(SRC:%=$(SRC_DIR)/%) \
	| sed -e 's:^[^ ]:$(OBJ_DIR)/&:' > Makefile.depend
endif
	@echo "OK"

$(OUTPUT_DIR)/lib$(GLOBAL_TARGET).a: $(OBJ)
	@echo -n "  + Build $(notdir $@) : "
	@\rm -rf $@
	@ar rc $@ $(OBJ)
	@echo "OK"

$(OUTPUT_DIR)/lib$(GLOBAL_TARGET).so: $(OBJ)
	@echo -n "  + Build $(notdir $@) : "
	@\rm -rf $@
	@$(CXX) $(LDFLAGS) $(OBJ) $(LIBS) -o $@
	@echo "OK"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(FILES_EXT)
	@echo -n "  + Compile $(notdir $@) : "
	@$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@
	@echo "OK"

clean: header
	@echo -n "  + Delete objects and libraries : "
	@\rm -rf $(OBJ_DIR) $(OUTPUT_DIR)
	@echo "OK"

footer:

.PHONY: clean

include Makefile.depend
