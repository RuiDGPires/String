DEFAULT:=default
STATIC_TARGET_NAME:=String

SOURCE_FOLDER:=src
HEADER_FOLDER:=include
EXAMPLE_FOLDER:=examples
CPP_FILES:=$(wildcard $(SOURCE_FOLDER)/*.cpp)
HPP_FILES:=$(wildcard $(HEADER_FOLDER)/*)

BUILD_FOLDER:=build
OBJ_FOLDER:=$(BUILD_FOLDER)/objs
OBJ_FILES:=$(CPP_FILES:$(SOURCE_FOLDER)/%.cpp=$(OBJ_FOLDER)/%.o)

STATIC_TARGET:=$(BUILD_FOLDER)/lib$(STATIC_TARGET_NAME).a

#---------

CC:=g++
FLAGS:=-Wall -Wextra -pedantic -I$(HEADER_FOLDER)

#---------

.PHONY: default
default: $(BUILD_FOLDER)/$(EXAMPLE_FOLDER)/$(DEFAULT)

$(BUILD_FOLDER)/$(EXAMPLE_FOLDER)/%: $(EXAMPLE_FOLDER)/%.cpp $(STATIC_TARGET) | $(BUILD_FOLDER)/$(EXAMPLE_FOLDER) 
	$(CC) $(FLAGS) $< -o $@ -L$(BUILD_FOLDER) -l$(STATIC_TARGET_NAME)

.PHONY: static
static: $(STATIC_TARGET)

$(OBJ_FOLDER)/%.o: $(SOURCE_FOLDER)/%.cpp $(HPP_FILES) | $(OBJ_FOLDER)
	$(CC) $(FLAGS) -c $< -o $@  

$(STATIC_TARGET): $(OBJ_FILES) | $(BUILD_FOLDER)
	ar rcs $@ $^ 

$(BUILD_FOLDER)/$(EXAMPLE_FOLDER): 
	mkdir -p $@

$(OBJ_FOLDER):
	mkdir -p $@

$(BUILD_FOLDER):
	mkdir -p $@

.PHONY: clean
clean: 
	rm -rf $(BUILD_FOLDER)
