//
//  Movable.cpp
//  Navy Simulator
//
//  Created by Rachel klibowitz on 4/8/18.
//  Copyright © 2018 Rachel klibowitz. All rights reserved.
//

#include "Movable.h"
#include "Orders.h"
#include <string>
#include <list>
#include <cmath>
#include <math.h>
#include <map>
////#include "SimulationMgr.h"
#define _USE_MATH_DEFINES
using namespace std;
//typedef list<Location> HistoryList;
//typedef std::map<std::string,Movable*> NavyMap;


Location::Location(){X=0; Y=0; Z=0;};
Location::Location(ATime a, double x, double y, double z): t(a), X(x), Y(y), Z(z){};
Location::Location(ATime a, double x, double y): t(a), X(x), Y(y) {Z=0;};
void Location::getXY(double& x_pos, double& y_pos) const{
    x_pos=X;
    y_pos=Y;
};
void Location::getXYZ(double& x_pos, double& y_pos, double& z_pos) const{
    x_pos=X;
    y_pos=Y;
    z_pos=Z;
};
void Location::getLoc(ATime& time, double& x, double& y, double& z) const{
    time=t;
    x=X;
    y=Y;
    z=Z;
};
void Location::printloc(){
    cout << ATime() << " " << X << " " << Y << " " << Z << endl;
};

bool Movable::isDeployed(){
    return currentdstatus;
};

bool Movable::wasDeployed(){
    if (alltimedstatus!=0){
        return true;
    }
    else{
        return false;
    }
};
HistoryList* Movable::getHistory(){
    return &hl;
};

double Movable::RadToDeg(double x){
    return ((x*180)/ M_PI);
    
};
double Movable::DegToRad(double x){
    return ((x * M_PI) /180);
};
ATime Location::getTime(){
    return t;
};
Movable::Movable(){
    NAME=" ";
    ID=" ";
    max_speed=0;
}
Movable::Movable(string n, string id, double ms){
    NAME=n;
    ID=id;
    max_speed=ms;
};
double Movable::getHeading(){
    return heading;
};

std::string Movable::getID(){
    return ID;
};
Location Movable::getBoatLoc(){
    return loc;
};
///////////////////////////////////////////


AircraftCarrier::AircraftCarrier(){
    max_number_of_Aircraft=0;
    max_speed=0;
    NAME=" ";
    ID=" ";
    alltimedstatus=false;
    currentdstatus=false;

};
AircraftCarrier::AircraftCarrier(string n, string id, int a, double ms):Movable(n,id,ms){
    max_number_of_Aircraft=a;
    alltimedstatus=false;
    currentdstatus=false;
};

void AircraftCarrier::print(){
    cout << NAME << " " << (ID) << " " << max_number_of_Aircraft  << " " <<max_speed << endl;
};
void AircraftCarrier::Deploy(ATime t, double x, double y, double h, double s){
    alltimedstatus=true;
    currentdstatus=true;
//    this->heading=h;
    heading=h;
//    this->speed=s;
    speed=s;
    loc=Location(t, x, y);
    hl.push_back(loc);
    cout << "Deploying ship..." << endl;
};

void AircraftCarrier::Change(ATime t, double h, double  s){
//    alltimedstatus=1;
//    currentdstatus=1;
    if(isDeployed()==true){
        if(h>=0){
            heading=h;
        };
        if (s>=0){
            speed=s;
        };
        updatePosition(t);
        cout << "Changing ship orders..." << endl;
    }
    else{
        cout << "Aircraft carrier is not deployed" << endl;
    };
};

void AircraftCarrier::updatePosition(ATime nt){
    if (isDeployed()==true){
        ATime oldtime, newtime=nt;
        double x_pos, y_pos, newx, newy, x, y, distance, elapsedtime, headingrad;
        oldtime=loc.getTime();
        elapsedtime=(newtime-oldtime)/3600.0;
        loc.getXY(x_pos,y_pos);
        distance=elapsedtime*speed;
//        if (heading<0){
//            heading=getHeading();
//        }
        headingrad=DegToRad(heading);
        x=distance*(sin(headingrad));
        y=distance*(cos(headingrad));
        newx=x_pos+x;
        newy=y_pos+y;
        loc=Location(newtime, newx, newy);
        hl.push_back(loc);
    }
    else {
        cout << "Aircraft carrier is not deployed" << endl;
    };
};
    

//////////////////////////////////////////////


Cruiser::Cruiser(){
    NAME=" ";
    ID=" ";
    max_number_of_missiles=0;
    max_speed=0;
    alltimedstatus=false;
    currentdstatus=false;
};
Cruiser::Cruiser(string n, string id, int m, double s):Movable(n, id, s){
    max_number_of_missiles=m;
    alltimedstatus=false;
    currentdstatus=false;
};

void Cruiser::print(){
    cout << NAME << " " << (ID) << " " << max_number_of_missiles << " " << max_speed << endl;
};

void Cruiser::Deploy(ATime t, double x, double y, double h, double s){
    alltimedstatus=true;
    currentdstatus=true;
    heading=h;
    speed=s;
    loc=Location(t, x, y);
    hl.push_back(loc);
    cout << "Deploying ship..." << endl;
};

