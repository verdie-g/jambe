CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17 -pedantic -fsanitize=address
LDLIBS = -lasan

VPATH = src/

OBJS = main.o route.o
BIN = jambe

all: CXXFLAGS += -O2
all: $(BIN)

debug: CXXFLAGS += -g
debug: $(BIN)

clean:
	$(RM) $(OBJS) $(BIN)

$(BIN): $(OBJS)
	$(CXX) -o $@ $^ $(LDLIBS)
