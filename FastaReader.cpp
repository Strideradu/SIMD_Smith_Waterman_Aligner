/*
 * The MIT License
 *
 * Copyright 2017 Nan.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* 
 * File:   FastaReader.cpp
 * Author: Nan
 * 
 * Created on April 4, 2017, 2:44 PM
 */

#include "FastaReader.h"

template<class T>
FastaReader<T>::~FastaReader() {
}

/** \brief read fasta object
* \param dst 
* \param max_butes
* \returns status
*/
template<class T>
bool FastaReader<T>::read_objects(std::vector<std::unique_ptr<T>>& dst, uint64_t max_bytes) {

    bool status = false;
    uint64_t current_bytes = 0;
    uint64_t total_bytes = 0;

    std::string name(kSmallBufferSize, 0);
    uint32_t name_length = 0;

    char* data = &this->large_buffer_[0];
    uint32_t data_length = 0;

    // unique_ptr<FILE> to FILE*
    auto input_file = this->input_file_.get();
    bool is_end = feof(input_file);

    bool is_valid = false;
    uint32_t line_number = 0;

    while (!is_end) {

        uint64_t read_bytes = fread(this->buffer_.data(), sizeof(char),
            kSmallBufferSize, input_file);
        is_end = feof(input_file);

        total_bytes += read_bytes;
        if (max_bytes != 0 && total_bytes > max_bytes) {
            fseek(input_file, -(current_bytes + read_bytes), SEEK_CUR);
            status = true;
            break;
        }

        for (uint32_t i = 0; i < read_bytes; ++i) {
            auto c = this->buffer_[i];

            if (c == '\n') {
                ++line_number;
                if (is_end && i == read_bytes - 1) {
                    is_valid = true;
                }
            } else if (c == '>' && line_number != 0) {
                is_valid = true;
                line_number = 0;
            } else {
                switch (line_number) {
                    case 0:
                        if (name_length < kSmallBufferSize) {
                            if (!(name_length == 0 && (c == '>' || isspace(c)))) {
                                name[name_length++] = c;
                            }
                        }
                        break;
                    default:
                        data[data_length++] = c;
                        if (data_length >= this->large_buffer_.size()) {
                            this->large_buffer_.resize(kLargeBufferSize, 0);
                            data = &this->large_buffer_[0];
                        }
                        break;
                }
            }

            ++current_bytes;

            if (is_valid) {
                while (name_length > 0 && isspace(name[name_length - 1])) {
                    --name_length;
                }
                while (data_length > 0 && isspace(data[data_length - 1])) {
                    --data_length;
                }

                dst.emplace_back(std::unique_ptr<T>(new T(this->num_objects_read_,
                    name.c_str(), name_length, (const char*) data, data_length)));

                this->num_objects_read_ += 1;
                current_bytes = 0;

                name_length = 0;
                data_length = 0;
                is_valid = false;
            }
        }
    }

    return status;
}
