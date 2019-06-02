/*******************************************************************************
** Program: cardtest4.c
** Author: Jeffrey Moulton (moultoje@oregonstate.edu)
** Course: CS362 - Software Engineering II
** Date Modified: 5/5/2019
** Description: Unit test for the smithyEffect function from the dominion.c 
                program. This unit test is a boundary unit test that checks that
                checks how smithyEffect function deals with boundary conditions.
                The game state is initialized with 2 players. The test then
                moves all but one card from the deck to the discard pile. The 
                smithyEffect function is called (through the cardEffect) and the
                test checks to see if the player gained a net of two cards into
                their hand. The boundary being tested here is that the deck runs
                out of cards.
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
    int k[10] = {adventurer, gardens, embargo, estate, minion, gold, cutpurse,
        sea_hag, tribute, smithy};
    int seed = 1000;

    // Initialize variables needed to test the function.
    int newCards = 3;
    int discarded = 1;
    int choice1 = -1; 
    int choice2 = -1;
    int choice3 = -1;
    int handPos = 0;
    int curPlayer = 0;
    int i;

    // Initialize a game state
    initializeGame(numPlayers, k, seed, &preState);    

    printf("TESTING SMITHY CARD\n");

    // Test #1: Player gets three cards added and one card removed.
    printf("The player's deck has 1 card in it. The program should shuffle in"
        " the discarded cards into the deck.\n");
    for (i = preState.deckCount[curPlayer]; i > 1; --i)
    {
        preState.discard[curPlayer][preState.discardCount[curPlayer]] = 
            preState.deck[curPlayer][i - 1];
        preState.discardCount[curPlayer]++;
    }
    preState.deckCount[curPlayer] = 1;
    preState.whoseTurn = 0;
    preState.hand[curPlayer][handPos] = smithy;
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    cardEffect(smithy, choice1, choice2, choice3, &postState, handPos, NULL);
    printf("Checking that the player's hand increased by 2:\n");
    assertTrue(postState.handCount[curPlayer] == preState.handCount[curPlayer] +
        newCards - discarded, __FILE__, __LINE__);

    return 0;
}