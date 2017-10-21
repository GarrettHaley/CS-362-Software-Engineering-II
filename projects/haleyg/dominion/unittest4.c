#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"
#include <time.h>

// Unit Test for isGameOver() function
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
  printf("\nUNIT 4 TEST: isGameOver function\n");
  struct gameState state;
  int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  initializeGame(2, k, 2, &state);
  state.supplyCount[province] = 5;


  int a1 =  ASSERT(isGameOver(&state)== 0,"Function correctly identified when the game should not end.");

  state.supplyCount[province] = 0;

  int a2 =  ASSERT(isGameOver(&state) == 1,"Function correctly identified when the game should end.");
  if(a1+a2 == 0)
     printf("UNIT 4 TEST WAS SUCCESSFUL\n");
  else
     printf("UNIT 4 TEST FAILED\n"); 
  return 0;
}
