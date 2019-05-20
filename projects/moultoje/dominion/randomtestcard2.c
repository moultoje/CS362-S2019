/*******************************************************************************
** Program: randomtestcard2.c
** Author: Jeffrey Moulton (moultoje@oregonstate.edu)
** Course: CS362 - Software Engineering II
** Date Modified: 5/19/2019
** Description: 
*******************************************************************************/

#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    // Initialize variables used in the randomtestcard2 function.
    int i, j, k;
    int numPlayers;
    int curPlayer;
    int cards[10]; // Cards used in the game
    int choice1; // Choice to discard or gain an estate
    int hasEstate = 0; // Whether or not the player has an estate in the hand
    int testDescription = 0; // Flag for if the test description has been printed
    int randomInt; // Random integer
    struct gameState preState; // State of the game before calling function
    struct gameState postState; // State of the game after calling function
    int numTests = 1000; // Number of random tests
    int numFails = 0; // Number of scenarios failed
    int failFlag = 0; // Flag to be set when a failure occurs

    // Seed random
    srand(time(NULL));

    // Inform the user which test is being run.
    printf("The Baron card is being tested.\n");
    printf("%d tests will be run against the card.\n\n", numTests);

    // Start loop for testing.
    for (i = 0; i < numTests; ++i)
    {
        // Set the failFlag, hasEstate, and testDescription to false.
        failFlag = 0;
        hasEstate = 0;
        testDescription = 0;

        // Randomize the number of players and current player. The number of 
        // players should be between 2 and 4.
        numPlayers = rand() % (4 - 2 + 1) + 2;
        curPlayer = rand() % numPlayers;

        // Randomize the cards, force baron and estate to be in the array.
        cards[0] = baron;
        cards[1] = estate;
        j = 2;
        while (j < 10)
        {
            // Get random integer in card value range
            randomInt = rand() % 27;

            // Check that the card already isn't in the array.
            for (k = 0; k < j; ++k)
            {
                if (cards[k] == randomInt)
                {
                    randomInt = -1;
                }
            }

            // If randomInt is not -1, add it to the array in increment j
            if (randomInt != -1)
            {
                cards[j] = randomInt;
                ++j;
            }
        }

        // Initialize the game
        initializeGame(numPlayers, cards, rand(), &preState);

        // Randomize the features of baron: player's decks and discard 
        // piles. Draw the current player's hand. Randomize the number of
        // estate cards in supply. Tell the state whose turn it is.
        for (j = 0; j < numPlayers; ++j) // Randomize decks.
        {
            // Get random deck size.
            preState.deckCount[j] = rand() % MAX_DECK;

            // Fill the deck with random cards.
            for (k = 0; k < preState.deckCount[j]; ++k)
            {
                preState.deck[j][k] = cards[rand() % 10];
            }
        }
        for (j = 0; j < numPlayers; ++j) // Randomize discards.
        {
            // Determine the discard size based off of the deck size.
            preState.discardCount[j] = MAX_DECK - preState.deckCount[j];

            // Fill the discard pile with random cards.
            for (k = 0; k < preState.discardCount[j]; ++k)
            {
                preState.discard[j][k] = cards[rand() % 10];
            }
        }
        preState.handCount[curPlayer] = 0; // Set the hand count to zero.
        for (j = 0; j < 5; ++j) // Draw deck for current player.
        {
            drawCard(curPlayer, &preState);
            // If the drawn card was estate, set hasEstate flag
            if (preState.hand[curPlayer][j] == estate)
            {
                hasEstate = 1;
            }
        }
        if (numPlayers > 2) // Randomize the number of estates
        {
            // Number of players over 2, max of 12 estates.
            preState.supplyCount[estate] = rand() % 13;
        }
        else
        {
            // 2 players, max of 8 estates.
            preState.supplyCount[estate] = rand() % 9;
        }
        preState.whoseTurn = curPlayer;

        // Copy the preState to the postState.
        memcpy(&postState, &preState, sizeof(struct gameState));

        // Randomize choice1. Call the baron effect function.
        choice1 = rand() % 2;
        baronEffect(&postState, curPlayer, choice1);

        // Error testing with choice1 = 1 and the player has an estate card.
        if (choice1 == 1 && hasEstate == 1)
        {
            // Check that the current player's hand decreased by one.
            if (postState.handCount[curPlayer] != 
                (preState.handCount[curPlayer] - 1))
            {
                printf("Test %d: Player chose to discard estate and had an "
                    "estate in hand.\n", i);
                testDescription = 1;
                printf("Test %d FAILURE: Current player's hand did not decrease"
                    " by one! Expected value: %d, actual value: %d.\n", i, 
                    preState.handCount[curPlayer] - 1, 
                    postState.handCount[curPlayer]);
                failFlag = 1;
            }

            // Check if the player gained 4 coins.
            if (postState.coins != preState.coins + 4)
            {
                if (!testDescription)
                {
                    printf("Test %d: Player chose to discard estate and had an "
                        "estate in hand.\n", i);
                    testDescription = 1;
                }
                printf("Test: %d FAILURE: Number of coins did not increase "
                    "by four! Expected value: %d, actual value: %d.\n", i,
                    preState.coins + 4, postState.coins);
                failFlag = 1;
            }

            // Check that the current player's discard deck increase by one.
            if (postState.discardCount[curPlayer] !=
                (preState.discardCount[curPlayer] + 1))
            {
                if (!testDescription)
                {
                    printf("Test %d: Player chose to discard estate and had an "
                        "estate in hand.\n", i);
                    testDescription = 1;
                }
                printf("Test %d FAILURE: Current player's discard pile did not "
                    "increase by one! Expected value: %d, actual value: %d.\n",
                    i, preState.discardCount[curPlayer] + 1,
                    postState.discardCount[curPlayer]);
                failFlag = 1;
            }

            // Check that the number of estates didn't change.
            if (postState.supplyCount[estate] != preState.supplyCount[estate])
            {
                if (!testDescription)
                {
                    printf("Test %d: Player chose to discard estate and had an "
                        "estate in hand.\n", i);
                    testDescription = 1;
                }
                printf("Test %d FAILURE: Supply of estates changed!\n", i);
                failFlag = 1;
            }
        }
        else // Error testing for gaining estate
        {
            // Check that the player's hand didn't change size
            if (postState.handCount[curPlayer] != 
                (preState.handCount[curPlayer]))
            {
                printf("Test %d: Player gains estate card.\n", i);
                testDescription = 1;
                printf("Test %d FAILURE: Current player's hand changed "
                    "size!\n");
                failFlag = 1;
            }

            // Check if the player gained any coins.
            if (postState.coins != preState.coins)
            {
                if (!testDescription)
                {
                    printf("Test %d: Player gains estate card.\n", i);
                    testDescription = 1;
                }
                printf("Test: %d FAILURE: Number of coins changed!\n", i);
                failFlag = 1;
            }

            // If the preState had more than one estate card, check the
            // discard count and supply of estates.
            if (preState.supplyCount[estate] > 0)
            {
                // Check if the player's discard deck increased by one.
                if (postState.discardCount[curPlayer] !=
                    (preState.discardCount[curPlayer] + 1))
                {
                    if (!testDescription)
                    {
                        printf("Test %d: Player gains estate card.\n", i);
                        testDescription = 1;
                    }
                    printf("Test %d FAILURE: Current player's discard pile did "
                        "not increase by one! Expected value: %d, actual value:"
                        " %d.\n", i, preState.discardCount[curPlayer] + 1,
                        postState.discardCount[curPlayer]);
                    failFlag = 1;
                }

                // Check if the supply of estates didn't decrease by one.
                if (postState.supplyCount[estate] != 
                    preState.supplyCount[estate] - 1)
                {
                    if (!testDescription)
                    {
                        printf("Test %d: Player gains estate card.\n", i);
                        testDescription = 1;
                    }
                    printf("Test %d FAILURE: Supply of estates did not decrease"
                        " by one! Expected value: %d, actual value: %d.\n", i,
                        preState.supplyCount[estate] - 1,
                        postState.supplyCount[estate]);
                    failFlag = 1;
                }
            }
        }

        // Check that the other player's discard pile did not change size.
        for (j = 0; j < numPlayers; ++j)
        {
            if (j != curPlayer)
            {
                if (postState.discardCount[j] != preState.discardCount[j])
                {
                    printf("Test %d FAILURE: Player %d's discard pile changed "
                        "sizes.\n", i, j);
                    failFlag = 1;
                }
            }
        }

        // If the failFlag is set, increment the number of tests failed.
        if (failFlag)
        {
            ++numFails;
        }
    }

    // Print out how many failures there were in the total amount of tests.
    printf("\n%d tests failed out of %d tests. A test is marked as failed if "
        "any check in the test was not valid.\n\n", numFails, numTests);

    return 0;
}