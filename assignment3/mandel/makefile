all: mandel_seq mandel_par

mandel_seq: mandel_seq.c pngwriter.c
	gcc -o $@ -I. -O3 $^ -lpng
mandel_par: mandel_par.c pngwriter.c
	gcc -o $@ -I. -O3 $^ -lpng -fopenmp

clean:
	rm -rf mandel_seq
	RM -rf mandel_par

