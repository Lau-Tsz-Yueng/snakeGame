# Specify the compiler
CXX = g++

# Specify the compiler flags
CXXFLAGS = -std=c++17 -Iinclude -I/opt/homebrew/Cellar/sfml/2.6.0/include

# Specify the linker flags
LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system

# Specify the target file
TARGET = game

# Specify the source files
SOURCES = src/main.cpp src/Wall.cpp src/Food.cpp

# Specify the object files
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
