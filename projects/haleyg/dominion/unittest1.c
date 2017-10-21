#include "stdlib.h"
#include "stdio.h"
#include "dominion.h"
#include "time.h"
#include "rngs.h"
#include "math.h"
#include "dominion_helpers.h"
#include "assert.h"

//This unit test covers getCost 
int ASSERT(int b, char* s, char* card) {
  if (!b) {
    printf ("ASSERTION FAILURE: %s %s \n", s,card);
    return 1;
  }
  else{
    printf("%s %s\n",s,card);
    return 0;
  }
}

int main(){
   printf("UNIT TEST 1: getCost function\n");
   int i;
   int testNum[26] = {0, 3, 4, 6, 2, 5, 8, 0, 6, 5, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};
   int testCards[26] = {curse, silver, gardens, adventurer, estate, duchy, province, copper, gold, council_room, feast, mine, remodel, smithy, village, baron, great_hall,minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
   int testCheck[26];
   char* cardnames[26] = {"curse","silver","gardens","adventurer","estate", "duchy", "province", "copper", "gold", "council_room", "feast", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
   for (i = 0; i < 26; i++){
      testCheck[i] = getCost(testCards[i]);
   }

   int assertCheck = 0;
   for(i = 0; i < 26; i++){
      assertCheck += ASSERT(testNum[i] == testCheck[i],"Function returned the correct value of the card: ",cardnames[i]);
   }
   int DNE = -5;
   int failCheck = ASSERT(getCost(DNE) == -1,"Function returns error when an invalid card is passed to it: ","DNE");
   if(assertCheck + failCheck == 0)
   	printf("UNIT 1 TEST WAS SUCCSESSFUL \n");
   else
        printf("UNIT 1 TEST FAILED \n");
   return 0;
}

