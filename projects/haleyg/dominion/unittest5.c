#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int ASSERT(int b, char* s) {
  if (!b) {
    printf ("ASSERTION FAILURE: %s %s \n", s);
    return 1;
  }
  else{
    printf("%s\n",s);
    return 0;
  }
}

int main()
{
    printf("\nUNIT 5 TEST: SupplyCount function\n");
    int assert1,assert2;
    // Tests that supplyCount works properly
    struct gameState GameState;

    GameState.supplyCount[copper] = 2;
    assert1 = ASSERT(supplyCount(copper, &GameState) == 2, "Function returns the correct supply count.");
    
    GameState.supplyCount[copper] = 0;
    assert2 = ASSERT(supplyCount(copper,&GameState) == 0,"Function returns zero is the supply count is zero.");
   
   if(assert1 + assert2 == 0)
    printf("UNIT 5 TEST WAS SUCCESSFUL.\n");
   else
    printf("UNIT 5 TEST FAILED\n");
    return 0;
}
