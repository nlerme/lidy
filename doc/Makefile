#####################################################################################
#                                                                                   #
#                       Compiling Makefile for documentation                        #
#                                                                                   #
#####################################################################################


#----------------------- Initialisation of misc. variables --------------------------
BIN_DIR      = ../bin
COLOR_BIN    = $(BIN_DIR)/color
DOXYGEN_FILE = doc.doxygen
DOCS_DIRS    = `find . -maxdepth 1 -type d -printf "%f " | cut -d' ' -f2- -`


#---------------------------------- Makefile core -----------------------------------
all: header
	@echo -n "`$(COLOR_BIN) ltyellow`+ Generate doc`$(COLOR_BIN) off` : "
	@doxygen $(DOXYGEN_FILE) 2>/dev/null >/dev/null
	@echo "`$(COLOR_BIN) ltred`OK`$(COLOR_BIN) off`"

header:
	@echo "`$(COLOR_BIN) ltwhite`[ Documentation ]`$(COLOR_BIN) off`"

clean: header
	@echo -n "`$(COLOR_BIN) ltyellow`+ Delete doc`$(COLOR_BIN) off` : "
	@for Dir in $(DOCS_DIRS); do \
		\rm -rf $$Dir/*; \
	done
	@echo "`$(COLOR_BIN) ltred`OK`$(COLOR_BIN) off`"

footer:

.PHONY: clean
