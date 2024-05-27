Modules = modules/process.c modules/gantt.c modules/algorithms.c

gcc = gcc

compile: main.c $(Modules)
	$(gcc) -o run main.c $(Modules)

run: compile
	./run

clean:
	rm run