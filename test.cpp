#include "graph_v2.h"
#include <iostream>

using namespace std;

vector<unsigned int> node_array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
vector<unsigned int> arc_array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

vector<tuple<unsigned int, unsigned int, unsigned int, double>> connections = {
    {0, 0, 1, 8.0}, {13, 9, 6, 7.0}, {1, 1, 2, 2.0}, {14, 9, 13, 8.0}, {2, 1, 4, 6.0}, {15, 13, 12, 2.0}, {3, 4, 3, 4.0}, {16, 12, 9, 10.0}, {4, 1, 3, 3.0}, {17, 10, 12, 5.0}, {5, 3, 5, 4.0}, {18, 9, 10, 5.0}, {6, 2, 5, 3.0}, {19, 11, 10, 10.0}, {7, 5, 14, 3.0}, {20, 3, 11, 10.0}, {8, 5, 7, 2.0}, {9, 7, 14, 2.0}, {10, 14, 8, 8.0}, {11, 14, 6, 2.0}, {12, 7, 9, 8.0}};

Graph my_graph(node_array, arc_array, connections);

int main(){
    auto list = my_graph.get_arcs();
    cout << list.size() << '\n';
    const Node* node1 = my_graph.find_node(3);
    const Node* node2 = my_graph.find_node(10); 
    for (auto a : my_graph.shortest_path(node1, node2).get_arcs())
    {
        cout << a.id << ' ' << a.start->id << ' ' << a.end->id << ' ' << a.cost << '\n';
    }
    return 0;
}