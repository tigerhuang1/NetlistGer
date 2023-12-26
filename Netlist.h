#pragma once
#ifndef NETLIST_H
#define NETLIST_H
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

class NetlistNode {
public:
    NetlistNode( float x, float y,const std::string& layerName);
    std::string float2id(float x)const;
    std::string generateNodeName()const;
protected:
    void replaceInvalidChars(std::string& LayerName)const;
    struct NetNode{
    float X;
    float Y;
    std::string LayerName;
    };
    NetNode netlistnode;
};


class Netlist {
public:
    void addComponentR(const std::vector<NetlistNode>& nodes, float value, const std::string& unit_type = "ohm");
    void addComponentL(const std::vector<NetlistNode>& nodes, float value, const std::string& unit_type = "H");
    void addComponentC(const std::vector<NetlistNode>& nodes, float value, const std::string& unit_type = "F");
    std::string generateNetlist() const;
    void addControlCommand(const std::string& command);




private:
    struct Component {
        std::string type;
        std::vector<std::string> nodes;
        std::string value;
    };

    std::vector<Component> components;
    std::string controlCommands;
};

#endif // NETLIST_H
