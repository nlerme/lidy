#####################################################################################
#                                                                                   #
#                          Compiling Makefile for examples                          #
#                                                                                   #
#####################################################################################


#----------------------- Initialisation of misc. variables --------------------------
EXAMPLES_DIRS = `find . -maxdepth 1 -type d -printf "%f " | cut -d' ' -f2- -`


#---------------------------------- Makefile core -----------------------------------
all: examples

examples:
	@for Dir in $(EXAMPLES_DIRS); do \
		 $(MAKE) -C $$Dir -s; \
	done

clean:
	@for Dir in $(EXAMPLES_DIRS); do \
		 $(MAKE) -C $$Dir -s clean; \
	done

.PHONY: clean
