//
//  ATime.cpp
//  ATime
//
//  Created by Rachel klibowitz on 3/25/18.
//  Copyright © 2018 Rachel klibowitz. All rights reserved.
//

#include "ATime.h"
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;
std::ostream& operator<<(std::ostream& os, ATime at){
    return os <<at.getSVal();
    
};
ATime operator+(const int i,const ATime& t){
    ATime temp;
    temp.m_time=t.m_time+i;
    return temp;
//    ATime temp;
//    temp=t+i;
//    return temp;
};
ATime::ATime(){
    m_time=0;
};
ATime::ATime(string d, string ut){
    int day, mon, yr, hr, min, sec;
    char slash;
    string date=d;
    istringstream is(date);
    is >> mon >> slash >> day >> slash >> yr;
    
    string time=ut;
    istringstream ss(time);
    ss >> hr >> slash >> min >> slash >> sec;
    
    struct tm timeinfo;
    
    timeinfo.tm_mon=mon-1;
    timeinfo.tm_mday=day;
    timeinfo.tm_year=yr-1900;
    timeinfo.tm_hour=hr;
    timeinfo.tm_min=min;
    timeinfo.tm_sec=sec;
    timeinfo.tm_isdst=1;
    m_time=mktime(&timeinfo);
};
ATime::ATime(time_t t){
    m_time=t;
};
std::string ATime::getSVal() const{
    struct tm* p;
    p=localtime(&m_time);
    int m, d, y, hr, min, sec;
    m=p->tm_mon+1;
    d=p->tm_mday;
    y=p->tm_year+1900;
    hr=p->tm_hour;
    min=p->tm_min;
    sec=p->tm_sec;
    std::ostringstream oss;
    oss << m << "/" << d << "/" << y << " " << std::setw(2) << std::setfill('0')
    << hr << ":" << std::setw(2) << std::setfill('0') << min <<  ":" << std::setw(2)
    << std::setfill('0') << sec;
    std::string newstring= oss.str();
    return newstring;
};

bool ATime::isValid() const{
    return m_time!=0;
};
bool ATime::operator<(const ATime &t) const{
    return this->m_time<t.m_time;
};
bool ATime::operator>(const ATime &t) const{
    return this->m_time>t.m_time;
};
bool ATime::operator==(const ATime &t) const{
    return this->m_time==t.m_time;
};
bool ATime::operator!=(const ATime &t) const{
    return this->m_time!=t.m_time;
};
ATime ATime::operator+(const int i) const{
    ATime temp;
    temp.m_time=this->m_time+i;
    return temp;
};
ATime ATime::operator++( ){
    ATime temp;
    temp=this->m_time++;
    return temp;
};   // preinc add one second
ATime ATime::operator++(int i){
    ATime temp;
    temp.m_time=this->m_time;
    this->m_time++;
    return temp;
};         // postinc add one second
ATime& ATime::operator+=(int i){
    this->m_time+=i;
    return *this;
};
int ATime::operator-(const ATime& t) const{
    int temp;
    temp=this->m_time-t.m_time;
    return temp;
};    // return seconds
int ATime::operator-(const int x) const{
    int temp;
    temp=this->m_time-x;
    return temp;
};        // subract seconds






