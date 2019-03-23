//
// Created by wojtek on 23.03.19.
//

#include "Element.h"

Element::Element(std::string s) : SimpleElement(s) {
    this->parts = new std::vector<SimpleElement>();
    this->parts->emplace_back(SimpleElement(s));
}

Element::~Element() {
    this->parts->clear();
    this->parts->shrink_to_fit();
    delete this->parts;
}

std::vector<SimpleElement>* Element::getParts() {
    return this->parts;
}

bool Element::appendElement(Element e, unsigned int p) {
    //try to append element e on p common nucleotides
    std::string s1 = this->getTail(p);
    std::string s2 = e.getHead(p);
    if(s1 == s2){
        this->value += e.getTail((int)e.getValue().size()-p);
        this->size += e.getSize();
        this->parts->insert(this->parts->end(), e.getParts()->begin(), e.getParts()->end());
        return true;
    } else {
        return false;
    }

}

SimpleElement::SimpleElement(std::string s) {
    this->value = s;
    this->size = 1;
}

std::string SimpleElement::getValue() {
    return this->value;
}

int SimpleElement::getSize() {
    return this->size;
}

std::vector<SimpleElement>* SimpleElement::getParts() {
    return nullptr;
}

std::string SimpleElement::getHead(unsigned int p) {
    return this->value.substr(0,p);
}

std::string SimpleElement::getTail(unsigned int p) {
    return this->value.substr(std::max(0, (int)this->value.size()-(int)p), (unsigned int)this->value.size());
}

int SimpleElement::appendSize(SimpleElement se) {
    unsigned int l = std::max((int)std::min(se.getValue().size(), this->value.size()) - 1,0);
    while(l>0){
        if(se.getHead(l) == this->getTail(l)){
            return l;
        }
        l--;
    }
    return 0;
}