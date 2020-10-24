//
//  Movable.hpp
//  Navy Simulator
//
//  Created by Rachel klibowitz on 4/8/18.
//  Copyright © 2018 Rachel klibowitz. All rights reserved.
//

#ifndef Movable_h
#define Movable_h

#include <stdio.h>
#include "ATime.h"
//#include "Orders.h"
#include <string>
#include <cmath>
#include <list>


class Location{
public:
    void getXY(double& x_pos, double& y_pos) const;
    void getXYZ(double& x_pos, double& y_pos, double& z_pos) const;
    Location();
    Location(ATime, double, double, double);
    Location(ATime, double, double);
    void printloc();
    ATime getTime();
    void getLoc(ATime&, double&, double&, double&) const;
    
protected:
    double X;
    double Y;
    double Z;
    ATime t;
};
typedef std::list<Location> HistoryList;

class Movable{
public:
    Movable();
    Movable(std::string, std::string, double);
    bool isDeployed();
    bool wasDeployed();
    virtual void updatePosition(ATime){}; //make pure virtual
    HistoryList* getHistory();
    virtual void print(){};
    virtual void Deploy(ATime, double, double, double, double){}; //for deploy ship
    virtual void Deploy(ATime, double, double, double){};//for deploy aircraft
    virtual void Change(ATime, double, double){}; //for changing ship orders
    virtual void Change(ATime, double, double, double){}; //for changing aircraft orders
    double RadToDeg(double);
    double DegToRad(double);
    double getHeading();
    std::string getID();
    Location getBoatLoc();
    virtual ~Movable(){};
    

protected:
    std::string NAME;
    std::string ID;
    double max_speed;
    //Location locaton;
    double speed;
    double heading;
    bool currentdstatus;
    bool alltimedstatus;
    HistoryList hl;
    Location loc;
   // Location bloc;
//    Movable* landingboat;
   
};

class AircraftCarrier:public Movable{
public:
    AircraftCarrier();
    AircraftCarrier(std::string, std::string, int, double);
    void print();
    void Deploy(ATime, double, double, double, double);
    void Change(ATime, double, double);
    void updatePosition(ATime);
protected:
    int max_number_of_Aircraft;
};

class Cruiser:public Movable{
public:
    Cruiser();
    Cruiser(std::string, std::string, int, double);
    void print();
    void Deploy(ATime, double, double, double, double);
    void Change(ATime, double, double);
    void updatePosition(ATime);
protected:
    int max_number_of_missiles;
};

class Fighter:public Movable{
public:
    Fighter();
    Fighter(std::string, std::string, Movable*, double, double, int);
    void print();
    void Land(ATime, Movable*);
    void Deploy(ATime, double, double, double);
    void Change(ATime, double, double, double);
    Location GetBoatLoc(Movable*);
    void updatePosition(ATime);
    bool Landing();
protected:
    double max_ceiling;
    int max_bombs;
    //std::string shipID;
    Movable* shipID;
    bool islanding;
    double altitude;
};

#endif /* Movable_h */
