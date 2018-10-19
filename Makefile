CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17 -pedantic

VPATH = src/ tests/

OBJS = route.o
BIN-OBJS = main.o
BIN = jambe

TEST-OBJS = unittest_jambe.o
TEST-BIN = check

bin: CXXFLAGS += -O2
bin: $(BIN)

bin-debug: CXXFLAGS += -g -fsanitize=address
bin-debug: LDLIBS = -lasan
bin-debug: $(BIN)

$(TEST-BIN): CXXFLAGS += -g -fsanitize=address -I./include -I./src
$(TEST-BIN): LDLIBS = -lasan -lgtest -lgtest_main
$(TEST-BIN): $(OBJS) $(TEST-OBJS)
	$(CXX) -o $@ $^ $(LDLIBS)
	./$@

clean:
	$(RM) $(OBJS) $(BIN-OBJS) $(BIN) $(TEST-OBJS) $(TEST-BIN)

$(BIN): $(OBJS) $(BIN-OBJS)
	$(CXX) -o $@ $^ $(LDLIBS)
