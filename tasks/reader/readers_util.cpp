#include "readers_util.h"

LimitReader::LimitReader(std::unique_ptr<Reader> reader, size_t limit) : limit_(limit) {
    reader_ = std::move(reader);
}

size_t LimitReader::Read(char* buf, size_t len) {
    size_t read_bytes = reader_->Read(buf, std::min(len, limit_));
    limit_ -= read_bytes;
    buf[read_bytes] = '\0';
    return read_bytes;
}

TeeReader::TeeReader(std::vector<std::unique_ptr<Reader>> readers) {
    readers_ = std::move(readers);
}

size_t TeeReader::Read(char* buf, size_t len) {
    size_t pos = 0;
    for (const std::unique_ptr<Reader>& reader : readers_) {
        pos += reader->Read(buf + pos, len - pos);
        current_++;
    }
    return pos;
}

HexDecodingReader::HexDecodingReader(std::unique_ptr<Reader> reader) {
    reader_ = std::move(reader);
}

size_t HexDecodingReader::Read(char* buf, size_t len) {
    const int hex_base = 16;
    const int base = 10;
    const size_t symbol_length = 2;
    char cur_symb[symbol_length];
    size_t pos = 0;
    while (len > 0 && reader_->Read(cur_symb, std::min(symbol_length, len)) != 0) {
        int first_digit = 0;
        int second_digit = 0;
        if ('0' <= cur_symb[0] && cur_symb[0] <= '9') {
            first_digit = cur_symb[0] - '0';
        } else {
            first_digit = cur_symb[0] - 'a' + base;
        }
        if ('0' <= cur_symb[1] && cur_symb[1] <= '9') {
            second_digit = cur_symb[1] - '0';
        } else {
            second_digit = cur_symb[1] - 'a' + base;
        }
        buf[pos++] = static_cast<char>(first_digit * hex_base + second_digit);
        len -= 2;
    }
    return pos;
}