//
// definition of base eception
//

#ifndef ISA_PROJ_BASEEXCEPTION_H
#define ISA_PROJ_BASEEXCEPTION_H


#include "../BaseObject.h"

using namespace std;

/**
 * class serves as a common superclass to all project exceptions,
 * this way it is possible to catch everything in one catch black if neccessary
 */
class BaseException : BaseObject {
protected:
    string _name = "BaseException";
    string _msg;
public:
    BaseException():_msg("NULL"){}

    /**
     * @return tho content of the message
     */
    virtual string what();
    /**
     * @return string representations
     */
    virtual string toString() const ;
    virtual string getLoggableName() const ;
};


#endif //ISA_PROJ_BASEEXCEPTION_H
