#include "ringbuffer.h"
#include <stdio.h>
#include <string.h>

void init_buffer(struct buffer_type *b, unsigned char *buffer)
{

    b->head = buffer;
    b->tail = buffer;
    b->buffer = buffer;

}

void empty_buffer(struct buffer_type *b)
{
	memset(b->buffer,'_',b_length);
	b->head = b->buffer;
	b->tail = b->buffer;
}

signed int get_buffer_status(struct buffer_type b, int *err)
{
	if( b.head == b.tail )
	{//buffer empty
		*err = 2;
	}
	else if ( ( ( b.head - b.buffer) + 1 )  % b_length == ( b.tail - b.buffer ) )
        {//buffer full
                *err = 4;
        }
	else if( b.tail > ( b.buffer + b_length ) || b.tail < ( b.buffer - 1 ) ||  b.head > ( b.buffer + b_length ) || b.head < ( b.buffer - 1 )  )
	{
		*err = 3;
	}
	else
	{
		*err = 0;
	}
	return 0;
}

int add_char_to_buffer(struct buffer_type* b, unsigned char c, int *err)
{
	if( ( ( b->head - b->buffer) + 1 ) % b_length == ( b->tail - b->buffer ) )
	{//buffer is full
		*(b->head) ='_';
		return -1;
	}
	else
	{
		*( b->head ) = c;
                b->head++;
		if( b->head  - b->buffer == b_length )
                {
                        b->head = b->buffer;
                }

		int head_position = b->head - b->buffer;
		int tail_position = b->tail - b->buffer;
		if( head_position > tail_position )
		{
			return head_position - tail_position;
		}
		else
		{
			return b_length - tail_position + head_position;
		}
	}
}

unsigned char get_char_from_buffer(struct buffer_type *b, int *err)
{
	if( b->head == b->tail )
	{//buffer is empty
		*err = 2;
		return '_';
	}
	else
	{
		unsigned char tmp = *( b->tail );
		*(b->tail) = '_';
		b->tail ++ ;
		if( b->tail - b->buffer == b_length )
		{
			b->tail = b->buffer;
		}
		return tmp;
	}
}

int print_buffer(struct buffer_type b, int *err)
{
	 int head_position = b.head - b.buffer;
         int tail_position = b.tail - b.buffer;
	 int n_chars = -1;
	 printf("\n Buffer contents: %s \n", b.buffer );
	  if( head_position > tail_position )
         {//head is in front of tail
         	n_chars = head_position - tail_position;
         }
         else if( head_position < tail_position )
         {//tail is in front of head
         	n_chars = b_length - tail_position + head_position;
         }
	else if ( head_position == tail_position )
	{//buf empty
		*err = 2;
	}
	else if ( ( head_position + 1 ) % b_length  == tail_position )
        {//buf full
                *err = 4;
        }

	return n_chars;
} 


int add_string_to_buffer(struct buffer_type *b, unsigned char *s, int *err)

{
	int head_position = b->head - b->buffer;
	int tail_position = b->tail - b->buffer;
	int n_occupied 	= 0;
	int n_free	= 0;
	int count 	= 0; 
	if( head_position == tail_position)
	{//buffer empty
		n_free = b_length;
	}
	else if( head_position > tail_position )
	{//head in front of tail
		n_occupied = head_position - tail_position;
	}
	else
	{//tail in front of head
		n_occupied = b_length + head_position - tail_position;
	}
	n_free = b_length - n_occupied;
	while (s [count] != '\0')
	{
		count ++;
	}
	if (count <= n_free)
	{//if there is enough space, add string
		while ( *s!= '\0' )
		{
			add_char_to_buffer(b, *s, err);
			s++;
		}
	}
	else
	{
		count = -1;
	}
	printf("\n %d \n",count);
	return count;
}


int  get_string_from_buffer(struct buffer_type *b, unsigned char *dest, int len, int *err)

{
	int head_posetion, tail_posetion, length;
   	head_posetion =b->head - b->buffer ;
   	tail_posetion = b->tail - b->buffer ;
   	length = ((head_posetion - tail_posetion) + b_length)%b_length;
   
    if ( b->head == b->tail)
        //buffer is empty 
        {
        
            return 1;
        }
    
    if (length >= len )
        {
            memcpy(dest, b->buffer, len);
            return len;
        }
    else 
        {
           memcpy(dest, b->buffer, length);
            return length;
        }

}
/*
void main()
{
	unsigned char rx_buffer[ b_length + 1 ];
	rx_buffer[ b_length ] = '\0';
	struct buffer_type b;
	int err = 0; 
	init_buffer(&b, rx_buffer);
	print_buffer(b,&err);
	get_char_from_buffer( &b, &err );
	printf(" \n %d \n",add_char_to_buffer(&b, '1', &err) );
printf("\n %s \n", rx_buffer);
	printf(" \n %d \n",add_char_to_buffer(&b, '2', &err) );
printf("\n %s \n", rx_buffer);
	printf(" \n %d \n",add_char_to_buffer(&b, '3', &err) );
printf("\n %s \n", rx_buffer);
	printf(" \n %d \n",add_char_to_buffer(&b, '4', &err) );
printf("\n %s \n", rx_buffer);
	printf(" \n %d \n",add_char_to_buffer(&b, '5', &err) );
printf("\n %s \n", rx_buffer);
	printf(" \n %d \n",add_char_to_buffer(&b, '6', &err) );
printf("\n %s \n", rx_buffer);
	printf(" \n %d \n",add_char_to_buffer(&b, '7', &err) );

	printf("\n %s \n", rx_buffer);
	printf("\n %c \n",  get_char_from_buffer( &b, &err ) );
	printf("\n %c \n",  get_char_from_buffer( &b, &err ) );
	printf("\n %s \n", rx_buffer);
	add_char_to_buffer(&b, 'a', &err);
	printf("\n %s \n", rx_buffer);
	printf("\n %c \n",  get_char_from_buffer( &b, &err ) );
printf("\n %c \n",  get_char_from_buffer( &b, &err ) );
printf("\n %c \n",  get_char_from_buffer( &b, &err ) );
printf("\n %c \n",  get_char_from_buffer( &b, &err ) );
printf("\n %c \n",  get_char_from_buffer( &b, &err ) );
printf("\n %c \n",  get_char_from_buffer( &b, &err ) );
printf("\n %c \n",  get_char_from_buffer( &b, &err ) );
printf("\n %c \n",  get_char_from_buffer( &b, &err ) );
printf("\n %c \n",  get_char_from_buffer( &b, &err ) );
printf("\n %c \n",  get_char_from_buffer( &b, &err ) );
print_buffer( b, &err );
printf("\n%d\n",add_string_to_buffer(&b, "tryt4t4t4t4t\0", &err));
print_buffer( b, &err );
empty_buffer(&b);
print_buffer( b, &err );
}
*/
