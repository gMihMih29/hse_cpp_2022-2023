#include "cstring.h"

size_t Strlen(const char* str) {
    size_t cnt = 0;
    while (*str != '\0') {
        ++cnt;
        ++str;
    }
    return cnt;
}

int Strcmp(const char* first, const char* second) {
    size_t size1 = Strlen(first);
    size_t size2 = Strlen(second);
    size_t size = (size1 > size2 ? size2 : size1);
    for (size_t i = 0; i < size; ++i) {
        if (*(first + i) < *(second + i)) {
            return -1;
        }
        if (*(first + i) > *(second + i)) {
            return 1;
        }
    }
    if (size1 < size2) {
        return -1;
    }
    if (size1 > size2) {
        return 1;
    }
    return 0;
}

int Strncmp(const char* first, const char* second, size_t count) {
    if (count == 0) {
        return 0;
    }
    size_t i = 0;
    for (; i < count && *(first + i) != '\0' && *(second + i) != '\0'; ++i) {
        if (*(first + i) < *(second + i)) {
            return -1;
        }
        if (*(first + i) > *(second + i)) {
            return 1;
        }
    }
    if (i == count) {
        return 0;
    }
    if ((*(first + i) == '\0' && *(second + i) == '\0') || (*(first + i) != '\0' && *(second + i) != '\0')) {
        return 0;
    }
    if (*(first + i) == '\0') {
        return -1;
    }
    return 1;
}

char* Strcpy(char* dest, const char* src) {
    size_t i = 0;
    while (*(src + i) != '\0') {
        *(dest + i) = *(src + i);
        ++i;
    }
    *(dest + i) = '\0';
    return dest;
}

char* Strncpy(char* dest, const char* src, size_t count) {
    size_t src_size = Strlen(src);
    for (size_t i = 0; i < count; ++i) {
        if (i >= src_size) {
            *(dest + i) = '\0';
            continue;
        }
        *(dest + i) = *(src + i);
    }
    return dest;
}

char* Strcat(char* dest, const char* src) {
    size_t size = Strlen(dest);
    Strcpy(dest + size, src);
    return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
    size_t size = Strlen(dest);
    Strncpy(dest + size, src, count);
    return dest;
}

const char* Strchr(const char* str, char symbol) {
    while (*str != '\0') {
        if (*str == symbol) {
            return str;
        }
        ++str;
    }
    if (*str == symbol) {
        return str;
    }
    return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
    size_t i = Strlen(str) + 1;
    while (i > 0) {
        if (*(str + i - 1) == symbol) {
            return str + i - 1;
        }
        --i;
    }
    return nullptr;
}

size_t Strspn(const char* dest, const char* src) {
    size_t size_dest = Strlen(dest);
    size_t size_src = Strlen(src);
    size_t cnt = 0;
    for (size_t i = 0; i < size_dest; ++i) {
        bool has_found = false;
        for (size_t j = 0; j < size_src; ++j) {
            if (*(dest + i) == *(src + j)) {
                has_found = true;
                break;
            }
        }
        if (!has_found) {
            break;
        }
        ++cnt;
    }
    return cnt;
}

size_t Strcspn(const char* dest, const char* src) {
    size_t size_dest = Strlen(dest);
    size_t size_src = Strlen(src);
    size_t cnt = 0;
    for (size_t i = 0; i < size_dest; ++i) {
        bool has_found = false;
        for (size_t j = 0; j < size_src; ++j) {
            if (*(dest + i) == *(src + j)) {
                has_found = true;
                break;
            }
        }
        if (has_found) {
            break;
        }
        ++cnt;
    }
    return cnt;
}

const char* Strpbrk(const char* dest, const char* breakset) {
    size_t size_dest = Strlen(dest);
    size_t size_breakset = Strlen(breakset);
    for (size_t i = 0; i < size_dest; ++i) {
        for (size_t j = 0; j < size_breakset; ++j) {
            if (*(dest + i) == *(breakset + j)) {
                return dest + i;
            }
        }
    }
    return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
    if (!str || !pattern) {
        return nullptr;
    }
    size_t size_str = Strlen(str);
    size_t size_pattern = Strlen(pattern);
    if (size_str < size_pattern) {
        return nullptr;
    }
    if (size_pattern == 0) {
        return str;
    }
    for (size_t i = 0; i <= size_str - size_pattern; ++i) {
        bool is_identical = true;
        for (size_t j = 0; j < size_pattern; ++j) {
            if (*(str + i + j) != *(pattern + j)) {
                is_identical = false;
                break;
            }
        }
        if (is_identical) {
            return str + i;
        }
    }
    return nullptr;
}