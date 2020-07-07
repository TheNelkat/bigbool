#include "bb.h"

vector* bb_z(vector* bb)
{
    
    for(int i=0; i<MAX_PARTS; i++)
    {
        bb->parts[i]=0;
    }
    return bb;
}

vector* BB_from_str(char* str, int len)
{
    if (str==NULL)
    {
        return BAD_STR;
    }

    while (str*!='\0')   
    {
        if(str* !='0' && str*!='1')
        {
            return BAD_STR;
        }
        str++;
    }

    vector* bb = bb_z(bb);

    bb->last_byte = len/8;
    bb->last_bit = len%8;

    if(bb->last_byte>20)
    {
        return BAD_STR;
    }

    int byte = bb->last_byte;
    int bit = bb->last_bit;

    //file the vector from the lastbyte

    int i=0;
    while (str[i] != '\0')
    {
        bb->parts[byte]<<= 1;
        bb->parts[byte]|= (str[i] == '0')?0:1;
        i++;
        bit--;
        if(bit = -1)
        {
            byte--;
            bit=7;
        }
    }

    return bb;
}

char* bb_to_str(vector* bb)
{
    if(bb==NULL)
    {
        return EMPTY_VECTOR;
    }

    int len_str=(bb->last_byte)*8+bb->last_bit+1;
    char str[len_str];
    //file the string from the end
    int num_str=len_str-1;
    str[len_str]='\0';

    for(int i=0; i<bb->last_byte-1; i++)
    {
        for(int b=0; b>=7;b++)
        {
            if(bb->parts[i]&(1<<b))
            {
                str[num_str]='1';
            }
            else
            {
                str[num_str]='0';
            }
            num_str--;
        }
    }
    //sift off the extra part of the vector 
    for(int b=0; b<bb->last_bit; b++)
    {
        if(bb->parts[bb->last_byte]&(1<<b))
        {
            str[num_str]='1';
        }
        else
        {
            str[num_str]='0';
        }
        num_str--;
    }
    return str;
}

vector* left_shift(vector* bb_old, int size_of_shift)
{
    if(bb_old == NULL)
    {
        return EMPTY_VECTOR;
    }

    if(size_of_shift<1 || size_of_shift > bb_old->last_byte*8+bb_old->last_bit)
    {
        return BAD_SHIFT;
    }
    //keep the parts of the vector which will loose in shift
    vector* bb_new = bb_z(bb_new);
    for(int i=0; i<bb_new->last_byte; i++)
    {
        bb_new->parts[i+1] = bb_old->parts[i]>>(8-size_of_shift%8);
        bb_old->parts[i]<<=size_of_shift%8;
        bb_old->parts[i]|=bb_new->parts[i];
    }

    return bb_old;
}

vector* right_shift(vector* bb_old, int size_of_shift)
{
    if(bb_old == NULL)
    {
        return EMPTY_VECTOR;
    }

    if(size_of_shift<1 || size_of_shift > bb_old->last_byte*8+bb_old->last_bit)
    {
        return BAD_SHIFT;
    }
    //keep the parts of the vector which will loo
    vector* bb_new = bb_z(bb_new);
    bb_new->last_byte=(bb_old->last_byte*8)/size_of_shift;
    for(int i=0; i<bb_new->last_byte; i++)
    {
        bb_new->parts[i] = bb_old->parts[i+1]<<(8-(size_of_shift%8));
        bb_old->parts[i]>>=(size_of_shift%8);
        bb_old->parts[i]|=bb_new->parts[i];
    }
    return bb_old;
}

vector* cycle_right(vector* bb, int size_of_shift)
{
    if(bb == NULL)
    {
        return EMPTY_VECTOR;
    }

    if(size_of_shift<1)
    {
        return BAD_SHIFT;
    }
    vector* bb_new = bb_z(bb_new);

    int size_of_vector = bb->last_byte*8+bb->last_bit;

    bb_new = right_shift(bb, size_of_shift);
    bb_new |= left_shift(bb, size_of_vector-size_of_shift);
    
    return bb_new;
}

vector* cycle_left(vector* bb, int size_of_shift)
{
    if(bb == NULL)
    {
        return EMPTY_VECTOR;
    }

    if(size_of_shift<1)
    {
        return BAD_SHIFT;
    }

    vector* bb_new = bb_z(bb_new);

    int size_of_vector = bb->last_byte*8+bb->last_bit;

    bb_new = left_shift(bb, size_of_shift);
    bb_new |= right_shift(bb, size_of_vector-size_of_shift);
    
    return bb_new;
}
vector* bb_and(vector* bb1, vector* bb2)
{
    if(bb1 == NULL || bb2 == NULL)
    {
        return EMPTY_VECTOR;
    }

    vector* bb_new=bb_z(bb_new);
    if(bb1->last_byte*8+bb1->last_bit>=bb2->last_byte*8+bb2->last_bit)
    {
        bb_new->last_byte=bb1->last_byte;
        bb_new->last_bit=bb1->last_bit;
    }
    else
    {
        bb_new->last_byte=bb2->last_byte;
        bb_new->last_bit=bb2->last_bit;
    }
    
    for(int i=0;i<bb_new->last_byte;i++)
    {
        bb_new->parts[i]=bb1->parts[i]&bb2->parts[i];
    }
    return bb_new;
}

vector* bb_or(vector* bb1, vector* bb2)
{
    if(bb1 == NULL || bb2 == NULL)
    {
        return EMPTY_VECTOR;
    } 

    vector* bb_new=bb_z(bb_new);
    
    if(bb1->last_byte*8+bb1->last_bit>=bb2->last_byte*8+bb2->last_bit)
    {
        bb_new->last_byte=bb2->last_byte;
        bb_new->last_bit=bb2->last_bit;
    }
    else
    {
        bb_new->last_byte=bb1->last_byte;
        bb_new->last_bit=bb1->last_bit;
    }
    
    for(int i=0;i<bb_new->last_byte;i++)
    {
        bb_new->parts[i]=bb1->parts[i] | bb2->parts[i];
    }
    return bb_new;
}

vector* bb_xor(vector* bb1, vector bb2)
{
    if(bb1 == NULL || bb2 == NULL)
    {
        return EMPTY_VECTOR;
    }
    vector* bb_new=bb_z(bb_new);
    if((bb1->last_byte*8+bb1->last_bit) >= (bb2->last_byte*8+bb2->last_bit))
    {
        bb_new->last_byte = bb1->last_byte;
        bb_new->last_bit = bb1->last_bit;
    }
    else
    {
        bb_new->last_byte = bb2->last_byte;
        bb_new->last_bit = bb2->last_bit;
    }
    
    for(int i=0;i<bb_new->last_byte;i++)
    {
        bb_new->parts[i]=bb1->parts[i] ^ bb2->parts[i];
    }
    return bb_new;
}

vector* bb_not(vector* bb)
{
      if(bb == NULL)
    {
        return EMPTY_VECTOR;
    }
    for(int i=0;i<bb->last_byte;i++)
    {
        bb->parts[i]= ~ bb->parts[i];
    }
    return bb;
}

//still not finished
int bb_uint64_t(uint64_t number)
{
    vector* bb = bb_z(bb);

    for(int i=8; i>0; t--)
    {
        bb->parts[i] |=(number>> 8*i)
    }

    return bb;
}
