#include "bigbool.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

#define LOG_ERR(msg) \
    printf(RED"%s:%d %s [ERR] %s\n"RESET, \
        __FILE__, __LINE__, __func__, msg); 


int test_add_func(vector* bb1, vector* bb2)
{   
    int err_flag=0;

    //TEST COPY
    bb_from_str(bb1,"0110100100101000001000111010101110010101100111101000");
    copy(bb1,bb2);
    char* str=bb_to_str(bb2);
    if(strcmp("0110100100101000001000111010101110010101100111101000",str))
    {
        LOG_ERR("Function copy does not work\n");
        err_flag++;
    }
    
    free(str);
    bb_zero(bb1);
    bb_zero(bb2);

    //TEST ZERO
    bb_from_str(bb1, "0001111011110010101011111101010");
    bb_zero(bb1);
    str=bb_to_str(bb1);
    if(strcmp("0",str))
    {
        LOG_ERR("Function bb_zero does not work\n");
        err_flag++;
    }
    free(str);

    return err_flag;
}

int test_conversion(vector* bb)
{
    int err_flag=0;
    //min len
    bb_from_str(bb,"0");
    char* str=bb_to_str(bb);
    if(strcmp("0",str))
    {
        LOG_ERR("bb_from_str->bb_to_str doesn't work\n");
        printf("0->%s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);


    //len<byte
    bb_from_str(bb,"1010110");
    str=bb_to_str(bb);
    if(strcmp("1010110",str))
    {
        LOG_ERR("bb_from_str->bb_to_str doesn't work\n");
        printf("1010110->%s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);


    //len%8==0
    bb_from_str(bb,"110111101000101110100001");
    str=bb_to_str(bb);
    if(strcmp("110111101000101110100001",str))
    {
        LOG_ERR("bb_from_str->bb_to_str doesn't work\n");
        printf("110111101000101110100001->%s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);


    //len%8!=0
    bb_from_str(bb,"1001011011010111110111000101010001101010011000010111");
    str=bb_to_str(bb);
    if(strcmp("1001011011010111110111000101010001101010011000010111",str))
    {
        LOG_ERR("bb_from_str->bb_to_str doesn't work\n");
        printf("1001011011010111110111000101010001101010011000010111->%s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);


    //len==MAX_PARTS
    bb_from_str(bb,"1111111111000000000111111110101010011101110100000000110101001010110010101011001111111111111111111000000000000000101010101110111001101010111110101110101011111011");
    str=bb_to_str(bb);
    if(strcmp("1111111111000000000111111110101010011101110100000000110101001010110010101011001111111111111111111000000000000000101010101110111001101010111110101110101011111011",str))
    {
        LOG_ERR("bb_from_str->bb_to_str doesn't work\n");
        printf("1111111111000000000111111110101010011101110100000000110101001010110010101011001111111111111111111000000000000000101010101110111001101010111110101110101011111011->\n%s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);

    return err_flag;

}

int test_uint64(vector* bb)
{
    int err_flag=0;

    bb_from_uint64(bb, 0);
    char* str=bb_to_str(bb);

    if(strcmp("0",str))
    {
        LOG_ERR("f1");
        err_flag++;
    }

    free(str);
    bb_zero(bb);

    bb_from_uint64(bb, 123);
    str=bb_to_str(bb);
    
    if(strcmp("01111011",str))
    {
        LOG_ERR("f2");
        err_flag++;
    }

    free(str);
    bb_zero(bb);


    bb_from_uint64(bb,677843965);
    str=bb_to_str(bb);
    
    if(strcmp("00101000011001110001001111111101",str))
    {
        LOG_ERR("f3");
        err_flag++;
    }

    free(str);
    bb_zero(bb);


    bb_from_uint64(bb,10064622730194380714);
    str=bb_to_str(bb);

    if(strcmp("1000101110101100101110010000110001100111100011101110011110101010",str))
    {
        LOG_ERR("f4");
        err_flag++;
    }

    free(str);
    bb_zero(bb);

    return err_flag;
}

int test_not(vector* bb)
{
    int err_flag=0;

    //len<byte
  
    bb_from_str(bb, "101011");
    bb_not(bb);
    char* str = bb_to_str(bb);
    if(strcmp("010100", str))
    {
        LOG_ERR("bb_not doesn't work \n");
        printf("~101011 != 010100\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);


    //len % byte == 0
            
    bb_from_str(bb,"1110101101111011");
    bb_not(bb);
    str = bb_to_str(bb);

    if(strcmp("0001010010000100", str))
    {
        LOG_ERR("bb_not doesn't work \n");
        printf("~1110101101111011 != 0001010010000100\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);


    //len%byte != 0
            
    bb_from_str(bb, "1001011011010111110111000101010001101010011000010111");
    bb_not(bb);
    str = bb_to_str(bb);

    if(strcmp("0110100100101000001000111010101110010101100111101000", str))
    {
        LOG_ERR("bb_not doesn't work \n");
        printf("~001011011010111110111000101010001101010011000010111 != 0110100100101000001000111010101110010101100111101000\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);

   
   //max len
            
    bb_from_str(bb, "1111111111000000000111111110101010011101110100000000110101001010110010101011001111111111111111111000000000000000101010101110111001101010111110101110101011111011");
    bb_not(bb);
    str = bb_to_str(bb);

    if(strcmp("0000000000111111111000000001010101100010001011111111001010110101001101010100110000000000000000000111111111111111010101010001000110010101000001010001010100000100", str))
    {
        LOG_ERR("bb_not doesn't work \n");
        printf("~1111111111000000000111111110101010011101110100000000110101001010110010101011001111111111111111111000000000000000101010101110111001101010111110101110101011111011 !=\n0000000000111111111000000001010101100010001011111111001010110101001101010100110000000000000000000111111111111111010101010001000110010101000001010001010100000100\n output %s\n",str);
        err_flag++;
    }

    
    free(str);
    bb_zero(bb);

    return err_flag;
}

int test_and(vector* bb1, vector* bb2)
{
    int err_flag=0;

    //len<byte
    bb_from_str(bb1, "1110101");
    bb_from_str(bb2, "0010110");

    bb_and(bb1, bb2);
    char* str = bb_to_str(bb1);

     if(strcmp("0010100", str))
    {
        LOG_ERR("bb_and doesn't work \n");
        printf("1110101 & 0010110 != 0010100\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);


    //len % byte == 0
  
    bb_from_str(bb1, "110111101000101110100001");
    bb_from_str(bb2, "001011101101110111010011");

    bb_and(bb1, bb2);
    str = bb_to_str(bb1);

     if(strcmp("000011101000100110000001", str))
    {
        LOG_ERR("bb_and doesn't work \n");
        printf("110111101000101110100001 & 001011101101110111010011 != 000011101000100110000001\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);


    //different len

    bb_from_str(bb1, "11110110101100001010111110001010100101111111100");
    bb_from_str(bb2, "010101101110011000");

    bb_and(bb1, bb2);
    str = bb_to_str(bb1);

     if(strcmp("00000000000000000000000000000010100101110011000", str))
    {
        LOG_ERR("bb_and doesn't work \n");
        printf("11110110101100001010111110001010100101111111100 & 010101101110011000 != 00000000000000000000000000000010100101110011000\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);


    //max len
    
    bb_from_str(bb1, "0101010010111111111111101000000000011111111111110111111111100101100101001111111111111111111100001010101010100101011111111110000101100011100010001000000111001000");
    bb_from_str(bb2, "0000001110001010111101100010101111100000000000000000000011110000010101100001010101010111111111111100011111111111111111111111000000111001010110010001101011100111");

    bb_and(bb1, bb2);
    str = bb_to_str(bb1);

     if(strcmp("0000000010001010111101100000000000000000000000000000000011100000000101000001010101010111111100001000001010100101011111111110000000100001000010000000000011000000", str))
    {
        LOG_ERR("bb_and doesn't work \n");
        printf("0101010010111111111111101000000000011111111111110111111111100101100101001111111111111111111100001010101010100101011111111110000101100011100010001000000111001000 &\n0000001110001010111101100010101111100000000000000000000011110000010101100001010101010111111111111100011111111111111111111111000000111001010110010001101011100111 !=\n0000000010001010111101100000000000000000000000000000000011100000000101000001010101010111111100001000001010100101011111111110000000100001000010000000000011000000\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);

    return err_flag;
}

int test_or(vector* bb1, vector* bb2)
{
    int err_flag=0;

    //len<byte
  
    bb_from_str(bb1, "0111101");
    bb_from_str(bb2, "1101000");

    bb_or(bb1, bb2);
    char* str = bb_to_str(bb1);

     if(strcmp("1111101", str))
    {
        LOG_ERR("bb_or doesn't work \n");
        printf("0111101 | 1101000 != 1111101\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);


    //len == byte
    
    bb_from_str(bb1, "1111110100101000");
    bb_from_str(bb2, "1101010000010001");

    bb_or(bb1, bb2);
    str = bb_to_str(bb1);

     if(strcmp("1111110100111001", str))
    {
        LOG_ERR("bb_or doesn't work \n");
        printf("1111110100101000 | 1101010000010001 != 1111110100111001\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);


    //different len

    bb_from_str(bb1, "0001111011110010101011101000010");
    bb_from_str(bb2, "110101000");

    bb_or(bb1, bb2);
    str = bb_to_str(bb1);

     if(strcmp("0001111011110010101011111101010", str))
    {
        LOG_ERR("bb_or doesn't work \n");
        printf("0001111011110010101011101000010 | 110101000 != 0001111011110010101011111101010\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);

    //max len

    bb_from_str(bb1, "1111101001011111111111111111110000010110101110000000000011111111111010101100000001010100101100000000000000001111111111111111111111011111110000110011010000111110");
    bb_from_str(bb2, "1101010110110000010110110010001010101101001111101001100110101101110101000100100000000000000010111010010000101110101001111111111111010110000000000000111111111101");

    bb_or(bb1, bb2);
    str = bb_to_str(bb1);

     if(strcmp("1111111111111111111111111111111010111111101111101001100111111111111111101100100001010100101110111010010000101111111111111111111111011111110000110011111111111111", str))
    {
        LOG_ERR("bb_or doesn't work \n");
        printf("1111101001011111111111111111110000010110101110000000000011111111111010101100000001010100101100000000000000001111111111111111111111011111110000110011010000111110 |\n 1101010110110000010110110010001010101101001111101001100110101101110101000100100000000000000010111010010000101110101001111111111111010110000000000000111111111101 !=\n1111111111111111111111111111111010111111101111101001100111111111111111101100100001010100101110111010010000101111111111111111111111011111110000110011111111111111\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);

    return err_flag;
}

int test_xor(vector* bb1, vector* bb2)
{
    int err_flag=0;

    //len<byte
   
    bb_from_str(bb1, "100011");
    bb_from_str(bb2, "011101");

    bb_xor(bb1, bb2);
    char* str = bb_to_str(bb1);

     if(strcmp("111110", str))
    {
        LOG_ERR("bb_xor doesn't work \n");
        printf("100011 ^ 011101 != 111110\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);


    //len == byte
              
    bb_from_str(bb1, "110000011101011010111100");
    bb_from_str(bb2, "111000100011011101010000");

    bb_xor(bb1, bb2);
    str = bb_to_str(bb1);

     if(strcmp("001000111110000111101100", str))
    {
        LOG_ERR("bb_xor doesn't work \n");
        printf("110000011101011010111100 ^ 111000100011011101010000 != 001000111110000111101100\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);


    //different len

    bb_from_str(bb1, "101000001111010111000111010111001");
    bb_from_str(bb2, "001011110110");

    bb_xor(bb1, bb2);
    str= bb_to_str(bb1);

     if(strcmp("101000001111010111000110001001111", str))
    {
        LOG_ERR("bb_xor doesn't work \n");
        printf("101000001111010111000111010111001 ^ 001011110110 != 101000001111010111000110001001111\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);

    //max len

    bb_from_str(bb1, "1111101001011111111111111111110000010110101110000000000011111111111010101100000001010100101100000000000000001111111111111111111111011111110000110011010000111000");
    bb_from_str(bb2, "1010011011111111111110101001111111110001101010010100000000000000110100101111111111001011111111100000011100001010101000000110011111110000101101010001111010100011");

    bb_xor(bb1, bb2);
    str = bb_to_str(bb1);

     if(strcmp("0101110010100000000001010110001111100111000100010100000011111111001110000011111110011111010011100000011100000101010111111001100000101111011101100010101010011011", str))
    {
        LOG_ERR("bb_xor doesn't work \n");
        printf("1111101001011111111111111111110000010110101110000000000011111111111010101100000001010100101100000000000000001111111111111111111111011111110000110011010000111000\n ^ 1010011011111111111110101001111111110001101010010100000000000000110100101111111111001011111111100000011100001010101000000110011111110000101101010001111010100011 !=\n0101110010100000000001010110001111100111000100010100000011111111001110000011111110011111010011100000011100000101010111111001100000101111011101100010101010011011\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);

    return err_flag;
}


int test_shift_same(vector* bb)
{
    int err_flag=0;

    //shift%8 == 0
    bb_from_str(bb,"1111111111111110000010110101110000");
    right_shift_same(bb, 16);

    char* str = bb_to_str(bb);

    if(strcmp("0000000000000000111111111111111000", str))
    {
        LOG_ERR("right_shift_same doesn't work\n");
        printf("16->1111111111111110000010110101110000 != 0000000000000000111111111111111000\n output %s\n",str);
        err_flag++;
    }
    
    free(str);
    bb_zero(bb);
    

    //shift%8 != 0
    bb_from_str(bb,"11111111111111000001011010111000000000001111111111101010");
    right_shift_same(bb, 23);
    str = bb_to_str(bb);

    if(strcmp("00000000000000000000000111111111111110000010110101110000", str))
    {
        LOG_ERR("right_shift_same doesn't work\n");
        printf("23->11111111111111000001011010111000000000001111111111101010 !=\n00000000000000000000000111111111111110000010110101110000\n output %s\n",str);
        err_flag++;
    }
    
    free(str);
    bb_zero(bb);
    

    //shift>len
    bb_from_str(bb,"111101011111110111110100110011111111111111110");
    right_shift_same(bb, 47);
    str = bb_to_str(bb);

    if(strcmp("000000000000000000000000000000000000000000000", str))
    {
        LOG_ERR("right_shift_same doesn't work\n");
        printf("47->111101011111110111110100110011111111111111110 !=\n000000000000000000000000000000000000000000000\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);
    


     //shift%8 == 0
    bb_from_str(bb,"1111110000010110101110000000000011111");
    left_shift_same(bb, 8);
    str = bb_to_str(bb);

    if(strcmp("0001011010111000000000001111100000000", str))
    {
        LOG_ERR("left_shift_same doesn't work\n");
        printf("8<-1111110000010110101110000000000011111 !=\n0001011010111000000000001111100000000\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);

    //shift%8 != 0
    bb_from_str(bb,"1101011011110000010011111010101111000100001");
    left_shift_same(bb,13);
    str= bb_to_str(bb);

    if(strcmp("0000100111110101011110001000010000000000000", str))
    {
        LOG_ERR("left_shift_same doesn't work\n");
        printf("13<-1101011011110000010011111010101111000100001 !=\n0000100111110101011110001000010000000000000\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);

    //shift>len
    bb_from_str(bb,"111111111100000101101011100000011");
    left_shift_same(bb,50);
    str = bb_to_str(bb);

    if(strcmp("000000000000000000000000000000000", str))
    {
        LOG_ERR("right_shift_same doesn't work\n");
        printf("50<-111111111100000101101011100000011 != 000000000000000000000000000000000\n output %s\n",str);
        err_flag++;
    }

    bb_zero(bb);
    free(str);

    return err_flag;
}


int test_shift_dif(vector* bb)
{
    int err_flag=0;

    //shift%8 == 0
    bb_from_str(bb,"1111111111111110000010110101110000");
    right_shift_dif(bb,16);

    char* str = bb_to_str(bb);

    if(strcmp("111111111111111000", str))
    {
        LOG_ERR("right_shift_dif doesn't work\n");
        printf("16->1111111111111110000010110101110000 != 111111111111111000\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);


    //shift%8 != 0
    bb_from_str(bb,"11111111111111000001011010111000000000001111111111101010");
    right_shift_dif(bb,23);
    str = bb_to_str(bb);

    if(strcmp("111111111111110000010110101110000", str))
    {
        LOG_ERR("right_shift_dif doesn't work\n");
        printf("23-> 11111111111111000001011010111000000000001111111111101010 !=\n111111111111110000010110101110000\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);


    //shift>len
    bb_from_str(bb,"111101011111110111110100110011111111111111110");
    right_shift_dif(bb, 47);
    str = bb_to_str(bb);

    if(strcmp("0", str))
    {
        LOG_ERR("right_shift_dif doesn't work\n");
        printf("47->111101011111110111110100110011111111111111110 != 0\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);


    //shift%8 == 0
    bb_from_str(bb,"1111110000010110101110000000000011111");
    left_shift_dif(bb, 8);
    str = bb_to_str(bb);

    if(strcmp("111111000001011010111000000000001111100000000", str))
    {
        LOG_ERR("left_shift_dif doesn't work\n");
        printf("8<-1111110000010110101110000000000011111 !=\n111111000001011010111000000000001111100000000\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);


    //shift%8 != 0
    bb_from_str(bb,"1000111101101000010011111010101111000100001");
    left_shift_dif(bb,13);
    str = bb_to_str(bb);

    if(strcmp("10001111011010000100111110101011110001000010000000000000", str))
    {
        LOG_ERR("left_shift_dif doesn't work\n");
        printf("13<-1000111101101000010011111010101111000100001 !=\n10001111011010000100111110101011110001000010000000000000\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);


    //shift>len
    bb_from_str(bb,"111111111100000101101011100000011");
    left_shift_dif(bb,50);
    str = bb_to_str(bb);
    
    if(strcmp("11111111110000010110101110000001100000000000000000000000000000000000000000000000000", str))
    {
        LOG_ERR("left_shift_dif doesn't work\n");
        printf("50<-111111111100000101101011100000011 !=\n11111111110000010110101110000001100000000000000000000000000000000000000000000000000\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb);

    return err_flag;
}

int test_cycle(vector*bb1, vector* bb2)
{
    int err_flag=0;

    //shift%8 == 0
    bb_from_str(bb1,"10010000101111111111111111111111011111");
    cycle_right(bb1, bb2, 16);

    char* str = bb_to_str(bb1);

    if(strcmp("11111111110111111001000010111111111111", str))
    {
        LOG_ERR("cycle_right doesn't work\n");
        printf("16->10010000101111111111111111111111011111 !=\n11111111110111111001000010111111111111\n output %s\n",str);
        err_flag++;
    }
    
    free(str);
    bb_zero(bb1);
    bb_zero(bb2);
    

    //shift%8 != 0
    bb_from_str(bb1,"111111111000001011010111000000000001111111111101010");
    cycle_right(bb1,bb2,27);
    str = bb_to_str(bb1);

    if(strcmp("000000000001111111111101010111111111000001011010111", str))
    {
        LOG_ERR("cycle_right doesn't work\n");
        printf("27->111111111000001011010111000000000001111111111101010 !=\n000000000001111111111101010111111111000001011010111\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);
    

    //shift>len
    bb_from_str(bb1,"1100000001010100101100000000000000001111111111111111");
    cycle_right(bb1,bb2,73);
    str = bb_to_str(bb1);

    if(strcmp("0000011111111111111111100000001010100101100000000000", str))
    {
        LOG_ERR("cycle_right doesn't work\n");
        printf("73->1100000001010100101100000000000000001111111111111111 !=\n0000011111111111111111100000001010100101100000000000\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);
    


     //shift%8 == 0
    bb_from_str(bb1,"1000010111010100111111111111101011000");
    cycle_left(bb1,bb2, 8);
    str = bb_to_str(bb1);

    if(strcmp("1101010011111111111110101100010000101", str))
    {
        LOG_ERR("cycle_left doesn't work\n");
        printf("8<-1000010111010100111111111111101011000 !=\n1101010011111111111110101100010000101\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);
    


    //shift%8 != 0
    bb_from_str(bb1,"111010100111111111111101011000000000");
    cycle_left(bb1,bb2,15);
    str = bb_to_str(bb1);

    if(strcmp("111111101011000000000111010100111111", str))
    {
        LOG_ERR("cycle_left doesn't work\n");
        printf("15<-111010100111111111111101011000000000 !=\n11111101011000000000111010100111111\n output %s\n",str);
        err_flag++;
    }
    
    free(str);
    bb_zero(bb1);
    bb_zero(bb2);
    

    //shift>len
    bb_from_str(bb1,"11111111111111000001011010111000000000001111111111101010");
    cycle_left(bb1,bb2,103);
    str = bb_to_str(bb1);

    if(strcmp("11110101011111111111111000001011010111000000000001111111", str))
    {
        LOG_ERR("cycle_left doesn't work\n");
        printf("103<-11111111111111000001011010111000000000001111111111101010 !=\n11110101011111111111111000001011010111000000000001111111\n output %s\n",str);
        err_flag++;
    }

    free(str);
    bb_zero(bb1);
    bb_zero(bb2);
    

    return err_flag;     
}


int xor_operations(vector* a, vector* na, vector* b, vector* nb)
{
    int err_flag=0;


    bb_random(a);
    bb_random(b);

    if(a->last_byte*8 + a->last_bit >= b->last_byte*8 +b->last_bit)
    {
        b->last_byte=a->last_byte;
        b->last_bit=a->last_bit;
    }
    else
    {
        a->last_byte=b->last_byte;
        a->last_bit=b->last_bit;
    }

    //(~a&b) | (a&~b)
    copy(a,na);
    bb_not(na);//a=~na

    copy(b,nb);
    bb_not(nb);//b=~nb;

    bb_and(na,b);
    bb_and(nb,a);

    bb_or(na,nb);

    char* str1=bb_to_str(na);

    bb_xor(a,b);
    char* str2=bb_to_str(a);

    if(strcmp(str1,str2))
    {
        LOG_ERR("(~a&b) | (a&~b) != a^b\n");
        err_flag++;
    }
    
    bb_zero(a);
    bb_zero(na);
    bb_zero(b);
    bb_zero(nb);
    free(str1);
    free(str2);

    return err_flag;
}


int test_errors(vector* bb)
{
    int err_flag=0;

    if(bb_from_str(bb,"1234566789")!=BAD_STR)
    {
        LOG_ERR("Incorrect BAD_STR\n");
        err_flag++;
    }

    if(bb_from_str(bb,"01010100101111111111111010000000000111111111111101111111111001011001010011111111111111111111000010101010101001010111111111100001011000111000100010000001110010001101")!=BAD_STR)
    {
        LOG_ERR("Incorrect BAD_STR\n");
        err_flag++;
    }

    bb_from_str(bb, "110100111010");
    if(right_shift_same(bb,-23)!=BAD_SHIFT)
    {
        LOG_ERR("Incorrect BAD_SHIFT\n");
        err_flag++;
    }

    if(left_shift_dif(bb,167)!=BAD_SHIFT)
    {
        LOG_ERR("Incorrect BAD_SHIFT\n");
        err_flag++;
    }

    return err_flag;
}

int main()
{
    int err_flag=0;

    vector* bb1=calloc(1,sizeof(vector));
    vector* bb2=calloc(1,sizeof(vector));
    vector* bb3=calloc(1,sizeof(vector));
    vector* bb4=calloc(1,sizeof(vector));
    

    err_flag+=test_not(bb1);
    err_flag+=test_and(bb1,bb2);
    err_flag+=test_or(bb1,bb2);
    err_flag+=test_xor(bb1,bb2);
    err_flag+=test_shift_same(bb1);
    err_flag+=test_shift_dif(bb1);
    err_flag+=test_cycle(bb1,bb2);

    err_flag+=test_conversion(bb1);
    err_flag+=test_uint64(bb1);
    err_flag+=test_add_func(bb1, bb2);
    err_flag+=test_errors(bb1);

    int count=10000000;
    while(count)
    {
        err_flag+=xor_operations(bb1,bb2,bb3,bb4);
        count--;
    }

    if(err_flag>0)
    {
        printf(RED"Failed %d tests\n"RESET, err_flag);
    }
    else
    {
        printf(GREEN"[OK] All ok!\n"RESET);
    }

    free(bb1);
    free(bb2);
    free(bb3);
    free(bb4);
    
    return 0;    
}