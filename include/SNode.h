#ifndef CSNODE_H
#define CSNODE_H

#include "StreetMap.h"
#include <map>

class CSNode : public CStreetMap::SNode {
private:
    TNodeID DNodeID;
    TLocation DLocation;
    std::map<std::string, std::string> DAttributes;

public:
    // Implementation of SNode functions
    TNodeID ID() const noexcept override { return DNodeID; }
    TLocation Location() const noexcept override { return DLocation; }
    std::size_t AttributeCount() const noexcept override { return DAttributes.size(); }
    std::string GetAttributeKey(std::size_t index) const noexcept override;
    bool HasAttribute(const std::string &key) const noexcept override;
    std::string GetAttribute(const std::string &key) const noexcept override;

    // Additional functions
    void SetID(TNodeID id) { DNodeID = id; }
    void SetLocation(TLocation location) { DLocation = location; }
    void AddAttribute(const std::string &key, const std::string &value) { DAttributes[key] = value; }
};

#endif