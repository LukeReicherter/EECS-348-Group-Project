CC = g++
CFLAGS = -c -Wall

AEEprogram: AEEmain.o ParserandEvaluator.o Tokenizer.o
		$(CC) AEEmain.o ParserandEvaluator.o Tokenizer.o -o AEEprogram

AEEmain.o: AEEmain.cpp
		$(CC) $(CFLAGS) AEEmain.cpp

ParserandEvaluator.p: ParserandEvaluator.cpp
		$(CC) $(CFLAGS) ParserandEvaluator.cpp

Tokenizer.o: Tokenizer.cpp
		$(CC) $(CFLAGS) Tokenizer.cpp

clean:
		rm -rf *.o AEEprogram