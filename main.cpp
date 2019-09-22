// Project Identifier: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD
//  main.cpp
//  Project1
//
//  Created by Andrew Myers on 9/17/19.
//  Copyright © 2019 Andrew Myers. All rights reserved.
//
#include <getopt.h>
#include <deque>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "xcode_redirect.hpp"

using namespace std;

struct Hunt {
    deque<pair<int, int>> sailContainer;
    deque<pair<int, int>> searchContainer;
    deque<pair<int, int>> discoveredLocations;
    int waterLocations = 0;
    int landLocations = 0;
    int timesAshore = 0;
    int investLocations = 0;
    pair<int, int> startingLocation;
    bool successfulHunt = false;
    bool showStats = false;
    bool showVerbose = false;
    string showPath;
    string captainCon = "stack";
    string fmCon = "queue";
    string huntOrder = "nesw";
    
};
struct Backtracer {
    vector<pair<int, int>> coordinates;
    vector<char> directions;
    deque<pair<int, int>> sailBack;
    deque<pair<int, int>> searchBack;
};
void printMap(Backtracer &bt,vector<vector<char>> &map, string mapType) {
    if(mapType == "M") {
        for(size_t i = 0; i < map.size(); i++) {
            for(size_t j = 0; j < map.size(); j++) {
                cout << map[i][j];
            }
            cout << '\n';
        }
    }
    else {
        cout << "Sail:" << '\n';
        for(size_t i = 0; i < bt.sailBack.size(); i++) {
            cout << bt.sailBack[i].first << ',' << bt.sailBack[i].second << '\n';
        }
        cout << "Search:" << '\n';
        for(size_t i = 0; i < bt.searchBack.size(); i++) {
            cout << bt.searchBack[i].first << ',' << bt.searchBack[i].second << '\n';
        }
    }
}


int runBacktracer(Backtracer &bt, Hunt &h, pair<int, int> p, vector<vector<char>> &map) {
    int pathLength = 0;
    pair<int, int> starter = p;
    if(h.showPath == "M") {
        map[size_t(p.first)][size_t(p.second)] = 'X';
    }
    size_t counter = 0;
    while(starter != h.startingLocation) {
        counter++;
        if(counter > map.size() * map.size()) {
            return int(counter - 1);
        }
        for(size_t i = 0; i < bt.coordinates.size(); i++) {
            if(bt.coordinates[i] == starter) {
                if(bt.directions[i] == 'n') {
                    pair<int, int> temp(starter.first + 1, starter.second);
                    starter = temp;
                    pathLength++;
                    if(h.showPath == "M") {
                        if(map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] == 'X') {
                            break;
                        }
                        if(map[size_t(bt.coordinates[i+1].first)][size_t(bt.coordinates[i+1].second)] == 'X') {
                            map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] = '|';
                        }
                        else if(map[size_t(bt.coordinates[i+1].first)][size_t(bt.coordinates[i+1].second)] == '-') {
                            map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] = '+';
                        }
                        else {
                            map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] = '|';
                        }
                    }
                    else if(h.showPath == "L") {
                        if(map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] == '$') {
                            break;
                        }
                        else if(map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] == 'o') {
                            bt.searchBack.push_front(bt.coordinates[i]);
                        }
                        else {
                            bt.sailBack.push_front(bt.coordinates[i]);
                        }
                    }
                    break;
                }
                else if(bt.directions[i] == 'e') {
                    pair<int, int> temp(starter.first, starter.second - 1);
                    starter = temp;
                    pathLength++;
                    if(h.showPath == "M") {
                        if(map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] == 'X') {
                            break;
                        }
                        if(map[size_t(bt.coordinates[i+1].first)][size_t(bt.coordinates[i+1].second)] == 'X') {
                            map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] = '-';
                        }
                        else if(map[size_t(bt.coordinates[i+1].first)][size_t(bt.coordinates[i+1].second)] == '|') {
                            map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] = '+';
                        }
                        else {
                            map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] = '-';
                        }
                    }
                    else if(h.showPath == "L") {
                        if(map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] == '$') {
                            break;
                        }
                        else if(map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] == 'o') {
                            bt.searchBack.push_front(bt.coordinates[i]);
                        }
                        else {
                            bt.sailBack.push_front(bt.coordinates[i]);
                        }
                    }
                    break;
                }
                else if(bt.directions[i] == 's') {
                    pair<int, int> temp(starter.first - 1, starter.second);
                    starter = temp;
                    pathLength++;
                    if(h.showPath == "M") {
                        if(map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] == 'X') {
                            break;
                        }
                        if(map[size_t(bt.coordinates[i+1].first)][size_t(bt.coordinates[i+1].second)] == 'X') {
                            map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] = '|';
                        }
                        else if(map[size_t(bt.coordinates[i+1].first)][size_t(bt.coordinates[i+1].second)] == '-') {
                            map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] = '+';
                        }
                        else {
                            map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] = '|';
                        }
                    }
                    else if(h.showPath == "L") {
                        if(map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] == '$') {
                            break;
                        }
                        else if(map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] == 'o') {
                            bt.searchBack.push_front(bt.coordinates[i]);
                        }
                        else {
                            bt.sailBack.push_front(bt.coordinates[i]);
                        }
                    }
                    break;
                }
                else {
                    pair<int, int> temp(starter.first, starter.second + 1);
                    starter = temp;
                    pathLength++;
                    if(h.showPath == "M") {
                        if(map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] == '$') {
                            break;
                        }
                        if(map[size_t(bt.coordinates[i+1].first)][size_t(bt.coordinates[i+1].second)] == 'X') {
                            map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] = '-';
                        }
                        else if(map[size_t(bt.coordinates[i+1].first)][size_t(bt.coordinates[i+1].second)] == '|') {
                            map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] = '+';
                        }
                        else {
                            map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] = '-';
                        }
                    }
                    else if(h.showPath == "L") {
                        if(map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] == 'X') {
                            break;
                        }
                        else if(map[size_t(bt.coordinates[i].first)][size_t(bt.coordinates[i].second)] == 'o') {
                            bt.searchBack.push_front(bt.coordinates[i]);
                        }
                        else {
                            bt.sailBack.push_front(bt.coordinates[i]);
                        }
                    }
                    break;
                }
            }
        }
    }
    if(h.showPath == "L") {
        bt.searchBack.push_back(p);
        bt.sailBack.push_front(h.startingLocation);
    }
    return pathLength;
}

