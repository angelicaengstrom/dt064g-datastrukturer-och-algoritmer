//
// Created by angel on 2022-04-05.
//

#include "List.h"

adjacency_matrix_t List::create_matrix() {
    adjacency_matrix_t matrix(list.first.size(), std::vector<weight_t>(list.first.size()));
    for(node_id_t y_pos = 0; y_pos < list.first.size(); y_pos++){
        matrix[y_pos].assign(list.first.size(), inf_t::max());
        for(node_id_t list_pos = 0; list_pos < list.second.size(); list_pos++){
            const node_id_t n1 = list.second[list_pos].n1;
            if(n1 == y_pos){
                if(matrix[y_pos][y_pos] == inf_t::max()) {
                    matrix[y_pos][y_pos] = Weight::SELF;
                }
                const node_id_t n2 = list.second[list_pos].n2;
                const weight_t weight = list.second[list_pos].weight;
                matrix[y_pos][n2] = weight;
            }
        }
    }
    return matrix;
}

bool List::generate_dfs(const node_id_t &start) {
    std::vector<node_id_t> visited(size());
    visited.assign(size(), Visited::FALSE);

    node_id_t curr_pos = start;

    std::stack<node_id_t> neighbours;
    neighbours.push(curr_pos);

    while(!neighbours.empty()) {
        curr_pos = neighbours.top();
        visited[curr_pos] = Visited::TRUE;
        neighbours.pop();

        for (node_id_t x_pos = 0; x_pos < size(); x_pos++) {
            weight_t edge = matrix[curr_pos][x_pos];
            if (edge != inf_t::max() && edge != Weight::SELF && visited[x_pos] == Visited::FALSE){
                neighbours.push(x_pos);
            }
        }
    }
    return is_connected(visited);
}

bool List::is_connected(const std::vector<node_id_t> &visited_nodes) {
    for(node_id_t i = 0; i < visited_nodes.size(); i++) {
        if(visited_nodes[i] == Visited::FALSE){
            return false;
        }
    }
    return true;
}

bool List::generate_bfs(const node_id_t &start) {
    std::vector<node_id_t> visited(size());
    visited.assign(size(), Visited::FALSE);

    node_id_t curr_pos = start;

    std::list<node_id_t> neighbours;
    neighbours.push_back(curr_pos);

    while(!neighbours.empty()) {
        curr_pos = neighbours.front();
        visited[curr_pos] = Visited::TRUE;
        neighbours.pop_front();

        for (node_id_t x_pos = 0; x_pos < size(); x_pos++) {
            weight_t edge = matrix[curr_pos][x_pos];
            if (edge != inf_t::max() && edge != Weight::SELF && visited[x_pos] == Visited::FALSE){
                neighbours.push_back(x_pos);
            }
        }
    }
    return is_connected(visited);
}

size_t List::size() const{
    return matrix.size();
}

std::string List::get_edge_name(const int& index) const{
    return list.first.at(index);
}

std::vector<node_t> List::generate_dijkstras(const node_id_t &start) {
    std::vector<node_t> handled_nodes(size());
    handled_nodes.assign(size(), std::make_pair(inf_t::max(), Visited::FALSE));

    std::priority_queue<path_t, std::vector<path_t>, std::greater<>> neighbour_nodes;
    neighbour_nodes.push(std::make_pair(Weight::SELF, std::make_pair(Visited::TRUE, start)));

    while(!neighbour_nodes.empty()){
        path_t min_path = neighbour_nodes.top();
        neighbour_nodes.pop();

        handled_nodes[min_path.second.second].first = std::min(min_path.first, handled_nodes[min_path.second.second].first);

        if(!handled_nodes[min_path.second.second].second) {
            std::string path_name = list.first[min_path.second.second];
            std::cout << path_name << "(" << handled_nodes[min_path.second.second].first
                      << ") is set\n";

            for (node_id_t x_node = 0; x_node < size(); x_node++) {
                weight_t edge = matrix[min_path.second.second][x_node];
                if (edge != inf_t::max()) {
                    if (handled_nodes[x_node].first > edge && !handled_nodes[x_node].second) {
                        path_t path = std::make_pair(edge + min_path.first, std::make_pair(Visited::FALSE, x_node));

                        std::string path_name = list.first[min_path.second.second];
                        std::string neighbour_name = list.first[path.second.second];

                        if(path_name != neighbour_name) {
                            std::cout << path_name << " -> " << neighbour_name << "(" << path.first << ")\n";
                            neighbour_nodes.push(path);
                        }
                    }
                }
            }
        }
        handled_nodes[min_path.second.second].second = Visited::TRUE;
    }

    return handled_nodes;
}

adjacency_list_t List::get() const {
    return this->list;
}




