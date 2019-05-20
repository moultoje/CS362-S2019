/*******************************************************************************
** Program: randomtestcard1.c
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
    // Initialize variables used in the randomtestcard1 function.
    int i, j, k;
    int numPlayers;
    int curPlayer;
    int cards[10]; // Cards used in the game
    int handPos; // Position of the smithy card in the hand
    int randomInt; // Random integer
    struct gameState preState; // State of the game before calling function
    struct gameState postState; // State of the game after calling function
    int numTests = 1000; // Number of random tests
    int numFails = 0; // Number of scenarios failed
    int failFlag = 0; // Flag to be set when a failure occurs

    // Seed random
    srand(time(NULL));

    // Inform the user which test is being run.
    printf("The Smithy card is being tested.\n");
    printf("%d tests will be run against the card.\n\n", numTests);

    // Start loop for testing.
    for (i = 0; i < numTests; ++i)
    {
        // Set the failFlag to false.
        failFlag = 0;

        // Randomize the number of players and current player. The number of 
        // players should be between 2 and 4.
        numPlayers = rand() % (4 - 2 + 1) + 2;
        curPlayer = rand() % numPlayers;

        // Randomize the cards, force smithy to be in the array.
        cards[0] = smithy;
        j = 1;
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

        // Randomize the features of smithy: player's decks and discard 
        // piles. Draw the current player's hand, force the smithy card to be
        // at the handPos position in the player's hand. Tell the state whose
        // turn it is.
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
        handPos = rand() % 5; // Get a random hand position
        preState.handCount[curPlayer] = 0; // Set the hand count to zero.
        for (j = 0; j < 5; ++j) // Draw deck for current player.
        {
            if (j == handPos) // At the position for the smithy card
            {
                // Add smithy to the hand.
                preState.hand[curPlayer][handPos] = smithy;
            }
            else
            {
                // Draw from the deck.
                drawCard(curPlayer, &preState);
            }
        }
        preState.whoseTurn = curPlayer;

        // Copy the preState to the postState.
        memcpy(&postState, &preState, sizeof(struct gameState));

        // Call the smithy effect function.
        smithyEffect(&postState, curPlayer, handPos);

        // Check that the current player's hand increased by two.
        if (postState.handCount[curPlayer] != 
            (preState.handCount[curPlayer] + 2))
        {
            printf("Test %d FAILURE: Current player's hand did not increase by "
                "two! Expected value: %d, actual value: %d.\n", i, 
                preState.handCount[curPlayer] + 2, 
                postState.handCount[curPlayer]);
            failFlag = 1;
        }

        // Check that the current player's deck decreased by three.
        if (postState.deckCount[curPlayer] != preState.deckCount[curPlayer] - 3)
        {
            printf("Test %d FAILURE: Current player's deck did not decrease by "
                "three! Expected value: %d, actual value: %d.\n", i,
                preState.deckCount[curPlayer] - 3,
                postState.deckCount[curPlayer]);
            failFlag = 1;
        }

        // Check that the current player's played card pile increased by one.
        if (postState.playedCardCount != preState.playedCardCount + 1)
        {
            printf("Test %d FAILURE: The played card pile did not increase by "
                "one! Expected value: %d, actual value: %d.\n", i,
                preState.playedCardCount + 1,
                postState.playedCardCount);
            failFlag = 1;
        }

        // Check that the other player's decks did not change size.
        for (j = 0; j < numPlayers; ++j)
        {
            if (j != curPlayer)
            {
                if (postState.deckCount[j] != preState.deckCount[j])
                {
                    printf("Test %d FAILURE: Player %d's deck changed sizes.\n",
                        i, j);
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