BUILD_DIR = build
SOURCES   = $(wildcard src/*.c)
OBJECTS   = $(patsubst src/%.c,build/%.o,$(SOURCES)) \
            $(patsubst driverlib/%.c,build/driverlib/%.o,$(wildcard driverlib/*.c))

SUPPORT_FILE_DIR = $(MSP430GCC)/include

DEVICE  = MSP430FR5969
CC      = $(MSP430GCC)/bin/msp430-elf-gcc
OBJCOPY = $(MSP430GCC)/bin/msp430-elf-objcopy
FLASHER = $(MSPFLASHER)/MSP430Flasher
MAKETXT = srec_cat

CFLAGS  = -I $(SUPPORT_FILE_DIR) -I driverlib -mmcu=$(DEVICE) -O0 -Wall -g
LDFLAGS = -L $(SUPPORT_FILE_DIR) -T $(shell echo $(DEVICE) | tr A-Z a-z).ld -Wl,-Map,$(BUILD_DIR)/$(DEVICE).map,--gc-sections 

.PHONY: clean all upload debug

all: $(BUILD_DIR)/$(DEVICE).elf $(BUILD_DIR)/$(DEVICE).txt

$(BUILD_DIR)/$(DEVICE).elf: $(OBJECTS)
	@echo "链接 $^"
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJECTS): | $(BUILD_DIR) $(BUILD_DIR)/driverlib

$(BUILD_DIR)/%.o: src/%.c
	@echo "编译 $<"
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/driverlib/%.o: driverlib/%.c
	@echo "编译 $<"
	$(CC) -c $(CFLAGS) -w $< -o $@

$(BUILD_DIR):
	@echo "创建构建目录"
	mkdir $@

$(BUILD_DIR)/driverlib: | $(BUILD_DIR)
	@echo "创建 driverlib 构建目录"
	mkdir $@

%.hex: %.elf
	@echo "生成 Intel-hex $@"
	$(OBJCOPY) -O ihex $< $@

%.txt: %.hex
	@echo "生成 TI-txt $@"
	$(MAKETXT) -O $@ -TITXT $< -I

clean:
	@echo "清理构建文件"
	rm -rf $(BUILD_DIR)

upload:
	@echo "烧写 $(BUILD_DIR)/$(DEVICE).txt 到开发版"
	LD_LIBRARY_PATH=$(MSPFLASHER) DYLD_LIBRARY_PATH=$(MSPFLASHER) $(FLASHER) \
	-w $(BUILD_DIR)/$(DEVICE).txt -v -g -z [VCC]

debug:
	@echo "开始调试"
	./scripts/debug.sh
