
linux: $(LINUX_BUILD_DIR)/$(PROJECT_NAME).so

$(LINUX_BUILD_DIR)/$(PROJECT_NAME).so: $(LINUX_OBJ) | $(LINUX_BUILD_DIR) $(INCLUDE)
	$(CXX) -shared $(LINUX_BUILD_DIR)/sdl/ -o $@ $^ $(LD_FLAGS)

$(LINUX_BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(INCLUDE) $(LINUX_BUILD_DIR)
	@ mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(LINUX_BUILD_DIR):
	mkdir -p $@

sdl_linux:
	cmake -S ./deps/SDL -B $(LINUX_BUILD_DIR)/sdl -DSDL_SHARED=ON
	cmake --build $(LINUX_BUILD_DIR)/sdl
