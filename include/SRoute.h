#ifndef SROUTE_H
#define SROUTE_H

#include <memory>
#include <string>
#include <vector>
#include "CSVBusSystem.h"

class SRoute : public CCSVBusSystem
{
    public:
        //SRoute(std::shared_ptr<CCSVBusSystem> route);
        virtual ~SRoute();
        virtual std::string Name() const noexcept = 0;
        virtual std::size_t StopCount() const noexcept = 0;
        virtual TStopID GetStopID(std::size_t index) const noexcept = 0; 
};

#endif