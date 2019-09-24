// Project Identifier: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD
//  main.cpp
//  Project1
//
//  Created by Andrew Myers on 9/17/19.
//  Copyright © 2019 Andrew Myers. All rights reserved.
//
#include <unordered_set>
#include <getopt.h>
#include <deque>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "xcode_redirect.hpp"
#include <utility>



using namespace std;
struct Tile {
    pair<int, int> coordinate;
    char direction;
    bool isDiscovered;
};
struct Hunt {
    deque<Tile> sailContainer;
    deque<Tile> searchContainer;
    pair<int, int> startingLocation;
    string showPath;
    string captainCon = "stack";
    string fmCon = "queue";
    string huntOrder = "nesw";
    int waterLocations = 0;
    int landLocations = 0;
    int timesAshore = 0;
    bool successfulHunt = false;
    bool showStats = false;
    bool showVerbose = false;
    
};
struct Backtracer {
    vector<Tile> coordinates;
    deque<pair<int, int>> sailBack;
    deque<pair<int, int>> searchBack;
    deque<char> lastCharacter;
    deque<char> lastDirection;
};
void printMap(Backtracer &bt,vector<vector<pair<char, char>>> &map, string mapType) {
    if(mapType == "M") {
        for(size_t i = 0; i < map.size(); i++) {
            for(size_t j = 0; j < map.size(); j++) {
                cout << map[i][j].first;
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

int runBacktracer(Backtracer &bt, Hunt &h, const pair<int, int> &p, vector<vector<pair<char, char>>> &map) {
    int pathLength = 0;
    pair<int, int> starter = p;
    if(h.showPath == "M") {
        map[size_t(p.first)][size_t(p.second)].first = 'X';
    }
    size_t i = bt.coordinates.size() - 1;
    while(starter != h.startingLocation) {
        while(bt.coordinates[i].coordinate != starter) {
            i--;
        }
        const char &c1 = bt.coordinates[i].direction;
        if(c1 == 'n' || c1 == 'N') {
            if(h.showPath == "M") {
                if(i == bt.coordinates.size() - 1) {
                    bt.lastCharacter.push_front('X');
                }
                else {
                    if(bt.lastCharacter[0] == 'X') {
                        if(bt.lastDirection[0] == 'e' || bt.lastDirection[0] == 'w') {
                            map[size_t(starter.first)][size_t(starter.second)].first = '+';
                            bt.lastCharacter.push_front('+');
                        }
                        else {
                            map[size_t(starter.first)][size_t(starter.second)].first = '|';
                            bt.lastCharacter.push_front('|');
                        }
                    }
                    else if(bt.lastCharacter[0] == '-') {
                        map[size_t(starter.first)][size_t(starter.second)].first = '+';
                        bt.lastCharacter.push_front('+');
                    }
                    else if(bt.lastCharacter[0] == '+') {
                        if(bt.lastDirection[0] == 'e' || bt.lastDirection[0] == 'w') {
                            map[size_t(starter.first)][size_t(starter.second)].first = '+';
                            bt.lastCharacter.push_front('+');
                        }
                        else {
                            map[size_t(starter.first)][size_t(starter.second)].first = '|';
                            bt.lastCharacter.push_front('|');
                        }
                    }
                    else {
                       map[size_t(starter.first)][size_t(starter.second)].first = '|';
                        bt.lastCharacter.push_front('|');
                    }
                }
            }
            else if(h.showPath == "L") {
                if(map[size_t(starter.first)][size_t(starter.second)].first == '$') {
                    
                }
                else if(map[size_t(starter.first)][size_t(starter.second)].first == 'o') {
                    bt.searchBack.push_front(starter);
                }
                else {
                    bt.sailBack.push_front(starter);
                }
            }
            pair<int, int> temp(starter.first + 1, starter.second);
            starter = temp;
            pathLength++;
            i--;
            bt.lastDirection.push_front('n');
        }
        else if(c1 == 'e' || c1 == 'E') {
            if(h.showPath == "M") {
                if(i == bt.coordinates.size() - 1) {
                    bt.lastCharacter.push_front('X');
                }
                else {
                    if(bt.lastCharacter[0] == 'X') {
                        if(bt.lastDirection[0] == 'n' || bt.lastDirection[0] == 's') {
                            map[size_t(starter.first)][size_t(starter.second)].first = '+';
                            bt.lastCharacter.push_front('+');
                        }
                        else {
                            map[size_t(starter.first)][size_t(starter.second)].first = '-';
                            bt.lastCharacter.push_front('-');
                        }
                    }
                    else if(bt.lastCharacter[0] == '|') {
                        map[size_t(starter.first)][size_t(starter.second)].first = '+';
                        bt.lastCharacter.push_front('+');
                    }
                    else if(bt.lastCharacter[0] == '+') {
                        if(bt.lastDirection[0] == 'n' || bt.lastDirection[0] == 's') {
                            map[size_t(starter.first)][size_t(starter.second)].first = '+';
                            bt.lastCharacter.push_front('+');
                        }
                        else {
                            map[size_t(starter.first)][size_t(starter.second)].first = '-';
                            bt.lastCharacter.push_front('-');
                        }
                    }
                    else {
                        map[size_t(starter.first)][size_t(starter.second)].first = '-';
                        bt.lastCharacter.push_front('-');
                    }
                }
            }
            else if(h.showPath == "L") {
                if(map[size_t(starter.first)][size_t(starter.second)].first == '$') {
                    
                }
                else if(map[size_t(starter.first)][size_t(starter.second)].first == 'o') {
                    bt.searchBack.push_front(starter);
                }
                else {
                    bt.sailBack.push_front(starter);
                }
            }
            pair<int, int> temp(starter.first, starter.second - 1);
            starter = temp;
            pathLength++;
            i--;
            bt.lastDirection.push_front('e');
        }
        else if(c1 == 's' || c1 == 'S') {
            if(h.showPath == "M") {
                if(i == bt.coordinates.size() - 1) {
                    bt.lastCharacter.push_front('X');
                }
                else {
                    if(bt.lastCharacter[0] == 'X') {
                        if(bt.lastDirection[0] == 'e' || bt.lastDirection[0] == 'w') {
                            map[size_t(starter.first)][size_t(starter.second)].first = '+';
                            bt.lastCharacter.push_front('+');
                        }
                        else {
                            map[size_t(starter.first)][size_t(starter.second)].first = '|';
                            bt.lastCharacter.push_front('|');
                        }
                    }
                    else if(bt.lastCharacter[0] == '-') {
                        map[size_t(starter.first)][size_t(starter.second)].first = '+';
                        bt.lastCharacter.push_front('+');
                    }
                    else if(bt.lastCharacter[0] == '+') {
                        if(bt.lastDirection[0] == 'e' || bt.lastDirection[0] == 'w') {
                            map[size_t(starter.first)][size_t(starter.second)].first = '+';
                            bt.lastCharacter.push_front('+');
                        }
                        else {
                            map[size_t(starter.first)][size_t(starter.second)].first = '|';
                            bt.lastCharacter.push_front('|');
                        }
                    }
                    else {
                        map[size_t(starter.first)][size_t(starter.second)].first = '|';
                        bt.lastCharacter.push_front('|');
                    }
                }
            }
            else if(h.showPath == "L") {
                if(map[size_t(starter.first)][size_t(starter.second)].first == '$') {
                    
                }
                else if(map[size_t(starter.first)][size_t(starter.second)].first == 'o') {
                    bt.searchBack.push_front(starter);
                }
                else {
                    bt.sailBack.push_front(starter);
                }
            }
            pair<int, int> temp(starter.first - 1, starter.second);
            starter = temp;
            pathLength++;
            i--;
            bt.lastDirection.push_front('s');
        }
        else {
            if(h.showPath == "M") {
                if(i == bt.coordinates.size() - 1) {
                    bt.lastCharacter.push_front('X');
                }
                else {
                    if(bt.lastCharacter[0] == 'X') {
                        if(bt.lastDirection[0] == 'n' || bt.lastDirection[0] == 's') {
                            map[size_t(starter.first)][size_t(starter.second)].first = '+';
                            bt.lastCharacter.push_front('+');
                        }
                        else {
                            map[size_t(starter.first)][size_t(starter.second)].first = '-';
                            bt.lastCharacter.push_front('-');
                        }
                    }
                    else if(bt.lastCharacter[0] == '|') {
                        map[size_t(starter.first)][size_t(starter.second)].first = '+';
                        bt.lastCharacter.push_front('+');
                    }
                    else if(bt.lastCharacter[0] == '+') {
                        if(bt.lastDirection[0] == 'n' || bt.lastDirection[0] == 's') {
                            map[size_t(starter.first)][size_t(starter.second)].first = '+';
                            bt.lastCharacter.push_front('+');
                        }
                        else {
                            map[size_t(starter.first)][size_t(starter.second)].first = '-';
                            bt.lastCharacter.push_front('-');
                        }
                    }
                    else {
                        map[size_t(starter.first)][size_t(starter.second)].first = '-';
                        bt.lastCharacter.push_front('-');
                    }
                }
            }
            else if(h.showPath == "L") {
                if(map[size_t(starter.first)][size_t(starter.second)].first == '$') {

                }
                else if(map[size_t(starter.first)][size_t(starter.second)].first == 'o') {
                    bt.searchBack.push_front(starter);
                }
                else {
                    bt.sailBack.push_front(starter);
                }
            }
            pair<int, int> temp(starter.first, starter.second + 1);
            starter = temp;
            pathLength++;
            i--;
            bt.lastDirection.push_front('w');
        }
    }
    if(h.showPath == "L") {
        bt.searchBack.push_back(p);
        bt.sailBack.push_front(h.startingLocation);
    }
    return pathLength;
}

void readTreasureMap(vector<vector<pair<char, char>>> &map, char &mapStyle, size_t N, Hunt &h) {
    char mapSpace;
    if(mapStyle == 'M') {
        for(size_t i = 0; i < N; i++) {
            for(size_t j = 0; j < N; j++) {
                cin >> mapSpace;
                if(mapSpace == '@') {
                    pair<int, int> p(i, j);
                    Tile t;
                    t.coordinate = p;
                    t.direction = 'n';
                    if(h.captainCon == "queue") {
                        h.sailContainer.push_back(t);
                    }
                    else {
                        h.sailContainer.push_front(t);
                    }
                }
                map[i][j].first = mapSpace;
                map[i][j].second = 'f';
            }
        }
    }
    else if(mapStyle == 'L') {
        size_t rowNum;
        size_t colNum;
        while(cin >> rowNum) {
            cin >> colNum;
            cin >> mapSpace;
            if(mapSpace == '@') {
                pair<int, int> p(rowNum, colNum);
                Tile t;
                t.coordinate = p;
                t.direction = 'n';
                if(h.captainCon == "queue") {
                    h.sailContainer.push_back(t);
                }
                else {
                    h.sailContainer.push_front(t);
                }
            }
            map[rowNum][colNum].first = mapSpace;
            map[rowNum][colNum].second = 'f';
        }
        for(size_t i = 0; i < N; i++) {
            for(size_t j = 0; j < N; j++) {
                if(map[i][j].first == '\0') {
                    map[i][j].first = '.';
                    map[i][j].second = 'f';
                }
            }
        }
    }
}
void failedHunt(Hunt &h) {
    if(h.showVerbose == true) {
        cout << "Treasure hunt failed" << '\n';
    }
    if(h.showStats == true) {
        cout << "--- STATS ---\n" << "Starting location: " << h.startingLocation.first << ',' << h.startingLocation.second << '\n' << "Water locations investigated: " << h.waterLocations << '\n' << "Land locations investigated: " << h.landLocations << '\n' << "Went ashore: " << h.timesAshore << '\n' << "--- STATS ---\n";
    }
    cout << "No treasure found after investigating " <<
    h.waterLocations + h.landLocations << " locations.\n";
}
void endHunt(const pair<int, int> &p, Hunt &h, Backtracer &bt, vector<vector<pair<char, char>>> &map) {
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

void searchFMLocation(const vector<pair<int, int>> &v, vector<vector<pair<char, char>>> &map, Hunt &h, Backtracer &bt) {
    string huntO = h.huntOrder;
    for(size_t i = 0; i < 4; i++) {
        const pair<int, int> &p = v[i];
        const static int size = int(map[0].size());
        const char &mapChar = map[size_t(p.first)][size_t(p.second)].second;
        if((p.first > -1 && p.first < size && (p.second > -1
                                                              && p.second < size))) {
            if(map[size_t(p.first)][size_t(p.second)].first == 'o') {
                if(mapChar == 'f') {
                    map[size_t(p.first)][size_t(p.second)].second = 't';
                    Tile t;
                    t.coordinate = p;
                    t.direction = huntO[i];
                    if(h.fmCon == "stack") {
                       h.searchContainer.push_front(t);
                    }
                    else {
                        h.searchContainer.push_back(t);
                    }
                }
            }
            else if(map[size_t(p.first)][size_t(p.second)].first == '$') {
                Tile t;
                t.coordinate = p;
                t.direction = huntO[i];
                if(h.showVerbose == true) {
                    cout << "party found treasure at " << p.first << ',' <<
                    p.second << ".\n";
                }
                h.landLocations++;
                if(h.fmCon == "stack") {
                    h.searchContainer.push_front(t);
                }
                else {
                    h.searchContainer.push_back(t);
                }
                bt.coordinates.push_back(t);
                endHunt(p, h, bt, map);
                return;
            }
            
        }
    }
}
void firstMateTakeOver(Hunt &h, vector<vector<pair<char, char>>> &map, Backtracer &bt) {
    if(h.showVerbose == true) {
        cout << "Went ashore at: " << h.searchContainer.front().coordinate.first << ','
        << h.searchContainer.front().coordinate.second
        << '\n';
        cout << "Searching island... ";

    }
    h.timesAshore++;
    while(h.searchContainer.empty() == false) {
        pair<int, int> currentLocation = h.searchContainer.front().coordinate;
        bt.coordinates.push_back(h.searchContainer.front());
        h.landLocations++;
        h.searchContainer.pop_front();
        vector<pair<int, int>> locations;
        pair<int, int> north(currentLocation.first - 1, currentLocation.second);
        pair<int, int> east(currentLocation.first, currentLocation.second + 1);
        pair<int, int> south(currentLocation.first + 1, currentLocation.second);
        pair<int, int> west(currentLocation.first, currentLocation.second - 1);
        for(size_t i = 0; i < 4; i++) {
            if(h.huntOrder[i] == 'n' || h.huntOrder[i] == 'N') {
                locations.push_back(north);
            }
            else if(h.huntOrder[i] == 'e' || h.huntOrder[i] == 'E') {
               locations.push_back(east);
            }
            else if(h.huntOrder[i] == 's' || h.huntOrder[i] == 'S') {
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

void searchLocation(const vector<pair<int, int>> &v, vector<vector<pair<char, char>>> &map, Hunt &h, Backtracer &bt) {
    for(size_t i = 0; i < 4; i++) {
        if(h.successfulHunt == true) {
            return;
        }
        string huntO = h.huntOrder;
        const pair<int, int> & p = v[i];
        const static int size = int(map[0].size());
        char mapChar = 't';
        if(size_t(p.first) < map.size() && size_t(p.second) < map.size()) {
            mapChar = map[size_t(p.first)][size_t(p.second)].second;
        }
        if((p.first > -1 && p.first < size && (p.second > -1
        && p.second < size))) {
            if(map[size_t(p.first)][size_t(p.second)].first == '.') {
                if(mapChar == 'f') {
                    map[size_t(p.first)][size_t(p.second)].second = 't';
                    Tile t;
                    t.coordinate = p;
                    t.direction = huntO[i];
                    if(h.captainCon == "queue") {
                        h.sailContainer.push_back(t);
                    }
                    else {
                        h.sailContainer.push_front(t);
                    }
                }
            }
            else if(map[size_t(p.first)][size_t(p.second)].first == 'o') {
                if(mapChar == 'f') {
                    map[size_t(p.first)][size_t(p.second)].second = 't';
                    Tile t;
                    t.coordinate = p;
                    t.direction = huntO[i];
                    if(h.fmCon == "stack") {
                        h.searchContainer.push_front(t);
                    }
                    else {
                        h.searchContainer.push_back(t);
                    }
                    firstMateTakeOver(h, map, bt);
                }
            }
            else if(map[size_t(p.first)][size_t(p.second)].first == '$') {
                if(mapChar == 'f') {
                    map[size_t(p.first)][size_t(p.second)].second = 't';
                    Tile t;
                    t.coordinate = p;
                    t.direction = huntO[i];
                    if(h.showVerbose == true) {
                        cout << "Went ashore at: " << p.first << ',' <<
                        p.second << "\n" << "Searching island... " << "party found treasure at " << p.first << ',' <<
                        p.second << ".\n";
                    }
                    h.landLocations++;
                    h.timesAshore++;
                    if(h.fmCon == "stack") {
                        h.searchContainer.push_front(t);
                    }
                    else {
                        h.searchContainer.push_back(t);
                    }
                    bt.coordinates.push_back(t);
                    endHunt(p, h, bt, map);
                    return;
                }
            }
        }
    }
}
void startHunt(Hunt &h, vector<vector<pair<char, char>>> &map, Backtracer &bt) {
    pair<int, int> p(h.sailContainer.front().coordinate.first, h.sailContainer.front().coordinate.second);
    h.startingLocation = p;
    if(h.showVerbose == true) {
        cout << "Treasure hunt started at: " <<
        p.first << ',' << p.second
        << '\n';
    }
    while(h.sailContainer.empty() == false) {
        pair<int, int> currentLocation = h.sailContainer.front().coordinate;
        bt.coordinates.push_back(h.sailContainer.front());
        h.waterLocations++;
        h.sailContainer.pop_front();
        vector<pair<int, int>> locations;
        pair<int, int> north(currentLocation.first - 1, currentLocation.second);
        pair<int, int> east(currentLocation.first, currentLocation.second + 1);
        pair<int, int> south(currentLocation.first + 1, currentLocation.second);
        pair<int, int> west(currentLocation.first, currentLocation.second - 1);
        for(size_t i = 0; i < 4; i++) {
            if(h.huntOrder[i] == 'n' || h.huntOrder[i] == 'N' ) {
                locations.push_back(north);
            }
            else if(h.huntOrder[i] == 'e' || h.huntOrder[i] == 'E' ) {
                locations.push_back(east);
            }
            else if(h.huntOrder[i] == 's' || h.huntOrder[i] == 'S' ) {
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
                cout << "Try running the executable with some command line options (for instance: -vspL). Also, make sure you use input redirection to get the output for the right map." << '\n';
                exit(1);
                
            case 'v':
                h.showVerbose = true;
                break;
                
            case 's':
                h.showStats = true;
                break;
            
            case 'p':
                if(h.showPath.length() > 0) {
                    cerr << "Error: invalid showPath" << endl;
                    exit(1);
                }
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
                if(h.huntOrder.length() != 4 || ((h.huntOrder.find('n') == string::npos && h.huntOrder.find('N') == string::npos) || (h.huntOrder.find('e') == string::npos && h.huntOrder.find('E') == string::npos) || (h.huntOrder.find('s') == string::npos && h.huntOrder.find('S') == string::npos) || (h.huntOrder.find('w') == string::npos && h.huntOrder.find('W') == string::npos))) {
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
    
    vector<vector<pair<char, char>>> treasureMap(N, vector<pair<char, char>>(N));
    Hunt honcho;
    Backtracer bt;
    handleCline(argc, argv, honcho);
    readTreasureMap(treasureMap, mapStyle, N, honcho);
    startHunt(honcho, treasureMap, bt);
    return 0;
}

