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
  printf("\nStarting Card Test 3: Village\n");

//Initialize the gamestate
 int players, player,opponent,opponentHandCount,opponentDeckCount, numActions, handCount, deckCount, seed;
 struct gameState GameState;
 int k[10] = {minion, smithy, gardens, tribute, baron, adventurer, village, mine, embargo, outpost};
 seed = 10;
 players = 2;
 initializeGame(players, k, seed, &GameState);
//set player indices
opponent = 1;//this player should not have their gamestate altered by their oppents play of the village card
player = 0;//(this player will play the village card)

//Set and save gamestate of player 2 (to check against after the village card has been played for any changes)
GameState.whoseTurn = opponent;
GameState.hand[opponent][0] = village;
GameState.deckCount[opponent] = 3;
opponentDeckCount = GameState.deckCount[opponent];
opponentHandCount = GameState.handCount[1];
 GameState.whoseTurn = player;
//Set gamestate to player 1's turn
 GameState.hand[player][0] = village;
//Put the village card in their hand
 GameState.deckCount[player] = 3;
//set their decksize to three cards

//Save the current settings of the gamestate to check against the gamestate after the village card has been played
 numActions = GameState.numActions;
 deckCount = GameState.deckCount[player];
 handCount = GameState.handCount[0];

//Play the village card
int cardReturnValue = cardEffect(village, 1, 1, 1, &GameState, 0, NULL);

//Verify the handcount has in fact increased by 3 cards
  int assert1 = ASSERT((handCount == GameState.handCount[0]), "Village +1 card to players hand.");
//Verify the number of actions were not altered
  int assert2 = ASSERT(numActions + 2 == GameState.numActions, "Number of actions were increased by 2.");
//Verify the deck was decreased by 3 cards
  int assert3 = ASSERT(deckCount - 1  == GameState.deckCount[player],"Deck size was properly decreased by 1.");

//Verify opponent's handcount was not altered
  int assert4 = ASSERT((opponentHandCount == GameState.handCount[opponent]),"Oppenents's hand size was not altered.");
//Verify opponent's deckCount was not altered
  int assert5 = ASSERT((opponentDeckCount == GameState.deckCount[opponent]),"Oppenents's deck size was not altered.");
//Verify return value of card
  int assert6 = ASSERT((cardReturnValue == 0),"Card returned from cardEffect with the correct value of 0.");
//if all of this was verified, print that this test was successful
  if(assert1 + assert2 + assert3 + assert4 + assert5 + assert6  == 0)
     printf("TEST SUCCESSFULLY COMPLETED\n");
//if a section could not be verified, print that this test was a faliure
  else
     printf("TEST FAILED\n");
  return 0;
}
