################################################################################
## Program Name: Makefile
## Author: Jeffrey Moulton (moultoje@oregonstate.edu)
## Class: CS362 - Software Engineering 2
## Date Modified: 12 May 2019
## Description:
################################################################################

CFLAGS = -Wall -fpic -coverage -std=c99

.DEFAULT_GOAL := runtests

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

runtests: testme
	echo "Running tests on testme.c."
	echo "Starting testme with a timeout of 5 minutes."
	-timeout 300 ./testme
	echo -e "\nGenerating GCOV data."
	gcov -fb testme.c

clean:
	rm -f testme *.gcov *.gcda *.gcno