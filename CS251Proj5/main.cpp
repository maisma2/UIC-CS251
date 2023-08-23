/*main.cpp*/

//
// Prof. Scott Reckinger
// University of Illinois Chicago
// CS 251: Summer 2023
// Project #05: open street maps, graphs, and Dijkstra's alg
// 
// References:
// TinyXML: https://github.com/leethomason/tinyxml2
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:  
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#include <iostream>
#include <iomanip>  /*setprecision*/
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <limits>
#include <cctype>

#include "tinyxml2.h"
#include "graph.h"
#include "dist.h"
#include "osm.h"

using namespace std;
using namespace tinyxml2;

void Dijkstra(graph<long long, double>& G, long long start, map<long long, double>& distances ,map<long long, long long>& preds){
    double INF = numeric_limits<double>::max();
    for(const auto& node : G.getVertices()){
        distances[node] = INF;
        preds[node] = -1;
    }

    distances[start] = 0;

    priority_queue<pair<double, long long>, vector <pair<double, long long>>, greater<pair<double, long long>>> pq; //pq to sort each node when comparing weights

    pq.push(make_pair(0, start));

    while(!pq.empty()){
        long long from = pq.top().second;
        pq.pop();

        for (const auto& i : G.neighbors(from)){
            long long to = i;
            double weight;
            G.getWeight(from, to, weight);

            if(distances[to] > distances[from] + weight){
                distances[to] = distances[from] + weight;
                pq.push(make_pair(distances[to], to));
                preds[to] = from;
            }
        }
    }
}

