################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CApp.cpp \
../src/CLine.cpp \
../src/CPoint.cpp \
../src/CPolygon.cpp \
../src/CScene.cpp \
../src/CTriangle.cpp \
../src/OpenGlRenderer.cpp \
../src/Renderer.cpp \
../src/XRenderer.cpp \
../src/XSoftwareRenderer.cpp \
../src/main.cpp 

OBJS += \
./src/CApp.o \
./src/CLine.o \
./src/CPoint.o \
./src/CPolygon.o \
./src/CScene.o \
./src/CTriangle.o \
./src/OpenGlRenderer.o \
./src/Renderer.o \
./src/XRenderer.o \
./src/XSoftwareRenderer.o \
./src/main.o 

CPP_DEPS += \
./src/CApp.d \
./src/CLine.d \
./src/CPoint.d \
./src/CPolygon.d \
./src/CScene.d \
./src/CTriangle.d \
./src/OpenGlRenderer.d \
./src/Renderer.d \
./src/XRenderer.d \
./src/XSoftwareRenderer.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


