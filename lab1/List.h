//
// Created by angel on 2022-04-05.
//

#ifndef LAB1_LIST_H
#define LAB1_LIST_H

#include <string>
#include <vector>
#include <stack>
#include <list>
#include <queue>
#include <iostream>
#include <algorithm>
#include "reader.h"

using adjacency_matrix_t = std::vector<std::vector<weight_t>>;
using inf_t = std::numeric_limits<weight_t>;
using visited_t = bool;
using node_t = std::pair<weight_t, visited_t>;
using path_t = std::pair<weight_t,std::pair<visited_t, node_id_t>>;

enum Weight{ SELF = 0 };
enum Visited{ FALSE, TRUE };

class List {
public:
    List();
    List(const std::string& filename): list(parse_file(filename)){
        this->matrix = create_matrix();
    };
    bool generate_dfs(const node_id_t& start);
    bool generate_bfs(const node_id_t& start);
    std::vector<node_t> generate_dijkstras(const node_id_t& start);
    size_t size() const;
    adjacency_list_t get() const;
    std::string get_edge_name(const int& index) const;
private:
    adjacency_list_t list;
    adjacency_matrix_t matrix;
    adjacency_matrix_t create_matrix();
    bool is_connected(const std::vector<node_id_t>& visited_nodes);
};


#endif //LAB1_LIST_H
