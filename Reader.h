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
 * File:   Reader.h
 * Author: Nan
 *
 * Created on April 3, 2017, 8:25 PM
 */

#ifndef READER_H
#define READER_H

#include <vector>
#include <memory>
#include <stdio.h>

constexpr uint32_t kSmallBufferSize = 4 * 1024; // 4 kB
constexpr uint32_t kMediumBufferSize = 5 * 1024 * 1024; // 5 MB
constexpr uint32_t kLargeBufferSize = 500 * 1024 * 1024; // 500 MB

/**
 * \brief Class readers for sequence file
 *
 * Reader for read file, may extend to read alignment file
 */
template<class T>
class Reader {
public:
    virtual ~Reader();
    
    // virtual function to read object
    virtual bool read_objects(std::vector<std::unique_ptr<T>>& dst, uint64_t max_bytes) = 0;

protected:
    /** \brief Constructor */
    Reader(FILE* input_file): input_file_(input_file, fclose), buffer_(kSmallBufferSize, 0),num_objects_read_(0) {}                
    
    /** \brief Copy constructor disabled */
    Reader(const Reader& orig) = delete;
    
    /** \brief Assignment constructor disabled */
    const Reader& operator=(const Reader&) = delete;
    
    std::unique_ptr<FILE, int(*)(FILE*)> input_file_;
    std::vector<char> buffer_;
    uint64_t num_objects_read_;
    
private:

};

#endif /* READER_H */

