#include "bigbool.h"

/**
 * 
 * ADDITIONAL FUNCTIONS
 * 
 */

int bb_random(vector* bb)
{
    if(bb==NULL)
    {
        return EMPTY_VECTOR;
    }

    bb->last_byte=rand() % MAX_PARTS;
    bb->last_bit=rand() %8;

    for(int i=0;i<=bb->last_byte;i++)
    {
        bb->parts[i]=rand()%256;
    }
   
    for(int i=8;i>bb->last_bit;i--)
    {
        bb->parts[bb->last_byte]&(0<<i);
    }

    return ERR_OK;
}

int bb_zero(vector* bb)
{
    if(bb==NULL)
    {
        return EMPTY_VECTOR;
    }

    for(int i=0; i<MAX_PARTS;i++)
    {
        bb->parts[i]=0;
    }
    bb->last_byte=0;
    bb->last_bit=1;

    return ERR_OK;
}

int copy(vector* org, vector* cop)
{
    if(org==NULL || cop==NULL)
    {
        return EMPTY_VECTOR;
    }

    cop->last_byte = org->last_byte;
    cop->last_bit = org->last_bit;

    for(int i=0; i<=org->last_byte; i++)
    {
        cop->parts[i]=org->parts[i];
    }

    return ERR_OK;
}
 
/**
 * 
 * CONVERSSION
 * 
 */ 

int bb_from_str(vector* bb, char* str)
{
    if(bb==NULL)
    {
        return EMPTY_VECTOR;
    }

    if (str==NULL)
    {
        return BAD_STR;
    }

    int len = strlen(str);

    if(len>MAX_PARTS*8)
    {
        return BAD_STR;
    }

    for(int i = 0; i<len; i++)  
    {
        if(str[i] !='0' && str[i] !='1')
        {
            return BAD_STR;
        }
    }

    
     if(len%8 == 0)
    {
        bb->last_byte = (len/8)-1;
        bb->last_bit = 8; 
    }
    else
    {
        bb->last_byte = len/8;
        bb->last_bit = len%8;
    }


    int byte = bb->last_byte;
    int bit = bb->last_bit;

    //file the vector from the lastbyte

    for(int i =0; i<len; i++)
    {
        bb->parts[byte]<<= 1;
        bb->parts[byte]|= (str[i] == '0') ? 0 : 1;
        bit--;
        if(bit == 0)
        {
            byte--;
            bit=8;
        }
    }

    return ERR_OK;
}

char* bb_to_str(vector* bb)
{
    int len_str=(bb->last_byte)*8 + bb->last_bit;
    char* str= (char*)calloc(len_str+1, sizeof(char));

    if(bb==NULL)
    {
        return str;
    }

    if(str==NULL)
    {
        return str;
    }

    //file the string from the end
    int num_str=len_str-1;
    str[len_str]='\0';

    for(int i=0; i<bb->last_byte; i++)
    {
        for(int b=0; b<8;b++)
        {
            if(bb->parts[i]&(1<<b))
            {
                str[num_str]=1;
            }
            else
            {
                str[num_str]=0;
            }
            str[num_str]+='0';
            num_str--;
        }
    }

    //sift off the extra part of the vector 
    for(int b=0; b < bb->last_bit; b++)
    {
        if(bb->parts[bb->last_byte]&(1<<b))
        {
            str[num_str]= 1;
        }
        else
        {
            str[num_str]= 0;
        }
        str[num_str]+='0';
        num_str--;
    }
    return str;
}

int bb_from_uint64(vector* bb, uint64_t num)
{
    if(bb==NULL)
    {
        return EMPTY_VECTOR;
    }

    if(num==0)
    {
        return bb_zero(bb);
    }

    int i=0;
    while(num)
    {
        bb->parts[i]|=num;
        num>>=8u;
        i++;
    }
    bb->last_byte=i;
    bb->last_bit=0;

    return ERR_OK;
}

/**
 * 
 * LOGICAL OPERATIONS
 * 
 */

int bb_not(vector* bb)
{
      if(bb == NULL)
    {
        return EMPTY_VECTOR;
    }

    for(int i=0;i<=bb->last_byte;i++)
    {
        bb->parts[i]= ~ bb->parts[i];
    }
    return ERR_OK;
}

int bb_and(vector* bb1, vector* bb2)
{
    if(bb1 == NULL || bb2 == NULL)
    {
        return EMPTY_VECTOR;
    }

    if(bb1->last_byte*8+bb1->last_bit<bb2->last_byte*8+bb2->last_bit)
    {
        
        bb1->last_byte = bb2->last_byte;
        bb1->last_bit = bb2->last_bit;
    }

    for(int i=0;i<=bb1->last_byte;i++)
    {
        bb1->parts[i]&=bb2->parts[i];
    }

    return ERR_OK;
}

int bb_or(vector* bb1, vector* bb2)
{
    if(bb1 == NULL || bb2 == NULL)
    {
        return EMPTY_VECTOR;
    }

    if(bb1->last_byte*8+bb1->last_bit<bb2->last_byte*8+bb2->last_bit)
    {
        
        bb1->last_byte = bb2->last_byte;
        bb1->last_bit = bb2->last_bit;
    }

    for(int i=0;i<=bb1->last_byte;i++)
    {
        bb1->parts[i]|=bb2->parts[i];
    }

    return ERR_OK;
}

