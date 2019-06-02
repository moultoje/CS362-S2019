/*******************************************************************************
** Program: cardtest2.c
** Author: Jeffrey Moulton (moultoje@oregonstate.edu)
** Course: CS362 - Software Engineering II
** Date Modified: 5/5/2019
** Description: Unit test for the embargo case of the cardEffect function from
                the dominion.c program. This unit test is a positive unit test
                that checks that the embargo card works like it should. The game
                state is initialized with 2 players. The first test has the 
                player choose a card that is in play for the game. The test 
                checks that the user gains 2 coins, an embargo token is added
                to the pile, and the player's hand is decreased by one. The 
                second test has the player choose a card that is not in play for
                the game. The test checks that the user gains 2 coins, but the 
                pile does not get an embargo coin nor does the player's hand 
                decrease.
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
    int xtraCoins = 2;
    int discard = 1;
    int choice1 = minion; 
    int choice2 = -1;
    int choice3 = -1;
    int handPos = 0;
    int curPlayer = 0;

    // Initialize a game state
    initializeGame(numPlayers, k, seed, &preState);    

    printf("TESTING EMBARGO CARD\n");

    // Test #1: Player chooses pile in play.
    printf("Test #1: Player chooses pile in play. The player gains two coins"
        " and adds an embargo token to that pile.\n");
    preState.whoseTurn = 0;
    preState.hand[curPlayer][handPos] = embargo;
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    cardEffect(embargo, choice1, choice2, choice3, &postState, handPos, NULL);
    printf("Checking that the player's coins increased by two:\n");
    assertTrue(postState.coins == preState.coins + xtraCoins, __FILE__, 
        __LINE__);
    printf("Checking that the choice1 embargo tokens increased:\n");
    assertTrue(postState.embargoTokens[choice1] == 
        preState.embargoTokens[choice1] + 1, __FILE__, __LINE__);
    printf("Checking that the player's hand decreased by one:\n");
    assertTrue(postState.handCount[curPlayer] == preState.handCount[curPlayer] -
        discard, __FILE__, __LINE__);

    // Test #2. Player chooses pile not in play.
    printf("Test #2: Player chooses pile not in play. The player gains two" 
        " coins.\n");
    preState.whoseTurn = 0;
    preState.hand[curPlayer][handPos] = embargo;
    choice1 = outpost;
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    cardEffect(embargo, choice1, choice2, choice3, &postState, handPos, NULL);
    printf("Checking that the player's coins increased by two:\n");
    assertTrue(postState.coins == preState.coins + xtraCoins, __FILE__, 
        __LINE__);
    printf("Checking that the choice1 embargo tokens did not change:\n");
    assertTrue(postState.embargoTokens[choice1] == 
        preState.embargoTokens[choice1], __FILE__, __LINE__);
    printf("Checking that the player's hand did not change:\n");
    assertTrue(postState.handCount[curPlayer] == preState.handCount[curPlayer], 
        __FILE__, __LINE__);

    return 0;
}