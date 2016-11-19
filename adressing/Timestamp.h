//
// definition of class modelling a certain moment in time - a timestamp
//

#ifndef ISA_PROJ_TIMESTAMP_H
#define ISA_PROJ_TIMESTAMP_H

#include <iostream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

#include "../BaseObject.h"
#include "../constants.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std;

namespace addressing {
    /**
     * class models certain moment in time
     */
    class Timestamp : public BaseObject {
        const string _name = "TimeStamp";
        /**
         * fomat of the ouput when printed
         */
        const char* TIME_FORMAT = "%Y-%m-%d_%H:%M";

        /**
         * class uses time_point as internal representations
         */
        chrono::system_clock::time_point _startTime;


    public:
        /**
         * creates the object specifies the timepoint
         * @return
         */
        Timestamp();

        Timestamp &operator=(Timestamp other);
        bool operator==(const Timestamp &rhs);
        bool operator!=(const Timestamp &rhs);

        /**
         * @return true if the lease is expired false otherwise
         */
        bool isLeaseExpired();

        /**
         * self explanatory
         * @return
         */
        int countSecondsSinceStarted() const ;

        /**
         * prints timestamp initial time and current time
         */
        void printTimeInfo();

        virtual string toString() const ;
        virtual string getLoggableName() const ;
    };
}


#endif //ISA_PROJ_TIMESTAMP_H