int bb_xor(vector* bb1, vector* bb2)
{
    if(bb1 == NULL || bb2 == NULL)
    {
        return EMPTY_VECTOR;
    }

    if(bb1->last_byte*8+bb1->last_bit<bb2->last_byte*8+bb2->last_bit)
    {
        
        bb1->last_byte = bb2->last_byte;
        bb1->last_bit = bb2->last_bit;
    }

    for(int i=0;i<=bb1->last_byte;i++)
    {
        bb1->parts[i]^=bb2->parts[i];
    }

    return ERR_OK;
}

/**
 * 
 * SHIFTS
 * 
 */

int right_shift_same(vector* bb, int shift)
{
    if(bb== NULL)
    {
        return EMPTY_VECTOR;
    }

    if(shift<1)
    {
        return BAD_SHIFT;
    }

    if((bb->last_byte*8+bb->last_bit)<=shift)
    {
        for(int i=0; i<=bb->last_byte; i++)
        {
            bb->parts[i] = 0;
        }
        return ERR_OK;
    }

    int def_byte = ((bb->last_byte+1) *8 - shift)/8;
    uint8_t byte = 0;

    for(int i=0; i<=def_byte; i++)
    {
        byte = bb->parts[shift/8+1 + i]<<(8-(shift%8));
        bb->parts[i]=bb->parts[shift/8 + i];
        bb->parts[i]>>=shift%8;
        bb->parts[i]|=byte ;
    }
    
    for(int i = def_byte+1; i<=bb->last_byte; i++)
    {
        bb->parts[i]=0;
    }

    return ERR_OK;
}

int right_shift_dif(vector* bb, int shift)
{
    if(bb== NULL)
    {
        return EMPTY_VECTOR;
    }

    if(shift<1)
    {
        return BAD_SHIFT;
    }

    if((bb->last_byte*8+bb->last_bit)<=shift)
    {
        bb->parts[0]=0;
        bb->last_byte=0;
        bb->last_bit=1;
        return ERR_OK;
    }

    int def_byte = ((bb->last_byte+1) *8 - shift)/8 ;
    uint8_t byte = 0;

    for(int i=0; i<=def_byte; i++)
    {
        byte = bb->parts[shift/8+1 + i]<<(8-(shift%8));
        bb->parts[i]=bb->parts[shift/8 + i];
        bb->parts[i]>>=shift%8;
        bb->parts[i]|=byte;
    }
    
    int new_len=(bb->last_byte*8)+bb->last_bit-shift;

    bb->last_byte= new_len/8;
    bb->last_bit= new_len%8;

    return ERR_OK;
}

int left_shift_same(vector* bb, int shift)
{
    if(bb== NULL)
    {
        return EMPTY_VECTOR;
    }

    if(shift<1)
    {
        return BAD_SHIFT;
    }

    int def_byte = bb->last_byte -(((bb->last_byte+1) *8 - shift)/8);
    if(shift%8==0)
    {
        def_byte++;
    }
    uint8_t byte = 0;

    for(int i=bb->last_byte; i>=def_byte; i--)
    {
        byte = bb->parts[i-def_byte-1]>>(8-(shift%8));
        bb->parts[i]=bb->parts[i-def_byte];
        bb->parts[i]<<=shift%8;
        bb->parts[i]|=byte ;
    }
    
    for(int i=0; i<def_byte; i++)
    {
        bb->parts[i]=0;
    }

    return ERR_OK;
}

int left_shift_dif(vector* bb, int shift)
{
    if(bb == NULL)
    {
        return EMPTY_VECTOR;
    }
    if(shift <1 || (bb->last_byte*8)+bb->last_bit+shift > 160)
    {
        return BAD_SHIFT;
    }
    
    int new_len= (bb->last_byte*8)+bb->last_bit+shift;

    bb->last_byte= new_len/8;
    bb->last_bit= new_len%8;
    
    int def_byte = bb->last_byte -(((bb->last_byte+1) *8 - shift)/8);
    if(shift%8==0)
    {
        def_byte++;
    }
    uint8_t byte = 0;

    for(int i=bb->last_byte; i>=def_byte; i--)
    {
        byte = bb->parts[i-def_byte-1]>>(8-(shift%8));
        bb->parts[i]=bb->parts[i-def_byte];
        bb->parts[i]<<=shift%8;
        bb->parts[i]|=byte ;
    }
    
    for(int i=0; i<def_byte; i++)
    {
        bb->parts[i]=0;
    }

    return ERR_OK;
}

int cycle_right(vector* bb1, vector* bb2, int shift)
{
    if(shift<1)
    {
        return BAD_SHIFT;
    }

    copy(bb1,bb2);

    int len=(bb1->last_byte*8)+bb1->last_bit;
    shift%=len;
    right_shift_same(bb1,shift);
    left_shift_same(bb2,len-shift);
    bb_or(bb1, bb2);

    return ERR_OK;

}

int cycle_left(vector* bb1, vector* bb2, int shift)
{
    if(shift<1)
    {
        return BAD_SHIFT;
    }

    copy(bb1,bb2);

    int len=(bb1->last_byte*8)+bb1->last_bit;
    shift%=len;
    right_shift_same(bb1,len-shift);
    left_shift_same(bb2,shift);
    bb_or(bb1, bb2);

    return ERR_OK;

}
