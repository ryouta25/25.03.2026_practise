CXXFLAGS += -Wall -Wextra -Weffc++ -std=c++14 _MMD

UNIT_TESTS = pe-vector-tests
OBJS = main.o
DEPS = main.d

$(UNIT_TESTS): $(OBJS)
	$(CXX) -o $@ $^

clean:
	$(RM) $(UNIT_TESTS) $(OBJS) $(DEPS)

-include main.d
