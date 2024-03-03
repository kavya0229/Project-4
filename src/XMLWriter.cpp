// XMLWriter.cpp
// ECS 034
//----------------------------------------------------------------------------
// C++ Headers
#include <fstream> 
#include <iostream>
#include <sstream>
#include <memory>
#include <string>
// Project Headers
#include "XMLWriter.h"
#include "DataSink.h"
//----------------------------------------------------------------------------

struct CXMLWriter::SImplementation 
{
    std::shared_ptr<CDataSink> sink;

    SImplementation(std::shared_ptr<CDataSink> sink) : sink(sink) {}

    void HandleSpecial(std::ostream &os, const std::string &value)
    {
        for (char ch : value)
        {
            switch (ch)
            {
                case '&': os << "&amp;"; break;
                case '<': os << "&lt;"; break;
                case '>': os << "&gt;"; break;
                case '\"': os << "&quot;"; break;
                case '\'': os << "&apos;"; break;
                default: os << ch; break;
            }
        }
    }

    void StartElement(const std::string &name, const std::vector<SXMLEntity::TAttribute> &attributes)
    {
        std::stringstream ss;
        ss << '<';
        HandleSpecial(ss, name);
        for (const auto &attr : attributes)
        {
            ss << ' ';
            HandleSpecial(ss, attr.first);
            ss << "=\"";
            HandleSpecial(ss, attr.second);
            ss << '\"';
        }
        ss << '>';
        std::string temp = ss.str();
        sink->Write(std::vector<char>(temp.begin(), temp.end()));
    }

    void EndElement(const std::string &name)
    {
        std::stringstream ss;
        ss << "</";
        HandleSpecial(ss, name);
        ss << '>';
        std::string temp = ss.str();
        sink->Write(std::vector<char>(temp.begin(), temp.end()));
    }

    void CompleteElement(const std::string &name, const std::vector<SXMLEntity::TAttribute> &attributes)
    {
        std::stringstream ss;
        ss << '<';
        HandleSpecial(ss, name);
        for (const auto &attr : attributes)
        {
            ss << ' ';
            HandleSpecial(ss, attr.first);
            ss << "=\"";
            HandleSpecial(ss, attr.second);
            ss << '\"';
        }
        ss << "/>";
        std::string temp = ss.str();
        sink->Write(std::vector<char>(temp.begin(), temp.end()));
    }

    void CharData(const std::string &data)
    {
        std::stringstream ss;
        HandleSpecial(ss, data);
        std::string temp = ss.str();
        sink->Write(std::vector<char>(temp.begin(), temp.end()));
    }
};

CXMLWriter::CXMLWriter(std::shared_ptr<CDataSink> sink)
    : DImplementation(new SImplementation(std::move(sink))) {}

CXMLWriter::~CXMLWriter() = default;


//----------------------------------------------------------------------------
// Outputs all end elements for those that have been started
bool CXMLWriter::Flush() 
{
    // Not needed for direct case based stream appending (Always Return True)
    return true;
}

//----------------------------------------------------------------------------
// Writes out the entity to the output stream
bool CXMLWriter::WriteEntity(const SXMLEntity &entity)
{
    switch (entity.DType)
    {
        // Calls StartElement()
        case SXMLEntity::EType::StartElement:
            DImplementation->StartElement(entity.DNameData, entity.DAttributes); break;

        // Calls EndElement()
        case SXMLEntity::EType::EndElement:
            DImplementation->EndElement(entity.DNameData); break;

        // Calls CompleteElement()
        case SXMLEntity::EType::CompleteElement:
            DImplementation->CompleteElement(entity.DNameData, entity.DAttributes); break;

        // Calls CharData()
        case SXMLEntity::EType::CharData:
            DImplementation->CharData(entity.DNameData); break;

        // No Data To Write
        default: return false; 
    }

    return true;
}