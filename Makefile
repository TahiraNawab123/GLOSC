# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Output executable
TARGET = project

# Source files
SRCS = \
main.cpp \
Common/linkedList.cpp \
Common/smartArray.cpp \
WarehouseManagement/*.cpp \
FleetManagement/*.cpp \
OrderManagement/*.cpp \
ShipmentTracking/*.cpp

# Default target
all: $(TARGET)

# Build target
$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean build files
clean:
	rm -f $(TARGET)

# Run program
run: all
	./$(TARGET)
