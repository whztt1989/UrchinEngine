################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/loader/model/LoaderMD5Anim.cpp \
../src/loader/model/LoaderMD5Mesh.cpp 

OBJS += \
./src/loader/model/LoaderMD5Anim.o \
./src/loader/model/LoaderMD5Mesh.o 

CPP_DEPS += \
./src/loader/model/LoaderMD5Anim.d \
./src/loader/model/LoaderMD5Mesh.d 


# Each subdirectory must supply rules for building sources it contributes
src/loader/model/%.o: ../src/loader/model/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -fPIC -D_DEBUG -DGLEW_STATIC -DGL_GLEXT_PROTOTYPES -I/usr/include/freetype2 -I"/home/greg/Project/VideoGame/urchinEngine/3dEngine/src" -I"/home/greg/Project/VideoGame/urchinEngine/common/src" -I/usr/include/GL -O0 -g3 -Wall -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

