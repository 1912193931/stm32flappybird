#list of source files
#SOURCES = main.c
SOURCES += ./*.c   
#SOURCES += ./CORE/core_cm3.c
SOURCES += ./HARDWARE/*.c
SOURCES += ./STM32F10x_FWLib/src/*.c
SOURCES += ./SYSTEM/*.c
SOURCES += ./CORE/startup_stm32f10x_hd.s

# name for output binaary files
PROJECT ?= bird

# compiler, objcopy (should be in PATH)
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# specify compiler flags
CFLAGS  = -g -O2 -Wall
CFLAGS += -T ./stm32_flash.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m3 -mthumb-interwork

#CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 -specs=nano.specs -specs=nosys.specs
CFLAGS += -mfloat-abi=soft -specs=nano.specs -specs=nosys.specs
CFLAGS += -D STM32F10X_HD -D USE_STDPERIPH_DRIVER
CFLAGS += -Wl,--gc-sections
CFLAGS += -I.
CFLAGS += -I./CORE
CFLAGS += -I./HARDWARE
CFLAGS += -I./STM32F10x_FWLib/inc
CFLAGS += -I./SYSTEM

OBJS = $(SOURCES:.c=.o)

all: $(PROJECT).elf

# compile
$(PROJECT).elf: $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJECT).elf $(PROJECT).hex
	$(OBJCOPY) -O binary $(PROJECT).elf $(PROJECT).bin

# remove binary files
clean:
	rm -f *.o *.elf *.hex *.bin


