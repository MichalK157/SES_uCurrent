/*
 * circular_buffer.c
 *
 *  Created on: Dec 5, 2022
 *      Author: mkac
 */


#include "stdlib.h"
#include "string.h"

#include <circular_buffer.h>

void circular_buffer_init(CircularBuffer* circular_buffer, uint32_t size)
{

    if(size <= BUFFER_SIZE_MAX)
    {
        circular_buffer->size_of_buffer = size;
    }
    else
    {
    	/*
    	 * error size
    	 * set to max size of buffer
    	 */
    	circular_buffer->size_of_buffer = size;
    }
    circular_buffer->buffer_length = 0;
    circular_buffer->read_index = 0;
    circular_buffer->write_index = 0;
    memset(circular_buffer->input_buff, 0, circular_buffer->size_of_buffer * sizeof(circular_buffer->input_buff[0]));
}

int32_t circular_buffer_read(CircularBuffer* circular_buffer)
{
    int32_t read_value;

    if(circular_buffer_is_empty(circular_buffer))
    {
        return 0;
    }

    read_value = circular_buffer->input_buff[circular_buffer->read_index];

    --circular_buffer->buffer_length;
    ++circular_buffer->read_index;

    if(circular_buffer->read_index == circular_buffer->size_of_buffer) // read_index == size_of_buffer
    {
        circular_buffer->read_index = 0;
    }

    return read_value;
}

void circular_buffer_write(CircularBuffer* circular_buffer, int32_t data_to_write)
{
    circular_buffer->input_buff[circular_buffer->write_index] = data_to_write;

    ++circular_buffer->write_index;
    if(circular_buffer->write_index == circular_buffer->size_of_buffer)
    {
        circular_buffer->write_index = 0;
    }
    if(!circular_buffer_is_full(circular_buffer)) // buffer_length == size_of_buffer
    {
        ++circular_buffer->buffer_length;
    }
}

uint8_t circular_buffer_is_empty(CircularBuffer* const circular_buffer)
{
    return (uint8_t)(circular_buffer->buffer_length == 0);
}

uint8_t circular_buffer_is_full(CircularBuffer* const circular_buffer)
{
    return (uint8_t)(circular_buffer->buffer_length == circular_buffer->size_of_buffer);
}

void circular_buffer_fill(CircularBuffer* circular_buffer, int32_t val)
{
    for(uint32_t i = 0; i < circular_buffer->size_of_buffer; ++i)
    {
        circular_buffer_write(circular_buffer, val);
    }
}

uint32_t circular_buffer_calculate_mean(CircularBuffer* const circular_buffer)
{
    uint64_t sum = 0;
    if(!circular_buffer_is_full(circular_buffer))
        return 0;

    for(int i = 0; i < circular_buffer->size_of_buffer; ++i)
    {
        sum += circular_buffer->input_buff[i];
    }

    return (uint32_t)sum / circular_buffer->size_of_buffer;
}

