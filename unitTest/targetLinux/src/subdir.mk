################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AssertHelper.cpp \
../src/MainTest.cpp 

OBJS += \
./src/AssertHelper.o \
./src/MainTest.o 

CPP_DEPS += \
./src/AssertHelper.d \
./src/MainTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -fPIC -D_DEBUG -I"/home/greg/Project/VideoGame/urchinEngine/physicsEngine/src" -I"/home/greg/Project/VideoGame/urchinEngine/common/src" -I"/home/greg/Project/VideoGame/urchinEngine/unitTest/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

