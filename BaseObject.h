//
// Created by david on 5.10.16.
//

#ifndef ISA_PROJ_BASEOBJECT_H
#define ISA_PROJ_BASEOBJECT_H

#include <iostream>

using namespace std;

class BaseObject {
public:
    virtual string toString() const = 0;

    virtual string getLoggableName() const = 0;
};


#endif //ISA_PROJ_BASEOBJECT_H
