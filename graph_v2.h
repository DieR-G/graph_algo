#include<memory>
#include<vector>
#include<list>
#include<tuple>
#include<algorithm>

struct Arc;
struct Node;

struct Node {
    unsigned int id;
    std::list<std::list<Arc>::iterator> arcs;

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
    Node* end;
    double cost;
    unsigned int id;
    Arc(const unsigned int _id): id(_id){
        start = nullptr;
        end = nullptr;
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
    std::list<Node> nodes;
    std::list<Arc> arcs;
    Graph _dfs(const Node* current_node, const Node* end_node, Graph &current_path){
        current_path.add_node(*current_node);
        if(current_node == end_node){
            return current_path;
        }
        for( auto arc : current_node->arcs ){
            const Node* next_node = ((arc->start) == current_node) ? arc->end : arc->start;
            if(!(current_path.find_node(next_node->id))){
                //current_path = _dfs(next_node, end_node, current_path);
                current_path.add_arc(*arc);
                return _dfs(next_node, end_node, current_path);
            }
        }
        return current_path;
    }
public:
    Graph(){};
    Graph(const Graph &rhs):nodes(rhs.nodes), arcs(rhs.arcs){
    }
    Graph(std::list<Node> _nodes, std::list<Arc> _arcs): nodes(_nodes), arcs(_arcs){};
    Graph(std::vector<unsigned int> _nodes, std::vector<unsigned int> _arcs){
        for(auto n_id: _nodes){
            nodes.push_back(Node(n_id));
        }
        for(auto a_id: _arcs){
            arcs.push_back(Arc(a_id));
        }
    };
    // connection is a tuple with (arc id, start node id, end node id, cost of the arc)
    Graph(std::vector<unsigned int> _nodes, std::vector<unsigned int> _arcs, std::vector<std::tuple<unsigned int, unsigned int, unsigned int, double>> connections)
    : Graph(_nodes, _arcs)
    {
        for( auto con : connections ){
            auto arc = std::find(arcs.begin(), arcs.end(), std::get<0>(con));
            auto s_n = std::find(nodes.begin(), nodes.end(), std::get<1>(con));
            auto e_n = std::find(nodes.begin(), nodes.end(), std::get<2>(con));
            double cost = std::get<3>(con);
            arc->start = &(*s_n);
            arc->end = &(*e_n);
            arc->cost = cost;
            if(s_n != nodes.end() && e_n != nodes.end()){
                s_n->arcs.push_back(arc);
                e_n->arcs.push_back(arc);
            }
        }    
    };

    const std::list<Arc> get_arcs(){
        return arcs;
    }

    const std::list<Node> get_nodes(){
        return nodes;
    }

    const Node* find_node(unsigned int id){
        auto it = std::find(nodes.begin(), nodes.end(), Node(id));
        if(it != nodes.end()){
            return &(*it);
        }
        else{
            return nullptr;
        }
    }

    const Arc* find_arc(unsigned int id){
        auto it = std::find(arcs.begin(), arcs.end(), Arc(id));
        if(it != arcs.end()){
            return &(*it);
        }
        else{
            return nullptr;
        }
    }

    void add_node(Node n){
        nodes.push_back(n);
    }

    void add_arc(Arc a){
        arcs.push_back(a);
    }

    Graph dfs(const Node* current_node, const Node* end_node){
        Graph path;
        return _dfs(current_node, end_node, path);
    }
};