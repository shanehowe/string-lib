#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    char*   data;     // strings value
    size_t  length;   // current string length equivelent to strlen(str->data)
    size_t  capacity; // total space allocated for str->data. for internal use only
} string;


string* string_init(const char* raw_str)
{
    string* s = malloc(sizeof(string));

    if (NULL == s) {
        printf("[string error]: allocation failed.");
        exit(1);
    }

    size_t raw_str_len = strlen(raw_str);
    size_t extra_bytes = 10;
    size_t capacity = raw_str_len + extra_bytes + 1; // +1 for null terminator

    s->data = malloc(capacity);
    if (NULL == s->data) {
        free(s);
        printf("[string error]: allocation failed.");
        exit(1);
    }

    s->length = raw_str_len;
    s->capacity = capacity;
    strcpy(s->data, raw_str);

    return s;
}


void string_free(string* str)
{
    if (!str)
        return;

    free(str->data);
    str->data = NULL;
    free(str);
    str = NULL;
}


bool string_concat(string* dest, const char* source)
{
    size_t source_len = strlen(source);
    size_t capacity_needed = source_len + dest->length;

    if (capacity_needed >= dest->capacity) {
        size_t new_capicity = capacity_needed + 1;
        char* buffer = strdup(dest->data);
        dest->data = realloc(dest->data, new_capicity);

        if (NULL == dest->data) {
            dest->data = buffer;
            return false;
        }

        free(buffer);
        dest->capacity = capacity_needed + 1;
    }

    size_t i, j;
    for (i = dest->length, j = 0; j < source_len; i++, j++) {
        dest->data[i] = source[j];
    }
    dest->data[i] = '\0';
    dest->length += source_len;

    return true;
}


bool string_isdigit(const string* str)
{
    for (size_t i = 0; i < str->length; i++) {
        if (!isdigit(str->data[i]))
            return false;
    }
    return true;
}


int string_count_chars(const string* str, char char_to_count)
{
    int count = 0;
    for (int i = 0; i < str->length; i++) {
        if (str->data[i] == char_to_count)
            count++;
    }
    return count;
}


string* string_substr(const string* str, size_t start_index, size_t end_index)
{
    if (start_index >= end_index) {
        return NULL;
    } else if (start_index >= str->length || end_index > str->length) {
        return NULL;
    }

    int buffer_size = end_index - start_index + 1;
    char* buffer = malloc(buffer_size * sizeof(char));
    if (NULL == buffer) {
        return NULL;
    }

    size_t i = 0;
    while (start_index < end_index) {
        buffer[i++] = str->data[start_index++];
    }

    buffer[i] = '\0';
    string* substr = string_init(buffer);
    free(buffer);

    return substr;
}


int main(void)
{
    string* test_str = string_init("Hello");
    string_concat(test_str, " World");
    string_concat(test_str, "\nGoodbye World");

    for (int i = 0; i < test_str->length; i++) {
        printf("%c", test_str->data[i]);
    }

    string* substr = string_substr(test_str, 0, 5);
    printf("\n");
    for (int i = 0; i < substr->length; i++) {
        printf("%c", substr->data[i]);
    }
    printf("\n");

    string_free(test_str);
    string_free(substr);
    return 0;
}


