#ifndef AWS_COMMON_JSON_H
#define AWS_COMMON_JSON_H

/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include <aws/common/byte_buf.h>
#include <aws/common/common.h>

struct aws_json_value;

// ====================
// Create and pass type

/**
 * Creates a new string aws_json_value with the given string and returns a pointer to it.
 *
 * Note: You will need to free the memory for the aws_json_value using aws_json_destroy on the aws_json_value or
 * on the object/array containing the aws_json_value.
 * @param string A byte pointer to the string you want to store in the aws_json_value
 * @param allocator The allocator to use when creating the value
 * @return A new string aws_json_value
 */
AWS_COMMON_API
struct aws_json_value *aws_json_value_new_string(struct aws_allocator *allocator, struct aws_byte_cursor string);

/**
 * Creates a new number aws_json_value with the given number and returns a pointer to it.
 *
 * Note: You will need to free the memory for the aws_json_value using aws_json_destroy on the aws_json_value or
 * on the object/array containing the aws_json_value.
 * @param number The number you want to store in the aws_json_value
 * @param allocator The allocator to use when creating the value
 * @return A new number aws_json_value
 */
AWS_COMMON_API
struct aws_json_value *aws_json_value_new_number(struct aws_allocator *allocator, double number);

/**
 * Creates a new array aws_json_value and returns a pointer to it.
 *
 * Note: You will need to free the memory for the aws_json_value using aws_json_destroy on the aws_json_value or
 * on the object/array containing the aws_json_value.
 * Deleting this array will also destroy any aws_json_values it contains.
 * @param allocator The allocator to use when creating the value
 * @return A new array aws_json_value
 */
AWS_COMMON_API
struct aws_json_value *aws_json_value_new_array(struct aws_allocator *allocator);

/**
 * Creates a new boolean aws_json_value with the given boolean and returns a pointer to it.
 *
 * Note: You will need to free the memory for the aws_json_value using aws_json_destroy on the aws_json_value or
 * on the object/array containing the aws_json_value.
 * @param boolean The boolean you want to store in the aws_json_value
 * @param allocator The allocator to use when creating the value
 * @return A new boolean aws_json_value
 */
AWS_COMMON_API
struct aws_json_value *aws_json_value_new_boolean(struct aws_allocator *allocator, bool boolean);

/**
 * Creates a new null aws_json_value and returns a pointer to it.
 *
 * Note: You will need to free the memory for the aws_json_value using aws_json_destroy on the aws_json_value or
 * on the object/array containing the aws_json_value.
 * @param allocator The allocator to use when creating the value
 * @return A new null aws_json_value
 */
AWS_COMMON_API
struct aws_json_value *aws_json_value_new_null(struct aws_allocator *allocator);

/**
 * Creates a new object aws_json_value and returns a pointer to it.
 *
 * Note: You will need to free the memory for the aws_json_value using aws_json_destroy on the aws_json_value or
 * on the object/array containing the aws_json_value.
 * Deleting this object will also destroy any aws_json_values it contains.
 * @param allocator The allocator to use when creating the value
 * @return A new object aws_json_value
 */
AWS_COMMON_API
struct aws_json_value *aws_json_value_new_object(struct aws_allocator *allocator);
// ====================

// ====================
// Value getters

/**
 * Gets the string of a string aws_json_value.
 * @param value The string aws_json_value.
 * @param output The string
 * @return AWS_OP_SUCESS if the value is a string, otherwise AWS_OP_ERR.
 */
AWS_COMMON_API
int aws_json_value_get_string(const struct aws_json_value *value, struct aws_byte_cursor *output);

/**
 * Gets the number of a number aws_json_value.
 * @param value The number aws_json_value.
 * @param output The number
 * @return AWS_OP_SUCESS if the value is a number, otherwise AWS_OP_ERR.
 */
AWS_COMMON_API
int aws_json_value_get_number(const struct aws_json_value *value, double *output);

/**
 * Gets the boolean of a boolean aws_json_value.
 * @param value The boolean aws_json_value.
 * @param output The boolean
 * @return AWS_OP_SUCESS if the value is a boolean, otherwise AWS_OP_ERR.
 */
AWS_COMMON_API
int aws_json_value_get_boolean(const struct aws_json_value *value, bool *output);
// ====================

// ====================
// Object API

