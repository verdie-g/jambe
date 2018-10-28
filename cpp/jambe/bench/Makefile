CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17 -pedantic
LDFLAGS = -lbenchmark -lbenchmark_main

OBJS = str_to_method.o
BIN = bench

$(BIN): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)
	sudo cpupower frequency-set --governor performance
	./$(BIN)
	sudo cpupower frequency-set --governor powersave

clean:
	$(RM) $(OBJS) $(BIN)
