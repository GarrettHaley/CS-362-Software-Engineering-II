#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include "rngs.h"
#include "assert.h"

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

int main () {
  printf("\nStarting Card Test 2: Smithy\n");

//Initialize the gamestate
 int players, player,opponent,opponentHandCount,opponentDeckCount, numActions, handCount, deckCount, seed;
 struct gameState GameState;
 int k[10] = {minion, smithy, gardens, tribute, baron, adventurer, cutpurse, mine, embargo, outpost};
 seed = 10;
 players = 2;
 initializeGame(players, k, seed, &GameState);
//set player indices
opponent = 1;//this player should not have their gamestate altered by their oppents play of the smithy card
player = 0;//(this player will play the smithy card)

//Set and save gamestate of player 2 (to check against after the smithy card has been played for any changes)
GameState.whoseTurn = opponent;
GameState.hand[opponent][0] = smithy;
GameState.deckCount[opponent] = 3;
opponentDeckCount = GameState.deckCount[opponent];
opponentHandCount = GameState.handCount[1];

 GameState.whoseTurn = player;
//Set gamestate to player 1's turn
 GameState.hand[player][0] = smithy;
//Put the smithy card in their hand
 GameState.deckCount[player] = 3;
//set their decksize to three cards

//Save the current settings of the gamestate to check against the gamestate after the smithy card has been played
 numActions = GameState.numActions;
 deckCount = GameState.deckCount[player];
 handCount = GameState.handCount[0];
//Play the smithy card
int cardReturnValue =  cardEffect(smithy, 1, 1, 1, &GameState, handCount, NULL);

//Verify the handcount has in fact increased by 3 cards
  int assert1 = ASSERT((handCount - 1 + 3 == GameState.handCount[0]), "Smithy +3 cards to the players hand.");
//Verify the number of actions were not altered
  int assert2 = ASSERT(numActions == GameState.numActions, "Number of actions remained the same.");
//Verify the deck was decreased by 3 cards
  int assert3 = ASSERT(deckCount - 3 == GameState.deckCount[player],"Deck size was properly decreased by 3.");

//Verify opponent's handcount was not altered
  int assert4 = ASSERT((opponentHandCount == GameState.handCount[opponent]),"Oppenents's hand size was not altered.");
//Verify opponent's deckCount was not altered
  int assert5 = ASSERT((opponentDeckCount == GameState.deckCount[opponent]),"Oppenents's deck size was not altered.");
//Verify card return value is correct
 int assert6 = ASSERT((cardReturnValue == 0),"Card returned from cardEffect with the correct value of 0.");
//if all of this was verified, print that this test was successful
  if(assert1 + assert2 + assert3 + assert4 + assert5 + assert6 == 0)
     printf("TEST SUCCESSFULLY COMPLETED\n");
//if a section could not be verified, print that this test was a faliure
  else
     printf("TEST FAILED\n");
  return 0;
}
