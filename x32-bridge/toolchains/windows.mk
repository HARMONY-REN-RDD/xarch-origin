CXX  := x86_64-w64-mingw32-g++
CXX_FLAGS += --sysroot=/usr/x86_64-w64-mingw32 -static

windows: $(WINDOWS_BUILD_DIR)/$(PROJECT_NAME).dll

$(WINDOWS_BUILD_DIR)/$(PROJECT_NAME).dll: $(WINDOWS_OBJ) | $(WINDOWS_BUILD_DIR)
	$(CXX) -shared $(CXX_FLAGS) -o $@ $^ $(LD_FLAGS)

$(WINDOWS_BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(WINDOWS_BUILD_DIR)
	@ mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) -c $< -o $@


$(WINDOWS_BUILD_DIR):
	mkdir -p $@
