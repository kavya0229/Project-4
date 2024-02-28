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
CDSVWriter::CDSVWriter(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall) 
    : DImplementation(new SImplementation(sink,delimiter,quoteall)){}

// Destructor
CDSVWriter::~CDSVWriter() = default;

//----------------------------------------------------------------------------

bool CDSVWriter::WriteRow(const std::vector< std::string > &row)
{
    std::vector<std::string> ProRow;
    std::string finalRow;
    char quoteChar = '"';
    bool needQuotes = false;

    for (const auto& field : row) 
    {
        std::string current = field;
        current = StringUtils::Replace(current, "\"", "\"\"");

        // Determined by CDSVWriter class
        if (DImplementation->quoteall) 
        { needQuotes = true; }

        else
        {   
            if (current.find(DImplementation->delimiter) != std::string::npos) { needQuotes = true; } // Check for delimiter in the string
            else if (current.find('"') != std::string::npos) { needQuotes = true; } // Check for double quote in the string
            else if (current.find('\n') != std::string::npos) { needQuotes = true; } // Check for newline in the string
        }

        if (needQuotes)
        { current = quoteChar + current + quoteChar; }

        ProRow.push_back(current);
    }

    // Join the processed fields using the delimiter
    for (size_t i = 0; i < ProRow.size(); ++i) 
    {
        finalRow += ProRow[i];
        if (i < ProRow.size() - 1) { finalRow += DImplementation->delimiter; }
    }

    // End the row with a newline character
    finalRow += '\n';

    // Convert finalRow to vector<char> and write to the data sink
    std::vector<char> vec(finalRow.begin(), finalRow.end());
    return DImplementation->sink->Write(vec);
}