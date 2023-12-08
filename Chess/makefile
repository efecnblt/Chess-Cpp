all: clean compile run

compile: main.cpp chess.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -o test main.cpp chess.cpp

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	./test
	@echo "================================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o 
	@rm -f test 