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
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../src/ \
../src/ASF/ \
../src/ASF/common/ \
../src/ASF/common/boards/ \
../src/ASF/common/boards/user_board/ \
../src/ASF/common/utils/ \
../src/ASF/common/utils/interrupt/ \
../src/ASF/sam/ \
../src/ASF/sam/utils/ \
../src/ASF/sam/utils/cmsis/ \
../src/ASF/sam/utils/cmsis/sam3s/ \
../src/ASF/sam/utils/cmsis/sam3s/include/ \
../src/ASF/sam/utils/cmsis/sam3s/include/component/ \
../src/ASF/sam/utils/cmsis/sam3s/include/instance/ \
../src/ASF/sam/utils/cmsis/sam3s/include/pio/ \
../src/ASF/sam/utils/cmsis/sam3s/source/ \
../src/ASF/sam/utils/cmsis/sam3s/source/templates/ \
../src/ASF/sam/utils/cmsis/sam3s/source/templates/gcc/ \
../src/ASF/sam/utils/header_files/ \
../src/ASF/sam/utils/linker_scripts/ \
../src/ASF/sam/utils/linker_scripts/sam3s/ \
../src/ASF/sam/utils/linker_scripts/sam3s/sam3s4/ \
../src/ASF/sam/utils/linker_scripts/sam3s/sam3s4/gcc/ \
../src/ASF/sam/utils/make/ \
../src/ASF/sam/utils/preprocessor/ \
../src/ASF/sam/utils/syscalls/ \
../src/ASF/sam/utils/syscalls/gcc/ \
../src/ASF/thirdparty/ \
../src/ASF/thirdparty/CMSIS/ \
../src/ASF/thirdparty/CMSIS/Include/ \
../src/ASF/thirdparty/CMSIS/Lib/ \
../src/ASF/thirdparty/CMSIS/Lib/GCC/ \
../src/config/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../src/ASF/common/boards/user_board/init.c \
../src/ASF/common/utils/interrupt/interrupt_sam_nvic.c \
../src/ASF/sam/utils/cmsis/sam3s/source/templates/exceptions.c \
../src/ASF/sam/utils/cmsis/sam3s/source/templates/gcc/startup_sam3s.c \
../src/ASF/sam/utils/cmsis/sam3s/source/templates/system_sam3s.c \
../src/ASF/sam/utils/syscalls/gcc/syscalls.c \
../src/main.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
src/ASF/common/boards/user_board/init.o \
src/ASF/common/utils/interrupt/interrupt_sam_nvic.o \
src/ASF/sam/utils/cmsis/sam3s/source/templates/exceptions.o \
src/ASF/sam/utils/cmsis/sam3s/source/templates/gcc/startup_sam3s.o \
src/ASF/sam/utils/cmsis/sam3s/source/templates/system_sam3s.o \
src/ASF/sam/utils/syscalls/gcc/syscalls.o \
src/main.o

OBJS_AS_ARGS +=  \
src/ASF/common/boards/user_board/init.o \
src/ASF/common/utils/interrupt/interrupt_sam_nvic.o \
src/ASF/sam/utils/cmsis/sam3s/source/templates/exceptions.o \
src/ASF/sam/utils/cmsis/sam3s/source/templates/gcc/startup_sam3s.o \
src/ASF/sam/utils/cmsis/sam3s/source/templates/system_sam3s.o \
src/ASF/sam/utils/syscalls/gcc/syscalls.o \
src/main.o

C_DEPS +=  \
src/ASF/common/boards/user_board/init.d \
src/ASF/common/utils/interrupt/interrupt_sam_nvic.d \
src/ASF/sam/utils/cmsis/sam3s/source/templates/exceptions.d \
src/ASF/sam/utils/cmsis/sam3s/source/templates/gcc/startup_sam3s.d \
src/ASF/sam/utils/cmsis/sam3s/source/templates/system_sam3s.d \
src/ASF/sam/utils/syscalls/gcc/syscalls.d \
src/main.d

