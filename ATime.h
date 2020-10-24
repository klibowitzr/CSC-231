//
//  ATime.h
//  ATime
//
//  Created by Rachel klibowitz on 3/25/18.
//  Copyright © 2018 Rachel klibowitz. All rights reserved.
//

//#ifndef ATime_hpp
//#define ATime_hpp

//#include <stdio.h>


#ifndef ATIME_H
#define ATIME_H

#include <iostream>
#include <ctime>

class ATime {
    friend std::ostream& operator<<(std::ostream& os, ATime at);
    friend ATime operator+(int, const ATime&);
public:
    ATime();
    ATime(std::string,std::string);  // mm/dd/yyyy  hh:mm:ss
    ATime(time_t t);
    std::string getSVal() const;
    
    bool isValid() const;
    bool operator<(const ATime &) const;
    bool operator>(const ATime &) const;
    bool operator==(const ATime &) const;
    bool operator!=(const ATime &) const;
    ATime operator+(const int)const;
    ATime operator++();            // preinc add one second
    ATime operator++(int);            // postinc add one second
    ATime& operator+=(int);            // add seconds
    int operator-(const ATime&) const;    // return seconds
    int operator-(const int) const;        // subtract seconds
private:
    time_t m_time;
};

#endif

