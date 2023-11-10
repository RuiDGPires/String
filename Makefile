TARGET_NAME:=a.out
STATIC_TARGET_NAME:=String

CC:=g++
FLAGS:=-Wall -Wextra -pedantic -Iinclude

SOURCE_FOLDER:=src
HEADER_FOLDER:=include
CPP_FILES:=$(wildcard $(SOURCE_FOLDER)/*.cpp)
HPP_FILES:=$(wildcard $(HEADER_FOLDER)/*)
MAIN_FILE:=main.cpp


BUILD_FOLDER:=build
OBJ_FOLDER:=$(BUILD_FOLDER)/objs
OBJ_FILES:=$(CPP_FILES:$(SOURCE_FOLDER)/%.cpp=$(OBJ_FOLDER)/%.o)

STATIC_TARGET:=$(BUILD_FOLDER)/lib$(STATIC_TARGET_NAME).a
TARGET:=$(BUILD_FOLDER)/$(TARGET_NAME)

#---------

$(TARGET): $(MAIN_FILE) $(STATIC_TARGET) | $(BUILD_FOLDER) 
	$(CC) $(FLAGS) $< -o $@ -L$(BUILD_FOLDER) -l$(STATIC_TARGET_NAME)

.PHONY: static
static: $(STATIC_TARGET)

$(OBJ_FOLDER)/%.o: $(SOURCE_FOLDER)/%.cpp $(HPP_FILES) | $(OBJ_FOLDER)
	$(CC) $(FLAGS) -c $< -o $@  

$(STATIC_TARGET): $(OBJ_FILES) | $(BUILD_FOLDER)
	ar rcs $@ $^ 

$(OBJ_FOLDER):
	mkdir -p $@

$(BUILD_FOLDER):
	mkdir -p $@

.PHONY: clean
clean: 
	rm -rf $(BUILD_FOLDER)
