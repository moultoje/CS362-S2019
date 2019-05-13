/*******************************************************************************
** Program: testHelpers.c
** Author: Jeffrey Moulton (moultoje@oregonstate.edu)
** Course: CS362 - Software Engineering II
** Date Modified: 5/12/2019
** Description: Helper functions for testing the Dominion cards.
*******************************************************************************/

#include "testHelpers.h"
#include <string.h>
#include <stdio.h>

void assertTrue(int expr, const char *file, int line)
{
    if (!expr)
    {
        printf("File: %s, Line: %d: Assertion failed\n", file, line);
    }
}