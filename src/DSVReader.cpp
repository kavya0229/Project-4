// DSVReader.cpp 
// ECS 034
//----------------------------------------------------------------------------
// C++ Headers
#include <fstream> 
#include <iostream>
#include <sstream>
// Project Headers
#include "StringUtils.h"
//#include "DataSource.h"
#include "DSVReader.h"
//----------------------------------------------------------------------------

// Struct Implementation
struct CDSVReader::SImplementation
{ 
    std::shared_ptr< CDataSource > src;
    char delimiter;
    bool DataDone;

    SImplementation(std::shared_ptr<CDataSource> src, char delimiter) : src(src), delimiter(delimiter) {}
};

// Constructor (Initializes "CDSVReader" Object)
CDSVReader::CDSVReader(std::shared_ptr< CDataSource > src, char delimiter) 
    : DImplementation(new SImplementation(src,delimiter)) {}

// Destructor
CDSVReader::~CDSVReader() = default;

//----------------------------------------------------------------------------

bool CDSVReader::ReadRow(std::vector< std::string > &row)
{
    std::string unique_delimiter = std::string(1, DImplementation->delimiter) + "$3$%#&#$5";
    std::string unique_quotes = "@$64#&$%32#";
    std::string dataline;
    bool quoted = true;
    char ch, pk;

    // Place line of data on string to read in ReadRow()
    while(DImplementation->src->Get(ch))
    {
        // Read next available char
        DImplementation->DataDone = !DImplementation->src->Peek(pk);

        // Ignore delimiters found within quotes
        if (ch == '\n' ) { break; }
        else if (ch == '"' && pk != '"' ) { quoted = !quoted; dataline.push_back(ch); }

        // True delimiter (,) pushed along with ($3$5) to use (,$3$5) as the splt string for StringUtils()
        else if ( ch == DImplementation->delimiter && quoted == true ) { dataline += unique_delimiter; }
        
        // Base Case
        else { dataline.push_back(ch); }
    }

    // Replace double quotes (\"\") in dataline with single quote (\")
    dataline = StringUtils::Replace(dataline, "\"\"", unique_quotes);
    dataline = StringUtils::Replace(dataline, "\"", "" );
    dataline = StringUtils::Replace(dataline, unique_quotes, "\"");

    // Split dataline by the slightly altered delimiter
    row = StringUtils::Split(dataline, unique_delimiter);
    
    // Checks if any data was read
    return !dataline.empty();
}

//----------------------------------------------------------------------------

bool CDSVReader::End() const
{ return DImplementation->DataDone; }