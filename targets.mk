# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/token.c \
/scanner.c \
/main.c 

OBJS += \
./token.o \
./scanner.o \
./main.o 

C_DEPS += \
./token.d \
./scanner.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ./%.c
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished $<'
	@echo '--------------------'


