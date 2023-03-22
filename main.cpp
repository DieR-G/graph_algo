#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

directed_graph create_graph()
{
    ifstream file;
    file.open("test_graph.csv");
    string current_line;
    getline(file, current_line);
    unsigned int nodes = stoul(current_line);
    directed_graph graph(nodes);
    while (getline(file, current_line))
    {
        stringstream line_stream(current_line);
        string from, to, cost;
        getline(line_stream, from, ',');
        getline(line_stream, to, ',');
        getline(line_stream, cost, ',');
        graph.add_edge(stoul(from), stoul(to), stod(cost));
        graph.add_edge(stoul(to), stoul(from), stod(cost));
    }
    return graph;
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        directed_graph my_graph = create_graph();
        //76 272
        auto result = my_graph.dijkstra(atoi(argv[1]), atoi(argv[2]));
        for (auto x : result)
        {
            cout << x << ' ';
        }
    }
    return 0;
}