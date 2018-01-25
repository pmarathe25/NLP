BUILDDIR = build/
BINDIR = ~/bin/
TESTDIR = test/
SRCDIR = src/
# Objects
OBJS = $(addprefix $(BUILDDIR)/, Parser.o)
TESTOBJS = $(addprefix $(BUILDDIR)/, test.o)
LIB = lib/libstealthnlp.so
# Headers
INCLUDEPATH = include/
INCLUDE = -I$(INCLUDEPATH)
HEADERS = $(addprefix $(INCLUDEPATH)/, EnglishConstants.hpp Parser.hpp)
# Compiler settings
CXX = g++
CFLAGS = -fPIC -c -std=c++17 $(INCLUDE) -flto -O3 -Wpedantic -march=native
LFLAGS = -shared -flto -O3 -march=native
TESTLFLAGS = -flto -O3 -march=native -lstealthnlp
EXECLFLAGS = -flto -O3 -march=native

$(LIB): $(OBJS)
	$(CXX) $(LFLAGS) $(OBJS) -o $(LIB)

$(TESTDIR)/test: $(TESTOBJS) $(HEADERS) $(OBJS)
	$(CXX) $(TESTOBJS) $(TESTLFLAGS) -o $(TESTDIR)/test

$(BUILDDIR)/test.o: $(TESTDIR)/test.cpp $(HEADERS)
	$(CXX) $(CFLAGS) $(TESTDIR)/test.cpp -o $(BUILDDIR)/test.o

$(BUILDDIR)/Parser.o: $(SRCDIR)/Parser.cpp include/Parser.hpp include/EnglishConstants.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Parser.cpp -o $(BUILDDIR)/Parser.o

clean:
	rm $(OBJS) $(TESTOBJS) $(TESTDIR)/test

test: $(TESTDIR)/test
	$(TESTDIR)/test

lib: $(LIB)
