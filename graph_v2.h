#include<set>
#include<memory>

struct Arc;
struct Node;

struct Node {
    unsigned int id;
    std::set<Arc&> arcs;
};

struct Arc {
    Node& start;
    Node& finish;
    double cost;
};

class Graph{
    std::set<std::unique_ptr<Node>> nodes;
    std::set<std::unique_ptr<Arc>> arcs;
    
};