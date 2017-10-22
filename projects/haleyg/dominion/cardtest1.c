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
  printf("\nStarting Card Test 1: Adventurer\n");

//Initialize the gamestate 
 int players, player,opponent,opponentHandCount,opponentDeckCount, numActions, handCount, deckCount, seed;
 struct gameState GameState;
 int *k = kingdomCards(minion, smithy, gardens, tribute, baron, adventurer, cutpurse, mine, embargo, outpost);
 seed = 10;
 players = 2;
 initializeGame(players, k, seed, &GameState);
//set player indices
opponent = 1;//this player should not have their gamestate altered by their oppents play of the adventurer card
player = 0;//(this player will play the adventurer card)

//Set and save gamestate of player 2 (to check against after the adventurer card has been played for any changes)
GameState.whoseTurn = opponent;
GameState.hand[opponent][0] = adventurer;
GameState.deckCount[opponent] = 2;
opponentDeckCount = GameState.deckCount[opponent];
opponentHandCount = GameState.handCount[opponent];
endTurn(&GameState);

//Set gamestate to player 1's turn
 GameState.hand[player][0] = adventurer;
//Put the adventurer card in their hand
GameState.handCount[player] = 1;
GameState.deck[player][0] = copper;
GameState.deck[player][1] = copper;
GameState.deckCount[player] = 2;
//Save the current settings of the gamestate to check against the gamestate after the adventurer card has been played		
 numActions = GameState.numActions;
 deckCount = GameState.deckCount[player];
 handCount = GameState.handCount[0];
//Play the adventurer card
 int cardReturnValue = cardEffect(adventurer, 1, 1, 1, &GameState, 0, NULL);
 int adventureFunctionReturn = refactoredAdventurer(&GameState);
 
//Verify the handcount has in fact increased by 3 cards
  int assert1 = ASSERT((handCount  + 2 == GameState.handCount[0]), "Adventurer +2 cards to players hand.");
//Verify the number of actions were not altered
  int assert2 = ASSERT(numActions == GameState.numActions, "Number of actions remained the same.");
//Verify the deck was decreased by 3 cards
  int assert3 = ASSERT(deckCount > fullDeckCount(player,0,&GameState),"Size of deck was properly decreased.");
//Verify opponent's handcount was not altered
  int assert4 = ASSERT((opponentHandCount == GameState.handCount[opponent]),"Oppenents's hand size was not altered.");
//Verify opponent's deckCount was not altered
  int assert5 = ASSERT((opponentDeckCount == GameState.deckCount[opponent]),"Oppenents's deck size was not altered.");
//Verify card1 was in fact a treasure
  int assert6 = ASSERT((GameState.hand[player][2] == copper && GameState.hand[player][1] == copper),"Cards added are treasure cards.");
  int assert8 = ASSERT((cardReturnValue == 0),"Card returned from cardEffect with the correct value of 0.");
  int assert9 = ASSERT(cardReturnValue == adventureFunctionReturn,"CardEffect and refactoredAdventurer return the same value");
//if all of this was verified, print that this test was successful
  if(assert1 + assert2 + assert3 + assert4 + assert5 + assert6 + assert8  == 0)
     printf("TEST SUCCESSFULLY COMPLETED\n");
//if a section could not be verified, print that this test was a faliure
  else
     printf("TEST FAILED\n");
  return 0;
}