C_DEPS_AS_ARGS +=  \
src/ASF/common/boards/user_board/init.d \
src/ASF/common/utils/interrupt/interrupt_sam_nvic.d \
src/ASF/sam/utils/cmsis/sam3s/source/templates/exceptions.d \
src/ASF/sam/utils/cmsis/sam3s/source/templates/gcc/startup_sam3s.d \
src/ASF/sam/utils/cmsis/sam3s/source/templates/system_sam3s.d \
src/ASF/sam/utils/syscalls/gcc/syscalls.d \
src/main.d

OUTPUT_FILE_PATH +=sam_backend_newheader.elf

OUTPUT_FILE_PATH_AS_ARGS +=sam_backend_newheader.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+=  \
../src/ASF/sam/utils/linker_scripts/sam3s/sam3s4/gcc/flash.ld


# AVR32/GNU C Compiler
src/ASF/common/boards/user_board/init.o: ../src/ASF/common/boards/user_board/init.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAM3S4B__ -DDEBUG -Dscanf=iscanf -DBOARD=USER_BOARD -DARM_MATH_CM3=true -Dprintf=iprintf  -I"../src/ASF/common/boards" -I"../src/ASF/sam/utils" -I"../src/ASF/sam/utils/header_files" -I"../src/ASF/sam/utils/preprocessor" -I"../src/ASF/thirdparty/CMSIS/Include" -I"../src/ASF/thirdparty/CMSIS/Lib/GCC" -I"../src/ASF/common/utils" -I"../src/ASF/sam/utils/cmsis/sam3s/source/templates" -I"../src/ASF/sam/utils/cmsis/sam3s/include" -I"../src/ASF/common/boards/user_board" -I"../src" -I"../src/config"  -O1 -fdata-sections -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m3 -c -pipe -fno-strict-aliasing -Wall -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -std=gnu99 -ffunction-sections -fdata-sections -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int -Wmain -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef -Wshadow -Wbad-function-cast -Wwrite-strings -Wsign-compare -Waggregate-return  -Wmissing-declarations -Wformat -Wmissing-format-attribute -Wno-deprecated-declarations -Wpacked -Wredundant-decls -Wnested-externs -Wlong-long -Wunreachable-code -Wcast-align --param max-inline-insns-single=500 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/common/utils/interrupt/interrupt_sam_nvic.o: ../src/ASF/common/utils/interrupt/interrupt_sam_nvic.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAM3S4B__ -DDEBUG -Dscanf=iscanf -DBOARD=USER_BOARD -DARM_MATH_CM3=true -Dprintf=iprintf  -I"../src/ASF/common/boards" -I"../src/ASF/sam/utils" -I"../src/ASF/sam/utils/header_files" -I"../src/ASF/sam/utils/preprocessor" -I"../src/ASF/thirdparty/CMSIS/Include" -I"../src/ASF/thirdparty/CMSIS/Lib/GCC" -I"../src/ASF/common/utils" -I"../src/ASF/sam/utils/cmsis/sam3s/source/templates" -I"../src/ASF/sam/utils/cmsis/sam3s/include" -I"../src/ASF/common/boards/user_board" -I"../src" -I"../src/config"  -O1 -fdata-sections -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m3 -c -pipe -fno-strict-aliasing -Wall -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -std=gnu99 -ffunction-sections -fdata-sections -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int -Wmain -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef -Wshadow -Wbad-function-cast -Wwrite-strings -Wsign-compare -Waggregate-return  -Wmissing-declarations -Wformat -Wmissing-format-attribute -Wno-deprecated-declarations -Wpacked -Wredundant-decls -Wnested-externs -Wlong-long -Wunreachable-code -Wcast-align --param max-inline-insns-single=500 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/sam/utils/cmsis/sam3s/source/templates/exceptions.o: ../src/ASF/sam/utils/cmsis/sam3s/source/templates/exceptions.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAM3S4B__ -DDEBUG -Dscanf=iscanf -DBOARD=USER_BOARD -DARM_MATH_CM3=true -Dprintf=iprintf  -I"../src/ASF/common/boards" -I"../src/ASF/sam/utils" -I"../src/ASF/sam/utils/header_files" -I"../src/ASF/sam/utils/preprocessor" -I"../src/ASF/thirdparty/CMSIS/Include" -I"../src/ASF/thirdparty/CMSIS/Lib/GCC" -I"../src/ASF/common/utils" -I"../src/ASF/sam/utils/cmsis/sam3s/source/templates" -I"../src/ASF/sam/utils/cmsis/sam3s/include" -I"../src/ASF/common/boards/user_board" -I"../src" -I"../src/config"  -O1 -fdata-sections -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m3 -c -pipe -fno-strict-aliasing -Wall -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -std=gnu99 -ffunction-sections -fdata-sections -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int -Wmain -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef -Wshadow -Wbad-function-cast -Wwrite-strings -Wsign-compare -Waggregate-return  -Wmissing-declarations -Wformat -Wmissing-format-attribute -Wno-deprecated-declarations -Wpacked -Wredundant-decls -Wnested-externs -Wlong-long -Wunreachable-code -Wcast-align --param max-inline-insns-single=500 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/sam/utils/cmsis/sam3s/source/templates/gcc/startup_sam3s.o: ../src/ASF/sam/utils/cmsis/sam3s/source/templates/gcc/startup_sam3s.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAM3S4B__ -DDEBUG -Dscanf=iscanf -DBOARD=USER_BOARD -DARM_MATH_CM3=true -Dprintf=iprintf  -I"../src/ASF/common/boards" -I"../src/ASF/sam/utils" -I"../src/ASF/sam/utils/header_files" -I"../src/ASF/sam/utils/preprocessor" -I"../src/ASF/thirdparty/CMSIS/Include" -I"../src/ASF/thirdparty/CMSIS/Lib/GCC" -I"../src/ASF/common/utils" -I"../src/ASF/sam/utils/cmsis/sam3s/source/templates" -I"../src/ASF/sam/utils/cmsis/sam3s/include" -I"../src/ASF/common/boards/user_board" -I"../src" -I"../src/config"  -O1 -fdata-sections -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m3 -c -pipe -fno-strict-aliasing -Wall -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -std=gnu99 -ffunction-sections -fdata-sections -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int -Wmain -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef -Wshadow -Wbad-function-cast -Wwrite-strings -Wsign-compare -Waggregate-return  -Wmissing-declarations -Wformat -Wmissing-format-attribute -Wno-deprecated-declarations -Wpacked -Wredundant-decls -Wnested-externs -Wlong-long -Wunreachable-code -Wcast-align --param max-inline-insns-single=500 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/sam/utils/cmsis/sam3s/source/templates/system_sam3s.o: ../src/ASF/sam/utils/cmsis/sam3s/source/templates/system_sam3s.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAM3S4B__ -DDEBUG -Dscanf=iscanf -DBOARD=USER_BOARD -DARM_MATH_CM3=true -Dprintf=iprintf  -I"../src/ASF/common/boards" -I"../src/ASF/sam/utils" -I"../src/ASF/sam/utils/header_files" -I"../src/ASF/sam/utils/preprocessor" -I"../src/ASF/thirdparty/CMSIS/Include" -I"../src/ASF/thirdparty/CMSIS/Lib/GCC" -I"../src/ASF/common/utils" -I"../src/ASF/sam/utils/cmsis/sam3s/source/templates" -I"../src/ASF/sam/utils/cmsis/sam3s/include" -I"../src/ASF/common/boards/user_board" -I"../src" -I"../src/config"  -O1 -fdata-sections -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m3 -c -pipe -fno-strict-aliasing -Wall -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -std=gnu99 -ffunction-sections -fdata-sections -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int -Wmain -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef -Wshadow -Wbad-function-cast -Wwrite-strings -Wsign-compare -Waggregate-return  -Wmissing-declarations -Wformat -Wmissing-format-attribute -Wno-deprecated-declarations -Wpacked -Wredundant-decls -Wnested-externs -Wlong-long -Wunreachable-code -Wcast-align --param max-inline-insns-single=500 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/sam/utils/syscalls/gcc/syscalls.o: ../src/ASF/sam/utils/syscalls/gcc/syscalls.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAM3S4B__ -DDEBUG -Dscanf=iscanf -DBOARD=USER_BOARD -DARM_MATH_CM3=true -Dprintf=iprintf  -I"../src/ASF/common/boards" -I"../src/ASF/sam/utils" -I"../src/ASF/sam/utils/header_files" -I"../src/ASF/sam/utils/preprocessor" -I"../src/ASF/thirdparty/CMSIS/Include" -I"../src/ASF/thirdparty/CMSIS/Lib/GCC" -I"../src/ASF/common/utils" -I"../src/ASF/sam/utils/cmsis/sam3s/source/templates" -I"../src/ASF/sam/utils/cmsis/sam3s/include" -I"../src/ASF/common/boards/user_board" -I"../src" -I"../src/config"  -O1 -fdata-sections -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m3 -c -pipe -fno-strict-aliasing -Wall -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -std=gnu99 -ffunction-sections -fdata-sections -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int -Wmain -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef -Wshadow -Wbad-function-cast -Wwrite-strings -Wsign-compare -Waggregate-return  -Wmissing-declarations -Wformat -Wmissing-format-attribute -Wno-deprecated-declarations -Wpacked -Wredundant-decls -Wnested-externs -Wlong-long -Wunreachable-code -Wcast-align --param max-inline-insns-single=500 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/main.o: ../src/main.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAM3S4B__ -DDEBUG -Dscanf=iscanf -DBOARD=USER_BOARD -DARM_MATH_CM3=true -Dprintf=iprintf  -I"../src/ASF/common/boards" -I"../src/ASF/sam/utils" -I"../src/ASF/sam/utils/header_files" -I"../src/ASF/sam/utils/preprocessor" -I"../src/ASF/thirdparty/CMSIS/Include" -I"../src/ASF/thirdparty/CMSIS/Lib/GCC" -I"../src/ASF/common/utils" -I"../src/ASF/sam/utils/cmsis/sam3s/source/templates" -I"../src/ASF/sam/utils/cmsis/sam3s/include" -I"../src/ASF/common/boards/user_board" -I"../src" -I"../src/config"  -O1 -fdata-sections -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m3 -c -pipe -fno-strict-aliasing -Wall -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -std=gnu99 -ffunction-sections -fdata-sections -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int -Wmain -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef -Wshadow -Wbad-function-cast -Wwrite-strings -Wsign-compare -Waggregate-return  -Wmissing-declarations -Wformat -Wmissing-format-attribute -Wno-deprecated-declarations -Wpacked -Wredundant-decls -Wnested-externs -Wlong-long -Wunreachable-code -Wcast-align --param max-inline-insns-single=500 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
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

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: ARM/GNU Linker : 6.3.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -mthumb -Wl,-Map="sam_backend_newheader.map" -Wl,--start-group -larm_cortexM3l_math -lm  -Wl,--end-group -L"../src/ASF/thirdparty/CMSIS/Lib/GCC"  -Wl,--gc-sections -mcpu=cortex-m3 -Wl,--entry=Reset_Handler -Wl,--cref -mthumb -T../src/ASF/sam/utils/linker_scripts/sam3s/sam3s4/gcc/flash.ld  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O binary "sam_backend_newheader.elf" "sam_backend_newheader.bin"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "sam_backend_newheader.elf" "sam_backend_newheader.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O binary "sam_backend_newheader.elf" "sam_backend_newheader.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objdump.exe" -h -S "sam_backend_newheader.elf" > "sam_backend_newheader.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "sam_backend_newheader.elf" "sam_backend_newheader.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-size.exe" "sam_backend_newheader.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "sam_backend_newheader.elf" "sam_backend_newheader.a" "sam_backend_newheader.hex" "sam_backend_newheader.bin" "sam_backend_newheader.lss" "sam_backend_newheader.eep" "sam_backend_newheader.map" "sam_backend_newheader.srec"
	