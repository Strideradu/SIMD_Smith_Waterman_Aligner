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
 * File:   main.cpp
 * Author: Nan
 *
 * Created on April 3, 2017, 7:01 PM
 */

#include <cstdlib>
#include "ReaderFactory.h"
#include "Seq.h"
//#include "Reader.h"
#include "bioparser.h"

using namespace std;
using namespace bioparser;

class Read {
    public:
        Read(uint64_t id, const char* name, uint32_t name_length, const char* data,
            uint32_t data_length)
                : id_(id), name_(name, name_length), data_(data, data_length), quality_() {
        }

        Read(uint64_t id, const char* name, uint32_t name_length, const char* data,
            uint32_t data_length, const char* quality, uint32_t quality_length)
                : id_(id), name_(name, name_length), data_(data, data_length),
                quality_(quality, quality_length) {
        }

        uint64_t id_;
        std::string name_;
        std::string data_;
        std::string quality_;
};
/*
 * 
 */
int main(int argc, char** argv) {
    
    
    ReaderFactory factory;
        
    //FastaReader reader;
    auto reader = createReader<Read, FastaReader>(argv[1]);
    std::vector<std::unique_ptr<Seq>> test;

    return 0;
}

