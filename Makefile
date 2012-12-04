TARGET = main
OBJS = main.o

CFLAGS = -I./include
LIBS = -lglut -lGLU -lGL

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

.cpp.o:
	$(CXX) -c -o $@ $< $(CFLAGS)

clean:
	$(RM) $(TARGET) $(OBJS) *~ src/*~ src/*/*~
