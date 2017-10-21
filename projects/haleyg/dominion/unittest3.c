#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"
#include <time.h>'

//Unit Test for buyCard
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

int main(){
  printf("\nUNIT 3 TEST: BuyCard function\n");
  struct gameState state;
  int s;
  int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  initializeGame(2, k, 2, &state);

  state.numBuys = 0;

  s = buyCard(5, &state);

  ASSERT(s == -1,"Correctly denied a buy when there are no buys.");

  state.numBuys = 5;

  state.coins = 0;

  s = buyCard(5, &state);

  ASSERT(s == -1,"Correctly denied a buy when there way not enough coins.");

  state.coins = 100;

  s = buyCard(5, &state);

  ASSERT(s == 0,"Correctly bought card when there was enough buys and coins.");

  printf("UNIT TEST 3 WAS SUCCESSFUL\n");
  return 0;
}
