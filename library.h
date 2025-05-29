/*
 * This code is distributed under the terms of the GNU General Public License.
 * For more information, please refer to the LICENSE file in the root directory.
 * -------------------------------------------------
 * Copyright (C) 2025 Rodrigo R.
 * This program comes with ABSOLUTELY NO WARRANTY; for details type show w'.
 * This is free software, and you are welcome to redistribute it
 * under certain conditions; type show c' for details.
*/

// ============= FLUENT LIB C =============
// String Padding Utility
// ----------------------------------------
// Pads a given string with spaces on the right to match a target width.
//
// Useful for formatting console output, aligning columns, or preparing
// fixed-width string layouts.
//
// Function Provided:
// ----------------------------------------
// char *str_pad(const size_t spaces, const char *str);
//
// Description:
// - Pads the input string `str` with spaces on the right so that its
//   final length is `spaces`.
// - If `str` is longer than `spaces`, returns a copy of the original string.
// - Uses `string_builder_t` internally for efficient appending.
// - Caller is responsible for freeing the returned string.
//
// Usage Example:
// ----------------------------------------
//     char *padded = str_pad(10, "hi");
//     printf("'%s'\n", padded);  // Output: 'hi        '
//     free(padded);
//
// Notes:
// - Returns NULL if `str` is NULL or `spaces` is 0
// - Returned string is dynamically allocated
// - Depends on fluent_libc `string_builder.h`
//
// Dependencies:
// ----------------------------------------
// - fluent/string_builder
//
// ----------------------------------------
// Initial revision: 2025-05-28
// ----------------------------------------

#ifndef STRING_PAD_LIBRARY_H
#define STRING_PAD_LIBRARY_H
#ifndef FLUENT_LIBC_RELEASE
#   include <string_builder.h> // fluent_libc
#else
#   include <fluent/string_builder/string_builder.h> // fluent_libc
#endif

// ============= FLUENT LIB C++ =============
#if defined(__cplusplus)
extern "C"
{
#endif

typedef long int ssize_t; // Signed size type

/**
 * Pads the given string with spaces on the right to reach the specified total width.
 *
 * @param spaces The total width the resulting string should have (including the original string).
 * @param str    The input string to pad. Must not be NULL.
 * @return       A newly allocated, padded string, or NULL if no padding is needed or input is invalid.
 *               The returned string must be freed by the caller.
 *
 * If the length of `str` is greater than or equal to `spaces`, a copy of the original string is returned.
 * Uses a string builder for efficient string manipulation.
 */
inline char *str_pad(const size_t spaces, const char *str)
{
    if (spaces == 0 || str == NULL)
    {
        return NULL; // No padding needed or invalid string
    }

    // Create a new string builder
    string_builder_t sb;
    init_string_builder(&sb, 15, 1.5); // 1.5x growth factor to avoid overallocation

    size_t len = 0; // Length of the original string
    // Append the string while we calculate its length
    while (*str != '\0') // Iterate until we find the null terminator
    {
        write_char_string_builder(&sb, *str); // Write the character to the string builder
        len++; // Increment the length
        str++; // Move to the next character
    }

    // Determine the difference in order to calculate the padding
    const ssize_t diff = spaces - len;
    if (diff <= 0)
    {
        // No padding needed, return the original string
        return collect_string_builder_no_copy(&sb); // Return the string from the string builder
    }

    // Write spaces to the string builder
    for (ssize_t i = 0; i < diff; i++)
    {
        write_char_string_builder(&sb, ' '); // Append spaces to the string builder
    }

    // Return the padded string without copying
    return collect_string_builder_no_copy(&sb); // Collect the string from the string builder without copying
}

#if defined(__cplusplus)
}
#endif
#endif //STRING_PAD_LIBRARY_H