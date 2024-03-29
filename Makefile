CXX=g++
RM=rm -f
CPPFLAGS=-Wall -std=c++17 -pthread -O3

SRCS=cipher_algorithms.cc cipher_crackers.cc dictionaries.cc distance_measures.cc frequency_analyzers.cc key_length_finders.cc
TSTS=./__TESTS__/cipher_algorithms_tests.cc ./__TESTS__/cipher_crackers_tests.cc ./__TESTS__/distance_measures_tests.cc ./__TESTS__/frequency_analyzers_tests.cc ./__TESTS__/key_length_finders_tests.cc
OBJS=$(subst .cc,.o,$(SRCS))

all: $(OBJS)
		$(CXX) $(CPPFLAGS) -o maharjan-roberts-zitek-decrypt $(OBJS) maharjan-roberts-zitek-decrypt-source.cc
test: $(OBJS)
		$(CXX) $(CPPFLAGS) -o ./run_tests.exe $(OBJS) $(TSTS) ./__TESTS__/run_tests.cc && time ./run_tests.exe
clean:
		$(RM) $(OBJS) ./maharjan-roberts-zitek-decrypt ./run_tests.exe
