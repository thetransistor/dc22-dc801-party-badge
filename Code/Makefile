PROJECT=template

LDCRIPT=core/lpc1347.ld

OPTIMIZATION = 1

#########################################################################

SRC=$(wildcard core/*.c)  $(wildcard core/libs/*.c) drivers/vfd.c drivers/armmath.c drivers/ssp1.c $(wildcard *.c)


OBJECTS= $(SRC:.c=.o) 
LSSFILES= $(SRC:.c=.lst) 
HEADERS=$(wildcard core/*.h) $(wildcard core/inc/*.h) drivers/armmath.h drivers/vfd.h $(wildcard *.h)

#  Compiler Options
GCFLAGS = -std=gnu99 -mcpu=cortex-m3 -mthumb -O$(OPTIMIZATION) -I. -Icore -Icore/inc
# Warnings
#GCFLAGS += -Wstrict-prototypes -Wundef -Wall -Wunreachable-code  
# Optimizazions
#GCFLAGS += -fsingle-precision-constant -funsigned-char -funsigned-bitfields -fshort-enums

# Debug stuff
#GCFLAGS += -Wa,-adhlns=$(<:.c=.lst),-gstabs -g 

LDFLAGS =  -mcpu=cortex-m3 -mthumb -O$(OPTIMIZATION) -nostartfiles  -T$(LDCRIPT) 


#  Compiler/Linker Paths
GCC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
REMOVE = rm -f
SIZE = arm-none-eabi-size

#########################################################################

all: tools firmware.bin Makefile stats

tools:
	make -C tools
	
firmware.bin: $(PROJECT).elf Makefile
	$(OBJCOPY) -R .stack -O binary $(PROJECT).elf firmware.bin
	tools/lpcrc firmware.bin
	tools/padto firmware.bin 64
	
$(PROJECT).elf: $(OBJECTS) Makefile
	@echo "  \033[1;34mLD \033[0m (\033[1;33m $(OBJECTS)\033[0m) -> $(PROJECT).elf"
	@$(GCC) $(LDFLAGS) $(OBJECTS) -o $(PROJECT).elf -lm
	arm-none-eabi-strip -s $(PROJECT).elf

stats: $(PROJECT).elf Makefile
	$(SIZE) $(PROJECT).elf

clean:
	$(REMOVE) $(OBJECTS)
	$(REMOVE) $(LSSFILES)
	$(REMOVE) firmware.bin
	$(REMOVE) $(PROJECT).elf
	$(REMOVE) $(PROJECT).map
	make -C tools clean

#########################################################################

%.o: %.c Makefile $(HEADERS)
	@echo "  \033[1;34mGCC\033[0m $<"
	@$(GCC) $(GCFLAGS) -o $@ -c $<

#########################################################################

flash: firmware.bin
	cp firmware.bin /Volumes/CRP\ DISABLD/
	diskutil eject `diskutil list | grep -B 2 CRP | grep dev`


.PHONY : clean all flash tools

