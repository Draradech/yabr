# MCU name
MCU = atmega644p


# Processor frequency
F_CPU = 20000000


# Target file name
TARGET = yabr


# C source files
SRC = environment.c init.c main.c ram.c sensor.c serial.c 


# Optimization level
OPT = s


# Debug info
DEBUG = dwarf-2


#---------------- Compiler Options ----------------
CFLAGS  = -mmcu=$(MCU)
CFLAGS += -O$(OPT)
CFLAGS += -g$(DEBUG)
CFLAGS += -funsigned-char
CFLAGS += -funsigned-bitfields
CFLAGS += -fpack-struct
CFLAGS += -fshort-enums
CFLAGS += -ffreestanding
CFLAGS += -combine
CFLAGS += -fwhole-program
CFLAGS += -Wall
CFLAGS += -Winline
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wsign-compare
CFLAGS += -std=gnu99
CFLAGS += -DF_CPU=$(F_CPU)UL
# bug in avr-libc 1.7.0, so do not use builtin delay cycles
CFLAGS += -D__HAS_DELAY_CYCLES=0
CFLAGS += -I.


#---------------- Linker Options ----------------
LDFLAGS  = -Wl,--relax
LDFLAGS += -lm


#---------------- Programming Options (avrdude) ----------------
# Programming hardware
AVRDUDE_PROGRAMMER = avr109

# Programming port
AVRDUDE_PORT = COM3

# Programming command
AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep

AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)


#============================================================================
# Define programs and commands.
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
AVRDUDE = avrdude
REMOVE = rm -f


# Define Messages
# English
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_COMPILING_LINKING = Compiling and Linking:
MSG_CLEANING = Cleaning project:
MSG_PROGRAM_FLASH = Programming target flash:
MSG_PROGRAM_EEPROM = Programming target eeprom:

# Default target.
all: build size

build: elf hex eep lss

elf: $(TARGET).elf
hex: $(TARGET).hex
eep: $(TARGET).eep
lss: $(TARGET).lss 


# Display size of file.
ELFSIZE = $(SIZE) --format=avr --mcu=$(MCU) $(TARGET).elf

size:
	@if test -f $(TARGET).elf; then echo; echo; $(ELFSIZE); \
	2>/dev/null; echo; fi


# Program the device  
program: $(TARGET).hex
	@echo
	@echo $(MSG_PROGRAM_FLASH)
	launcher.cs -p $(AVRDUDE_PORT)
	sleep 1
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)
	sleep 1
	launcher.cs -p $(AVRDUDE_PORT) -d


# Program the eeprom
program_eeprom: $(TARGET).eep
	@echo
	@echo $(MSG_PROGRAM_EEPROM)
	launcher.cs -p $(AVRDUDE_PORT)
	sleep 1
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_EEPROM)
	sleep 1
	launcher.cs -p $(AVRDUDE_PORT) -d


# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O ihex -R .eeprom $< $@

%.eep: %.elf
	@echo
	@echo $(MSG_EEPROM) $@
	-$(OBJCOPY) -j .eeprom --set-section-flags .eeprom=alloc,load \
	--change-section-lma .eeprom=0 -O ihex $< $@


# Create extended listing file from ELF output file.
%.lss: %.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S $< > $@


# Link: create ELF output file from object files.
%.elf: $(SRC)
	@echo
	@echo $(MSG_COMPILING_LINKING) $@
	$(CC) $(CFLAGS) $(LDFLAGS) $^ --output $@


# Target: clean project.
clean: begin clean_list end

clean_list :
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).eep
	$(REMOVE) $(TARGET).lss

# Listing of phony targets.
.PHONY : $(SRC) \
all begin end sizebefore sizeafter gccversion \
build elf hex eep lss \
clean clean_list program program_eeprom
