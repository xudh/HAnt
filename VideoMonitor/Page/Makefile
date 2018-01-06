CROSS=
CC=$(CROSS)gcc
AR=$(CROSS)ar

INC_DIR := Include
SRC_DIR := Source
LIB_DIR := Library
LIB_TARGET := libPage.a

CFLAGS = -std=gnu99 -O2 -Wall -fno-strict-aliasing
CFLAGS += -I$(INC_DIR)

OBJS :=	$(SRC_DIR)/Page

OBJS := $(foreach obj, $(OBJS), $(obj).o)
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_TARGET): $(OBJS)
	$(AR) ruc  $(LIB_TARGET) $(OBJS)
	mv $(LIB_TARGET) $(LIB_DIR)/

clean:
	rm -f $(OBJS)
	rm -f $(LIB_DIR)/$(LIB_TARGET)