string toLower(string str){
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

//////////////////////////////////////////////////////////////////
//
// main
//
int main()
{
    map<long long, Coordinates>  Nodes;     // maps a Node ID to it's coordinates (lat, lon)
    vector<FootwayInfo>          Footways;  // info about each footway, in no particular order
    vector<BuildingInfo>         Buildings; // info about each building, in no particular order
    XMLDocument                  xmldoc;
    graph<long long, double> G;
    double INF = numeric_limits<double>::max();
    long long startNode, destNode;

    cout << "** Navigating UIC open street map **" << endl;
    cout << endl;
    cout << std::setprecision(8);

    string def_filename = "map.osm";
    string filename;

    cout << "Enter map filename> ";
    getline(cin, filename);

    if (filename == "")
    {
        filename = def_filename;
    }

    //
    // 1. Load XML-based map file
    //
    if (!LoadOpenStreetMap(filename, xmldoc))
    {
        cout << "**Error: unable to load open street map." << endl;
        cout << endl;
        return 0;
    }

    //
    // 2. Read the nodes, which are the various known positions on the map:
    //
    int nodeCount = ReadMapNodes(xmldoc, Nodes);

    //
    // 3. Read the footways, which are the walking paths:
    //
    int footwayCount = ReadFootways(xmldoc, Footways);

    //
    // 4. Read the university buildings:
    //
    int buildingCount = ReadUniversityBuildings(xmldoc, Nodes, Buildings);

    //
    // Stats
    //
    assert(nodeCount == (int)Nodes.size());
    assert(footwayCount == (int)Footways.size());
    assert(buildingCount == (int)Buildings.size());

    cout << endl;
    cout << "# of nodes: " << Nodes.size() << endl;
    cout << "# of footways: " << Footways.size() << endl;
    cout << "# of buildings: " << Buildings.size() << endl;


    //Adding nodes as vertices
    for (const auto& node : Nodes){
        G.addVertex(node.first);
    }
    //Adding edges as footways
    for (const auto& footway : Footways){
        for (size_t i = 0; i < footway.Nodes.size() - 1; i++){
            //First two nodes
            long long node1 = footway.Nodes[i];
            long long node2 = footway.Nodes[i+1];

            //Calculating distance between nodes for weight
            double lat1 = Nodes[node1].Lat;
            double lat2 = Nodes[node2].Lat;

            double lng1 = Nodes[node1].Lon;
            double lng2 = Nodes[node2].Lon;

            //Giving the weight and adding 2 edges, distBetweenPoints in dist.cpp
            G.addEdge(node1, node2, distBetween2Points(lat1, lng1, lat2, lng2));
            G.addEdge(node2, node1, distBetween2Points(lat1, lng1, lat2, lng2));
        }
    }



    cout << "# of vertices: " << G.NumVertices() << endl;
    cout << "# of edges: " << G.NumEdges() << endl;
    cout << endl;

    //
    // Navigation from building to building
    // 7. Input start and dest buildings
    //



    while (true)
    {
        string startBuilding, destBuilding;
        cout << "Enter start (partial name or abbreviation), or #> ";
        getline(cin, startBuilding);
        if(startBuilding == "#"){
            cout << "** Done **" << endl;
            return 0;
        }
        cout << "Enter destination (partial name or abbreviation)> ";
        getline(cin, destBuilding);
        if(destBuilding == "#"){
            cout << "** Done **" << endl;
            return 0;
        }


        // 7) Lookup buildings
        BuildingInfo startB, destB;
        bool foundStart = false, foundDest = false;

        // 8) Find the nearest start and dest buildings and nodes, making it lowercase to have find look for stuff better
        for (const auto& building : Buildings){
            string fullLower = toLower(building.Fullname);
            string abbrevLower = toLower(building.Abbrev);
            string startLower = toLower(startBuilding);
            string destLower = toLower(destBuilding);

            if(!foundStart && (abbrevLower == startLower || fullLower.find(startLower) != string::npos)){
                startB = building;
                foundStart = true;
            }
            if(!foundDest && (abbrevLower == destLower || fullLower.find(destLower) != string::npos)){
                destB = building;
                foundDest = true;
            }

            if(foundStart && foundDest) break; //When both are true leave loop;

        }
        if (!foundStart){
            cout << "Start building not found" << endl;
        }
        else if (!foundDest){
            cout << "Destination building not found" << endl;
        }
        else{
            double minStartDist = INF;
            double minDestDist = INF;

            //Loops through the footways trying to find the shortest distances from the current Node
            for (const auto& footway : Footways){
                for (const auto& node : footway.Nodes){
                    double startDist = distBetween2Points(startB.Coords.Lat, startB.Coords.Lon, Nodes[node].Lat, Nodes[node].Lon);
                    double destDist = distBetween2Points(destB.Coords.Lat, destB.Coords.Lon, Nodes[node].Lat, Nodes[node].Lon);

                    if (startDist < minStartDist){
                        minStartDist = startDist;
                        startNode = node;
                    }

                    if (destDist < minDestDist){
                        minDestDist = destDist;
                        destNode = node;
                    }
                }
            }


        }

        //Applying Dijkstra and finding distances
        if(foundStart && foundDest){


            cout << "Starting point:" << endl
                 << " " << startB.Fullname  << endl
                 << " " << "(" << startB.Coords.Lat << ", " << startB.Coords.Lon << ")"
                 << endl;
            cout << "Destination point:" << endl
                 << " " << destB.Fullname << endl
                 << " " << "(" << destB.Coords.Lat << ", " << destB.Coords.Lon << ")" << endl << endl;
            cout << "Nearest start node:" << endl
                 << " " << startNode << endl << " ("
                 <<  Nodes[startNode].Lat << ", "
                 <<  Nodes[startNode].Lon << ")" << endl;
            cout <<"Nearest destination node:" << endl << " " << destNode << endl
                 << " " << "(" << Nodes[destNode].Lat << ", " << Nodes[destNode].Lon
                 << ")" << endl << endl;



            map<long long, long long> pred;
            map<long long, double> distances;
            Dijkstra(G, startNode, distances, pred);

            //10) Now measuring out distances
            if(distances[destNode] == INF){ //INF is unreachable
                cout << "Navigating with Dijkstra..." << endl;
                cout << "Sorry, destination unreachable" << endl;
            }

            else{ //It's DFS finding the path down the stack
                cout << "Navigating with Dijkstra..." << endl;
                cout << "Distance to dest: " << distances[destNode] << " miles" << endl;
                cout << "Path: ";
                stack<long long> path;
                long long node = destNode;
                while(node != -1){
                    path.push(node);
                    node = pred[node];
                }
                while (!path.empty()){
                    cout << path.top();
                    path.pop();
                    if(!path.empty()) cout << "->";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

}

