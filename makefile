debug ?= 0
NAME := codeCracker
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
LIB_DIR := lib
BIN_DIR := bin

# Compiler configuration
CC ?= clang
NVCC := nvcc
NVCC_HOST_COMPILER := clang++

# GPU architecture - RTX 3060 (Ampere) uses compute capability 8.6
# Adjust this for your GPU: https://developer.nvidia.com/cuda-gpus
# Using sm_80 for compatibility with CUDA driver 13.0
GPU_ARCH ?= sm_80

C_SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIB_DIR)/**/*.c)
CU_SRCS := $(wildcard $(SRC_DIR)/*.cu) $(wildcard $(LIB_DIR)/**/*.cu)
C_OBJS := $(patsubst %.c,%.o,$(C_SRCS))
CU_OBJS := $(patsubst %.cu,%.o,$(CU_SRCS))
OBJS := $(C_OBJS) $(CU_OBJS)

# C compiler flags
CFLAGS := -Wall -Wextra -g -I$(INCLUDE_DIR)

# NVCC flags
NVCCFLAGS := -I$(INCLUDE_DIR) -ccbin=$(NVCC_HOST_COMPILER) -arch=$(GPU_ARCH) -rdc=true -Xcompiler="-O3 -march=native -ffast-math"

ifeq ($(debug), 1)
	CFLAGS := $(CFLAGS) -g -O0
	NVCCFLAGS := $(NVCCFLAGS) -g -G -O0
else
	CFLAGS := $(CFLAGS) -Oz
	NVCCFLAGS := $(NVCCFLAGS) -O3
endif

# CUDA linking flags
LDFLAGS := -lcudart


# Build executable - compile all CUDA files in one command to avoid driver version issues
$(NAME): dir
	$(NVCC) $(NVCCFLAGS) -o $(BIN_DIR)/$@ $(CU_SRCS)

# Run valgrind memory checker on executable
check: $(NAME)
	@sudo valgrind -s --leak-check=full --show-leak-kinds=all $(BIN_DIR)/$< --help
	@sudo valgrind -s --leak-check=full --show-leak-kinds=all $(BIN_DIR)/$< --version
	@sudo valgrind -s --leak-check=full --show-leak-kinds=all $(BIN_DIR)/$< -v

# Setup build and bin directories
dir:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Clean build and bin directories
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
