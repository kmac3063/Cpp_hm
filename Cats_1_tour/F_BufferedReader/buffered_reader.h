#pragma once

#include <algorithm>

class BufferedReader {
 private:
    char *my_buf;
    int32_t pos = 0;
    int32_t len = 0;

 public:
    explicit BufferedReader(PackageStream* stream) {
        char* buf_str = new char[stream->PackageLen()];
        int32_t t = 0;


        while ((t = stream->ReadPackage(buf_str)) != 0) {
            char* buf_tmp = new char[len];
            for (int i = 0; i < len; i++) {
                buf_tmp[i] = my_buf[i];
            }

            if (len != 0)
                delete[] my_buf;
            my_buf = new char[len + t];

            for (int i = 0; i < len; i++)
                my_buf[i] = buf_tmp[i];
            delete[] buf_tmp;

            for (int i = 0; i < t; i++) {
                my_buf[len + i] = buf_str[i];
            }

            len += t;
        }

        delete[] buf_str;
    }

    ~BufferedReader() {
        if (len > 0)
            delete[] my_buf;
    }

    int32_t Read(char* output_buffer, int32_t buffer_len) {
        int32_t len_ = min<int32_t>(buffer_len, len - pos);
        memcpy(output_buffer, my_buf + pos, len_);

        pos += len_;
        return len_;
    }
};
