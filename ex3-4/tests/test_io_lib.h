/**
 * @file test_io_lib.h
 * @brief Header file for testing I/O functions.
 * 
 * This file contains declarations for functions used to test
 * the reading and writing functionality in the I/O library.
 * It includes test functions for reading records and writing output.
 * 
 * @see io_lib.h
 */

#ifndef _TEST_IO_LIB_H
#define _TEST_IO_LIB_H

/**
 * @brief Test the reading of records from an input source.
 * 
 * This function tests the functionality of reading records from
 * a given input source, ensuring that the records are read correctly.
 */
void test_read_records();

/**
 * @brief Test the writing of output to a destination.
 * 
 * This function tests the functionality of writing output to
 * a specified destination, ensuring that the output is written correctly.
 */
void test_write_output();

#endif // _TEST_IO_LIB_H
