all: res.pa1-p1-sol.log res.pa1-p2-sol.log res.pa1-p3-sol.log
res.pa1-p1-sol.log: pa1-p1-sol
	./pa1-p1-sol 2>&1 | tee res.pa1-p1-sol.log
res.pa1-p2-sol.log: pa1-p2-sol
	./pa1-p2-sol 2>&1 | tee res.pa1-p2-sol.log
res.pa1-p3-sol.log: pa1-p3-sol
	./pa1-p3-sol 2>&1 | tee res.pa1-p3-sol.log
pa1-p1-sol: pa1-p1-base.c pa1-p1-sol.c pa1-p1-main.c
	gcc -O3 pa1-p1-base.c pa1-p1-sol.c pa1-p1-main.c -o pa1-p1-sol
pa1-p2-sol: pa1-p2-base.c pa1-p2-sol.c pa1-p2-main.c
	gcc -O3 pa1-p2-base.c pa1-p2-sol.c pa1-p2-main.c -o pa1-p2-sol
pa1-p3-sol: pa1-p3-base.c pa1-p3-sol.c pa1-p3-main.c
	gcc -O3 pa1-p3-base.c pa1-p3-sol.c pa1-p3-main.c -o pa1-p3-sol

clean:
	rm pa1-p1-sol pa1-p2-sol pa1-p3-sol res.pa1-p1-sol.log res.pa1-p2-sol.log res.pa1-p3-sol.log