/**
 * Adds a aws_json_value to a object aws_json_value.
 *
 * Note that the aws_json_value will be destroyed when the aws_json_value object is destroyed
 * by calling "aws_json_destroy()"
 * @param object The object aws_json_value you want to add a value to.
 * @param key The key to add the aws_json_value at.
 * @param value The aws_json_value you want to add.
 * @return AWS_OP_SUCCESS if adding was successful.
 *          Will return AWS_OP_ERROR if the object passed is invalid or if the passed key
 *          is already in use in the object.
 */
AWS_COMMON_API
int aws_json_value_add_to_object(
    struct aws_json_value *object,
    struct aws_byte_cursor key,
    struct aws_json_value *value);

/**
 * Returns the aws_json_value at the given key.
 * @param object The object aws_json_value you want to get the value from.
 * @param key The key that the aws_json_value is at. Is case sensitive.
 * @return The aws_json_value at the given key, otherwise NULL.
 */
AWS_COMMON_API
struct aws_json_value *aws_json_value_get_from_object(const struct aws_json_value *object, struct aws_byte_cursor key);

/**
 * Checks if there is a aws_json_value at the given key.
 * @param object The value aws_json_value you want to check a key in.
 * @param key The key that you want to check. Is case sensitive.
 * @return True if a aws_json_value is found.
 */
AWS_COMMON_API
bool aws_json_value_has_key(const struct aws_json_value *object, struct aws_byte_cursor key);

/**
 * Removes the aws_json_value at the given key.
 * @param object The object aws_json_value you want to remove a aws_json_value in.
 * @param key The key that the aws_json_value is at. Is case sensitive.
 * @return AWS_OP_SUCCESS if the aws_json_value was removed.
 *          Will return AWS_OP_ERR if the object passed is invalid or if the value
 *          at the key cannot be found.
 */
AWS_COMMON_API
int aws_json_value_remove_from_object(struct aws_json_value *object, struct aws_byte_cursor key);
// ====================

// ====================
// Array API

/**
 * Adds a aws_json_value to the given array aws_json_value.
 *
 * Note that the aws_json_value will be destroyed when the aws_json_value array is destroyed
 * by calling "aws_json_destroy()"
 * @param array The array aws_json_value you want to add an aws_json_value to.
 * @param value The aws_json_value you want to add.
 * @return AWS_OP_SUCCESS if adding the aws_json_value was successful.
 *          Will return AWS_OP_ERR if the array passed is invalid.
 */
AWS_COMMON_API
int aws_json_value_add_array_element(struct aws_json_value *array, const struct aws_json_value *value);

/**
 * Returns the aws_json_value at the given index in the array aws_json_value.
 * @param array The array aws_json_value.
 * @param index The index of the aws_json_value you want to access.
 * @return A pointer to the aws_json_value at the given index in the array, otherwise NULL.
 */
AWS_COMMON_API
struct aws_json_value *aws_json_get_array_element(const struct aws_json_value *array, size_t index);

/**
 * Returns the number of items in the array aws_json_value.
 * @param array The array aws_json_value.
 * @return The number of items in the array_json_value.
 */
AWS_COMMON_API
size_t aws_json_get_array_size(const struct aws_json_value *array);

/**
 * Removes the aws_json_value at the given index in the array aws_json_value.
 * @param array The array aws_json_value.
 * @param index The index containing the aws_json_value you want to remove.
 * @return AWS_OP_SUCCESS if the aws_json_value at the index was removed.
 *          Will return AWS_OP_ERR if the array passed is invalid or if the index
 *          passed is out of range.
 */
AWS_COMMON_API
int aws_json_value_remove_array_element(struct aws_json_value *array, size_t index);
// ====================

// ====================
// Checks

/**
 * Checks if the aws_json_value is a string.
 * @param value The aws_json_value to check.
 * @return True if the aws_json_value is a string aws_json_value, otherwise false.
 */
AWS_COMMON_API
bool aws_json_value_is_string(const struct aws_json_value *value);

/**
 * Checks if the aws_json_value is a number.
 * @param value The aws_json_value to check.
 * @return True if the aws_json_value is a number aws_json_value, otherwise false.
 */
AWS_COMMON_API
bool aws_json_value_is_number(const struct aws_json_value *value);

/**
 * Checks if the aws_json_value is a array.
 * @param value The aws_json_value to check.
 * @return True if the aws_json_value is a array aws_json_value, otherwise false.
 */
AWS_COMMON_API
bool aws_json_value_is_array(const struct aws_json_value *value);

