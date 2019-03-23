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
    int size;                               //number of parts;

public:
    explicit SimpleElement(std::string s);  //every single part in this element

    int appendSize(SimpleElement se);       //get size of common part of nucleotides between this tail and next head
    std::string getTail(unsigned int p);
    std::string getHead(unsigned int p);

    std::string getValue();
    int getSize();
    virtual std::vector<SimpleElement>* getParts();
};

/*
 * this class represents single, complex chain of nucleotides and it's parts
 */

class Element : SimpleElement {
protected:
    std::vector<SimpleElement> *parts;          //actual parts

public:
    explicit Element(std::string s);
    ~Element();

    bool appendElement(Element e, unsigned int p); //append element on given size of common part,

    std::vector<SimpleElement>* getParts();

};

#endif //BIOINF_ELEMENT_H
