/*******************************************************************************
** Program: unittest3.c
** Author: Jeffrey Moulton (moultoje@oregonstate.edu)
** Course: CS362 - Software Engineering II
** Date Modified: 5/5/2019
** Description: Unit test for the baronEffect function from the dominion.c 
                program. This unit test is a positive unit test that checks that
                the baronEffect function works like it should. The game state
                is initialized with 2 players. The first test has the player 
                discard an estate card. The test checks that the player's hand
                decreases by one, the player gains 4 coins, and the player gains
                one buy. The second test has the player try to discard an estate
                card when they don't have one. The test checks that the player's
                hand increases by one, the player doesn't gain any coins, and 
                the player gains one buy. The third test has the player gain one
                estate. The test checks that the player's hand increases by one,
                the player doesn't gain any coins, and the player gains one buy.
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
    int k[10] = {adventurer, gardens, embargo, estate, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    int seed = 1000;

    // Initialize variables needed to test the function.
    int gainedCard = 1;
    int discard = 1;
    int xtraCoins = 4;
    int xtraBuys = 1;
    int choice1 = 1; // Discard estate
    int curPlayer = 0;
    int i, j;

    // Initialize a game state
    initializeGame(numPlayers, k, seed, &preState);    

    printf("TESTING BARON CARD\n");

    // Test #1: Discard an estate.
    printf("Test 1: Discarding an estate card. The player should discard an"
        " estate card (one less card in their hand) and should gain 4 gold.\n");
    gainCard(estate, &preState, 0, curPlayer); // Give the player an estate
    preState.supplyCount[estate]--;
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    baronEffect(&postState, curPlayer, choice1);
    printf("Checking that the player's hand decreased by one:\n");
    assertTrue(postState.handCount[curPlayer] == preState.handCount[curPlayer] -
        discard, __FILE__, __LINE__);
    printf("Checking that the player gained 4 gold:\n");
    assertTrue(postState.coins == preState.coins + xtraCoins, __FILE__, 
        __LINE__);
    printf("Checking that the player gained 1 buy:\n");
    assertTrue(postState.numBuys == preState.numBuys + xtraBuys, __FILE__,
        __LINE__);

    // Test #2: Discard an estate without an estate in the player's hand.
    printf("Test 2: Discard an estate without an estate in hand. The player"
        " should gain an estate since they don't have one to discard.\n");
    // Remove all estate cards from the player's hand.
    for (i = 0; i < preState.handCount[curPlayer]; ++i)
    {
        if (preState.hand[curPlayer][i] == estate)
        {
            for (j = 0; j + i < preState.handCount[curPlayer] - 1; ++j)
            {
                preState.hand[curPlayer][i + j] = preState.hand[curPlayer][i+j+1];
            }
            preState.hand[curPlayer][preState.handCount[curPlayer]] = -1;
            preState.handCount[curPlayer]--;
        }
    }
    preState.supplyCount[estate] = 8; // Ensuring there are estates to obtain.
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    baronEffect(&postState, curPlayer, choice1);
    printf("Checking that the player gained one card:\n");
    assertTrue(postState.handCount[curPlayer] == preState.handCount[curPlayer] +
        gainedCard, __FILE__, __LINE__);
    printf("Checking that the player didn't gain coins:\n");
    assertTrue(postState.coins == preState.coins, __FILE__, __LINE__);
    printf("Checking that the player gained 1 buy:\n");
    assertTrue(postState.numBuys == preState.numBuys + xtraBuys, __FILE__,
        __LINE__);

    // Test #3: Gain an estate card.
    printf("Test 3: Gain estate. The player should gain an estate.\n");
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    choice1 = 0; // Gain estate
    baronEffect(&postState, curPlayer, choice1);
    printf("Checking that the player gained one card:\n");
    assertTrue(postState.handCount[curPlayer] == preState.handCount[curPlayer] +
        gainedCard, __FILE__, __LINE__);
    printf("Checking that the player didn't gain coins:\n");
    assertTrue(postState.coins == preState.coins, __FILE__, __LINE__);
    printf("Checking that the player gained 1 buy:\n");
    assertTrue(postState.numBuys == preState.numBuys + xtraBuys, __FILE__,
        __LINE__);

    return 0;
}