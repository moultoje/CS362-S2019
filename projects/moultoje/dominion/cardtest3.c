/*******************************************************************************
** Program: cardtest3.c
** Author: Jeffrey Moulton (moultoje@oregonstate.edu)
** Course: CS362 - Software Engineering II
** Date Modified: 5/5/2019
** Description: Unit test for the minion case of the cardEffect function from
                the dominion.c program. This unit test is a positive unit test
                that checks that the minion card works like it should. The game
                state is initialized with 2 players. The first test has the 
                player getting 2 coins. It checks that the player's coins 
                increased by 2, the player gained an action, and the player's
                hand decreased by one. The second test has the player discarding
                their hand and drawing cards. The second test also starts with
                the player's opponents not having 5 or more cards in their hand
                such that they don't have to discard their hand. The test checks
                that the player didn't gain any coins, the player gained an 
                action, the player's hand now contains 4 cards, and the 
                opponent's hand does not contain 4 cards (preset to have 3). 
                The third test is the same as the second except the 
                opponent has 5 or more cards in their hand. The test checks that
                the palyer didn't gain any coins, the player gained an action, 
                the player's hand now contatins 4 cards, and the opponent's hand
                contains 4 cards.
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
    int choice1 = 1; 
    int choice2 = 0;
    int choice3 = 0;
    int handPos = 0;
    int curPlayer = 0;
    int i;

    // Initialize a game state
    initializeGame(numPlayers, k, seed, &preState);    

    printf("TESTING MINION CARD\n");

    // Test #1: Player gets two coins.
    printf("Test #1: Player chooses to get 2 coins. The player also gets an"
        " additional action.\n");
    preState.whoseTurn = 0;
    preState.hand[curPlayer][handPos] = minion;
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    cardEffect(minion, choice1, choice2, choice3, &postState, handPos, NULL);
    printf("Checking that the player's coins increased by two:\n");
    assertTrue(postState.coins == preState.coins + xtraCoins, __FILE__, 
        __LINE__);
    printf("Checking that the player gained one action::\n");
    assertTrue(postState.numActions == preState.numActions + 1, __FILE__,
        __LINE__);
    printf("Checking that the player's hand decreased by one:\n");
    assertTrue(postState.handCount[curPlayer] == preState.handCount[curPlayer] -
        discard, __FILE__, __LINE__);

    // Test #2. Player chooses to discard hand and draw cards. No opponents with
    // hands of 5 cards or more.
    printf("Test #2: Player chooses to discard hand and draw cards with no"
        " opponent having 5 or more cards in their hand. The player gets an"
        " additional action.\n");
    preState.whoseTurn = 0;
    preState.hand[curPlayer][handPos] = minion;
    choice1 = 0;
    choice2 = 1;
    preState.handCount[1] = 3;
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    cardEffect(minion, choice1, choice2, choice3, &postState, handPos, NULL);
    printf("Checking that the player's coins didn't change:\n");
    assertTrue(postState.coins == preState.coins, __FILE__, __LINE__);
    printf("Checking that the player gained one action::\n");
    assertTrue(postState.numActions == preState.numActions + 1, __FILE__,
        __LINE__);
    printf("Checking that the player's hand has 4 cards:\n");
    assertTrue(postState.handCount[curPlayer] == 4, __FILE__, __LINE__);
    printf("Check that the other player's hand didn't change:\n");
    assertTrue(postState.handCount[1] == preState.handCount[1], __FILE__, 
        __LINE__);

    // Test #3. Player chooses to discard hand and draw cards. An opponents has
    // a hand of 5 cards or more.
    printf("Test #2: Player chooses to discard hand and draw cards with an"
        " opponent having 5 or more cards in their hand. The player gets an"
        " additional action.\n");
    preState.whoseTurn = 0;
    preState.hand[curPlayer][handPos] = minion;
    choice1 = 0;
    choice2 = 1;
    preState.handCount[1] = 6;
    for (i = 0; i < preState.handCount[1]; ++i)
    {
        preState.hand[1][i] = adventurer;
    }
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    cardEffect(minion, choice1, choice2, choice3, &postState, handPos, NULL);
    printf("Checking that the player's coins didn't change:\n");
    assertTrue(postState.coins == preState.coins, __FILE__, __LINE__);
    printf("Checking that the player gained one action::\n");
    assertTrue(postState.numActions == preState.numActions + 1, __FILE__,
        __LINE__);
    printf("Checking that the player's hand has 4 cards:\n");
    assertTrue(postState.handCount[curPlayer] == 4, __FILE__, __LINE__);
    printf("Check that the other player's hand has 4 cards:\n");
    assertTrue(postState.handCount[1] == 4, __FILE__, __LINE__);

    return 0;
}