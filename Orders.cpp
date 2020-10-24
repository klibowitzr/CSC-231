//
//  Orders.cpp
//  Navy Simulator
//
//  Created by Rachel klibowitz on 3/27/18.
//  Copyright © 2018 Rachel klibowitz. All rights reserved.
//

#include "Orders.h"
#include "ATime.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Movable.h"
using namespace std;


bool Order::operator==(const Order& o){
    return (this->etime==o.etime);
};
bool Order::operator<(const Order& o){
    return (this->etime<o.etime);
};
bool Order::operator>(const Order& o){
    return (this->etime>o.etime);
};
bool Order::operator!=(const Order& o){
    return (this->etime!=o.etime);
};
ATime Order::exectime() const{
    return etime;
};


Order::Order(ATime t, std::string id):etime(t), iD(id){};


DeployShip::DeployShip(){etime=0; iD=" ";heading=0;speed=0;x=0;y=0;};

DeployShip::DeployShip(string d, string t, string id, double xcoord, double ycoord, double h, double s): Order(ATime(d,t),id), x(xcoord), y(ycoord), heading(h), speed(s){printtime=ATime(d,t).getSVal(); printtime=ATime(d,t).getSVal(); };

void DeployShip::print(){
    cout << printtime << " " << iD << " " << x << " " << y << " " << heading << " " << speed << endl;
};
bool DeployShip::Execute(Movable* mp, ATime t){

    mp->Deploy(t, x, y, heading, speed);
        return true;
    };



DeployAircraft::DeployAircraft(){etime=0; iD=" ";heading=0; speed=0; altitude=0;};

DeployAircraft::DeployAircraft(string d, string t, string id, double h, double s, double a): Order(ATime(d,t),id), heading(h), speed(s), altitude(a){printtime=ATime(d,t).getSVal();};

void DeployAircraft::print(){
    cout << printtime << " " << iD << " " << heading << " " << speed << " " << altitude << endl;
};

bool DeployAircraft::Execute(Movable* mp, ATime t){

    mp->Deploy(t,heading,speed,altitude);
    return true;
};

ChangeAircraftOrders::ChangeAircraftOrders(){etime=0; iD=" ";heading=0; speed=0; altitude=0;};

ChangeAircraftOrders::ChangeAircraftOrders(string d, string t, string id, double h, double s, double a):Order(ATime(d,t),id), heading(h), speed(s), altitude(a){printtime=ATime(d,t).getSVal();};

void ChangeAircraftOrders::print(){
    cout << printtime << " " << iD << " " << heading << " " << speed << " " << altitude << endl;
};

bool ChangeAircraftOrders::Execute(Movable* mp, ATime t){
    mp->Change(t, heading, speed, altitude);
    return true;
}


LandAircraft::LandAircraft(){etime=0; iD=" ";};

LandAircraft::LandAircraft(string d, string t, Movable* sid,string aid):Order(ATime(d,t),aid), shipID(sid){printtime=ATime(d,t).getSVal();};
//switched orders of sid and aid
void LandAircraft::print(){
    cout << printtime << " " << shipID->getID() << " " << iD << endl;
};

bool LandAircraft::Execute(Movable* mp, ATime t){
    Fighter* ap;
    ap=dynamic_cast<Fighter*>(mp);
    if(ap){
        ap->Land(t,shipID);
        return true;
    }
    else{
        cout << "Problem with executing land order in Orders.cpp" << endl;
        return false;
    }
};

ChangeShipOrders::ChangeShipOrders(){etime=0; iD=" ";heading=0;speed=0;};

ChangeShipOrders::ChangeShipOrders(string d, string t, string id, double h, double s):Order(ATime(d,t),id), heading(h), speed(s){printtime=ATime(d,t).getSVal();};

void ChangeShipOrders::print(){
    cout << printtime << " " << iD << " " << heading << " " << speed << endl;
};

bool ChangeShipOrders::Execute(Movable* mp, ATime t){
    mp->Change(t, heading, speed);
    return true;
};
string Order::get_id() const {
    return iD;
};
