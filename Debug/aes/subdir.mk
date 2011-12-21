################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../aes/aes_cbc.c \
../aes/aes_core.c \
../aes/aes_misc.c \
../aes/aes_ofb.c \
../aes/aes_wrap.c \
../aes/cbc128.c \
../aes/ofb128.c 

OBJS += \
./aes/aes_cbc.o \
./aes/aes_core.o \
./aes/aes_misc.o \
./aes/aes_ofb.o \
./aes/aes_wrap.o \
./aes/cbc128.o \
./aes/ofb128.o 

C_DEPS += \
./aes/aes_cbc.d \
./aes/aes_core.d \
./aes/aes_misc.d \
./aes/aes_ofb.d \
./aes/aes_wrap.d \
./aes/cbc128.d \
./aes/ofb128.d 


# Each subdirectory must supply rules for building sources it contributes
aes/%.o: ../aes/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


