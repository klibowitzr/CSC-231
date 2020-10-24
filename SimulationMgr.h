//
//  SimulationMgr.h
//  Navy Simulator
//
//  Created by Rachel klibowitz on 4/9/18.
//  Copyright © 2018 Rachel klibowitz. All rights reserved.
//
#ifndef SimulationMgr_h
#define SimulationMgr_h
#include <stdio.h>
#include "ATime.h"
#include "Orders.h"
#include "Movable.h"
#include <deque>
#include <map>
#include <list>
#include <fstream>
#include <algorithm>


typedef std::map<std::string,Movable*> NavyMap;
typedef std::deque< Order*> OrderQueue;

static bool cmp(Order*, const Order*);

class SimulationMgr{
public:
    bool simInit(std::string);
    void printOrders();
    void printNavy();
    void StopSim();
    void StartSim();
    void simDoUpdate(ATime);
    ATime getStart() const;
    ATime getStop() const;
    NavyMap* getNavy();
    OrderQueue* getOrderQueue();
    void sendUpdateCmd(ATime); 
    void SortList();
    void getNavyInfo();
    void printHistory();
    virtual ~SimulationMgr();
    
protected:
    OrderQueue oq;
    NavyMap nm;
    ATime Start;
    ATime Stop;    
};

#endif /* SimulationMgr_h */
