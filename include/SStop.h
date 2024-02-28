#ifndef SSTOP_H
#define SSTOP_H

#include <memory>
#include <string>
#include <vector>
#include "CSVBusSystem.h"

class SStop : public CCSVBusSystem
{
    public:
        virtual ~SStop();
        virtual TStopID ID() const noexcept = 0;
        virtual CStreetMap::TNodeID NodeID() const noexcept= 0;
};

#endif