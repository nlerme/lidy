#####################################################################################
#                                                                                   #
#                          Compiling Makefile for archive                           #
#                                                                                   #
#####################################################################################


#----------------------- Initialisation of misc. variables --------------------------
include ../Makefile.common
BIN_DIR   = ../bin
COLOR_BIN = $(BIN_DIR)/color


#------------------------------ Functions & procedures ------------------------------
cd_quiet = cd $1 1>/dev/null


#---------------------------------- Makefile core -----------------------------------
all: header
	@echo -n "`$(COLOR_BIN) ltyellow`+ Generate archive`$(COLOR_BIN) off` : "
	@cd ../.. && zip -qr9 $(GLOBAL_TARGET)/arch/$(GLOBAL_TARGET).zip $(GLOBAL_TARGET)/* && $(call cd_quiet, -)
	@echo "`$(COLOR_BIN) ltred`OK`$(COLOR_BIN) off`"

header:
	@echo "`$(COLOR_BIN) ltwhite`[ Archive ]`$(COLOR_BIN) off`"

clean: header
	@echo -n "`$(COLOR_BIN) ltyellow`+ Delete arch`$(COLOR_BIN) off` : "
	@\rm -rf $(GLOBAL_TARGET).zip
	@echo "`$(COLOR_BIN) ltred`OK`$(COLOR_BIN) off`"

footer:

.PHONY: clean
