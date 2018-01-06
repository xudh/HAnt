CROSS=
CC=$(CROSS)gcc
AR=$(CROSS)ar
STRIP=$(CROSS)strip

INC_DIR := Include ../Include ../Function/Include ../Page/Include
SRC_DIR := Source
BIN_DIR := Bin
BIN_TARGET := VideoMonitor.out

CFLAGS = -std=gnu99 -O2 -Wall -fno-strict-aliasing
LDFLAGS = -lFunction -lConfig -lPage -lpthread
#LDFLAGS += -lTextConfig -lNet
LIB_PATH = ../Library
CFLAGS += $(foreach dir,$(INC_DIR),-I$(dir))
LDFLAGS += $(foreach lib,$(LIB_PATH),-L$(lib))
OBJS :=	$(SRC_DIR)/VideoMonitor	\
		$(SRC_DIR)/Console

OBJS := $(foreach obj, $(OBJS), $(obj).o)
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_TARGET): $(OBJS)
	$(CC) -o $(BIN_TARGET) $(OBJS) $(LDFLAGS)
	$(STRIP) $(BIN_TARGET)
	mv $(BIN_TARGET) $(BIN_DIR)/

clean:
	rm -f $(OBJS)
	rm -f $(BIN_DIR)/$(BIN_TARGET)

