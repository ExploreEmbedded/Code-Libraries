################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../delay.c \
../eeprom.c \
../EEPROM_CharRdWr_LCD.c \
../lcd.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
delay.o \
eeprom.o \
EEPROM_CharRdWr_LCD.o \
lcd.o


OBJS_AS_ARGS +=  \
delay.o \
eeprom.o \
EEPROM_CharRdWr_LCD.o \
lcd.o


C_DEPS +=  \
delay.d \
eeprom.d \
EEPROM_CharRdWr_LCD.d \
lcd.d


C_DEPS_AS_ARGS +=  \
delay.d \
eeprom.d \
EEPROM_CharRdWr_LCD.d \
lcd.d


OUTPUT_FILE_PATH +=EEPROM_CharRdWr_LCD.elf

OUTPUT_FILE_PATH_AS_ARGS +=EEPROM_CharRdWr_LCD.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler









./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (WinAVR 20100110) 4.3.3
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DF_CPU=11059200  -Os -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=atmega16   -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : (WinAVR 20100110) 4.3.3
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="EEPROM_CharRdWr_LCD.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group  -mmcu=atmega16  
	@echo Finished building target: $@
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "EEPROM_CharRdWr_LCD.elf" "EEPROM_CharRdWr_LCD.hex"
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "EEPROM_CharRdWr_LCD.elf" "EEPROM_CharRdWr_LCD.eep" || exit 0
	"C:\WinAVR-20100110\bin\avr-objdump.exe" -h -S "EEPROM_CharRdWr_LCD.elf" > "EEPROM_CharRdWr_LCD.lss"
	"C:\WinAVR-20100110\bin\avr-size.exe" "EEPROM_CharRdWr_LCD.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "EEPROM_CharRdWr_LCD.elf" "EEPROM_CharRdWr_LCD.a" "EEPROM_CharRdWr_LCD.hex" "EEPROM_CharRdWr_LCD.lss" "EEPROM_CharRdWr_LCD.eep" "EEPROM_CharRdWr_LCD.map"
	