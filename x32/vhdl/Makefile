ENTITIES_DIR := entities
ARCHITECTURES_DIR := architectures
TESTBENCHES_DIR := testbenches
BUILD_DIR := build

ENTITIES := $(shell find $(ENTITIES_DIR) -type f -name '*.vhdl')
ARCHITECTURES := $(shell find $(ARCHITECTURES_DIR) -type f -name '*.vhdl')
TESTBENCHES := $(shell find $(TESTBENCHES_DIR) -type f -name '*.vhdl')

TB_ENTITIES := $(basename $(notdir $(TESTBENCHES)))

GHDL = ghdl
GHDL_FLAGS := --workdir=$(BUILD_DIR)

.PHONY: analyze test clean

analyze: $(BUILD_DIR)
	$(GHDL) -a $(GHDL_FLAGS) $(ENTITIES)
	$(GHDL) -a $(GHDL_FLAGS) $(ARCHITECTURES)
	$(GHDL) -a $(GHDL_FLAGS) $(TESTBENCHES)

test: analyze
	@mkdir -p build
	@for tb in $(TB_ENTITIES); do \
		echo "=== $$tb ==="; \
		$(GHDL) -r $(GHDL_FLAGS) $$tb; \
	done | tee build/sim.log
	@errors=$$(grep -i "error" build/sim.log); \
	if [ -n "$$errors" ]; then \
		echo "\033[31m=== Errors found ===\033[0m"; \
		echo "\033[31m$$errors\033[0m"; \
	fi


$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)
