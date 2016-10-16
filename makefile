# All of the sources participating in the build are defined here
-include targets.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

CC = gcc
OUT_PROG = scanner

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: BinarySearchTree

# Tool invocations
BinarySearchTree: $(OBJS) $(USER_OBJS)
	@echo 'Building main program :' $(OUT_PROG)
	$(CC)  -o $(OUT_PROG) $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building main program :' $(OUT_PROG)
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) $(OUT_PROG)
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
