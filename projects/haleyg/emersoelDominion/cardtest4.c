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
  printf("\nStarting Card Test 4: Outpost\n");

//Initialize the gamestate
 int players, player,opponent,opponentHandCount,opponentDeckCount, numActions, handCount, deckCount, seed, coins, numBuys;
 struct gameState GameState;
 int k[10] = {minion, smithy, gardens, tribute, baron, adventurer, cutpurse, mine, embargo, outpost};
 seed = 10;
 players = 2;
 initializeGame(players, k, seed, &GameState);
 player = 0;
 opponent = 1;
 //set gamestate of opponent
 GameState.handCount[opponent] = 1;
 GameState.deckCount[opponent] = 1;
 opponentHandCount = GameState.handCount[opponent];
 opponentDeckCount = GameState.deckCount[opponent];

 GameState.whoseTurn = player;
//Set gamestate to player 1's turn
 GameState.hand[player][0] = outpost;
 GameState.hand[player][1] = adventurer;
//Put the outpost card in their hand
 GameState.deckCount[player] = 3;
//set their decksize to three cards
 GameState.coins = 0;
 GameState.numBuys = 1;
//Save the current settings of the gamestate to check against the gamestate after the outpost card has been played
 numActions = GameState.numActions;
 deckCount = GameState.deckCount[player];
 handCount = GameState.handCount[player];
 coins = GameState.coins;
 numBuys = GameState.numBuys;
//Play the outpost card
 int cardReturnValue = cardEffect(outpost, adventurer, 0, 0, &GameState, 0, NULL);

//Verify the handCount decreased by 1
  int assert1 = ASSERT((handCount - 1  == GameState.handCount[0]), "Outpost -1 cards from players hand.");
//Verify the number of actions were not altered
  int assert2 = ASSERT(numActions == GameState.numActions, "Number of actions remained the same.");
//Verify the deck was decreased by 3 cards
  int assert3 = ASSERT(deckCount == GameState.deckCount[player],"deck size was unchanged.");
  int assert7 = ASSERT(coins + getCost( handCard(adventurer, &GameState))== GameState.coins, "Correct number of coins were added after adventurer discard");
  int assert8 = ASSERT(numBuys == GameState.numBuys,"Correct +1 to buys.");
  int scores[2]= {player,opponent}; 
  ASSERT(getWinners(scores,&GameState) == 0,"scoreUnaltered");
//Switch to opponent to check for any unwanted alteractions were made
 GameState.whoseTurn = opponent;
//Verify opponent's handcount was not altered
  int assert4 = ASSERT((opponentHandCount == GameState.handCount[opponent]),"Oppenents's handCount was not altered.");
//Verify opponent's deckCount was not altered
  int assert5 = ASSERT((opponentDeckCount == GameState.deckCount[opponent]),"Oppenents's deckCount was not altered.");
//Verify return value of card
  int assert6 = ASSERT((cardReturnValue == 0),"Card returned from cardEffect with the correct value of 0.");
//if all of this was verified, print that this test was successful
  if(assert1 + assert2 + assert3 + assert4 + assert5 + assert6 + assert7 + assert8 == 0)
     printf("TEST SUCCESSFULLY COMPLETED\n");
//if a section could not be verified, print that this test was a faliure
  else
     printf("TEST FAILED\n");
  return 0;
}
