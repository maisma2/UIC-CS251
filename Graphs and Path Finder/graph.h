/*graph.h*/

//
/* Abeer Ismail
Date: 8/4/2023
Purpose: To take a list of nodes and producing an adjacency list that we can use later on, the main change from the original
state of this graph.h file is now it will use a map of a vertex and vector<struct>.
*/
// original author: Prof. Scott Reckinger
// University of Illinois Chicago
// CS 251: Summer 2023
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>

using namespace std;


template<typename VertexT, typename WeightT>
class graph
{
private:

    //The first vector will store the vertices, the second will store a list of NeighborData which will be assigned to each Vertex
    struct NeighborData{
        VertexT Neighbor;
        WeightT Weight;

        NeighborData(VertexT vertex, WeightT weight) : Neighbor(vertex), Weight(weight){}
    };

    map<VertexT, vector<NeighborData>> AdjList;

    //Since we now have a map instead of the old adjMatrix we just need to know if the map carries the vertex with map.find() to maintain o(logn)
    bool _LookupVertex(VertexT v) const
    {
        return AdjList.find(v) != AdjList.end();
    }


public:
    graph() {}

    graph(const graph& other){ //Copy Constructor
        AdjList = other.AdjList;
    }

    void operator=(graph& orig){ //Copy operator
        AdjList = orig.AdjList;
    }



    //
    // NumVertices
    //
    // Returns the # of vertices currently in the graph.
    //
    int NumVertices() const
    {
        return AdjList.size();
    }

    //
    // NumEdges
    //
    // Returns the # of edges currently in the graph.
    //Loops through adjlist summing up the vector sizes that hold each edge, this is linear searching to find sums not to find a particular vertex/edge, which doesn't break the linear search rule.
    int NumEdges() const
    {
        int count = 0;

        for(const auto& kv : AdjList){
            count += kv.second.size();
        }

        return count;
    }

    //
    // addVertex
    //
    // Adds the vertex v to the graph if the vertex already
    // exists in the graph, then false is returned.
    //
    bool addVertex(VertexT v)
    {
        if (_LookupVertex(v)) {
            return false;
        }
        AdjList[v] = vector<NeighborData>();

        return true;
    }

    //
    // addEdge
    /*
    First checks From and To Exist, then it pushes it back of the from vector's neighbordata. O(N) complexity
    */
    bool addEdge(VertexT from, VertexT to, WeightT weight)
    {
        if (!_LookupVertex(from) || !_LookupVertex(to)){
            return false;
        }

        //Handling overwrites by looping and replacing weights
        for(auto& neighbor: AdjList[from]){
            if (neighbor.Neighbor == to){
                neighbor.Weight = weight;
                return true;
            }
        }

        //This is if the edge doesn't exist
        AdjList[from].push_back(NeighborData(to, weight));

        return true;
    }

    //
    // getWeight
    //
    // Returns the weight associated with a given edge.  If
    // the edge exists, the weight is returned via the reference
    // parameter and true is returned.  If the edge does not
    // exist, the weight parameter is unchanged and false is
    // returned. Loops through each neighbor for the from vector O(N) complexity
    //
    bool getWeight(VertexT from, VertexT to, WeightT& weight) const
    {
        if (!_LookupVertex(from) || !_LookupVertex(to)){
            return false;
        }
        else{
            for (const auto& neighbors : AdjList.at(from)){ //Maintains o(logn) and previous check should never throw out_of_range error
                if (neighbors.Neighbor == to){ //Checking each neighbor
                    weight = neighbors.Weight;
                    return true;
                }
            }
        }
        return false;
    }

    //
    // neighbors
    //
    // Returns a set containing the neighbors of v, i.e. all
    // vertices that can be reached from v along one edge.
    // Since a set is returned, the neighbors are returned in
    // sorted order; use foreach to iterate through the set.
    //
    set<VertexT> neighbors(VertexT v) const
    {
        set<VertexT> neighs;
        if (!_LookupVertex(v)) {
            return neighs;
        }
        for (const auto& neighburs: AdjList.at(v)){
            neighs.insert(neighburs.Neighbor);
        }

        return neighs;
    }

    //
    // getVertices
    //
    // Returns a vector containing all the vertices currently in
    // the graph.
    //
    vector<VertexT> getVertices() const
    {
        vector<VertexT> vertices;

        for (const auto& kv: AdjList){
            vertices.push_back(kv.first);
        }

        return vertices;
    }

    //
    // dump
    //
    // Dumps the internal state of the graph for debugging purposes.
    //
    // Example:
    //    graph<string,int>  G(26);
    //    ...
    //    G.dump(cout);  // dump to console
    //
    void dump(ostream& output) const
    {

        output << "***************************************************" << endl;
        output << "********************* GRAPH ***********************" << endl;

        output << "**Num vertices: " << this->NumVertices() << endl;
        output << "**Num edges: " << this->NumEdges() << endl;

        output << endl;
        output << "**Vertices:" << endl;
        for (const auto& vertex : this->getVertices()){
            output << vertex << endl;
        }

        output << endl;
        output << "**Edges:" << endl;
        for (const auto& kv : this->AdjList){
            output << kv.first << ": ";

            for (const auto& neighbors : kv.second){
                output    << "(" << kv.first
                          << "," << neighbors.Neighbor
                          << "," << neighbors.Weight
                          << ") ";
            }

            output << endl;
        }

        output << "**************************************************" << endl;
    }


};