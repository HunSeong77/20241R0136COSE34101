Modules = modules/process.c modules/gantt.c modules/algorithms.c

gcc = gcc

compile: main.c $(Modules)
	$(gcc) -o run main.c $(Modules)

run: compile
	# clear & ./run
	./run

clean:
	rm run