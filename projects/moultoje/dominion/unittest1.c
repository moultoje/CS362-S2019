/*******************************************************************************
** Program: unittest1.c
** Author: Jeffrey Moulton (moultoje@oregonstate.edu)
** Course: CS362 - Software Engineering II
** Date Modified: 5/5/2019
** Description: Unit test for the smithyEffect function from the dominion.c 
                program. This unit test is a positive unit test that checks that
                the smithyEffect function works like it should. The game state
                is initialized with 2 players and the smithyEffect function is 
                called. The test then checks that the current player's hand is 
                increased by two cards, their deck is decreased by three cards, 
                and their discard is increased by one card.
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelpers.h"
#include <string.h>
#include <stdio.h>

int main()
{
    // Initialize variables needed for the game.
    struct gameState preState, postState;
    int numPlayers = 2;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    int seed = 1000;

    // Initialize variables needed to test the function.
    int newCards = 3;
    int discarded = 1;
    int handPos = 0;
    int curPlayer = 0;

    // Initialize a game state
    initializeGame(numPlayers, k, seed, &preState);

    // Copy the game state
    memcpy(&postState, &preState, sizeof(struct gameState));

    printf("TESTING SMITHY CARD\n");
    smithyEffect(&postState, curPlayer, handPos);

    // Test #1: Ensure that three cards have been added to the player's hand and
    // one has been discarded.
    printf("Test 1: The current player's hand size should increase by two cards"
        " (draw 2 cards discard 1).\n");
    printf("Checking that the player's hand increased by 2:\n");
    assertTrue(postState.handCount[curPlayer] == preState.handCount[curPlayer] +
        newCards - discarded, __FILE__, __LINE__);

    // Test #2: Ensure that three cards have been removed from the player's deck.
    printf("Test 2: The current player's deck size should decrease by three"
        " cards.\n");
    printf("Checking that the player's deck decreased by 3:\n");
    assertTrue(postState.deckCount[curPlayer] == preState.handCount[curPlayer] -
        newCards, __FILE__, __LINE__);

    // Test #3: Ensure that one card has been added to the player's discards.
    printf("Test 3: The current player's discard size should increase by one"
        " card.\n");
    printf("Checking that the player's discard increased by one:\n");
    assertTrue(postState.discardCount[curPlayer] == preState.discardCount[curPlayer]
        + discarded, __FILE__, __LINE__);

    return 0;
}