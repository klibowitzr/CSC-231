//
//  Orders.h
//  Navy Simulator
//
//  Created by Rachel klibowitz on 3/27/18.
//  Copyright © 2018 Rachel klibowitz. All rights reserved.
//
//

#ifndef Orders_h
#define Orders_h
#include "ATime.h"
#include <string>
#include <iostream>
#include "Movable.h"


class Order {
public:
    bool operator==(const Order& o);
    bool operator<(const Order& o);
    bool operator>(const Order& o);
    bool operator!=(const Order& o);
    ATime exectime() const;
    std::string get_id() const;
    virtual bool Execute(Movable*, ATime)=0;  // make pure virtual
    Order(){};
    Order(ATime, std::string);
    virtual void print(){};
    virtual ~Order(){};
   
protected:
    ATime etime;
    std::string iD;
    std::string printtime;
};

class DeployShip: public Order{
public:
    DeployShip();
    DeployShip(std::string, std::string, std::string, double, double, double, double);
    void print();
    bool Execute(Movable*, ATime);

protected:
    double heading;
    double speed;
    double x;
    double y;
};

class DeployAircraft: public Order{
public:
    DeployAircraft();
    DeployAircraft(std::string, std::string, std::string, double, double, double);
    void print();
    bool Execute(Movable*, ATime);

protected:
    double heading;
    double speed;
    double altitude;
};

class ChangeAircraftOrders: public Order{
public:
    ChangeAircraftOrders();
    ChangeAircraftOrders(std::string, std::string, std::string, double, double, double);
    void print();
    bool Execute(Movable*, ATime);

protected:
    double heading;
    double speed;
    double altitude;
};

class LandAircraft: public Order{
public:
    LandAircraft();
    LandAircraft(std::string, std::string, Movable*, std::string);
    void print();
    bool Execute(Movable*, ATime);

protected:
    Movable* shipID;
};

class ChangeShipOrders: public Order{
public:
    ChangeShipOrders();
    ChangeShipOrders(std::string, std::string, std::string, double, double);
    void print();
    bool Execute(Movable*, ATime);

    
protected:
    double heading;
    double speed;
};

#endif  //Orders_h 
