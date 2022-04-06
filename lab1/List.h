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
using handled_t = std::pair<weight_t, bool>;
using path_t = std::pair<weight_t, node_id_t>;

enum Weight{ SELF = 0 };
enum Visited{ FALSE, TRUE };

class List {
public:
    List() = default;
    explicit List(const std::string& filename): list(parse_file(filename)){
        matrix.resize(list.first.size(), std::vector<weight_t>(list.first.size()));
        create_matrix();
    };

    bool generate_dfs(const node_id_t& start);
    bool generate_bfs(const node_id_t& start);
    std::vector<handled_t> generate_dijkstras(const node_id_t& start);

    size_t size() const{ return matrix.size(); }

    adjacency_list_t get() const{ return list; }
    std::string get_node_name(const int& index) const{ return list.first.at(index); }

private:
    adjacency_list_t list;
    adjacency_matrix_t matrix;
    void create_matrix();
};


#endif //LAB1_LIST_H
