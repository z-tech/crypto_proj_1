CXX=g++
RM=rm -f
CPPFLAGS=-Wall -std=c++11

SRCS=cipher_algorithms.cc cipher_crackers.cc dictionaries.cc distance_measures.cc frequency_analyzers.cc key_length_finders.cc
TSTS=frequency_analyzers_tests.cc key_length_finders_tests.cc
OBJS=$(subst .cc,.o,$(SRCS))

all: $(OBJS)
		$(CXX) $(CPPFLAGS) -o zitek-decrypt $(OBJS) key_length_finders_test.cc
test: $(OBJS)
		$(CXX) $(CPPFLAGS) -o run_tests $(OBJS) $(TSTS) run_tests.cc && ./run_tests
clean:
		$(RM) $(OBJS) ./zitek-decrypt ./tests
