// CBusSystem Class Documentation
// Project 3
// ECS 034
// Student 1: Felipe Gutierrez (919406096)
// Student 2: Kavya Sasikumar

- Overview

    The CBusSystem class represents a bus system, encapsulating functionalities related to bus stops and routes within a street map context. It provides interfaces for accessing stops and routes by their identifiers or names.

- Dependencies

    Includes: StreetMap.h

- Public Types

    TStopID: Alias for uint64_t, used to represent stop identifiers.
    InvalidStopID: Constant of TStopID, representing an invalid stop identifier. 
    
- Structures

    SStop
    // Abstract structure representing a bus stop.
    virtual ~SStop(): Destructor.
    virtual TStopID ID() const noexcept: Returns the stop's identifier.
    virtual CStreetMap::TNodeID NodeID() const noexcept: Returns the node ID of the stop on the street map.

    SRoute
    // Abstract structure representing a bus route.
    virtual ~SRoute(): Destructor.
    virtual std::string Name() const noexcept: Returns the route's name.
    virtual std::size_t StopCount() const noexcept: Returns the number of stops in the route.
    virtual TStopID GetStopID(std::size_t index) const noexcept: Returns the identifier of the stop at the specified index in the route.

- Members

    virtual ~CBusSystem(); // Destructor
    virtual std::size_t StopCount() const noexcept; // Returns the total number of stops in the bus system.
    virtual std::size_t RouteCount() const noexcept; // Returns the total number of routes in the bus system.
    virtual std::shared_ptr<SStop> StopByIndex(std::size_t index) const noexcept; // Returns a shared pointer to the stop at the specified index.
    virtual std::shared_ptr<SStop> StopByID(TStopID id) const noexcept; // Returns a shared pointer to the stop with the specified identifier.
    virtual std::shared_ptr<SRoute> RouteByIndex(std::size_t index) const noexcept; // Returns a shared pointer to the route at the specified index.
    virtual std::shared_ptr<SRoute> RouteByName(const std::string &name) const noexcept; //Returns a shared pointer to the route with the specified name.