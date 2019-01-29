//
// Created by leleyu on 19-1-21.
//

#include <graph/graph.h>

namespace graph {

void UndirectedGraph::Build() {
  std::unordered_map<NodeId, int32_t> degree;
  size_t num_edge = edges_.srcs.size();
  for (size_t i = 0; i < num_edge; i++) {
    auto it = degree.find(edges_.srcs[i]);
    if (it != degree.end())
      degree[edges_.srcs[i]] = it->second + 1;
    else
      degree[edges_.srcs[i]] = 1;
  }

  size_t num_node = degree.size();
  adj_.starts.resize(num_node + 1);
  adj_.neighbors.resize(num_edge);

  adj_.starts[0] = 0;

  for (size_t i = 0; i < num_edge; i++) {
    NodeId src = edges_.srcs[i];
    auto it = adj_.lookup_table.find(src);
    int32_t start = 0;

    // start position of each src node
    if (it != adj_.lookup_table.end())
      start = adj_.starts[it->second];
    else {
      int32_t num = adj_.lookup_table.size();
      adj_.lookup_table[src] = num;
      adj_.starts[num] = adj_.starts[num - 1] + degree[src];
      start = adj_.starts[num];
    }

    // position of neighbor
    int32_t position = start + degree[src] - 1;
    adj_.neighbors[position] = edges_.dsts[i];
    degree[src] = degree[src] - 1;
  }
}


size_t UndirectedGraph::GetDegree(NodeId node) const {
  auto it = adj_.lookup_table.find(node);
  if (it != adj_.lookup_table.end()) {
    int32_t index = it->second;
    return adj_.starts[index + 1] - adj_.starts[index];
  } else
    return 0;
}

NodeId* UndirectedGraph::GetNeighborPtr(NodeId node) {
  auto it = adj_.lookup_table.find(node);
  if (it != adj_.lookup_table.end()) {
    int32_t index = it->second;
    return &adj_.starts[index];
  } else
    return nullptr;
}




}; // namespace graph
