#include <gtest/gtest.h> 
#include <stdio.h> 
#include "ringbuffer.h"
#include <string.h>
TEST(Add_char_to_buffer,MyTEst)
{

    unsigned char rx_buffer[b_length];
    struct buffer_type r;
    init_buffer(&r, rx_buffer);
    int err = 0;
    EXPECT_EQ(1, add_char_to_buffer( &r, '1', &err) );
}

TEST(Add_char_to_buffer2,MyTEst)
{

    unsigned char rx_buffer[b_length];
    struct buffer_type r;


    init_buffer(&r, rx_buffer);
    int err = 0;
    add_char_to_buffer( &r, '1', &err);
    add_char_to_buffer( &r, '2', &err);
    EXPECT_EQ(3, add_char_to_buffer( &r, '3', &err) );
}

TEST(Add_char_to_buffer3,MyTEst)
{

    unsigned char rx_buffer[b_length];
    struct buffer_type r;


    init_buffer(&r, rx_buffer);
    int err = 0;
    add_char_to_buffer( &r, '1', &err);
    add_char_to_buffer( &r, '2', &err);
    add_char_to_buffer( &r, '3', &err);
    EXPECT_EQ(4, add_char_to_buffer( &r, '4', &err) );
}




   TEST(Add_char_to_buffer4,MyTest)
{

    unsigned char rx_buffer[b_length];
    struct buffer_type r;
    int err = 0;

    init_buffer(&r, rx_buffer);

    EXPECT_TRUE(r.head == rx_buffer);
    EXPECT_TRUE(r.tail == rx_buffer);
    EXPECT_TRUE(r.buffer == rx_buffer);
}

/*test empetty buffer*/
   TEST(test_empetty_buffer,MyTest)
{
    unsigned char rx_buffer[b_length];
    unsigned char compar;
    struct buffer_type r;
    init_buffer(&r, rx_buffer);
    empty_buffer(&r);
    //compar = strcmp(rx_buffer, r.buffer);
    EXPECT_TRUE(r.head == rx_buffer);
    EXPECT_TRUE(r.tail == rx_buffer);
   // EXPECT_EQ('0',compar);
//	printf("\n %c \n %c", rx_buffer[0],r.buffer[0]);


}




// get_char_from_buffer
   TEST(get_char_from_buffer,MyTest)
{
    unsigned char get_value ;
    unsigned char rx_buffer [b_length];
    struct buffer_type r;
    int err = 0;
    init_buffer(&r, rx_buffer);
   add_char_to_buffer(&r, 'O', &err);
    get_value = get_char_from_buffer(&r ,&err) ;
    EXPECT_TRUE(get_value == 'O');
}


//add_char_to_buffer

   TEST(add_char_to_buffer,MyTest)
{
	int get_value; 
	unsigned char rx_buffer[b_length];
	struct buffer_type r;
	int err = 0;
	init_buffer(&r, rx_buffer);
	add_char_to_buffer(&r, 'c', &err);
	get_value = add_char_to_buffer(&r, 'c', &err);
	EXPECT_TRUE(get_value == 2);
}


// print_buffer


   TEST(print_buffer,MyTest)
{
	int get_value; 
	unsigned char rx_buffer[2];
	struct buffer_type r;
	int err = 0;
        init_buffer(&r, rx_buffer);
	add_char_to_buffer(&r, 'L', &err);
	add_char_to_buffer(&r, 'c', &err);
	get_value =  print_buffer(r, &err);
	EXPECT_EQ(2, get_value);
}

// add string to buffer
TEST(add_string_to_buffer,MyTest)
{
        int get_value;
        unsigned char rx_buffer[b_length];
        struct buffer_type r;
        int err = 0;
        init_buffer(&r, rx_buffer);
        add_char_to_buffer(&r, '1', &err);
        add_char_to_buffer(&r, '2', &err);
	unsigned char string[] = "hello\0";
	get_value = add_string_to_buffer(&r, string, &err);
        EXPECT_EQ(5, get_value);// it can add, b_length is 50
}


// add string to buffer
TEST(add_string_to_buffer2,MyTest)
{
        int get_value;
        unsigned char rx_buffer[b_length];
        struct buffer_type r;
        int err = 0;
        init_buffer(&r, rx_buffer);
        add_char_to_buffer(&r, '1', &err);
        add_char_to_buffer(&r, '2', &err);
        unsigned char string[] = "hello122312j124jk14kjb214k21b4h12b4h12b4jh12b4jh12b4jh2b43j2hb323hb23jhb23jnjknjknkjnkjnkjnkjb\0";
        get_value = add_string_to_buffer(&r, string, &err);
        EXPECT_EQ(-1, get_value);// it can add, b_length is 50
}

// get buffer status
TEST(get_buffer_status,MyTest)
{
        int err;
        unsigned char rx_buffer[b_length];
        struct buffer_type r;
        init_buffer(&r, rx_buffer);
        add_char_to_buffer(&r, '1', &err);
	get_buffer_status( r, &err );
	EXPECT_EQ(0, err);// buffer ok

}

// get buffer status
TEST(get_buffer_status_buffer_empty,MyTest)
{
        int err;
        unsigned char rx_buffer[b_length];
        struct buffer_type r;
	init_buffer(&r, rx_buffer);
        empty_buffer(&r);
        get_buffer_status( r, &err );
        EXPECT_EQ(2, err);// buffer empty

}


// get buffer status
TEST(get_buffer_status_pointer_err,MyTest)
{
        int err;
        unsigned char rx_buffer[b_length];
        struct buffer_type r;
        init_buffer(&r, rx_buffer);
	r.head = r.buffer + ( b_length + 5 ); 
        get_buffer_status( r, &err );
        EXPECT_EQ(3, err);// pointer err

}

TEST(buffer_full,MyTest)
{
        int err;
        unsigned char rx_buffer[ b_length];
        struct buffer_type r;
        init_buffer(&r, rx_buffer);
        add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
        add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);        
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);        
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);        
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
 add_char_to_buffer( &r, '1', &err);
	 get_buffer_status( r, &err );
        EXPECT_EQ(4, err);// buffer full

}



// get_string_from_buffer
TEST(get_string_from_buffer,MyTest)
{
	int length;
        int err= 0;
        unsigned char rx_buffer[b_length];
	unsigned char rx_buffer2[2];
        struct buffer_type r;
	init_buffer(&r, rx_buffer);
	add_char_to_buffer( &r, 'a', &err);
	add_char_to_buffer( &r, 'b', &err);
	length = get_string_from_buffer(&r, rx_buffer2,2,&err);
       	printf("%s",rx_buffer2);
	EXPECT_EQ(2, length);

}
