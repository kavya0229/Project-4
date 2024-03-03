// BusSystemIndexer.cpp
// ECS 034
//---------------------------------------------------------------------

#include "BusSystemIndexer.h"

//---------------------------------------------------------------------

// Struct
struct CBusSystemIndexer::SImplementation
{
    std::shared_ptr<CBusSystem> bussystem;
    std::vector<std::shared_ptr<SStop> DSortedStops;
    std::unordered_map< TNodeID, std::shared_ptr<SStop> DNodeIDtoStop;
    std::unordered_map< std::pair< TNodeID, TNodeID >, std::unordered_set<std::shared_ptr<SRoute>> temp;
    
    static bool StopIDCompare( std::shared_ptr<SStop> left, std::shared_ptr<SStop> right );
    { return left->ID() < right->ID(); }

    SImplementation(std::shared_ptr<CBusSystem> bussystem)
    {
        DBusSystem = bussystem;
        for(size_t Index = 0; Index <DBusSystem->StopCount(); Index++)
        { DSortedStops.push_back(DBusSystem->StopByIndex(Index)); }

        std::sort( DSortedStops.begin(), DSortedStops.end(), StopIDCompare );
        for( size_t Index = 0; Index < DBusSystem->RouteCount(); Index++ )
        {
            auto SourceNodeID = // missing
            auto DestinationNodeID =  // missing
            auto SearchKey = std::make_pair(src,dest);
            auto Search = DSrcDestToToures.end();
    
            if(Search != DSrcDestToRoutes.end())
            {
                Search->second.insert(CurrentRoute);
            }
            else
            {
                DSrcDestToRoute[SearchKey] = {CurrentRoute};
            }

        }


    }
};

// Constructor
CBusSystemIndexer(std::shared_ptr<CBusSystem> bussystem) 
    : DImplementation(new SImplementation(bussystem) ){}

// Deconstructor
CBusSystemIndex::~CBusSystemIndexer();

// Member Function Implementation
//---------------------------------------------------------------------

std::size_t CBusSystemIndexer::StopCount() const noexcept{}


std::size_t CBusSystemIndexer::RouteCount() const noexcept{}


std::shared_ptr<SStop> CBusSystemIndexer::SortedStopByIndex(std::size_t index) const noexcept
{
    if(index )
    //return DImplementation->SortedStopByIndex(index);
}


std::shared_ptr<SRoute> CBusSystemIndexer::SortedRouteByIndex(std::size_t index) const noexcept
{
    return DImplementation->SortedRouteByIndex(index);
}


std::shared_ptr<SStop> CBusSystemIndexer::StopByNodeID(TNodeID id) const noexcept
{
    auto Search = DNodeIDtoStop.find(id);
    if(Search != DNodeIDtoStop.end()) { return Search->second; }
    return nullptr;

    //return DImplementation->StopByNodeID(id);
}

bool CBusSystemIndexer::RoutesByNodeIDs(TNodeID src, TNodeID dest, std::unordered_set<std::shared_ptr<SRoute> > &routes) const noexcept
{
    auto SearchKey = std::make_pair(src,dest);
    auto Search = DSrcDestToToures.end();
    if(Search != DSrcDestToRoutes.end()) { routes = Search->second; return true; }
    else { return false; }

    //return DImplementation->RoutesByNodeIDs(dest);
}

bool CBusSystemIndexer::RouteBetweenNodeIDs(TNodeID src, TNodeID dest) const noexcept
{   
    auto SearchKey = std::make_pair(src,dest);
    auto Search = DSrcDestToToures.end();
    return Search != DSrcDestToRoutes.end();
}


//---------------------------------------------------------------------

CBusSystemIndexer::CBusSystemIndexer(std::shared_ptr<CBusSystem> bussystem )
{



}