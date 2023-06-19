#include <memory>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
#include <set>

struct Arc;
struct Node;

struct Node{
    unsigned int id;
    std::vector<std::vector<Arc>::iterator> arcs;

    Node(const unsigned int _id) : id(_id){};

    bool operator<(const Node &rhs) const
    {
        return id < rhs.id;
    }

    bool operator==(const Node &rhs) const
    {
        return id == rhs.id;
    }
};

struct Arc{
    Node *start;
    Node *end;
    double cost;
    unsigned int id;
    Arc(const unsigned int _id) : id(_id)
    {
        start = nullptr;
        end = nullptr;
        cost = 0.0;
    }

    bool operator<(const Arc &rhs) const
    {
        return id < rhs.id;
    }

    bool operator==(const Arc &rhs) const
    {
        return id == rhs.id;
    }
};

class Graph{
    std::vector<Node> nodes;
    std::vector<Arc> arcs;
    struct Path{
        const Node *start = nullptr;
        const Node *end = nullptr;
        double cost;
        std::vector<std::vector<Arc>::iterator> arcs;
        bool operator>(const Path &rhs) const{
            return cost > rhs.cost;
        }
    };

    Path _shortest_path(const Node *starting_node, const Node *ending_node){
        std::priority_queue<Path, std::vector<Path>, std::greater<Path>> pq;
        std::set<const Node*> visited_nodes;
        Path start = {starting_node, starting_node, 0.0, std::vector<std::vector<Arc>::iterator>()};
        pq.push(start);
        Path current_path;
        do{
            current_path = pq.top();
            pq.pop();
            const Node *current_node = current_path.end;
            if(visited_nodes.count(current_node)){
                continue;
            }
            for (auto arc : current_node->arcs){
                Path aux_path = current_path;
                aux_path.arcs.push_back(arc);
                aux_path.end = ((arc->start) == current_node) ? arc->end : arc->start;
                aux_path.cost += arc->cost;
                pq.push(aux_path);
            }
            visited_nodes.insert(current_node);
            if(current_path.end == ending_node){
                return current_path;
            }
        } while (!pq.empty());
        //If the ending node is not found, returns an empty path
        return Path();
    }

    Graph create_graph_from_path(Path graph_path){
        //std::set<Node> node_set;
        std::vector<Node> node_vector;
        std::vector<Arc> arc_vector;
        Node current_node = *graph_path.start;
        node_vector.push_back(current_node);
        for( auto arc : graph_path.arcs ){
            arc_vector.push_back(*arc);
            current_node = (*(arc->start) == current_node) ? *arc->end : *arc->start;
            node_vector.push_back(current_node);
        }
        //std::vector<Node> node_vector(node_set.begin(), node_set.end());
        return Graph(node_vector, arc_vector);
    }
    Graph _dfs(const Node *current_node, const Node *end_node, Graph &current_path){
        current_path.add_node(*current_node);
        if (current_node == end_node){
            return current_path;
        }
        for (auto arc : current_node->arcs){
            const Node *next_node = ((arc->start) == current_node) ? arc->end : arc->start;
            if (!(current_path.find_node(next_node->id))){
                // current_path = _dfs(next_node, end_node, current_path);
                current_path.add_arc(*arc);
                return _dfs(next_node, end_node, current_path);
            }
        }
        return current_path;
    }

public:
    Graph(){}
    Graph(const Graph &rhs) : nodes(rhs.nodes), arcs(rhs.arcs){}
    Graph(std::vector<Node> _nodes, std::vector<Arc> _arcs) : nodes(_nodes), arcs(_arcs){}
    Graph(std::vector<unsigned int> _nodes, std::vector<unsigned int> _arcs){
        for (auto n_id : _nodes){
            nodes.push_back(Node(n_id));
        }
        for (auto a_id : _arcs){
            arcs.push_back(Arc(a_id));
        }
    }
    // connection is a tuple with (arc id, start node id, end node id, cost of the arc)
    Graph(std::vector<unsigned int> _nodes, std::vector<unsigned int> _arcs, std::vector<std::tuple<unsigned int, unsigned int, unsigned int, double>> connections)
        : Graph(_nodes, _arcs){
        for (auto con : connections){
            auto arc = std::find(arcs.begin(), arcs.end(), std::get<0>(con));
            auto s_n = std::find(nodes.begin(), nodes.end(), std::get<1>(con));
            auto e_n = std::find(nodes.begin(), nodes.end(), std::get<2>(con));
            double cost = std::get<3>(con);
            arc->start = &(*s_n);
            arc->end = &(*e_n);
            arc->cost = cost;
            if (s_n != nodes.end() && e_n != nodes.end()){
                s_n->arcs.push_back(arc);
                e_n->arcs.push_back(arc);
            }
        }
    }

    const std::vector<Arc> get_arcs(){
        return arcs;
    }

    const std::vector<Node> get_nodes(){
        return nodes;
    }

    const Node *find_node(unsigned int id){
        auto it = std::find(nodes.begin(), nodes.end(), Node(id));
        if (it != nodes.end()){
            return &(*it);
        }
        else{
            return nullptr;
        }
    }

    const Arc *find_arc(unsigned int id){
        auto it = std::find(arcs.begin(), arcs.end(), Arc(id));
        if (it != arcs.end()){
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

    Graph dfs(const Node *current_node, const Node *end_node){
        Graph path;
        return _dfs(current_node, end_node, path);
    }

    Graph shortest_path(const Node *from, const Node *to){
        return create_graph_from_path(_shortest_path(from, to));
    }

    double get_total_cost(){
        double total = 0.0;
        for(auto a : arcs){
            total += a.cost;
        }
        return total;
    }
};