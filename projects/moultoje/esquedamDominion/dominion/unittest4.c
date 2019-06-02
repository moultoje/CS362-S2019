/*******************************************************************************
** Program: unittest4.c
** Author: Jeffrey Moulton (moultoje@oregonstate.edu)
** Course: CS362 - Software Engineering II
** Date Modified: 6/1/2019
** Description: Unit test for the stewardEffect function from the dominion.c 
                program. This unit test is a positive unit test that checks that
                the stewardEffect function works like it should. The game state
                is initialized with 2 players. The first test has the player 
                draw two cards. The test then checks that the user gained one
                card into their hand, didn't get any coins, and their played
                card pile increased by one. The second test has the player gain
                two coins. This test checks that the user lost one card from
                their hand, gained two coins, and added one card to their played
                card pile. The third test has the player trash two cards. It 
                checks that their hand decreased by three cards, they didn't 
                gain any coins, and they added one card to the played card pile.
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
    int gainedCard = 2;
    int playedCard = 1;
    int discard = 1;
    int xtraCoins = 0;
    int choice1 = 1; // Draw 2 cards
    int choice2 = -1;
    int choice3 = -1;
    int handPos = 0;
    int curPlayer = 0;

    // Initialize a game state
    initializeGame(numPlayers, k, seed, &preState);    

    printf("TESTING STEWARD CARD\n");

    // Test #1: Draw 2 cards.
    printf("Test 1: Drawing 2 cards. The player should gain one card in their"
        " hand (draw 2 discard 1).\n");
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    cardEffect(steward, choice1, choice2, choice3, &postState, handPos, NULL);
    printf("Checking that the player's hand increased by one:\n");
    assertTrue(postState.handCount[curPlayer] == preState.handCount[curPlayer] +
        gainedCard - playedCard, __FILE__, __LINE__);
    printf("Checking that the player didn't gain any coins:\n");
    assertTrue(postState.coins == preState.coins, __FILE__, 
        __LINE__);
    printf("Checking that the player's played pile increased by one:\n");
    assertTrue(postState.playedCardCount == 
        preState.playedCardCount + playedCard, __FILE__, __LINE__);

    // Test #2: Gain 2 coins
    printf("Test 2: Gaining 2 coins. The player should gain 2 coins.\n");
    gainedCard = 0;
    xtraCoins = 2;
    choice1 = 2; // Get 2 coins
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    cardEffect(steward, choice1, choice2, choice3, &postState, handPos, NULL);
    printf("Checking that the player's hand decreased by zero:\n");
    assertTrue(postState.handCount[curPlayer] == preState.handCount[curPlayer] +
        gainedCard - discard, __FILE__, __LINE__);
    printf("Checking that the player gained two coins:\n");
    assertTrue(postState.coins == preState.coins + xtraCoins, __FILE__, 
        __LINE__);
    printf("Checking that the player's played pile increased by one:\n");
    assertTrue(postState.playedCardCount == 
        preState.playedCardCount + playedCard, __FILE__, __LINE__);

    // Test #3: Trash 2 cards.
    printf("Test 3: Trash 2 cards. The player should lose two cards out of"
        " their hand along with the played steward.\n");
    choice1 = 0; // Trash 2 cards
    choice2 = 1;
    choice3 = 2;
    xtraCoins = 0;
    discard = 3;
    memcpy(&postState, &preState, sizeof(struct gameState)); // Copy the state
    cardEffect(steward, choice1, choice2, choice3, &postState, handPos, NULL);
    printf("Checking that the player's hand decreased by three:\n");
    assertTrue(postState.handCount[curPlayer] == preState.handCount[curPlayer] -
        discard, __FILE__, __LINE__);
    printf("Checking that the player didn't gain any coins:\n");
    assertTrue(postState.coins == preState.coins, __FILE__, 
        __LINE__);
    printf("Checking that the player's played pile increased by one:\n");
    assertTrue(postState.playedCardCount == 
        preState.playedCardCount + playedCard, __FILE__, __LINE__);

    return 0;
}