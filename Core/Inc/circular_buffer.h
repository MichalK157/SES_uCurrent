/*
 * circular_buffer.h
 *
 *  Created on: Dec 5, 2022
 *      Author: mkac
 */

#ifndef INC_CIRCULAR_BUFFER_H_
#define INC_CIRCULAR_BUFFER_H_

#include <stdint.h>

#define BUFFER_SIZE_MAX 32

typedef struct _CircularBuffer
{
    uint32_t buffer_length;
    uint32_t read_index;
    uint32_t write_index;
    uint32_t size_of_buffer;
    int32_t input_buff[BUFFER_SIZE_MAX];
} CircularBuffer;


void circular_buffer_init(CircularBuffer* circular_buffer, uint32_t size);
int32_t circular_buffer_read(CircularBuffer* circular_buffer);
void circular_buffer_write(CircularBuffer* circular_buffer, int32_t data_to_write);
uint8_t circular_buffer_is_empty(CircularBuffer* const circular_buffer);
uint8_t circular_buffer_is_full(CircularBuffer* const circular_buffer);
void circular_buffer_fill(CircularBuffer* circular_buffer, int32_t val);
uint32_t circular_buffer_calculate_mean(CircularBuffer* const circular_buffer);


#endif /* INC_CIRCULAR_BUFFER_H_ */
