#include<set>
#include<memory>
#include<vector>
#include<tuple>

struct Arc;
struct Node;

struct Node {
    unsigned int id;
    std::set<Arc*> arcs;

    Node(const unsigned int _id) : id(_id){
    };

    bool operator<(const Node &rhs) const{
        return id < rhs.id;
    }

    bool operator==(const Node &rhs) const{
        return id == rhs.id;
    }

};

struct Arc {
    Node* start;
    Node* finish;
    double cost;
    unsigned int id;
    Arc(const unsigned int _id): id(_id){
        start = nullptr;
        finish = nullptr;
        cost = 0.0;
    }

    bool operator<(const Arc &rhs) const{
        return id < rhs.id;
    }

    bool operator==(const Arc &rhs) const{
        return id == rhs.id;
    }
};


class Graph{
    std::set<Node> nodes;
    std::set<Arc> arcs;
public:
    Graph(std::set<Node> _nodes, std::set<Arc> _arcs): nodes(_nodes), arcs(_arcs){};
    Graph(std::vector<unsigned int> _nodes, std::vector<unsigned int> _arcs){
        for(auto n_id: _nodes){
            nodes.insert(Node(n_id));
        }
        for(auto a_id: _arcs){
            arcs.insert(Arc(a_id));
        }
    };
    Graph(std::vector<unsigned int> _nodes, std::vector<unsigned int> _arcs, std::vector<std::tuple<unsigned int, unsigned int, unsigned int, double>> connections)
    : Graph(_nodes, _arcs)
    {
        for( auto con : connections ){
            auto s_n = nodes.find(std::get<1>(con));

        }    
    };

};