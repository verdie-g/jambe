CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17 -pedantic

VPATH = src/ tests/

OBJS = route.o
TEST-OBJS = unittest_jambe.o
BIN-OBJS = main.o

BIN = jambe

bin: CXXFLAGS += -O2
bin: $(BIN)

bin-debug: CXXFLAGS += -g -fsanitize=address
bin-debug: LDLIBS = -lasan
bin-debug: $(BIN)

check: CXXFLAGS += -g -fsanitize=address -I./include -I./src
check: LDLIBS = -lasan -lgtest -lgtest_main
check: $(OBJS) $(TEST-OBJS)
	$(CXX) -o $@ $^ $(LDLIBS)
	./$@

clean:
	$(RM) $(OBJS) $(BIN-OBJS) $(BIN)

$(BIN): $(OBJS) $(BIN-OBJS)
	$(CXX) -o $@ $^ $(LDLIBS)
