OBJECTS= ./build/mini_alloc.o ./build/mini_construct.o ./build/mini_uninitialized.o ./build/m_hashtable.o
INCLUDES= -I./
LIBS= /usr/lib/libgtest.a




test1: $(OBJECTS)
	g++ ./test/test.cpp $(OBJECTS) $(LIBS) -lpthread -g -o ./test/test -fpermissive
test2: $(ONJECTS)
	g++ ./test/test_not_POD.cpp $(OBJECTS) $(LIBS) -lpthread -g -o ./test/test -fpermissive
test3: $(OBJECTS)
	g++ ./test/test_deque.cpp $(OBJECTS) $(LIBS) -lpthread -g -o ./test/test -fpermissive
test4: $(OBJECTS)
	g++ ./test/test_rb.cpp $(OBJECTS) $(LIBS) -lpthread -g -o ./test/test -fpermissive
test5: $(OBJECTS)
	g++ ./test/test_hash.cpp $(OBJECTS) $(LIBS) -lpthread -g -o ./test/test -fpermissive
test6: $(OBJECTS)
	g++ ./test/test_hash_.cpp $(OBJECTS) $(LIBS) -lpthread -g -o ./test/test -fpermissive
test7: $(OBJECTS)
	g++ ./test/test_algo.cpp  $(LIBS) -lpthread -g -o ./test/test -fpermissive
test8: $(OBJECTS)
	g++ ./test/test_stackqueue.cpp  $(LIBS) -lpthread -g -o ./test/test -fpermissive
test9: $(OBJECTS)
	g++ ./test/test_set.cpp  $(LIBS) -lpthread -g -o ./test/test -fpermissive


./build/m_hashtable.o: ./src/hashtable/m_hashtable.cpp
	g++ ./src/hashtable/m_hashtable.cpp -o ./build/m_hashtable.o -c

./build/mini_alloc.o: ./src/mini_memory/mini_alloc.cpp
	g++ ./src/mini_memory/mini_alloc.cpp -o ./build/mini_alloc.o -c

./build/mini_construct.o: ./src/mini_memory/mini_construct.cpp
	g++ ./src/mini_memory/mini_construct.cpp -o ./build/mini_construct.o -c

./build/mini_uninitialized.o: ./src/mini_memory/mini_uninitialized.cpp
	g++ ./src/mini_memory/mini_uninitialized.cpp -o ./build/mini_uninitialized.o -c


clean:
	rm -rf $(OBJECTS)