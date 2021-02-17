CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall -std=c++11

SRCS=cipher_algorithms_test.cc cipher_algorithms.cc cipher_crackers.cc dictionaries.cc distance_measures.cc frequency_analyzers.cc key_length_finders.cc
OBJS=$(subst .cc,.o,$(SRCS))

all: $(OBJS)
		$(CXX) $(CPPFLAGS) -o zitek-decrypt $(OBJS)
clean:
		$(RM) $(OBJS)
