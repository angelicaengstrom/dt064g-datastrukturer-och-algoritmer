//
// Created by angel on 2022-04-05.
//

#include "List.h"

void List::create_matrix() {
    for(node_id_t y_pos = 0; y_pos < size(); y_pos++){
        matrix[y_pos].assign(size(), inf_t::max());
        matrix[y_pos][y_pos] = Weight::SELF;
        for(const auto& edge : list.second){
            if(edge.n1 == y_pos){
                matrix[edge.n1][edge.n2] = edge.weight;
            }
        }
    }
}

bool List::generate_dfs(const node_id_t &start) {
    std::vector<bool> visited(size());
    visited.assign(size(), Visited::FALSE);

    node_id_t n1 = start;

    std::stack<node_id_t> neighbours;
    neighbours.push(n1);

    while(!neighbours.empty()) {
        n1 = neighbours.top();
        visited[n1] = Visited::TRUE;
        neighbours.pop();

        for (node_id_t n2 = 0; n2 < size(); n2++) {
            weight_t weight = matrix[n1][n2];
            if (weight != inf_t::max() && visited[n2] == Visited::FALSE){
                neighbours.push(n2);
            }
        }
    }
    return std::all_of(visited.begin(), visited.end(), [](const auto& node){ return node; });
}

bool List::generate_bfs(const node_id_t &start) {
    std::vector<bool> visited(size());
    visited.assign(size(), Visited::FALSE);

    node_id_t n1 = start;

    std::list<node_id_t> neighbours;
    neighbours.push_back(n1);

    while(!neighbours.empty()) {
        n1 = neighbours.front();
        visited[n1] = Visited::TRUE;
        neighbours.pop_front();

        for (node_id_t n2 = 0; n2 < size(); n2++) {
            weight_t weight = matrix[n1][n2];
            if (weight != inf_t::max() && visited[n2] == Visited::FALSE){
                neighbours.push_back(n2);
            }
        }
    }
    return std::all_of(visited.begin(), visited.end(), [](const auto& node){ return node; });
}

std::vector<handled_t> List::generate_dijkstras(const node_id_t &start) {
    std::vector<handled_t> handled_nodes(size());
    handled_nodes.assign(size(), std::make_pair(inf_t::max(), Visited::FALSE));

    std::priority_queue<path_t, std::vector<path_t>, std::greater<>> neighbour_nodes;
    neighbour_nodes.push(std::make_pair(Weight::SELF, start));

    while(!neighbour_nodes.empty()){
        path_t min_path = neighbour_nodes.top();
        neighbour_nodes.pop();

        handled_nodes[min_path.second].first = std::min(min_path.first, handled_nodes[min_path.second].first);

        if(!handled_nodes[min_path.second].second) {
            std::string handled_name = get_node_name(min_path.second);
            std::cout << handled_name << "(" << handled_nodes[min_path.second].first
                      << ") is set\n";
            handled_nodes[min_path.second].second = Visited::TRUE;

            for (node_id_t x_node = 0; x_node < size(); x_node++) {
                weight_t weight = matrix[min_path.second][x_node];
                if (handled_nodes[x_node].first > weight && !handled_nodes[x_node].second) {
                    path_t neighbour = std::make_pair(weight + min_path.first,  x_node);
                    std::string neighbour_name = get_node_name(neighbour.second);

                    std::cout << handled_name << " -> " << neighbour_name << "(" << neighbour.first << ")\n";
                    neighbour_nodes.push(neighbour);
                }
            }
        }
    }
    return handled_nodes;
}




