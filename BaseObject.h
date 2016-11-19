#ifndef ISA_PROJ_BASEOBJECT_H
#define ISA_PROJ_BASEOBJECT_H

#include <iostream>

using namespace std;

/**
 * Common superclass for all classes in the project,
 * contains virtual methods that every class has to implements
 */
class BaseObject {
public:
    /**
     * @return the string representation of given object and its state
     */
    virtual string toString() const = 0;

    /**
     * @return name of the class for logging system( could be useful in the future)
     */
    virtual string getLoggableName() const = 0;
};


#endif //ISA_PROJ_BASEOBJECT_H
