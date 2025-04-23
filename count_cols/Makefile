IN = count_cols.c
OUT = count_cols.o
COMPILER_FLAGS = -std=c23 -Wall -Werror -Wpedantic

$(OUT): $(IN)
	@gcc-14 -o $(OUT) $(COMPILER_FLAGS) $(IN)

run: $(OUT)
	@if [ -e ./$(OUT) ]; then ./$(OUT); fi

clean:
	@if [ -e ./$(OUT) ]; then rm ./$(OUT); fi
