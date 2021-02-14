/**
* @brief Assignment DNA Strand
* @name Randy Randall
*/

#include <iostream>
#include <string>
#include <cstring>
#include "DNAStrand.h"
using namespace std;


DNAStrand::DNAStrand(const char* startingString){
   length = strlen(startingString);
   bases = new char[length];
   for(int i = 0; i < length; i++)
       if(startingString[i] != 'A' && startingString[i] != 'C' && startingString[i] != 'G' && startingString[i] != 'T')
           throw logic_error("Enter DNA values A, C, G, or T");
       else{
           bases[i] = startingString[i];
       }

}

DNAStrand::DNAStrand(const DNAStrand& other){
    length = other.length;

    //allocate our own storage
    bases = new char[length];

    for(int i = 0; i < length; i++) {
        bases[i] = other.bases[i];
    }
}


DNAStrand& DNAStrand::operator=(const DNAStrand& other){
    //avoid self assignment
    if(this != &other) {
        //clear old storage
        delete [] bases;

        length = other.length;

        bases = new char[length];


        for(int i = 0; i < length; i++) {
            bases[i] = other.bases[i];
        }
    }

    return *this;

}

DNAStrand::~DNAStrand() {
    delete [] bases;
}

bool DNAStrand::operator==(const DNAStrand& other) const{
    if(length != other.length)
        return false;

    //Same size, walk through items looking for mismatch
    for(int i = 0; i < length; i++) {
        if(bases[i] != other.bases[i])
            return false;
    }

    //Must be identical
    return true;


}

char DNAStrand::operator[](int index) const{
    if(index < 0 || index >= length)
        throw out_of_range("Bad index for [ ]: " + to_string(index));

    return bases[index];
}

DNAStrand DNAStrand::operator+(const DNAStrand& other) const{
    DNAStrand temp(this->getLength() + other.getLength());
    int j = 0;

    for(int i = 0; i < this->getLength(); i++, j++) {
        temp.bases[j] = this->bases[i];
    }

    for(int i = 0; i < other.getLength(); i++, j++) {
       temp.bases[j] = other.bases[i];
    }

    return temp;
}


//Declare as friend... declared after class
std::ostream& operator<<(std::ostream& dest, const DNAStrand& source){

    for(int i = 0; i < source.length; i++) {
         dest << source.bases[i];
    }

    return dest;
}

int DNAStrand::getLength() const{
    return length;
}


DNAStrand DNAStrand::getComplement() const{

    DNAStrand temp2(length);

    for(int i = 0; i < length; i++){
        switch(bases[i]) {
           case 'A' :
              temp2.bases[i] = 'T';
              break;
           case 'C' :
              temp2.bases[i] = 'G';
              break;
           case 'T' :
              temp2.bases[i] = 'A';
              break;
           case 'G' :
              temp2.bases[i] = 'C';
              break;
        default:
            cout << "invalid";
        }
    }
    return temp2;
}

DNAStrand DNAStrand::substr(int start, int length) const{

    int endIndex = start + length;
    if((start < 0 || length < 0) || (endIndex > this->length))
        throw out_of_range("Bad data");

    DNAStrand temp3(length);
    int j = start;
    for(int i = 0; i < length; i++, j++) {
        temp3.bases[i] = this->bases[j];
    }

    return temp3;

}

DNAStrand::DNAStrand(int length){
    this->length = length;
    bases = new char[length];

}
