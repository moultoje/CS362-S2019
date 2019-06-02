/*******************************************************************************
** Program: cardtest1.c
** Author: Jeffrey Moulton (moultoje@oregonstate.edu)
** Course: CS362 - Software Engineering II
** Date Modified: 5/5/2019
** Description: Unit test for the adventurerEffect function from the dominion.c 
                program. This unit test is a positive unit test that checks that
                the adventurerEffect function works like it should. The game
                state is initialized with 2 players. The test checks that the 
                player gains two cards from playing an andventurer card.
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
    int gainedCard = 2;
    int choice1 = -1; 
    int choice2 = -1;
    int choice3 = -1;
    int handPos = 0;
    int curPlayer = 0;

    // Initialize a game state
    initializeGame(numPlayers, k, seed, &preState);    

    printf("TESTING ADVENTURER CARD\n");

    // Test #1: Gain 2 cards.
    printf("Gain 2 cards. The player should gain 2 cards from playing the"
        " adventurer card.\n");
    preState.whoseTurn = 0;
    preState.hand[curPlayer][handPos] = adventurer;
    preState.deck[curPlayer][preState.deckCount[curPlayer] - 1] = minion;
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    cardEffect(adventurer, choice1, choice2, choice3, &postState, handPos, NULL);
    printf("Checking that the player's hand increased by two:\n");
    assertTrue(postState.handCount[curPlayer] == preState.handCount[curPlayer] +
        gainedCard, __FILE__, __LINE__);

    return 0;
}