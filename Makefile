CXX=g++
CXXFLAGS=-std=c++14 -stdlib=libc++
CXXFLAGS=-std=c++14
LDFLAGS=
SRCDIR=./
SOURCES=$(wildcard $(SRCDIR)/*.cpp)
OBJDIR=./build/obj/
OBJECTS=$(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
INCLUDE=
TARGET=jmemo2-parser
DEPENDS=$(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	-mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

all:clean $(TARGET)

clean:
	rm -rf $(OBJECTS) $(TARGET)

-include $(DEPENDS)
