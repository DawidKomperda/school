CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
INCLUDES := -Iinclude
LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC := \
	src/main.cpp \
	src/core/Arena.cpp \
	src/entities/Character.cpp \
	src/entities/Mage.cpp \
	src/entities/Warrior.cpp \
	src/spells/SpellEffect.cpp

TARGET := main

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)