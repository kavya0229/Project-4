// CCSVBusSystem Class Documentation
// Project 3
// ECS 034
// Student 1: Felipe Gutierrez (919406096)
// Student 2: Kavya Sasikumar

- Overview

    The CCSVBusSystem class extends the CBusSystem class, providing implementations specific to handling bus systems defined in Comma-Separated Values (CSV) format. It utilizes CSV readers to load and manage bus stop and route data.

- Dependencies

    Inherits: BusSystem.h
    Includes: DSVReader.h

- Constructor

    CCSVBusSystem(std::shared_ptr<CDSVReader> stopsrc, std::shared_ptr<CDSVReader> routesrc); // Initializes a CCSVBusSystem instance using shared pointers to CDSVReader for stops and routes data sources.

- Destructor

    ~CCSVBusSystem(): Destroys the CCSVBusSystem instance, cleaning up resources.

- Member Functions

    // Overrides the pure virtual functions from CBusSystem to implement CSV-specific logic
    std::size_t StopCount() const noexcept; // Returns the total number of stops in the bus system.
    std::size_t RouteCount() const noexcept; // Returns the total number of routes in the bus system.
    std::shared_ptr<SStop> StopByIndex(std::size_t index) const noexcept; // Returns a shared pointer to the stop at the specified index.
    std::shared_ptr<SStop> StopByID(TStopID id) const noexcept; // Returns a shared pointer to the stop with the specified identifier.
    std::shared_ptr<SRoute> RouteByIndex(std::size_t index) const noexcept; // Returns a shared pointer to the route at the specified index.
    std::shared_ptr<SRoute> RouteByName(const std::string &name) const noexcept; // Returns a shared pointer to the route with the specified name.

- Private Members

    struct SImplementation: A forward declaration of a private implementation structure to encapsulate internal data and functionalities.
    std::unique_ptr<SImplementation> DImplementation: Unique pointer to the private implementation, following the PImpl idiom.