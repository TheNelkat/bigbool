#include "bb.h"

int main()
{
    char str1[1000], str2[1000];

    scanf("%s",str1);
    scanf( "%s",str2);

    int a =strlen(str1);
    int b = strlen(str2);
    
    vector* bb1 = BB_from_str(str1, a);
    vector* bb2 = BB_from_str(str2, b);

    printf("AND %s", bb_to_str(bb_and(bb1, bb2)));
    printf("OR %s", bb_to_str(bb_or(bb1, bb2)));
    printf("XOR %s", bb_to_str(bb_xor(bb1, bb2)));
    printf("AND %s", bb_to_str(bb_not(bb1)));
    printf("LEFT SHIFT %s",bb_to_str(left_shift(bb1,6)));
    printf("RIGHT SHIFT %s",bb_to_str(right_shift(bb1,10)));
    printf("CYCLE LEFT SHIFT %s",bb_to_str(cycle_left_shift(bb1,9)));
    printf("CYCLE RIGHT SHIFT %s",bb_to_str(cycle_right_shift(bb1,7)));
    
   // printf("%s", bb3);
}