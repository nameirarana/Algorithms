#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define edge pair<int,int>
bool sortinrev(const pair<int,edge> &a, const pair<int,edge> &b){
       return (a.first > b.first);
}
class Graph_ {
public:
    vector<pair<int, edge> > Graph; // graph
    vector<pair<int, edge> > MST; // mst
    int *parent;
    int Vertices;

    Graph_(){
    }
    void Initialize(int v){
           Vertices = v;
           parent = new int[Vertices];
           for (int i = 0; i < Vertices; i++)
               parent[i] = i;

           Graph.clear();
           MST.clear();
    }

   int Find_Parent(int i){
        return i==parent[i]?i:parent[i]=Find_Parent(parent[i]);
    }

    void Graph_MST(){
        int i, u, v;
        sort(Graph.begin(), Graph.end(),sortinrev); // increasing weight
        for (i = 0; i < Graph.size(); i++) {
            u = Find_Parent(Graph[i].second.first);
            v = Find_Parent(Graph[i].second.second);
            if (u != v) {
                MST.push_back(Graph[i]); // add to tree
                parent[u] = parent[v];
            }
        }
    }
    void MST_Print(){
        for (int i = MST.size()- 1 ; i >= 0 ; i--) {
            printf("%d %d %d\n",MST[i].second.first,MST[i].second.second ,MST[i].first);
        }
    }
    void Print(){
        for (int i = 0 ; i < Graph.size() ; i++) {
            printf("%d %d %d\n",Graph[i].second.first,Graph[i].second.second ,Graph[i].first);
        }
    }
};
bool Graph_Path(int source, int destination, int **array, int size){
        for(int i = destination+1; i < size; i++){
            if(min(array[i][source], array[source][destination]) > array[i][destination] || min(array[i][destination], array[source][destination]) > array[i][source] || min(array[i][source], array[i][destination]) > array[source][destination]){
                return false;
            }
        }
        return true;
}
int main() {
    int iteration = 0, size = 0, value = 0, i, j, k;
    scanf("%d",&iteration);
    Graph_ graph;
    bool possible = true;
    for(i = 0; i < iteration; i++){
       scanf("%d",&size);
        int **array = new int*[size];
        graph.Initialize(size);
        for(int j = 0; j < size; j++){
             array[j] = new int[size];
        }
        for(j = 0; j < size; j++){
            //array[j] = new int[size];
            for(k = 0; k < size; k++){
                scanf("%d",&value);
                array[j][k] = value;
                graph.Graph.push_back(make_pair(value, edge(j, k)));
            }
        }
        for(int j = 0; j < size; j++){
            for(int k = j+1; k < size; k++){
                possible = Graph_Path(j, k, array, size);
                if(possible == false){
                        break;
                    }
                }
                if(possible == false){
                    break;
                }
        }
        printf("Case #%d: ",i+1);
        if(possible){
            printf("%d\n",size-1);
            graph.Graph_MST();
            graph.MST_Print();
        }
        else{
            puts("Impossible");
        }
    }
    return 0;
}
