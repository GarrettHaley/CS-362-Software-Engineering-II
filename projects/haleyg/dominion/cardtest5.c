#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "steward"
int ASSERT(int b, char* s) {
  if (!b) {
    printf ("ASSERTION FAILURE: %s\n", s);
    return 1;
  }
  else{
    printf("%s\n",s);
    return 0;
  }
}

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("\nStarting Card Test 5: %s\n", TESTCARD);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 2;
	xtraCoins = 0;
	int a1 = ASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,"Correct hand count after player chooses +2 cards.");
	int a2 = ASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "Correct deck count after player chooses +2 cards.");
	int a3 = ASSERT(testG.coins == G.coins + xtraCoins,"Correct coin count after player chooses +2 cards");

	// ----------- TEST 2: choice1 = 2 = +2 coins --------------

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 2;
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 0;
	xtraCoins = 2;
	int a4 = ASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,"Correct hand count after player chooses +2 coins");
	int a5 = ASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards,"Correct deck count after player chooses +2 coins");
	int a6 = ASSERT(testG.coins == G.coins + xtraCoins,"Correct coin count after player chooses +2 coins");
        int a7=0;
	// ----------- TEST 3: choice1 = 3 = trash two cards --------------
	choice1 = 3;

	// cycle through each eligible combination of 2 cards to trash
	for (i=1; i<G.handCount[thisPlayer]; i++) {
		for (j=i+1; j<G.handCount[thisPlayer]; j++) {

			G.hand[thisPlayer][0] = steward;
			G.hand[thisPlayer][1] = copper;
			G.hand[thisPlayer][2] = duchy;
			G.hand[thisPlayer][3] = estate;
			G.hand[thisPlayer][4] = feast;

			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));
			choice2 = j;
			choice3 = i;
			remove1 = testG.hand[thisPlayer][i];
			remove2 = testG.hand[thisPlayer][j];
			cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);
			
			// tests that the removed cards are no longer in the player's hand
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				if(testG.hand[thisPlayer][m] == remove1 || testG.hand[thisPlayer][m] == remove2)
					a7+=1;
			}
			}
			// tests for the appropriate number of remaining cards
			newCards = 0;
			xtraCoins = 0;
			discarded = 3;
			if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded)
				a7+=1;
			if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - newCards + shuffledCards)
				a7+=1;
		}
	if(a7 ==0){
	 ASSERT(1,"+2 cards removed properly");
	 ASSERT(1, "Correct hand count after player chooses -2 cards");
         ASSERT(1,"Correct deck count after player chooses -2 cards");
	}
	else
		ASSERT(-1,"There has been an error when removing the 2 cards from the deck");

        if(a1+a2+a3+a4+a5+a6+a7 == 0){
		printf("TEST WAS SUCCESSFULLY COMPLETED\n\n");
        }
	else{
		printf("TEST FAILED\n\n");
	}
	return 0;
}
