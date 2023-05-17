#include <functional>
#include <limits>
#include <list>
#include <queue>
#include <set>
#include <vector>

typedef std::vector<std::pair<unsigned int, double>> pair_vector;

std::function<bool(std::pair<int, double>, std::pair<int, double>)>
    compare_pair = [](const std::pair<unsigned int, double> &a,
                      const std::pair<unsigned int, double> &b) {
      return a.second < b.second;
    };

class directed_graph {
  unsigned int get_min_unvisited_node(pair_vector &distances,
                                      std::set<unsigned int> &visited);
  std::vector<unsigned int> make_min_path(pair_vector &distances,
                                          unsigned int from, unsigned int to);
  pair_vector dijkstra_util(unsigned int from, unsigned int to);

 public:
  unsigned int size = 0;
  directed_graph(unsigned int nodes);
  std::vector<pair_vector> adjacency_list;
  std::vector<unsigned int> dijkstra(unsigned int from, unsigned int to);
  void add_edge(unsigned int from, unsigned int to, double cost);
};

unsigned int directed_graph::get_min_unvisited_node(
    pair_vector &distances, std::set<unsigned int> &visited) {
  unsigned int result = size + 1;
  double cost = std::numeric_limits<double>::max();
  for (unsigned int i = 0; i < distances.size(); i++) {
    if (distances[i].second < cost && !visited.count(i)) {
      result = i;
      cost = distances[i].second;
    }
  }
  return result;
}

pair_vector directed_graph::dijkstra_util(unsigned int from, unsigned int to) {
  pair_vector distances(
      size, std::make_pair(size + 1, std::numeric_limits<double>::max()));
  std::set<unsigned int> visited;
  distances[from] = std::make_pair(from, 0.0);
  unsigned int current_node = from;
  while (visited.size() < size && current_node != to && current_node < size) {
    for (auto edge : adjacency_list[current_node]) {
      auto next = edge.first;
      if (visited.count(next)) {
        continue;
      }
      auto cost = edge.second;
      auto tentative_distance = distances[current_node].second + cost;
      if (tentative_distance < distances[next].second) {
        distances[next] = std::make_pair(current_node, tentative_distance);
      }
    }
    visited.insert(current_node);
    current_node = get_min_unvisited_node(distances, visited);
  }
  return distances;
}

std::vector<unsigned int> directed_graph::make_min_path(pair_vector &distances,
                                                        unsigned int from,
                                                        unsigned int to) {
  std::vector<unsigned int> path;
  unsigned int current_pos = to;
  while (current_pos != from) {
    path.insert(path.begin(), current_pos);
    current_pos = distances[current_pos].first;
    if (current_pos > size) {
      return std::vector<unsigned int>();
    }
  }
  path.insert(path.begin(), from);
  return path;
}

std::vector<unsigned int> directed_graph::dijkstra(unsigned int from,
                                                   unsigned int to) {
  auto distances = dijkstra_util(from, to);
  return make_min_path(distances, from, to);
}

directed_graph::directed_graph(unsigned int nodes) {
  adjacency_list = std::vector<pair_vector>(nodes);
  size = nodes;
}

void directed_graph::add_edge(unsigned int from, unsigned int to, double cost) {
  adjacency_list[from].push_back(std::make_pair(to, cost));
}
