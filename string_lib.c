#include "string_lib.h"

string* string_init(const char* raw_str)
{
    string* s = malloc(sizeof(string));

    if (NULL == s) {
        return NULL;
    }

    size_t raw_str_len = strlen(raw_str);
    size_t extra_bytes = 10;
    size_t capacity = raw_str_len + extra_bytes + 1; // +1 for null terminator

    s->data = malloc(capacity);
    if (NULL == s->data) {
        free(s);
        return NULL;
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
        size_t new_capacity = capacity_needed + 1;

        if (!string_reserve(dest, new_capacity))
            return false;
    }

    memcpy(&dest->data[dest->length], source, source_len);
    dest->length += source_len;
    dest->data[dest->length] = '\0'; // just make sure its terminated.

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


int string_count_char(const string* str, char char_to_count)
{
    int count = 0;
    for (size_t i = 0; i < str->length; i++) {
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

char* string_contains(const string* haystack, char* needle)
{
    if (haystack->length == 0)
        return NULL;

    return strstr(haystack->data, needle);
}

string* string_copy(const string* str)
{
    string* copy = malloc(sizeof(string));
    if (NULL == copy) {
        return NULL;
    }

    copy->data = malloc(str->capacity * sizeof(char));
    if (NULL == copy->data) {
        free(copy);
        return NULL;
    }

    strcpy(copy->data, str->data);
    copy->length = str->length;
    copy->capacity = str->capacity;

    return copy;
}

void string_trim(string* str)
{
    size_t start;
    for (start = 0; start < str->length && isspace(str->data[start]); start++)
        ;

    if (start == str->length) {
        // Entire string was whitespace
        str->data[0] = '\0';
        str->length = 0;
        return;
    }

    size_t end;
    for (end = str->length - 1; end > 0 && isspace(str->data[end]); end--)
        ;

    memmove(&str->data[0], &str->data[start], end - start + 1);
    str->length = end - start + 1;
    str->data[str->length] = '\0';
}

int string_compare(const string* s1, const string* s2)
{
    return strcmp(s1->data, s2->data);
}

void string_tolower(string* str)
{
    for (size_t i = 0; i < str->length; i++) {
        str->data[i] = tolower(str->data[i]);
    }
}

void string_toupper(string* str)
{
    for (size_t i = 0; i < str->length; i++) {
        str->data[i] = toupper(str->data[i]);
    }
}

bool string_reserve(string* str, size_t new_capacity)
{
    if (new_capacity <= str->capacity)
        return true;

    char* buffer = realloc(str->data, new_capacity);
    if (NULL == buffer)
        return false;

    str->data = buffer;
    str->capacity = new_capacity;

    return true;
}