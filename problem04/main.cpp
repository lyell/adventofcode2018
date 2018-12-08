#include <boost/regex.hpp>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <limits>

struct Entry {
    int yyyymmdd;
    int hour;
    int minute;
    std::string log;
};

std::ostream& operator<<(std::ostream& os, Entry const& e) {
    os << "[" << e.yyyymmdd << " " << e.hour << ":" << e.minute << " " << e.log << " ]"; 
    return os;
}

bool entryComp(Entry const& lhs, Entry const& rhs) {
    if (lhs.yyyymmdd < rhs.yyyymmdd) {
        return true;
    } else if (lhs.yyyymmdd > rhs.yyyymmdd) { 
        return false;
    } else if (lhs.yyyymmdd == rhs.yyyymmdd) { 
        if (lhs.hour < rhs.hour) {
            return true;
        } else if (lhs.hour > rhs.hour) {
            return false;
        } else if (lhs.hour == rhs.hour) {
            if (lhs.minute < rhs.minute) {
                return true;
            } else {
                return false;
            }
        }
    }

    return false;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "missing input file in arguments!" << std::endl;
        return 1;
    }

    boost::regex re("\\[(\\d+)-(\\d+)-(\\d+) (\\d+):(\\d+)\\] (.+)");

    typedef std::vector<Entry> Entries;
    Entries entries;

    std::ifstream inputFile(argv[1]);
    std::string line;
    while (!inputFile.eof()) {
        std::getline(inputFile, line);

        Entry e;
        boost::smatch matches;
        if (boost::regex_match(line, matches, re) && matches.size() == 7) {
            e.yyyymmdd = (atoi(matches[1].str().c_str()) * 10000) + (atoi(matches[2].str().c_str()) * 100) + atoi(matches[3].str().c_str());
            e.hour = atoi(matches[4].str().c_str());
            e.minute = atoi(matches[5].str().c_str());
            e.log = matches[6];

            //std::cout << "entry: " << e << std::endl;

            entries.push_back(e);
        }
    }

    // Sort the log by time
    std::sort(entries.begin(), entries.end(), entryComp);

    // Create a container that holds the guard id and a vector of sleep minutes
    typedef std::unordered_map<int, std::pair<int, std::vector<int> > > GuardMap;
    GuardMap guardMap;
    
    boost::regex guardRex("Guard #(\\d+) begins shift");

    GuardMap::iterator guard = guardMap.end();
    int startMinute = 0;

    int currentMax = 0;
    int currentMaxGuardId = 0;
    for (Entries::const_iterator it = entries.begin(); it != entries.end(); ++it) {
        if (it->log.find("Guard") != -1) {
            boost::smatch matches;
            if (boost::regex_match(it->log, matches, guardRex) && matches.size() == 2) {
                int guardId = atoi(matches[1].str().c_str());
                guard = guardMap.find(guardId);
                if (guard == guardMap.end()) {
                    guard = guardMap.insert(std::make_pair(guardId, std::make_pair(0, std::vector<int>(60, 0)))).first;
                }
            }
        } else if (it->log.find("falls asleep") != -1) {
            startMinute = it->minute;
        } else if (it->log.find("wakes up") != -1) {
            for (int i = startMinute; i < it->minute; ++i) {
                guard->second.first += 1;
                guard->second.second[i] += 1;
            }

            if (guard->second.first > currentMax) {
                currentMaxGuardId = guard->first;
                currentMax = guard->second.first;
            }
        }
    }

    std::cout << "guardId: " << currentMaxGuardId << " time: " << currentMax << std::endl;

    GuardMap::iterator it = guardMap.find(currentMaxGuardId);
    if (it != guardMap.end()) {
        int maxMinute = -1;
        int maxMinutePos = -1;
        std::vector<int>& v = it->second.second;
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] > maxMinute) {
                maxMinute = v[i];
                maxMinutePos = i;
            }
        }

        std::cout << "maxMinutePos: " << maxMinutePos << std::endl; 

        std::cout << "part 1 result: " << (it->first * maxMinutePos) << std::endl;
    }

    int maxMinute = -1;
    int maxMinutePos = -1;
    int maxGuardId = -1;
    for (it = guardMap.begin(); it != guardMap.end(); ++it) {
        std::vector<int>& v = it->second.second;
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] > maxMinute) {
                maxMinute = v[i];
                maxMinutePos = i;
                maxGuardId = it->first;
            }
        }
    }

    std::cout << "maxGuardId: " << maxGuardId << " maxMinutePos: " << maxMinutePos << std::endl;

    std::cout << "part 2 result: " << (maxGuardId * maxMinutePos) << std::endl;
    return 0;
}
