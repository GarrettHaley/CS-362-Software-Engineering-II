#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main (int argc, char** argv) {
        int kingdom[10] = {adventurer, gardens, embargo, village, council_room, mine, cutpurse, sea_hag, tribute, smithy};
        int testSuccessful = 0, testFailed = 0,i, tests = 50;//sets number of tests, testSuccessful = successful, testFailed = not successful

        for(i = 0; i < tests; i++) {

                int num_players = rand() % 4, player = 0, rand_seed = rand();//set player, #players, and random seed
                struct gameState *g = malloc(sizeof(struct gameState));//make gamestate
                initializeGame(num_players, kingdom, rand_seed, g);//Initialize the game with values above

                g->deckCount[player] = rand() % MAX_DECK;//randomize deck size
                g->discardCount[player] = rand() % MAX_DECK;//randomize discard size
                int pastHandCount = g->handCount[player] = rand() % MAX_HAND;//randomize hand size
                int opponentHandCount = g->handCount[1] = rand() % MAX_HAND;//randomize opponents hand size
                int pastNumBuys = g->numBuys;
                cardEffect(council_room, 1, 1, 1, g, 0, 0);//play the card
		if (pastHandCount + 3 == g->handCount[player] && pastNumBuys + 1 == g->numBuys && opponentHandCount + 1 == g->handCount[1]){//check if correct number of cards were added to hand of both player/opponent and buys was increased by 1.
			testSuccessful++;
		}
		else
			testFailed++;

                free(g);
        }
        printf("Random Test 2: Council Room Card");
        printf("\nThere were %d successful council room card plays, and %d failures [out of %d games]\n\n", testSuccessful, testFailed, tests);

        return 0;
}
