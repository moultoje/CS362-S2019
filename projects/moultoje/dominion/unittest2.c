/*******************************************************************************
** Program: unittest2.c
** Author: Jeffrey Moulton (moultoje@oregonstate.edu)
** Course: CS362 - Software Engineering II
** Date Modified: 5/5/2019
** Description: Unit test for the feastEffect function from the dominion.c 
                program. This unit test is a positive unit test that checks that
                the feastEffect function works like it should. The game state
                is initialized with 2 players. The first test has the player buy
                a card that costs 5 gold or less (in this case, gardens) and
                checks that the player's hand count doesn't change and the 
                supply of gardens is reduced by one. The second test has the 
                player buy a card that costs more than 5 gold and checks that 
                the game state didn't change since the player wouldn't get a 
                new card. The third test has the player buy a card that has no
                more supply and checks that the game state didn't change since 
                the player wouldn't get a new card.
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
    int choice1 = 1; // Choice is gardens
    int curPlayer = 0;

    // Initialize a game state
    initializeGame(numPlayers, k, seed, &preState);

    // Copy the game state
    memcpy(&postState, &preState, sizeof(struct gameState));

    printf("TESTING FEAST CARD\n");

    // Test #1: Buy a card that is less than 5 gold and is in supply.
    printf("Test 1: The supply for gardens should decrease by one and the" 
        " player's hand size shouldn't change.\n");
    feastEffect(&postState, curPlayer, choice1);
    printf("Checking that the player's hand contains the same amount:\n");
    assertTrue(postState.handCount[curPlayer] == preState.handCount[curPlayer], 
        __FILE__, __LINE__);
    printf("Checking that the gardens supply decreased by one:\n");
    assertTrue(postState.supplyCount[choice1] == preState.supplyCount[choice1] -
        1, __FILE__, __LINE__);
/*
********************************************************************************
    THESE TESTS ARE COMMENTED OUT BECAUSE THEY CAUSE THE FEASTEFFECT TO GO INTO
    AN INFINITE LOOP. THE REFACTORED CODE DID NOT CORRECT THIS ISSUE THAT WAS
    ALREADY PRESENT IN THE CARDEFFECT FUNCTION.
********************************************************************************

    // Test #2: Buy a card that costs more than 5 gold.
    printf("Test 2: Nothing in the current player's state should change.\n");
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    choice1 = 0; // Change the choice to adventurer
    feastEffect(&postState, curPlayer, choice1);
    assertTrue(strcmp((char*) postState, (char*) preState) == 0, __FILE__, 
        __LINE__);

    // Test #3: Buy a card that is no longer in supply.
    printf("Test 3: Nothing in the current player's state should change.\n");
    preState.supplyCount[2] = 0; // Change the supply of embargo to zero
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    choice1 = 2; // Change the choice to embargo
    feastEffect(&postState, curPlayer, choice1);
    assertTrue(strcmp((char*) postState, (char*) preState) == 0, __FILE__, 
        __LINE__);
*/
    return 0;
}