void Cruiser::updatePosition(ATime nt){
    if(isDeployed()==true){
        ATime oldtime, newtime=nt;
        double x_pos, y_pos, newx, newy, x, y, distance, elapsedtime, headingrad;
        oldtime=loc.getTime();
        elapsedtime=(newtime-oldtime)/3600.0;
        loc.getXY(x_pos,y_pos);
        distance=elapsedtime*speed;
        headingrad=DegToRad(heading);
        x=distance*(sin(headingrad));
        y=distance*(cos(headingrad));
        newx=x_pos+x;
        newy=y_pos+y;
        loc=Location(newtime, newx, newy);
        hl.push_back(loc);
    };
};


void Cruiser::Change(ATime t, double h, double s){
//    alltimedstatus=1;
//    currentdstatus=1;
    if(isDeployed()==true){
        if(h>=0){
            heading=h;
        };
        if(s>=0){
            speed=s;
        }
    //    loc=Location(t, x, y);
    //    hl.push_back(loc);
        //change info here
        updatePosition(t);
        cout << "Changing ship orders..." << endl;
    }
    else{
        cout << "Cruiser is not deployed" << endl;
    };
};


///////////////////////////////////////////////////


Fighter::Fighter(){
    max_speed=0;
    max_ceiling=0;
    max_bombs=0;
    NAME=" ";
    ID=" ";
    //shipID= " ";
    alltimedstatus=false;
    currentdstatus=false;

};
Fighter::Fighter(string n, string id, Movable* sid, double s, double c, int b) :
Movable(n,id,s), max_ceiling(c), shipID(sid), max_bombs(b){islanding=false; alltimedstatus=false; currentdstatus=false;};

void Fighter::print(){
    cout << NAME << " " << ID << " " <<  (shipID)->getID() << " " << max_speed << " " << max_ceiling << " " << max_bombs << endl;
};
bool Fighter::Landing(){
    return islanding;
};
void Fighter::Land(ATime t, Movable* b){
    alltimedstatus=true;
    currentdstatus=true;
    islanding=true;
    shipID=b;
    //updatePosition(t); //commented this out because it was causing a duplicate Location print?
    cout << "Landing fighter..." << endl;
};

void Fighter::Deploy(ATime t, double h, double s, double a){
    alltimedstatus=true;
    currentdstatus=true;
    islanding=false;
    double x, y;
    heading=h;
    speed=s;
    altitude=a;
    loc=shipID->getBoatLoc();
    loc.getXY(x, y);
    loc=Location(t, x, y, a);
    hl.push_back(loc);
    cout << "Deploying aircraft..." << endl;
};

void Fighter::Change(ATime t, double h, double s, double a){
//    alltimedstatus=1;
//    currentdstatus=1;
   // updatePosition(t);
    if(isDeployed()==true){
        if((h>=0)||(Landing()!=true)){
            this->heading=h;
        };
        if(s>=0){
          speed=s;
        };
        if(a>=0){
         altitude=a;
        };
    //    loc=getXYZ(t, double x, double y, double z);
    //    hl.push_back(loc);
        updatePosition(t);
        cout << "Changing aircraft orders..." << endl;
    }
    else{
        cout << "Fighter was never deployed" << endl;
    };
};

void Fighter::updatePosition(ATime nt){
    if(isDeployed()==true){
        ATime oldtime, newtime=nt;
        double x_pos, y_pos, newx, newy, x, y, distance, elapsedtime, headingrad;
        oldtime=loc.getTime();
        elapsedtime=(newtime-oldtime)/3600.0;
        loc.getXY(x_pos,y_pos);
        distance=elapsedtime*speed;
        headingrad=DegToRad(heading);
        x=distance*(sin(headingrad));
        y=distance*(cos(headingrad));
        newx=x_pos+x;
        newy=y_pos+y;//calculates new coordinates of fighter
        if(islanding==true){
            double landingradius, landingdistance, temp, bx, by, xdistance, ydistance;
            loc=shipID->getBoatLoc();
            loc.getXY(bx, by);
            //xdistance=bx-newx;
            //ydistance=by-newy;
            xdistance=bx-newx;
//            if(xdistance<0){
//                xdistance=newx-bx;
//            };
            ydistance=by-newy;
//            if(ydistance<0){
//                ydistance=newy-by;
//            };
            ////temp=sqrt(xdistance)+sqrt(ydistance);
            landingdistance=sqrt(pow(xdistance,2)+ pow(ydistance,2));
            //landingdistance=sqrt(temp);
            landingradius=speed/60.0;
                if(landingradius>=landingdistance){
                loc=shipID->getBoatLoc();
                    hl.push_back(loc);
                currentdstatus=false;
                }
                else{ //landingdistance>radius
                heading=RadToDeg(atan2(xdistance,ydistance));
                    if (heading<0){
                        heading+=360;
                        
                    };
                        loc=Location(newtime, newx, newy, altitude);
                        hl.push_back(loc);
                };
            }
        else{
            loc=Location(newtime, newx, newy, altitude);
            hl.push_back(loc);
        };
    }
    else{
        loc=shipID->getBoatLoc();
    }
};
//////////////////////////////////////////////////////


