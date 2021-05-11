#------------------------------- Makefile variable ----------------------------------
include Makefile.common
DOC_DIR      = doc
EXAMPLES_DIR = examples
CORE_DIR     = core

#---------------------------------- Makefile core -----------------------------------
all: header core examples footer

header:
	@echo "+----------------------------------------------------------------------------------"
	@echo "| Project name: $(PROJECT_NAME)"
	@echo "| Description : $(DESCRIPTION)"
	@echo "| Version     : $(VERSION)"
	@echo "| Authors     : $(AUTHORS)"
	@echo -e "+-----------------------------------------------------------------------------------\n"

core:
	@$(MAKE) -C $(CORE_DIR) -s

examples:
	@$(MAKE) -C $(EXAMPLES_DIR) -s

clean_core:
	@$(MAKE) -C $(CORE_DIR) -s clean

clean_examples:
	@$(MAKE) -C $(EXAMPLES_DIR) -s clean

clean_doc:
	@$(MAKE) -C $(DOC_DIR) -s clean

clean: clean_core clean_examples clean_doc

doc:
	@$(MAKE) -C $(DOC_DIR) -s

footer:
	@echo -e "\n-----------------------------------------------------------------------------------"

.PHONY: clean_core clean_examples clean_doc core examples doc
