IN = main.c
FLAGS = -std=c17
OUT = main.o

$(OUT): $(IN)
	@clang -o $(OUT) $(FLAGS) $(IN)

run: $(OUT)
	@./$(OUT)

clean:
	@if [ -e $(OUT) ]; then rm $(OUT); else echo "Nothing to clean."; fi
