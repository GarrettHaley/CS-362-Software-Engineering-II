#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


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

int main()
{
    printf("\nUNIT 2 TEST: Shuffle function\n");
    int player = 0;
    int assert1, assert2, assert3;
    // Create gamestate
    struct gameState GameState;
    GameState.deckCount[player] = 3;
    GameState.deck[player][0] = copper;
    GameState.deck[player][1] = silver;
    GameState.deck[player][2] = gold;

    //check if correct gamestate will produce the correct return value
    assert1 = ASSERT(shuffle(player, &GameState)==0,"Function successful returned with correct outputs given the correct inputs.");
    
    int cardsSet[MAX_DECK] = {0};
    int i;
  
    for (i=0 ; i<3 ; i++)
    {
        cardsSet[GameState.deck[player][i]] = 1;
    }
    //check if all the cards are still there
    assert2 = ASSERT(cardsSet[copper] && cardsSet[silver] && cardsSet[gold],"all cards remained in set after shuffle.");

    GameState.deckCount[player] = 0;
    //check if incorrect gamestate will produce the error return value
    assert3 = ASSERT(shuffle(player, &GameState) == -1, "Function successfully returned with error when incorrect input was given.");
  

    if(assert1+assert2+assert3 ==0)
    	printf ("UNIT 2 TEST WAS SUCCESSFULL.\n");
    else
  	printf("UNIT 2 TEST WAS UNSUCCESSFUL.\n");

    return 0;
}
