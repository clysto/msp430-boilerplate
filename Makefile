OBJECTS=blink.o
MAP=blink.map
MAKEFILE=Makefile

ifeq ($(OS),Windows_NT)
	ifeq ($(shell uname -o),Cygwin)
		RM= rm -rf
	else
		RM= del /q
	endif
else
	RM= rm -rf
endif

GCC_DIR = $(MSPGCC)/bin
SUPPORT_FILE_DIRECTORY = $(MSPGCC)/include

DEVICE  = MSP430FR5969
CC      = $(GCC_DIR)/msp430-elf-gcc
GDB     = $(GCC_DIR)/msp430-elf-gdb
OBJCOPY = $(GCC_DIR)/msp430-elf-objcopy
FLASHER = $(MSPFLASER)/MSP430Flasher
MAKETXT = srec_cat

CFLAGS = -I $(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -mlarge -mcode-region=either -mdata-region=lower -Og -Wall -g
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY) -Wl,-Map,$(MAP),--gc-sections 

all: $(DEVICE).out $(DEVICE).txt 

$(DEVICE).out: ${OBJECTS}
	$(CC) $(CFLAGS) $(LFLAGS) $? -o $(DEVICE).out

%.hex: %.out
	$(OBJCOPY) -O ihex $< $@

%.txt: %.hex
	$(MAKETXT) -O $@ -TITXT $< -I

clean: 
	$(RM) $(OBJECTS)
	$(RM) $(MAP)
	$(RM) *.out
	$(RM) *.txt
	$(RM) *.hex

debug: all
	$(GDB) $(DEVICE).out

upload:
	LD_LIBRARY_PATH=$(MSPFLASER) DYLD_LIBRARY_PATH=$(MSPFLASER) $(FLASHER) -w $(DEVICE).txt -v -g -z [VCC]
