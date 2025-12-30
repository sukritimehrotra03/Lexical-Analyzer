lexical_analyser.exe : main.o lexer.o
	gcc -o lexical_analyser.exe main.o lexer.o
main.o : main.c
	gcc -c main.c
lexer.o : lexer.c
	gcc -c lexer.c