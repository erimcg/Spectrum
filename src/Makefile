LFLAGS := -o ../bin/spectrum -L /home/atp/yices-1.0.13/lib -lyices -L /home/atp/gmp-4.2.2/.libs -lgmp
CFLAGS := -Wall -g -I /home/atp/yices-1.0.13/include
 
all:	link 

link: lex.yy.o y.tab.c struct.o factor.o skolem.o specdata.o ground_lits.o unify.o instantiate.o redundancy.o var_map.o sym_tree.o tptp_parser.o SMTSolver.o maximal.o distribute.o primal_pi.o resolution.o spectrum.o main.o
	g++ ${CFLAGS} lex.yy.o y.tab.c struct.o factor.o skolem.o specdata.o ground_lits.o unify.o instantiate.o redundancy.o var_map.o sym_tree.o tptp_parser.o maximal.o distribute.o SMTSolver.o primal_pi.o resolution.o spectrum.o main.o ${LFLAGS} 

main.o:
	g++ ${CFLAGS} -c main.cpp

spectrum.o:
	g++ ${CFLAGS} -c spectrum.cpp

resolution.o:
	g++ ${CFLAGS} -c resolution.cpp

primal_pi.o:
	g++ ${CFLAGS} -c primal_pi.cpp

distribute.o:
	g++ ${CFLAGS} -c distribute.cpp

maximal.o:
	g++ ${CFLAGS} -c maximal.cpp

factor.o:
	g++ ${CFLAGS} -c factor.cpp

skolem.o:
	g++ ${CFLAGS} -c skolem.cpp

SMTSolver.o:
	g++ ${CFLAGS} -c SMTSolver.cpp

tptp_parser.o:
	g++ ${CFLAGS} -c tptp_parser.cpp

sym_tree.o:
	g++ ${CFLAGS} -c sym_tree.cpp

var_map.o:
	g++ ${CFLAGS} -c var_map.cpp

redundancy.o:
	g++ ${CFLAGS} -c redundancy.cpp

instantiate.o:
	g++ ${CFLAGS} -c instantiate.cpp

unify.o:
	g++ ${CFLAGS} -c unify.cpp

ground_lits.o:
	g++ ${CFLAGS} -c ground_lits.cpp

specdata.o:
	g++ ${CFLAGS} -c specdata.cpp 

struct.o:
	g++ ${CFLAGS} -c struct.cpp 

lex.yy.o: lex.yy.c y.tab.c
	gcc ${CFLAGS} -c lex.yy.c -o lex.yy.o

y.tab.c:
	yacc -d parser.y

lex.yy.c:
	lex lexer.l 

clean:
	rm -rf *.o lex.yy.c y.tab.*


 
