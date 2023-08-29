# Specify the compiler
CXX = g++

# Specify the compiler flags
CXXFLAGS = -std=c++17 -Iinclude -I/opt/homebrew/Cellar/sfml/2.6.0/include

# Specify the linker flags
LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system

# Specify the target file
TARGET = game

# Specify the source files
SOURCES = src/*.cpp

# Specify the object files
OBJECTS = $(patsubst src/%.cpp, res/%.o, $(wildcard $(SOURCES)))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

res/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f res/*.o $(TARGET)