void readTreasureMap(vector<vector<char>> &map, char &mapStyle, size_t N, Hunt &h) {
    char mapSpace;
    size_t rowNum;
    size_t colNum;
    if(mapStyle == 'M') {
        for(size_t i = 0; i < N; i++) {
            for(size_t j = 0; j < N; j++) {
                cin >> mapSpace;
                if(mapSpace == '@') {
                    pair<int, int> p(i, j);
                    if(h.captainCon == "queue") {
                        h.sailContainer.push_back(p);
                    }
                    else {
                        h.sailContainer.push_front(p);
                    }
                }
                map[i][j] = mapSpace;
            }
        }
    }
    else if(mapStyle == 'L') {
        while(cin >> rowNum) {
            cin >> colNum;
            cin >> mapSpace;
            if(mapSpace == '@') {
                pair<int, int> p(rowNum, colNum);
                if(h.captainCon == "queue") {
                    h.sailContainer.push_back(p);
                }
                else {
                    h.sailContainer.push_front(p);
                }
            }
            map[rowNum][colNum] = mapSpace;
        }
        for(size_t i = 0; i < N; i++) {
            for(size_t j = 0; j < N; j++) {
                if(map[i][j] == '\0') {
                    map[i][j] = '.';
                }
            }
        }
    }
}
void failedHunt(Hunt &h) {
    cout << "No treasure found after investigating " <<
    h.discoveredLocations.size() << "locations.\n";
}
void endHunt(pair<int, int> p, Hunt &h, Backtracer &bt, vector<vector<char>> &map) {
    int pathLength = runBacktracer(bt, h, p, map);
    h.successfulHunt = true;
    if(h.showStats == true) {
       cout << "--- STATS ---\n" << "Starting location: " << h.startingLocation.first << ',' << h.startingLocation.second << '\n' << "Water locations investigated: " << h.waterLocations << '\n' << "Land locations investigated: " << h.landLocations << '\n' << "Went ashore: " << h.timesAshore << '\n' << "Path length: " << pathLength << '\n' << "Treasure location: " << p.first << ',' << p.second << '\n' << "--- STATS ---\n";
    }
    if(h.showPath == "M") {
        printMap(bt, map, "M");
    }
    else if(h.showPath == "L") {
        printMap(bt, map, "L");
    }
    cout << "Treasure found at " << p.first << ',' << p.second << " with path"
    << " length " << pathLength << "." << '\n';
    while(h.sailContainer.empty() != true) {
        h.sailContainer.pop_front();
    }
    while (h.searchContainer.empty() != true) {
        h.searchContainer.pop_front();
    }
}
bool checkPreviouslyDiscovered(pair<int, int> p, Hunt &h) {
    for(size_t i = 0; i < h.discoveredLocations.size(); i++) {
        if(h.discoveredLocations[i].first == p.first && h.discoveredLocations[i].second == p.second) {
            return true;
        }
    }
    return false;
}
void searchFMLocation(vector<pair<int, int>> v, vector<vector<char>> &map, Hunt &h, Backtracer &bt) {
    string huntO = h.huntOrder;
    for(size_t i = 0; i < 4; i++) {
        if((v[i].first > -1 && v[i].first < int(map[0].size())) && (v[i].second > -1
                                                              && v[i].second < int(map[0].size()))) {
            if(map[size_t(v[i].first)][size_t(v[i].second)] == 'o') {
                if(checkPreviouslyDiscovered(v[i], h) == false) {
                    if(huntO[i] == 'n') {
                        bt.directions.push_back('n');
                    }
                    else if(huntO[i] == 'e') {
                        bt.directions.push_back('e');
                    }
                    else if(huntO[i] == 's') {
                        bt.directions.push_back('s');
                    }
                    else {
                        bt.directions.push_back('w');
                    }
                    if(h.fmCon == "stack") {
                       h.searchContainer.push_front(v[i]);
                    }
                    else {
                        h.searchContainer.push_back(v[i]);
                    }
                    bt.coordinates.push_back(v[i]);
                    h.discoveredLocations.push_back(v[i]);
                }
            }
            else if(map[size_t(v[i].first)][size_t(v[i].second)] == '$') {
                if(huntO[i] == 'n') {
                    bt.directions.push_back('n');
                }
                else if(huntO[i] == 'e') {
                    bt.directions.push_back('e');
                }
                else if(huntO[i] == 's') {
                    bt.directions.push_back('s');
                }
                else {
                    bt.directions.push_back('w');
                }
                if(h.showVerbose == true) {
                    cout << "party found treasure at " << v[i].first << ',' <<
                    v[i].second << ".\n";
                }
                h.landLocations++;
                if(h.fmCon == "stack") {
                    h.searchContainer.push_front(v[i]);
                }
                else {
                    h.searchContainer.push_back(v[i]);
                }
                bt.coordinates.push_back(v[i]);
                h.discoveredLocations.push_front(v[i]);
                endHunt(v[i], h, bt, map);
                return;
            }
            
        }
    }
}
void firstMateTakeOver(Hunt &h, vector<vector<char>> &map, Backtracer &bt) {
    if(h.showVerbose == true) {
        cout << "Went ashore at: " << h.searchContainer.front().first << ','
        << h.searchContainer.front().second
        << '\n';
        cout << "Searching island... ";

    }
    h.timesAshore++;
    while(h.searchContainer.empty() == false) {
        pair<int, int> currentLocation = h.searchContainer.front();
        h.landLocations++;
        h.investLocations++;
        h.searchContainer.pop_front();
        vector<pair<int, int>> locations;
        pair<int, int> north(currentLocation.first - 1, currentLocation.second);
        pair<int, int> east(currentLocation.first, currentLocation.second - 1);
        pair<int, int> south(currentLocation.first + 1, currentLocation.second);
        pair<int, int> west(currentLocation.first, currentLocation.second + 1);
        for(size_t i = 0; i < 4; i++) {
            if(h.huntOrder[i] == 'n') {
                locations.push_back(north);
            }
            else if(h.huntOrder[i] == 'e') {
               locations.push_back(east);
            }
            else if(h.huntOrder[i] == 's') {
                locations.push_back(south);
            }
            else {
                locations.push_back(west);
            }
        }
        searchFMLocation(locations, map, h, bt);
    }
    if(h.showVerbose == true && h.successfulHunt == false) {
        cout << "party returned with no treasure." << '\n';
    }
    return;
}

