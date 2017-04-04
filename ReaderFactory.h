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
 * File:   ReaderFactory.h
 * Author: Nan
 *
 * Created on April 4, 2017, 1:40 PM
 */

#ifndef READERFACTORY_H
#define READERFACTORY_H
#include <memory>
#include "Reader.h"
#include "FastaReader.h"


/*
 *  class for reader factory
 */
class ReaderFactory {
public:
    ReaderFactory();
    virtual ~ReaderFactory();
    
    /** \brief Copy constructor disabled */
    ReaderFactory(const ReaderFactory& orig);
    
    /** \brief Create the reader
     * \returns New reader object */
    template<class T, template<class T_> class U>
    std::unique_ptr<Reader<T>> Create(const std::string& path);
protected:  

    
private:

};

#endif /* READERFACTORY_H */

