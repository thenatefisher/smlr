SRC_DIR   = src
BUILD_DIR = build
TESTS_DIR = tests
GTEST_DIR = googletest/googletest
GTEST_INC = -I$(GTEST_DIR)/include -I$(GTEST_DIR)/include/gtest -I$(GTEST_DIR)/include/gtest/internal

all : $(BUILD_DIR)/rel/smlr
	@git submodule	update --init

test : $(BUILD_DIR)/rel/smlr_ut
	@$(BUILD_DIR)/rel/smlr_ut

clean :
	rm -rf $(BUILD_DIR)

$(BUILD_DIR)/rel/smlr : $(BUILD_DIR)/smlr.o $(SRC_DIR)/smlr.c $(SRC_DIR)/smlr.h $(SRC_DIR)/main.c
	@mkdir -p $(BUILD_DIR)/rel
	@gcc -o $(BUILD_DIR)/rel/smlr -I$(SRC_DIR) -O3 $(SRC_DIR)/main.c $(BUILD_DIR)/smlr.o

$(BUILD_DIR)/rel/smlr_ut : $(BUILD_DIR)/smlr.o $(BUILD_DIR)/smlr_ut.o $(BUILD_DIR)/libgtest_main.a
	@mkdir -p $(BUILD_DIR)/rel
	@g++ -L $(BUILD_DIR) -lgtest_main $(GTEST_INC) -I$(SRC_DIR) $(BUILD_DIR)/smlr.o $(BUILD_DIR)/smlr_ut.o -o $(BUILD_DIR)/rel/smlr_ut

$(BUILD_DIR)/smlr.o : $(SRC_DIR)/smlr.c $(SRC_DIR)/smlr.h
	@mkdir -p $(BUILD_DIR)
	@gcc -c $(SRC_DIR)/smlr.c -I$(SRC_DIR) -Wall -Wextra -O3 -o $(BUILD_DIR)/smlr.o

$(BUILD_DIR)/smlr_ut.o : $(TESTS_DIR)/smlr_ut.cc $(SRC_DIR)/smlr.h
	@mkdir -p $(BUILD_DIR)
	@g++ -c $(TESTS_DIR)/smlr_ut.cc -I$(SRC_DIR) $(GTEST_INC) -o $(BUILD_DIR)/smlr_ut.o

# Make GTest

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h

$(BUILD_DIR)/gtest-all.o : $(GTEST_SRCS_)
	@g++ -I$(GTEST_DIR) $(GTEST_INC) -c $(GTEST_DIR)/src/gtest-all.cc -o $(BUILD_DIR)/gtest-all.o

$(BUILD_DIR)/gtest_main.o : $(GTEST_SRCS_)
	@g++ -I$(GTEST_DIR) $(GTEST_INC) -c $(GTEST_DIR)/src/gtest_main.cc -o $(BUILD_DIR)/gtest_main.o

$(BUILD_DIR)/libgtest_main.a : $(BUILD_DIR)/gtest-all.o $(BUILD_DIR)/gtest_main.o
	@ar cr $@ $^
