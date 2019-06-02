/*******************************************************************************
** Program: testHelpers.c
** Author: Jeffrey Moulton (moultoje@oregonstate.edu)
** Course: CS362 - Software Engineering II
** Date Modified: 5/5/2019
** Description:
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