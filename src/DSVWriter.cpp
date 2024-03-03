// DSVWriter.cpp
// ECS 034
//----------------------------------------------------------------------------
// C++ Headers
#include <expat.h>
#include <iostream>
#include <sstream>
#include <cctype>
#include <cstddef>
#include <vector>
// Project Headers
#include "DSVWriter.h"
#include "StringUtils.h"
//----------------------------------------------------------------------------

// Struct Implementation
struct CDSVWriter::SImplementation
{
    std::shared_ptr< CDataSink > sink;
    char delimiter;
    bool quoteall;

    SImplementation( std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall )
        : sink(sink), delimiter(delimiter), quoteall(quoteall) {}
};

// Constructor (Initializes "CDSVWriter" Object)
CDSVWriter::CDSVWriter(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall)
    : DImplementation(std::make_unique<SImplementation>(sink, delimiter, quoteall)) {}

// Destructor
CDSVWriter::~CDSVWriter() = default;

//----------------------------------------------------------------------------

bool CDSVWriter::WriteRow(const std::vector< std::string > &row)
{
    // '<<' operator used for stream operations
    std::stringstream stream;

    // Iterates through each entry of vector
    for (size_t i = 0; i < row.size(); i++)
    {   
        // Place Delimiter
        if (i != 0) { stream << DImplementation->delimiter; }

        std::string dataline = row[i];

        // AI Generated Section
        bool PutQuote = DImplementation->quoteall || 
                        dataline.find(DImplementation->delimiter) != std::string::npos ||
                        dataline.find('\"') != std::string::npos ||
                        dataline.find('\n') != std::string::npos;
        
        if ( PutQuote )
        {
            stream << '\"';
            // Add double quotes
            for(char ch : dataline) { if (ch == '\"') { stream << "\"\""; } else{ stream << ch; } }
            stream << '\"';
        }
        else { stream << dataline; }
    }

    // Write Line of Data to Sink
    std::string out = stream.str();
    if(out.back() == '\n'){ out.pop_back();}
    return DImplementation->sink->Write(std::vector<char>(out.begin(), out.end()));
}