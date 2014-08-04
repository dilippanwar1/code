#!/usr/bin/python
# Example graph, `G`:
# a connected to c, b, d; with weight of 3, 15, 4 respectively.
G = {
    'a':{'c':3,'b':15,'d':4},
    'b':{'c':10,'a':15,'d':9},
    'c':{'a':3,'b':10},
    'd':{'a':4,'b':9,'e':3,'f':7},
    'e':{'d':3,'f':5,'g':1},
    'f':{'d':7,'b':1,'e':5,'g':2},
    'g':{'e':1,'f':2}
}


#=============================================================================
# Implementation of dijkstra without using heap
# @param `G` dictionary representation of graph
# @param `v` source node
# @return a dictionary of shortest path of each node from `v`
def dijkstra1(G, v):

    # Helper functoin. find the node with shortest gready path.
    # using linear search, slow.
    def find_shortest_sofar(dist):
        best_node, best_value = None, 10000
        for v in dist:
            if dist[v] < best_value:
                (best_node, best_value) = (v, dist[v])
        return best_node

    # `final_list` is a dict which contains nodes whose shortest
    # path have been found.
    final_list = {}
    # `dist_sofar` is a dict contains greedy shortest path; i.e, nodes
    # that have not found final shortest path. (have not been explored).
    # Initially, only `v`'s shortest path is known.
    dist_sofar = {v: 0}

    # While there are nodes still haven't been processed
    while len(final_list) < len(G):
        # Find the node with shortest path to `final_list`, the node is
        # chosen from unexplored nodes.
        w = find_shortest_sofar(dist_sofar)
        # Node `w` has the shortest path, so it is added to `final_list`;
        # and is then removed from `dist_sofar`
        final_list[w] = dist_sofar[w]
        del dist_sofar[w]
        # For each node adjacent to `w`, update its greedy shortest path.
        for neighbor in G[w]:
            if neighbor not in final_list:
                if neighbor not in dist_sofar:
                    dist_sofar[neighbor] = final_list[w] + G[w][neighbor]
                elif final_list[w] + G[w][neighbor] < dist_sofar[neighbor]:
                    dist_sofar[neighbor] = final_list[w] + G[w][neighbor]
    return final_list


print "Shortest path to a: ", dijkstra1(G, 'a')
