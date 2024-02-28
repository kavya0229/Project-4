#ifndef CSWAY_H
#define CSWAY_H

#include "StreetMap.h"
#include <vector>
#include <map>

class CSWay : public CStreetMap::SWay 
{
private:
    TWayID DWayID;
    std::vector<TNodeID> DNodes;
    std::map<std::string, std::string> DAttributes;

public:
    // Implementation of SWay functions
    TWayID ID() const noexcept override { return DWayID; }
    std::size_t NodeCount() const noexcept override { return DNodes.size(); }
    TNodeID GetNodeID(std::size_t index) const noexcept override;
    std::size_t AttributeCount() const noexcept override { return DAttributes.size(); }
    std::string GetAttributeKey(std::size_t index) const noexcept override;
    bool HasAttribute(const std::string &key) const noexcept override;
    std::string GetAttribute(const std::string &key) const noexcept override;

    // Additional functions
    void SetID(TWayID id) { DWayID = id; }
    void AddNode(TNodeID id) { DNodes.push_back(id); }
    void AddAttribute(const std::string &key, const std::string &value) { DAttributes[key] = value; }
};

#endif