IN = main.c
DEPS = *.c
FLAGS = -std=c17
OUT = main.o

$(OUT): $(IN) $(DEPS)
	@clang -o $(OUT) $(FLAGS) $(IN)

run: $(OUT)
	@./$(OUT)

clean:
	@if [ -e $(OUT) ]; then rm $(OUT); else echo "Nothing to clean."; fi