/**
 * Checks if the aws_json_value is a boolean.
 * @param value The aws_json_value to check.
 * @return True if the aws_json_value is a boolean aws_json_value, otherwise false.
 */
AWS_COMMON_API
bool aws_json_value_is_boolean(const struct aws_json_value *value);

/**
 * Checks if the aws_json_value is a null aws_json_value.
 * @param value The aws_json_value to check.
 * @return True if the aws_json_value is a null aws_json_value, otherwise false.
 */
AWS_COMMON_API
bool aws_json_value_is_null(const struct aws_json_value *value);

/**
 * Checks if the aws_json_value is a object aws_json_value.
 * @param value The aws_json_value to check.
 * @return True if the aws_json_value is a object aws_json_value, otherwise false.
 */
AWS_COMMON_API
bool aws_json_value_is_object(const struct aws_json_value *value);
// ====================

// ====================
// Memory Management

/**
 * Initializes the JSON module for use.
 * @param allocator The allocator to use for creating aws_json_value structs.
 */
AWS_COMMON_API
void aws_json_module_init(struct aws_allocator *allocator);

/**
 * Cleans up the JSON module. Should be called when finished using the module.
 */
AWS_COMMON_API
void aws_json_module_cleanup(void);

/**
 * Removes the aws_json_value from memory. If the aws_json_value is a object or array, it will also destroy
 * attached aws_json_values as well.
 *
 * For example, if you called "aws_json_array_add(b, a)" to add an object "a" to an array "b", if you call
 * "aws_json_destroy(b)" then it will also free "a" automatically. All children/attached aws_json_values are freed
 * when the parent/root aws_json_value is destroyed.
 * @param value The aws_json_value to destroy.
 */
AWS_COMMON_API
void aws_json_value_destroy(struct aws_json_value *value);
// ====================

// ====================
// Utility

/**
 * Appends a unformatted JSON string representation of the aws_json_value into the passed byte buffer.
 * The byte buffer is expected to be already initialized so the function can append the JSON into it.
 *
 * Note: The byte buffer will automatically have its size extended if the JSON string is over the byte
 * buffer capacity AND the byte buffer has an allocator associated with it. If the byte buffer does not
 * have an allocator associated and the JSON string is over capacity, AWS_OP_ERR will be returned.
 *
 * Note: When you are finished with the aws_byte_buf, you must call "aws_byte_buf_clean_up_secure" to free
 * the memory used, as it will NOT be called automatically.
 * @param value The aws_json_value to format.
 * @param output The destination for the JSON string
 * @return AWS_OP_SUCCESS if the JSON string was allocated to output without any errors
 *      Will return AWS_OP_ERR if the value passed is not an aws_json_value or if there
 *      was an error appending the JSON into the byte buffer.
 */
AWS_COMMON_API
int aws_byte_buf_append_json_string(const struct aws_json_value *value, struct aws_byte_buf *output);

/**
 * Appends a formatted JSON string representation of the aws_json_value into the passed byte buffer.
 * The byte buffer is expected to already be initialized so the function can append the JSON into it.
 *
 * Note: The byte buffer will automatically have its size extended if the JSON string is over the byte
 * buffer capacity AND the byte buffer has an allocator associated with it. If the byte buffer does not
 * have an allocator associated and the JSON string is over capacity, AWS_OP_ERR will be returned.
 *
 * Note: When you are finished with the aws_byte_buf, you must call "aws_byte_buf_clean_up_secure" to free
 * the memory used, as it will NOT be called automatically.
 * @param value The aws_json_value to format.
 * @param output The destination for the JSON string
 * @return AWS_OP_SUCCESS if the JSON string was allocated to output without any errors
 *      Will return AWS_ERROR_INVALID_ARGUMENT if the value passed is not an aws_json_value or if there
 *      aws an error appending the JSON into the byte buffer.
 */
AWS_COMMON_API
int aws_byte_buf_append_json_string_formatted(const struct aws_json_value *value, struct aws_byte_buf *output);

/**
 * Parses the JSON string and returns a aws_json_value containing the root of the JSON.
 * @param allocator The allocator used to create the value
 * @param string The string containing the JSON.
 * @return The root aws_json_value of the JSON.
 */
AWS_COMMON_API
struct aws_json_value *aws_json_value_new_from_string(struct aws_allocator *allocator, struct aws_byte_cursor string);
// ====================

#endif // AWS_COMMON_JSON_H
