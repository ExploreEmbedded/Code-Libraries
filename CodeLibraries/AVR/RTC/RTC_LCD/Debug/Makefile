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
../i2c.c \
../lcd.c \
../rtc.c \
../RTC_LCD.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
delay.o \
i2c.o \
lcd.o \
rtc.o \
RTC_LCD.o


OBJS_AS_ARGS +=  \
delay.o \
i2c.o \
lcd.o \
rtc.o \
RTC_LCD.o


C_DEPS +=  \
delay.d \
i2c.d \
lcd.d \
rtc.d \
RTC_LCD.d


C_DEPS_AS_ARGS +=  \
delay.d \
i2c.d \
lcd.d \
rtc.d \
RTC_LCD.d


OUTPUT_FILE_PATH +=RTC_LCD.elf

OUTPUT_FILE_PATH_AS_ARGS +=RTC_LCD.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler











./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (WinAVR 20100110) 4.3.3
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DF_CPU=16000000  -Os -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=atmega16   -o"$@" "$<" 
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
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="RTC_LCD.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group  -mmcu=atmega16  
	@echo Finished building target: $@
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "RTC_LCD.elf" "RTC_LCD.hex"
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "RTC_LCD.elf" "RTC_LCD.eep" || exit 0
	"C:\WinAVR-20100110\bin\avr-objdump.exe" -h -S "RTC_LCD.elf" > "RTC_LCD.lss"
	"C:\WinAVR-20100110\bin\avr-size.exe" "RTC_LCD.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "RTC_LCD.elf" "RTC_LCD.a" "RTC_LCD.hex" "RTC_LCD.lss" "RTC_LCD.eep" "RTC_LCD.map"
	