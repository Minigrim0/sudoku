COMPILER_FLAGS= -std=c++17 -ggdb3 -Wpedantic -Wall -Wextra -Wold-style-cast -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant
LINKER_FLAGS=
EXECUTABLE=sudoku
CXX=g++ -ggdb

SOURCES=$(wildcard src/*.cpp)
TMP_OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS=$(TMP_OBJECTS:src/%=obj/%)

all: $(EXECUTABLE)
	@echo "=============== Done =================="

$(EXECUTABLE): main.cpp obj/cell.o obj/grid.o
	@echo "compiling : $^ -> $@"
	@$(CXX) $^ $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

obj/%.o: src/%.cpp
	@mkdir -p obj
	@echo " >> $^ -> $@"
	@$(CXX) $(COMPILER_FLAGS) -c $^ -o $@

clean:
	rm obj/*.o
	rm $(EXECUTABLE)