void searchLocation(vector<pair<int, int>> v, vector<vector<char>> &map, Hunt &h, Backtracer &bt) {
    for(size_t i = 0; i < 4; i++) {
        if(h.successfulHunt == true) {
            return;
        }
        string huntO = h.huntOrder;
        if((v[i].first > -1 && v[i].first < int(map[0].size())) && (v[i].second > -1
        && v[i].second < int(map[0].size()))) {
            if(map[size_t(v[i].first)][size_t(v[i].second)] == '.') {
                if(checkPreviouslyDiscovered(v[i], h) == false) {
                    if(huntO[i] == 'n') {
                        bt.directions.push_back('n');
                    }
                    else if(huntO[i] == 'e') {
                        bt.directions.push_back('e');
                    }
                    else if(huntO[i] == 's') {
                        bt.directions.push_back('s');
                    }
                    else {
                        bt.directions.push_back('w');
                    }
                    if(h.captainCon == "queue") {
                        h.sailContainer.push_back(v[i]);
                    }
                    else {
                        h.sailContainer.push_front(v[i]);
                    }
                    bt.coordinates.push_back(v[i]);
                    h.discoveredLocations.push_front(v[i]);
                }
            }
            else if(map[size_t(v[i].first)][size_t(v[i].second)] == 'o') {
                if(checkPreviouslyDiscovered(v[i], h) == false) {
                    if(huntO[i] == 'n') {
                        bt.directions.push_back('n');
                    }
                    else if(huntO[i] == 'e') {
                        bt.directions.push_back('e');
                    }
                    else if(huntO[i] == 's') {
                        bt.directions.push_back('s');
                    }
                    else {
                        bt.directions.push_back('w');
                    }
                    if(h.fmCon == "stack") {
                        h.searchContainer.push_front(v[i]);
                    }
                    else {
                        h.searchContainer.push_back(v[i]);
                    }
                    bt.coordinates.push_back(v[i]);
                    h.discoveredLocations.push_back(v[i]);
                    firstMateTakeOver(h, map, bt);
                }
            }
        }
    }
}
void startHunt(Hunt &h, vector<vector<char>> &map, Backtracer &bt) {
    pair<int, int> p(h.sailContainer.front().first, h.sailContainer.front().second);
    h.startingLocation = p;
    if(h.showVerbose == true) {
        cout << "Treasure hunt started at: " <<
        h.sailContainer.front().first << ',' << h.sailContainer.front().second
        << '\n';
    }
    while(h.sailContainer.empty() == false) {
        pair<int, int> currentLocation = h.sailContainer.front();
        h.waterLocations++;
        h.investLocations++;
        h.sailContainer.pop_front();
        vector<pair<int, int>> locations;
        pair<int, int> north(currentLocation.first - 1, currentLocation.second);
        pair<int, int> east(currentLocation.first, currentLocation.second + 1);
        pair<int, int> south(currentLocation.first + 1, currentLocation.second);
        pair<int, int> west(currentLocation.first, currentLocation.second - 1);
        for(size_t i = 0; i < 4; i++) {
            if(h.huntOrder[i] == 'n') {
                locations.push_back(north);
            }
            else if(h.huntOrder[i] == 'e') {
                locations.push_back(east);
            }
            else if(h.huntOrder[i] == 's') {
                locations.push_back(south);
            }
            else {
                locations.push_back(west);
            }
        }
        searchLocation(locations, map, h, bt);
    }
    if(h.successfulHunt == false) {
        failedHunt(h);
    }
}
void handleCline(int argc, char * argv[], Hunt &h) {
    
    // These are used with getopt_long()
    opterr = true; // Give us help with errors
    int choice;
    int option_index = 0;
    option long_options[] = {
        {"help", no_argument, nullptr, 'h'},
        {"captain", required_argument, nullptr, 'c'},
        {"first-mate", required_argument, nullptr, 'f'},
        {"hunt-order", required_argument, nullptr, 'o'},
        {"verbose", no_argument, nullptr, 'v'},
        {"stats", no_argument, nullptr, 's'},
        {"show-path", required_argument, nullptr, 'p'},
        { nullptr, 0, nullptr, '\0' }
    };

    
    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "hc:f:o:vsp:", long_options, &option_index)) != -1) {
        switch (choice) {
            case 'h':
                cout << "Hlep" << '\n';
                exit(0);
                
            case 'v':
                h.showVerbose = true;
                break;
                
            case 's':
                h.showStats = true;
                break;
            
            case 'p':
                h.showPath = optarg;
                if(h.showPath != "M" && h.showPath != "L") {
                    cerr << "Error: invalid showPath" << endl;
                    exit(1);
                }
                break;
                
            case 'c':
                h.captainCon = optarg;
                if(h.captainCon != "queue" && h.captainCon != "stack") {
                    cerr << "Error: invalid captain container" << endl;
                    exit(1);
                }
                break;
            
            case 'f':
                h.fmCon = optarg;
                if(h.fmCon != "queue" && h.fmCon != "stack") {
                    cerr << "Error: invalid first mate container" << endl;
                    exit(1);
                }
                break;
                
            case 'o':
                h.huntOrder = optarg;
                if(h.huntOrder.length() != 4 || (h.huntOrder.find('n') == string::npos || h.huntOrder.find('e') == string::npos || h.huntOrder.find('s') == string::npos || h.huntOrder.find('w') == string::npos)) {
                    cerr << "Error: invalid hunt order" << endl;
                    exit(1);
                }
                break;
                
                
            default:
                cerr << "Error: invalid option" << endl;
                exit(1);
        } // switch
    } // while
    
    
} // getMode()

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    size_t N;
    char mapStyle;
    cin >> mapStyle;
    while(mapStyle == '#') {
        string str;
        getline(cin, str);
        cin >> mapStyle;
    }
    cin >> N;
    
    vector<vector<char>> treasureMap(N, vector<char>(N));
    Hunt honcho;
    Backtracer bt;
    handleCline(argc, argv, honcho);
    readTreasureMap(treasureMap, mapStyle, N, honcho);
    startHunt(honcho, treasureMap, bt);
    return 0;
}

