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
 * File:   FastaReader.h
 * Author: Nan
 *
 * Created on April 4, 2017, 2:44 PM
 */

#ifndef FASTAREADER_H
#define FASTAREADER_H

#include "Reader.h"

/**
 * \brief Class readers for fasta file
 *
 * Reader for fasta file, derived from Reader.h
 */
template<class T>
class FastaReader: public Reader<T> {
public:
    virtual ~FastaReader();
    bool read_objects(std::vector<std::unique_ptr<T>>& dst, uint64_t max_bytes);
    //friend std::unique_ptr<Reader<T>> createReader<T, FastaReader>(const std::string& path);
private:
    /** \brief Constructor */
    FastaReader(FILE* input_file): Reader<T>(input_file), large_buffer_(kMediumBufferSize, 0) {}
    
    /** \brief Copy constructor disabled */
    FastaReader(const FastaReader&) = delete;
    
    /** \brief Assignment constructor disabled */
    const FastaReader& operator=(const FastaReader&) = delete;

    std::vector<char> large_buffer_;
};

#endif /* FASTAREADER_H */

