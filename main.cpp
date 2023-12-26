#include "Netlist.h"
#include <iostream>

int main() {
    Netlist netlist;
    NetlistNode node1(1.123456789, -2.3456789, "F.Cu1");
    NetlistNode node2(30.1456789123, 1400.11, "Layer@1");
    std::cout << "Node1 Name: " << node1.generateNodeName() << std::endl;
    std::cout << "Node2 Name: " << node2.generateNodeName() << std::endl;
    netlist.addComponentR( { node1, node2 }, 100);  //������Ĭ��Ϊohm
    netlist.addComponentL( { node1, node2 }, 1.35, "nH");  // ������Ĭ��ΪH
    netlist.addComponentC( { node2, node1 }, 200, "pF");   // ������Ĭ��ΪF
    std::cout << "Generated Netlist:" << std::endl;
    std::cout << netlist.generateNetlist() << std::endl;
    std::cout << ".END" << std::endl;
    return 0;
}
