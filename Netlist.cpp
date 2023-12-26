#include "Netlist.h"

#include <cmath>

NetlistNode::NetlistNode(float x, float y, const std::string& layerName) : netlistnode({ x,y, layerName}){
    netlistnode = { x, y, layerName };
}

std::string NetlistNode::float2id(float x)const 
{
    std::string fprefix = x >= 0 ? "0_" : "1_";
    x = abs(x);
    int a = (int)x;
    int b = (int)((x - a) * 1000);

    std::string prefix = std::to_string(a);
    std::string postfix = std::to_string(b);
    while (prefix.length() < 3)
    {
        prefix = "0" + prefix;
    }
    while (postfix.length() < 3)
    {
        postfix = "0" + postfix;
    }

    return fprefix + prefix + postfix;
}
void NetlistNode::replaceInvalidChars(std::string& layername)const {
        for (char& ch : layername) {
            if (!std::isalnum(ch)) {
                ch = '_';
            }
        }
 }

std::string NetlistNode::generateNodeName()const
{
    std::string layername = netlistnode.LayerName;
    replaceInvalidChars(layername);
    return float2id(netlistnode.X) + "_" + float2id(netlistnode.Y) + "_" + layername;
}

void Netlist::addComponentR(const std::vector<NetlistNode>& nodes, float value, const std::string& unit_type) {
    // Implement addComponentR logic
    std::vector<std::string> nodeNames;
    for (const auto& node : nodes) {
        nodeNames.push_back(node.generateNodeName());
    }
    components.push_back({ "R", nodeNames, std::to_string(value) + unit_type });
}
void Netlist::addComponentL(const std::vector<NetlistNode>& nodes, float value, const std::string& unit_type) {
    // Implement addComponentL logic
    std::vector<std::string> nodeNames;
    for (const auto& node : nodes) {
        nodeNames.push_back(node.generateNodeName());
    }
    components.push_back({ "L", nodeNames, std::to_string(value) + unit_type });
}
void Netlist::addComponentC(const std::vector<NetlistNode>& nodes, float value, const std::string& unit_type) {
    // Implement addComponentC logic
    std::vector<std::string> nodeNames;
    for (const auto& node : nodes) {
        nodeNames.push_back(node.generateNodeName());
    }
    components.push_back({ "C", nodeNames, std::to_string(value) + unit_type });
}
void Netlist::addControlCommand(const std::string& command) {
    controlCommands += command + "\n";
}

std::string Netlist::generateNetlist() const {
    std::string netlist;
    for (const auto& comp : components) {
        netlist += comp.type + " " ;
        for (const auto& node : comp.nodes) {
            netlist += node + " ";
        }
        
        netlist += comp.value + "\n";
    }
    netlist += "\n"+controlCommands;
    return netlist;
}


//void Netlist::addComponent(const std::string& type, const std::vector<NetlistNode>& nodes, float value, const std::string& unit_type) {
//    std::string nodeName;
//    for (const auto& node : nodes) {
//        if (!nodeName.empty()) {
//            nodeName += "_";
//        }
//        nodeName += node.generateNodeName();
//    }
//    std::stringstream valueStr;
//    valueStr << value;
//    if (!unit_type.empty()) {
//        valueStr << unit_type;
//    }
//    components.push_back({ type, nodeName, {valueStr.str()} });
//}
//
//void Netlist::addComponent(const std::string& type, const std::string& name,const std::string nodename, const std::vector<std::string>& value) {
//    components.push_back({ type, name, nodename, value });
//}