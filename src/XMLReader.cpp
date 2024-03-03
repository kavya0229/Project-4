// XMLReader.cpp 
// ECS 034
//----------------------------------------------------------------------------
// C++ Headers
#include <expat.h>
#include <memory>
#include <iostream>
#include <cstring>
#include <queue>
// Project Headers
#include "XMLReader.h"
//----------------------------------------------------------------------------

struct CXMLReader::SImplementation 
{
    std::shared_ptr<CDataSource> DDataSource;
    XML_Parser DXMLParser;
    std::queue<SXMLEntity> DEntityQueue;
    bool DataDone = false;
    //bool skipdata

    SImplementation(std::shared_ptr<CDataSource> src) // : src(std::move(src))
    {
        DDataSource = src;
        DXMLParser = XML_ParserCreate(NULL);
        XML_SetStartElementHandler(DXMLParser, StartElementHandlerCallback);
        XML_SetEndElementHandler(DXMLParser, EndElementHandlerCallback);
        XML_SetCharacterDataHandler(DXMLParser, CharacterDataHandlerCallback);
        XML_SetUserData(DXMLParser, this);
    };

    void StartElementHandler(const std::string &name, const std::vector<std::string> &attrs)
    {
        SXMLEntity TempEntity;
        TempEntity.DNameData = name;
        TempEntity.DType = SXMLEntity::EType::StartElement;
        for (size_t Index = 0; Index < attrs.size(); Index += 2)
        { TempEntity.SetAttribute(attrs[Index], attrs[Index + 1]); }
        DEntityQueue.push(TempEntity);
    }

    void EndElementHandler(const std::string &name)
    {
        SXMLEntity entity;
        entity.DType = SXMLEntity::EType::EndElement;
        entity.DNameData = name;
        DEntityQueue.push(entity);
    }

    void CharacterDataHandler(const std::string &data)
    {
        if (!DEntityQueue.empty() && DEntityQueue.back().DType == SXMLEntity::EType::CharData)
        { DEntityQueue.back().DNameData += data; }  // merge consecutive char data
        else
        {
            SXMLEntity entity;
            entity.DType = SXMLEntity::EType::CharData;
            entity.DNameData = data;
            DEntityQueue.push(entity);
        }
    }

    static void StartElementHandlerCallback(void *context, const XML_Char *name, const XML_Char **atts)
    {
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);
        std::vector<std::string> Attributes;
        auto AttrPtr = atts;
        while (*AttrPtr)
        { Attributes.push_back(*AttrPtr); AttrPtr++; }
        ReaderObject->StartElementHandler(name, Attributes);
    };

    static void EndElementHandlerCallback(void *context, const XML_Char *name)
    {
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);
        ReaderObject->EndElementHandler(name);
    };

    static void CharacterDataHandlerCallback(void *context, const XML_Char *s, int len)
    {
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);
        ReaderObject->CharacterDataHandler(std::string(s, len));
    }
};

CXMLReader::CXMLReader(std::shared_ptr<CDataSource> src)
    : DImplementation(new SImplementation(std::move(src))) {}

CXMLReader::~CXMLReader() = default;

//----------------------------------------------------------------------------
// Returns true if all entities have been read from the XML
bool CXMLReader::End() const 
{ return DImplementation->DataDone; }

//----------------------------------------------------------------------------
// Returns true if the entity is successfully read, else if skipcdata is true only element type entities will be returned
bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata)
{
    // XML Entity Functions
    // bool AttributeExists(const std::string &name)
    // std::string AttributeValue(const std::string &name)
    // bool SetAttribute(const std::string &name, const std::string &value)
    // Data Sink
    // String()
    // Put()
    // Write() 

    if (DImplementation->DEntityQueue.empty() && !DImplementation->DDataSource->End())
    {
        std::vector<char> buffer(1024);
        bool success = DImplementation->DDataSource->Read(buffer, buffer.size());

        if (success) { XML_Parse( DImplementation->DXMLParser, buffer.data(), buffer.size(), 0); }
        else { XML_Parse(DImplementation->DXMLParser, nullptr, 0, XML_TRUE); }
    }

    while (!DImplementation->DEntityQueue.empty())
    {
        const auto &frontEntity = DImplementation->DEntityQueue.front();
        if (skipcdata && frontEntity.DType == SXMLEntity::EType::CharData) { DImplementation->DEntityQueue.pop(); continue; }
        entity = frontEntity;
        DImplementation->DEntityQueue.pop();

        DImplementation->DataDone = true;
        return true;
    }

    return false;
}