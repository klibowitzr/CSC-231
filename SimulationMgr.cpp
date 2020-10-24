//
//  SimulationMgr.cpp
//  Navy Simulator
//
//  Created by Rachel klibowitz on 4/9/18.
//  Copyright © 2018 Rachel klibowitz. All rights reserved.
//

#include "SimulationMgr.h"
#include "ATime.h"
#include "Orders.h"
#include "Movable.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <algorithm>

using namespace std;
static bool cmp( Order* a, const Order* b){
    return(*a < *b);
};

bool SimulationMgr::simInit(string fname){
        std::string date;
        std::string time;
        std::string name;
        std::string iD;
        std::string sid;
        int max_aircraft;
        int max_missiles;
        int max_bombs;
        double max_speed;
        double max_ceiling;
        double start_x;
        double start_y;
        double heading;
        double speed;
        double altitude;

    string s, opcode;
    fstream fin;
    fin.open(fname);
    if(fin.fail()){
        cout << "file failed to open" << endl;
        return false;
    }
    else{
    while (getline(fin,s)){
        if(s.length()==0 || s[0]=='#' || s[0]==' '){
            continue;
        }
            else{
                    istringstream is(s);
                    is>>opcode;
                    if (opcode=="StartSim"){
                        if(is>>date>>time)
                            ;
                        Start=ATime(date,time);
                    }
                    else if(opcode=="StopSim"){
                        if(is>>date>>time)
                            ;
                        Stop=ATime(date,time);
                    }
                    else if(opcode=="CreateAircraftCarrier"){
                        if(is >> name >> iD >> max_aircraft >> max_speed)
                            ;
                        Movable* mp = new AircraftCarrier(name, iD, max_aircraft, max_speed);
                        nm[iD]=mp;
                
                    }
                    else if(opcode=="CreateCruiser"){
                        if(is >> name >> iD >> max_missiles >> max_speed)
                            ;
                        Movable* mp = new Cruiser(name, iD, max_missiles, max_speed);
                        nm[iD]=mp;
                    }
                    else if (opcode=="CreateFighter"){
                        if(is >> name >> iD >> sid >> max_speed >> max_ceiling >> max_bombs)
                            ;
                        NavyMap::iterator nmi;
                        nmi=nm.find(sid);
                        if(nmi!=nm.end()){
                            Movable* mp = new Fighter(name, iD, nmi->second, max_speed, max_ceiling, max_bombs);
                            nm[iD]=mp;
                        };
                    }
                    else if (opcode=="DeployShip"){
                        if(is >> date >> time >> iD >> start_x >> start_y >> heading >> speed)
                            ;
                        Order* p= new DeployShip(date, time, iD, start_x,start_y, heading, speed);
                        oq.push_back(p);
            
                    }
                    else if (opcode=="DeployAircraft"){
                        if(is >> date >> time >> iD >> heading >> speed >> altitude)
                            ;
                        Order* p= new DeployAircraft(date, time, iD, heading, speed, altitude);
                        oq.push_back(p);
                    }
                    else if (opcode=="ChangeAircraftOrders"){
                        if(is >> date >> time >> iD >> heading >> speed >> altitude)
                            ;
                        Order* p= new ChangeAircraftOrders(date, time, iD, heading, speed, altitude);
                        oq.push_back(p);
                    }
                    else if (opcode=="LandAircraft"){
                        if(is >> date >> time >> sid >> iD)
                            ;
                        NavyMap::iterator nmi;
                        nmi=nm.find(sid);
                        if(nmi!=nm.end()){
                            Order* p= new LandAircraft(date, time,  nmi->second,iD);
                            oq.push_back(p);
                        }
                        else{
                            cout << "problem with processing land order in SimInit" << endl;
                        }
                        
                                            }
                    else if (opcode=="ChangeShipOrders"){
                        if(is >> date >> time >> iD >> heading >> speed)
                            ;
                        Order* p= new ChangeShipOrders(date, time, iD, heading, speed);
                        oq.push_back(p);
                    }
                    else{
                        cout << "Order not valid." << opcode << endl;
                    };
                sort(oq.begin(),oq.end(),cmp);
                };

            
            }
    return true;
    };
};
void SimulationMgr::printHistory() {
    NavyMap::iterator nmi;
    for (nmi=nm.begin(); nmi!=nm.end(); nmi++) {
        if (nmi->second->isDeployed() || (nmi->second->wasDeployed()) ) {
            cout << (nmi->second)->getID() << ":\n";
            // get the movable object's history list
            HistoryList* hlp = (nmi->second)->getHistory();
            HistoryList::iterator hlpi;
            // iterate through it, printing out the locations
            // this assumes that Location has overloaded
            // operator<<.   You could call hlpi->print() instead
            for (hlpi=hlp->begin(); hlpi!=hlp->end(); hlpi++) {
                ATime t;
                double x,y,z;
                hlpi->getLoc(t,x,y,z);
                hlpi->printloc();// print time and position
                //cout << (*hlpi) << endl;
            }
        }
        else {
            cout << (nmi->second)->getID() << " was never deployed\n";
        }
    }
}

void SimulationMgr::printOrders(){
    
    OrderQueue:: iterator oqi;
    for(oqi=oq.begin();oqi!=oq.end();oqi++){
        (*oqi)->print();

    };
};
void SimulationMgr::printNavy(){
   
    NavyMap:: iterator nmi;
    for(nmi=nm.begin(); nmi!=nm.end(); nmi++){
        cout << nmi->first << " ";
        (nmi->second)->print();

    };
};
void SimulationMgr::simDoUpdate(ATime now) {
    Order* oP;
    NavyMap::iterator nmi;
    
    while (oq.size()) {
        oP = oq.front();
        if (oP->exectime() > now) break;
        oq.pop_front();
        
        nmi = nm.find(oP->get_id());
        
        if (nmi != nm.end()) {
            oP->Execute(nmi->second,now);
        }
        delete oP;
    }
    sendUpdateCmd(now);
};

ATime SimulationMgr::getStart() const{
    return Start;
};
ATime SimulationMgr::getStop() const{
    return Stop;
};
NavyMap* SimulationMgr::getNavy(){
    return (&nm);
};
void SimulationMgr::sendUpdateCmd(ATime t){
    NavyMap::iterator mi;
    for (mi = nm.begin(); mi != nm.end(); mi++) {
        (mi->second)->updatePosition(t);
    }
};
OrderQueue* SimulationMgr::getOrderQueue(){
    return &oq;
};
void SimulationMgr::SortList(){
    sort(oq.begin(),oq.end(),cmp);
};
SimulationMgr::~SimulationMgr(){
    Order *op;
    while(oq.size()){
        op=oq.front();
        oq.pop_front();
        delete op;
    }
    NavyMap::iterator nmi;
    for(nmi=nm.begin(); nmi!=nm.end(); nmi++){
        delete nmi->second;
    };
};


