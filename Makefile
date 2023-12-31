##
## EPITECH PROJECT, 2023
## bsq
## File description:
## Makefile
##

PROJECT_NAME			=	bsq
NAME					=	bsq

SRC 					:= $(shell find src/ -name '*.c' -type f \
| xargs grep -L "int main")

MAIN_SRC				:= src/main.c

BUILD_DIR 				= 	build
BUILD_DIR_DEFAULT		=	$(BUILD_DIR)/default
OBJ						=	$(SRC:%.c=$(BUILD_DIR_DEFAULT)/%.o) \
$(MAIN_SRC:%.c=$(BUILD_DIR_DEFAULT)/%.o)

DEBUG_BUILD_DIR			=	$(BUILD_DIR)/debug
DEBUG_OBJ				=	$(SRC:%.c=$(DEBUG_BUILD_DIR)/%.o) \
$(MAIN_SRC:%.c=$(DEBUG_BUILD_DIR)/%.o)

TEST_BUILD_DIR			=	$(BUILD_DIR)/tests
TEST_SRC				:=	$(shell find tests/unit_tests/ -name '*.c' -type f \
| xargs grep -L "int main")
TEST_OBJ				=	$(SRC:%.c=$(TEST_BUILD_DIR)/%.o) \
$(TEST_SRC:%.c=$(TEST_BUILD_DIR)/%.o)

CRITERION				=	-lcriterion --coverage
LCOV 					:= 	-fprofile-arcs -ftest-coverage
TEST_NAME				=	unit_tests

CFLAGS					=	-I include/ -O3

WFLAGS					=	-Wall -Wextra -Wformat -Wpedantic -Walloca \
							-Wduplicated-cond -Wshadow -Wduplicated-branches \
							-Wundef -Wdouble-promotion -Wmissing-include-dirs

_default:
	@$(MAKE) -j all --no-print-directory --silent

all:	$(NAME)

$(NAME):	$(OBJ)
	@gcc -o $(NAME) $(OBJ)\
	&& echo -e "\033[1;32m[OK]\033[0m" $(NAME) \
	|| echo -e "\033[1;31m[KO]\033[0m" $(NAME)

$(BUILD_DIR_DEFAULT)/%.o:	%.c
	@mkdir -p $(dir $@)
	@gcc -c -o $@ $< $(CFLAGS) $(WFLAGS) \
	&& echo -e "\033[1;32m[OK]\033[0m" $< \
	|| echo -e "\033[1;31m[KO]\033[0m" $<

_clean:
	@rm -rf $(BUILD_DIR_DEFAULT) $(DEBUG_BUILD_DIR) $(TEST_BUILD_DIR)
	@rm -f $(shell find -name '*.gc*' -type f)

clean: _clean
	@echo -e "\033[1;31m[CLEAN]\033[0m" $(PROJECT_NAME)

fclean: _clean
	@echo -e "\033[1;31m[FCLEAN]\033[0m" $(PROJECT_NAME)
	@rm -f $(NAME)
	@rm -f $(TEST_NAME)

re:	fclean _default

debug:	CFLAGS += -g -DDEBUG
debug:	$(DEBUG_OBJ)
	@gcc -o $(NAME) $(DEBUG_OBJ) $(LDLIBS) \
	&& echo -e "\033[1;32m[OK]\033[0m" $(NAME) \
	|| echo -e "\033[1;31m[KO]\033[0m" $(NAME)

$(DEBUG_BUILD_DIR)/%.o:	%.c
	@mkdir -p $(dir $@)
	@gcc -c -o $@ $< $(CFLAGS) $(WFLAGS) \
	&& echo -e "\033[1;32m[OK]\033[0m" $< \
	|| echo -e "\033[1;31m[KO]\033[0m" $<

tests_run:	CFLAGS += $(CRITERION)
tests_run:	$(TEST_NAME)
	@./$(TEST_NAME) --verbose --always-succeed
	gcovr --exclude tests/

$(TEST_NAME):	$(TEST_OBJ)
	@gcc -o $(TEST_NAME) $(TEST_OBJ) $(LDLIBS) $(CRITERION) \
	&& echo -e "\033[1;32m[OK]\033[0m" $(TEST_NAME) \
	|| echo -e "\033[1;31m[KO]\033[0m" $(TEST_NAME)

$(TEST_BUILD_DIR)/%.o:	%.c
	@mkdir -p $(dir $@)
	@gcc -c -o $@ $< $(CFLAGS) $(WFLAGS) \
	&& echo -e "\033[1;32m[OK]\033[0m" $< \
	|| echo -e "\033[1;31m[KO]\033[0m" $<

.PHONY: all clean fclean re debug tests_run
.SILENT: all clean fclean re debug tests_run
