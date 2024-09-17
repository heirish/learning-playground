#ifndef __DISJOINT_SETS__
#define __DISJOINT_SETS__
#include <unordered_map>
namespace DISJOINT_SETS {
class Disjoint_set {
public:
    Disjoint_set(bool basic_test = false) {
        if (basic_test) {
            char universe[] = {'a', 'b', 'c', 'd', 'e'}; //Universe of item: 'a', 'b', 'c', 'd', 'e'
            for (char x:universe) {//We have 5 disjoint sets, each set contain one item.
                MakeSet(x);
            }
            PARENT['d'] = 'b'; //'b' and 'd' are in same set, => 4 sets
            RANK['b'] = 1;
        }
    }
    char Find(char item) {
        if (PARENT[item] == item) {//root
            return item;
        } else {
            return Find(PARENT[item]);
        }
    }
    void Union(char set_1, char set_2) {
        if (RANK[set_1] > RANK[set_2]) {
            PARENT[set_2] = set_1; //set_1 is the new root, but because its RANK is already bigger than set_2, so union set_2 to set_1 will not increase set_1's RANK
        } else if (RANK[set_1] < RANK[set_2]) {
            PARENT[set_1] = PARENT[set_2];
        } else {
            PARENT[set_1] = set_2; //set_2 is the new root, since RANK[set_1] == RANK[set_2], so this will increase set_2's RANK
            RANK[set_2] += 1;
        }
    }
    void MakeSet(char c) {
        PARENT[c] = c;
        RANK[c] = 0;
    }
private:    
    std::unordered_map<char, char> PARENT;
    std::unordered_map<char, int> RANK; //the depth of trees
};

void basic_test() {
    Disjoint_set ds(true);
    std::cout << ds.Find('c') << std::endl; //'c'
    ds.Union('c', 'a'); //'a', 'c' are in the same set
    std::cout << ds.Find('c') << std::endl; //'a'
    ds.Union('a', 'b'); //'c', 'a', 'd', 'b' are in the same set.

}

struct  Edge {
    char vertex1;
    char vertex2;
    int weight;
    Edge(char v1, char v2, int w):vertex1(v1), vertex2(v2), weight(w){}
};
struct Graph {
    std::vector<char> vertices;
    std::vector<Edge> edges;
};
void Kruskal(Graph& g) {
    std::vector<Edge> A;

    Disjoint_set ds;
    for(auto c:g.vertices) {
        ds.MakeSet(c);
    }

    std::sort(g.edges.begin(), g.edges.end(), [](Edge x, Edge y){
        return x.weight < y.weight;
    }); //complexity:O(E*long(E))

    for(Edge e:g.edges) { //complexity: E
        char root1 = ds.Find(e.vertex1);
        char root2 = ds.Find(e.vertex2);
        if (root1 != root2) {
            A.push_back(e);
            ds.Union(root1, root2);
        }
    }
    std::for_each(A.begin(), A.end(), [](Edge item){
        std::cout << item.vertex1 << "--" << item.vertex2 << ",w:" << item.weight << std::endl;
    });
}
void kruskal_alg_test() {
    char t[] = {'a','b', 'c', 'd', 'e', 'f'};

    //sparse grahp(E=O(V)) represented with Adjacent
    //If it is a dense graph(E=O(V*V)), use Adjacent
    //Most interesting graphs are sparse.
    Graph g;
    g.vertices = std::vector<char>(t, t+sizeof(t)/sizeof(t[0]));
    g.edges.push_back(Edge('a', 'b', 4));
    g.edges.push_back(Edge('a', 'f', 2));
    g.edges.push_back(Edge('f', 'b', 5));
    g.edges.push_back(Edge('c', 'b', 6));
    g.edges.push_back(Edge('c', 'f', 1));
    g.edges.push_back(Edge('f', 'e', 4));
    g.edges.push_back(Edge('d', 'e', 2));
    g.edges.push_back(Edge('d', 'c', 3));
    Kruskal(g);
}

struct GraphP {
    std::vector<char> vertices;
    std::vector<Edge> edges;
    std::vector<std::pair<char, Edge>> adjacent(char u) {
        std::vector<std::pair<char, Edge>> res;
        for(Edge e:edges) {
            if (e.vertex1 == u) {
                res.push_back(std::make_pair(e.vertex2, e));
            } else if (e.vertex2 == u) {
                res.push_back(std::make_pair(e.vertex1, e));
            }
        }
        return res;
    }
};

void prim(GraphP& g) {
    std::unordered_map<char, char> A;
    std::unordered_map<char, char> PARENT;
    std::unordered_map<char, int> KEY;

    for(auto c:g.vertices) { //for each v in V, KEY[v]=MAX, PARENT[v]=null
        PARENT[c] = '\0';
        KEY[c] = INT_MAX;
    }
    KEY['a'] = 0; //KEY[r]=0, randomly set one vertex's key to 0
    std::vector<char> Q = g.vertices; //Q=V

    while(!Q.empty()) { //O(V)
        char u = *(std::min_element(Q.begin(), Q.end(), [&](char x, char y){ //O(V)
            return KEY[x] < KEY[y];
        }));
        std::cout << "u=" << u << std::endl;
        std::vector<char>::iterator it = std::remove(Q.begin(), Q.end(), u); //O(V)
        Q.erase(it, Q.end()); //erase() following remove() idom
        std::cout << "Q.size() == " << Q.size() << std::endl;
        if (PARENT[u] != '\0') {
            A[u] = PARENT[u];
        }
        std::vector<std::pair<char, Edge>> adj = g.adjacent(u); //O(E)
        for(std::pair<char, Edge> v:adj) {
            if (std::find(Q.begin(), Q.end(), v.first) != Q.end()  //O(V)
                && v.second.weight < KEY[v.first]) {
                    PARENT[v.first] = u;
                    KEY[v.first] = v.second.weight;
            }
        }
    }
    for(auto e:A) {
        std::cout << e.first << "--" << e.second << std::endl;
    }
}
void prim_alg_test() {
    char t[] = {'a','b', 'c', 'd', 'e', 'f'};

    GraphP g;
    g.vertices = std::vector<char>(t, t+sizeof(t)/sizeof(t[0]));
    g.edges.push_back(Edge('a', 'b', 4));
    g.edges.push_back(Edge('a', 'f', 2));
    g.edges.push_back(Edge('f', 'b', 3));
    g.edges.push_back(Edge('c', 'b', 6));
    g.edges.push_back(Edge('c', 'f', 1));
    g.edges.push_back(Edge('f', 'e', 4));
    g.edges.push_back(Edge('d', 'e', 2));
    g.edges.push_back(Edge('d', 'c', 3));
    prim(g);
}
}
#endif //__DISJOINT_SETS__