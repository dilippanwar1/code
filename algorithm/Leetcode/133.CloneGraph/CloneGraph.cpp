// Clone an undirected graph. Each node in the graph contains a label and a
// list of its neighbors.

#include <vector>
#include <unordered_map>
using namespace std;


struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};


class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {

        if (node == NULL)
            return NULL;

        unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> map;
        return cloneGraphHelper(node, map);
    }

    UndirectedGraphNode *cloneGraphHelper(UndirectedGraphNode *node,
        unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> &map) {

        UndirectedGraphNode *new_node = new UndirectedGraphNode(node->label);
        // current node has been visited, and keep its corresponding new node
        map[node] = new_node;

        // go through all neighbors, either create new node recursively, or
        // add directly using map
        for (int i = 0; i < node->neighbors.size(); i++) {
            if (map.count(node->neighbors[i]) != 0) {
                new_node->neighbors.push_back(map[node->neighbors[i]]);
            } else {
                new_node->neighbors.push_back(
                    cloneGraphHelper(node->neighbors[i], map));
            }
        }

        return new_node;
    }
};


int main(void) {

}
