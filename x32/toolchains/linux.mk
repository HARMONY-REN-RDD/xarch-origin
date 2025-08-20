CXX_LINUX := g++
LD_FLAGS_LINUX := -lcrypto -lpthread
CXX_FLAGS_LINUX := -std=c++17 -Wall -fPIC -I$(INCLUDE_DIR)


linux: $(LINUX_BUILD_DIR)/$(PROJECT_NAME).so

$(LINUX_BUILD_DIR)/$(PROJECT_NAME).so: $(LINUX_OBJ) | $(LINUX_BUILD_DIR) $(INCLUDE)
	$(CXX_LINUX) -shared -o $@ $^ $(LD_FLAGS_LINUX)

$(LINUX_BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(INCLUDE) $(LINUX_BUILD_DIR)
	@ mkdir -p $(dir $@)
	$(CXX_LINUX) $(CXX_FLAGS_LINUX) -c $< -o $@

$(LINUX_BUILD_DIR):
	mkdir -p $@
