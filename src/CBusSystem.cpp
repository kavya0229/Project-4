// COpenstreetmap.cpp
// Project 3
// ECS 034
//----------------------------------------------------------------------------
// C++ Headers
#include <expat.h>
#include <iostream>
#include <sstream>
#include <cctype>
#include <cstddef>
#include <set>
#include <vector>
// User Defined Headers
#include "CSVBusSystem.h"
#include "DSVReader.h"
#include "DSVWriter.h"
#include "XMLReader.h"
#include "XMLWriter.h"
#include "BusSystem.h"
#include "StreetMap.h"
#include "SStop.h"
#include "SRoute.h"
//-----------------------------------------------------------------------------
// PIMPL
//-----------------------------------------------------------------------------

/*
// Implementation goes inside struct

//-----------------------------------------------------------------------------
// Bus System Stop member functions Returns the stop id of the stop
TStopID CCSVBusSystem::SStop::ID() const noexcept{
    return DImplementation->stopsrc->ID();
}
//-----------------------------------------------------------------------------
// Returns the node id of the bus stop
CStreetMap::TNodeID CCSVBusSystem::SRoute::NodeID() const noexcept{
    return DImplementation->routesrc->GetStopID();
}
//-----------------------------------------------------------------------------
// Bus System Route member functions Returns the name of the route
std::string CCSVBusSystem::SRoute::Name() const noexcept{
    return DImplementation->routesrc->Name();
}
*/

struct CDSVReader::SImplementation 
{
    std::shared_ptr<CDataSource> DataSource;
    char Delimiter;

    SImplementation(std::shared_ptr<CDataSource> src, char delimiter)
        : DataSource(src), Delimiter(delimiter) {}

    bool End() const;
    bool ReadRow(std::vector<std::string> &row);
};

// constructor
CDSVReader::CDSVReader(std::shared_ptr<CDataSource> src, char delimiter)
    : DImplementation(std::make_unique<SImplementation>(src, delimiter)) {}

// destructor
CDSVReader::~CDSVReader() = default; 

//-----------------------------------------------------------------------------

struct CCSVBusSystem::SImplementation
{
    // Stop Interface
    struct SStop : CBusSystem::SStop
    {
        //TStopID ID;
        //CStreetMap::TNodeID NodeID;

        // Bus System Stop member functions Returns the stop id of the stop
        TStopID ID() const noexcept { return DImplementation->stopsrc->ID(); }
        CStreetMap::TNodeID NodeID() const noexcept { return DImplementation->routesrc->GetStopID(); }
        SStop( TStopID SID, CStreetMap::TNodeID NID ) : ID( SID ), NodeID( NID ) {}
    };

    // Route Interface
    struct SRoute : CBusSystem::SRoute
    {
        // std::string Name;
        
        std::size_t StopCount; // Remove?
        TStopID ID; // Remove?

        // Bus System Route member functions Returns the name of the route
        std::string Name() const noexcept { return DImplementation->routesrc->Name(); }

        SRoute( std::string RName, std::size_t SCount, TStopID SID ) : Name( RName ), StopCount( SCount ), ID(SID) {}
    };

    // SImplementation
        std::shared_ptr<SStop> stopsrc;
        std::shared_ptr<SRoute> routesrc;
        std::size_t StopCount() const noexcept;
        std::size_t RouteCount() const noexcept;
        std::shared_ptr<SStop> StopByIndex(std::size_t index) const noexcept;
        std::shared_ptr<SStop> StopByID(TStopID id) const noexcept;
        std::shared_ptr<SRoute> RouteByIndex(std::size_t index) const noexcept;
        std::shared_ptr<SRoute> RouteByName(const std::string &name) const noexcept;

    SImplementation(std::shared_ptr< CDSVReader > stopsrc, std::shared_ptr< CDSVReader > routesrc) : stopsrc(), routesrc() 
    {
        std::vector<std::string> Slist;
        std::vector<std::string> Rlist;
    }
};

// Constructor
    CCSVBusSystem::CCSVBusSystem(std::shared_ptr< CDSVReader > stopsrc, std::shared_ptr< CDSVReader > routesrc)
        : DImplementation(std::make_unique<SImplementation>(stopsrc, routesrc)) {}

// Destructor
    CCSVBusSystem::~CCSVBusSystem() {}

//-----------------------------------------------------------------------------
// CCSVBusSystem member functions
//-----------------------------------------------------------------------------

// Returns the number of stops in the system
std::size_t CCSVBusSystem::StopCount() const noexcept
{
    // Return the total stop count
    std::size_t stop_count;
    std::vector<std::string> list;
    bool temp = ReadRow(list);
    stop_count = list.size();
    return stop_count; 
}

//-----------------------------------------------------------------------------
// Returns the number of routes in the system
std::size_t CCSVBusSystem::RouteCount() const noexcept{

    std::vector<std::string> row;
    std::set<std::string> unique_routes; // Set type to store unique route names
    
    // iterate for unique route names
    while (!DImplementation->routesrc->End()) 
    {
        if (DImplementation->routesrc->ReadRow(row)) 
        {
            if (!row.empty())
            { unique_routes.insert(row[0]); }
        }
    }
    
    // The size of the set is the count of unique route names
    return unique_routes.size(); 
}

//-----------------------------------------------------------------------------
// Returns the SStop specified by the index, nullptr is returned if index is greater than equal to StopCount()
std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByIndex(std::size_t index) const noexcept{
    if( index >= StopCount() )
    {
        std::cout<<"Testing nullptr"<<std::endl;
        return nullptr; 
    }
    else
    {
        std::cout<<"Testing shared_ptr"<<std::endl;
        return DImplementation->stopsrc->temp[index]; 
    }
}
//-----------------------------------------------------------------------------
// Returns the SStop specified by the stop id, nullptr is returned if it is not in the stops
std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByID(TStopID id) const noexcept{

    for (const auto& stopsrc : DImplementation->stopsrc) 
    {   
        if (stopsrc->GetID() == id) 
        { return stopsrc; }
    }
    return nullptr;
}
//-----------------------------------------------------------------------------
// Returns the SRoute specified by the index, nullptr is returned if index is greater than equal to RouteCount()
std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByIndex(std::size_t index) const noexcept{
    // Return nullptr if index is out of bounds
    if( index >= DImplementation->routesrc.size() )
    { return nullptr; }
    else
    { return DImplementation->routesrc->temp[index]; }
}
//-----------------------------------------------------------------------------
// Returns the SRoute specified by the name, nullptr is returned if name is not in the routes
std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByName(const std::string &name) const noexcept{
    for (const auto& routesrc : DImplementation->route) 
    {   
        if ( routesrc->GetName() == name ) 
        { return routesrc; }
    }
    return nullptr;
}