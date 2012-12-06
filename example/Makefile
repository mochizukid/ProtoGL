TARGET = main
OBJS = main.o

CFLAGS = -I../include -Wall
LIBS = -lglut -lGLU -lGL

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

.cpp.o:
	$(CXX) -c -o $@ $< $(CFLAGS)

clean:
	$(RM) $(TARGET) $(OBJS) *~ ../include/*~ ../include/*/*~
