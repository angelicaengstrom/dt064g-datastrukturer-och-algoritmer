#include "reader.h"
#include "List.h"
#include <fstream>

bool edge_to_file(const std::string& filename, const std::string& edge_text){
    std::ofstream out(filename, std::ios::app);
    if(out << edge_text << "\n"){
        out.close();
        return true;
    }
    return false;
}

bool connect_graph(const std::vector<node_id_t>& connected_start_nodes, const List& adjacent_list){
    for (node_id_t node: connected_start_nodes) {
        for(const auto& edge : adjacent_list.get().second){
            if(node == edge.n1){
                std::string edge_text = std::to_string(edge.n2) + " " +
                        std::to_string(edge.n1) + " " +
                        std::to_string(edge.weight) +
                        edge.description;

                std::cout << "Adding '" << edge_text << "' to make a connected graph" << std::endl;
                if(!edge_to_file(R"(C:\Users\angel\OneDrive\Dokument\DT046G Datastrukturer och Algoritmer\lab1\edges.txt)", edge_text)){
                    std::cout << "Failed accessing file..." << std::endl;
                    return false;
                }
            }
        }
    }
    return true;
}

int main(){
    List adjacent_list(R"(C:\Users\angel\OneDrive\Dokument\DT046G Datastrukturer och Algoritmer\lab1\edges.txt)");
    std::vector<node_id_t> connected_start_nodes;

    for (node_id_t start_node = 0; start_node < adjacent_list.size(); start_node++) {
        if (adjacent_list.generate_dfs(start_node) && adjacent_list.generate_bfs(start_node)) {
            connected_start_nodes.push_back(start_node);
        }
    }

    if (connected_start_nodes.size() != adjacent_list.size()) {
        std::cout << "The graph is NOT connected..." << std::endl;
        connect_graph(connected_start_nodes, adjacent_list);
    }else{
        std::cout << "The graph IS connected... Press enter to continue" << std::endl;

        std::cin.get();

        std::cout << "Generate Dijkstras algorithm... The path from Nackstavägen Axvägen 1: \n";
        std::vector<handled_t> nacksta_path = adjacent_list.generate_dijkstras(24);
        std::cout << "===========================" << std::endl;
        std::cout << adjacent_list.get_node_name(24) << " -> " << adjacent_list.get_node_name(37) << " = " << nacksta_path[37].first << std::endl;
        std::cin.get();

        std::cout << "\nThe path from L319: \n";
        std::vector<handled_t> L319_path = adjacent_list.generate_dijkstras(46);
        std::cout << "===========================" << std::endl;
        std::cout << adjacent_list.get_node_name(46) << " -> " << adjacent_list.get_node_name(47) << " = " << L319_path[47].first << std::endl;
        std::cin.get();

        std::cout << "\nThe path from University: \n";
        std::vector<handled_t> uni_path = adjacent_list.generate_dijkstras(20);
        std::cout << "===========================" << std::endl;
        std::cout << adjacent_list.get_node_name(20) << " -> " << adjacent_list.get_node_name(19) << " = " << uni_path[19].first << std::endl;
    }
    return 0;
}
