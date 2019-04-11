//
// Created by wojtek on 23.03.19.
//

#ifndef BIOINF_ELEMENT_H
#define BIOINF_ELEMENT_H

// class representing single nucleotide chain

#include "Define.h"

/*
 * this class presents single, basic chain of nucleotides
 */

class SimpleElement {
private:

protected:
    std::string value;                      //nucleotides in this element

public:
    int size;                               //number of parts;

    SimpleElement(std::string s);  //every single part in this element
    ~SimpleElement()  = default;

    int appendSize(SimpleElement se);       //get size of common part of nucleotides between this tail and next head
    const std::string getTail(unsigned int p);
    const std::string getHead(unsigned int p);

    std::string getValue();
    int getSize();
    virtual std::vector<SimpleElement> * getParts();

//    bool operator = (const SimpleElement e) const {
//        return this->size == e.size;
//    }
//
//    bool operator < (const SimpleElement e) const {
//        return this->size < e.size;
//    }
//
//    bool operator > (const SimpleElement e) const {
//        return this->size > e.size;
//    }

    virtual std::string getValueFromParts();
};

/*
 * this class represents single, complex chain of nucleotides and it's parts
 */

class Element : public SimpleElement {
protected:
    std::vector<SimpleElement> parts;          //actual parts

public:
    Element(std::string s);
    ~Element();

    bool appendElement(Element e, unsigned int p); //append element on given size of common part,

    std::vector<SimpleElement> * getParts();

    int calculateTotalLengthOfParts();

    std::string getValueFromParts();

    void trimToSize(unsigned long size);

//    bool operator = (const Element e) const {
//        return this->size == e.size;
//    }
//
//    bool operator < (const Element e) const {
//        return this->size < e.size;
//    }
//
//    bool operator > (const Element e) const {
//        return this->size > e.size;
//    }

//    std::string getTail(unsigned int p);
//    std::string getHead(unsigned int p);

};

#endif //BIOINF_ELEMENT_H
