// DSVReader.cpp 
// ECS 034
//----------------------------------------------------------------------------
// C++ Headers
#include <fstream> 
#include <iostream>
#include <sstream>
// Project Headers
#include "StringUtils.h"
#include "DSVReader.h"
//----------------------------------------------------------------------------

// Struct Implementation
struct CDSVReader::SImplementation
{ 
    std::shared_ptr< CDataSource > src;
    char delimiter;

    SImplementation(std::shared_ptr< CDataSource > src, char del_param) : src(src), delimiter(delimiter) {}
};

// Constructor (Initializes "CDSVReader" Object)
CDSVReader::CDSVReader(std::shared_ptr< CDataSource > src, char delimiter) : DImplementation(new SImplementation(src,delimiter)) {}

// Destructor
CDSVReader::~CDSVReader() = default;

//----------------------------------------------------------------------------

bool CDSVReader::ReadRow(std::vector< std::string > &row)
{
    std::string line;
    char ch;
    std::string del = "";
    del = DImplementation->delimiter;
    bool lineRead = false;

    // Checks if all rows have been read
    if(End()) { return false; }

    // Reads first row of src char by char
    while( DImplementation->src->Get(ch) ) 
    {
        if (ch == '\n') { lineRead = true; break; }  
        else { line = line + ch; }
    }

    // Case 1: Splits values by delimiter
    if ( lineRead ) { row = StringUtils::Split(line,del); return true; } 

    // Case 2: No character found
    else { return false; }
}


bool CDSVReader::End() const
{   
    return DImplementation->src->End();
}