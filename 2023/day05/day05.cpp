#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>

#include "../utils/common.cpp"

//Notes:
//Order of look-up
// Seed -> Soil -> Fertilizer -> Water ->  Light -> Temperature -> Humidity -> Location
//
// The numbers seem to go up to around 4 billion so we need to use unsigned ints.

///Represents one line in each map block
struct MapLine {
    unsigned int destinationStart;
    unsigned int sourceStart;
    unsigned int range;
};

typedef std::vector<MapLine> MapType;

class MapReader{
    public:
    enum MAP_TYPE {
        INVALID = 0,
        SEED_SOIL,
        SOIL_FERTILIZER,
        FERTILIZER_WATER,
        WATER_LIGHT,
        LIGHT_TEMPERATURE,
        TEMPERATURE_HUMIDITY,
        HUMIDITY_LOCATION
    };
    
    private:
    std::vector<MapLine> seed_soil;
    std::vector<MapLine> soil_fertilizer;
    std::vector<MapLine> fertilizer_water;
    std::vector<MapLine> water_light;
    std::vector<MapLine> light_temperature;
    std::vector<MapLine> temperature_humidity;
    std::vector<MapLine> humidity_location;

    public:
    MAP_TYPE currentMap = MAP_TYPE::INVALID;

    void readMapLine(const std::string& line) {
        using namespace std;
        vector<MapLine>* targetMap = nullptr;

        switch (currentMap) {
            case MAP_TYPE::SEED_SOIL:
                targetMap = &seed_soil;
                break;
            case MAP_TYPE::SOIL_FERTILIZER:
                targetMap = &soil_fertilizer;
                break;
            case MAP_TYPE::FERTILIZER_WATER:
                targetMap = &fertilizer_water;
                break;
            case MAP_TYPE::WATER_LIGHT:
                targetMap = &water_light;
                break;
            case MAP_TYPE::LIGHT_TEMPERATURE:
                targetMap = &light_temperature;
                break;
            case MAP_TYPE::TEMPERATURE_HUMIDITY:
                targetMap = &temperature_humidity;
                break;
            case MAP_TYPE::HUMIDITY_LOCATION:
                targetMap = &humidity_location;
                break;
            default:
                cout << "Error: Invalid map" <<endl;
        } 

        if (targetMap==nullptr) {
            //throw exception
            return;
        }

        stringstream stream(line);
        MapLine newLine = {};
        stream >> newLine.destinationStart >> newLine.sourceStart >> newLine.range;
        targetMap->push_back(newLine);
    }
    
    void setMapType(const std::string& line) {
        const std::string id = line.substr(0,line.find(" "));
        if ( id == "seed-to-soil" ) { currentMap = SEED_SOIL; return;}
        if ( id == "soil-to-fertilizer" ) { currentMap = SOIL_FERTILIZER; return;}
        if ( id == "fertilizer-to-water" ) { currentMap = FERTILIZER_WATER; return;}
        if ( id == "water-to-light" ) { currentMap = WATER_LIGHT; return;}
        if ( id == "light-to-temperature" ) { currentMap = LIGHT_TEMPERATURE; return;}
        if ( id == "temperature-to-humidity" ) { currentMap = TEMPERATURE_HUMIDITY; return;}
        if ( id == "humidity-to-location" ) { currentMap = HUMIDITY_LOCATION; return;}

        std::cout << "Couldn't not set a valid map type" << std::endl;
        currentMap = INVALID;
        return;
    }

    void processLine(std::string line) {
        if ( line.length() == 0 ) {
            currentMap = MapReader::INVALID;
            return;
        }

        if (std::isdigit(line[0])) {
            readMapLine(line);
            return;
        } else {
            setMapType(line);
            return;
        }
    }
    private:
    void printMap(std::vector<MapLine> map) const {
        using namespace std;
        for (MapLine line: map) {
            cout << "Src: " << line.sourceStart << " Dest: " << line.destinationStart << " Range: " << line.range << endl;
        }
    }
    
    public:
    void printMaps() const {
        using namespace std;
        cout << "Seed to Soil" << endl;
        printMap(seed_soil);
        cout << endl;

        cout << "Soil to Fertilizer" << endl;
        printMap(soil_fertilizer);
        cout << endl;

        cout << "Fertilizer to Water" << endl;
        printMap(fertilizer_water);
        cout << endl;

        cout << "Water to Light" << endl;
        printMap(water_light);
        cout << endl;

        cout << "Light to Temperature" << endl;
        printMap(light_temperature);
        cout << endl;

        cout << "Temperature to Humidity" << endl;
        printMap(temperature_humidity);
        cout << endl;

        cout << "Humidity to Location" << endl;
        printMap(humidity_location);
        cout << endl;

    }

    unsigned int mapSeedToLocation(unsigned int seed) const{
        unsigned int answer = seed;
        answer = mapNumber(answer, seed_soil);
        answer = mapNumber(answer, soil_fertilizer);
        answer = mapNumber(answer, fertilizer_water);
        answer = mapNumber(answer, water_light);
        answer = mapNumber(answer, light_temperature);
        answer = mapNumber(answer, temperature_humidity);
        answer = mapNumber(answer, humidity_location);

        return answer;
    }

    unsigned int mapNumber(unsigned int number, const MapType& map) const {
        unsigned  int answer = 0;
        bool found = false;
        for (MapLine line : map) {
            if (number >= line.sourceStart && number < line.sourceStart + line.range) {
                found = true;
                answer = line.destinationStart + (number - line.sourceStart);
                break;
            }
        }

        if (!found) answer = number;

        return answer;
    }
};


std::vector<unsigned> readSeeds(std::string buffer) {
    using namespace std;
    vector<unsigned> answer;
    stringstream stream(buffer);
    stream.ignore(20, ' ');   //Ignore the leading "seeds:" label

    unsigned int value;
    while ( stream >> value ) {
        answer.push_back(value);    
    }

    //Debug line
    //for (unsigned i : answer) { cout << "Seed: " << i << endl;}
    return answer;
}

std::vector<std::pair<unsigned, unsigned>> readSeedsAsRange(std::string buffer) {
    using namespace std;
    vector<pair<unsigned, unsigned>> answer;
    stringstream stream(buffer);
    stream.ignore(20, ' ');   //Ignore the leading "seeds:" label

    unsigned int value, range;
    while ( stream >> value >> range ) {
	pair<unsigned, unsigned> seedAndRange(value, range); 
        answer.push_back(seedAndRange);
    }

    //Debug line
    //for (unsigned i : answer) { cout << "Seed: " << i << endl;}
    return answer;
}


void getMinimumLocationFromRange( unsigned start, unsigned finished, const MapReader& mapReader, std::vector<unsigned>& output); 

int main (int argc, char* argv[]) {
    if (!checkArgsForFileOnly(argc, argv)) return 0;
    using namespace std;
    
    ifstream inputFile;
    inputFile.open(argv[1]);
    if (!inputFile.good()) {
        cout << "Problem reading input file " << argv[1] <<endl;
        return 0;
    }

    string buffer;
    getline(inputFile, buffer);
//    vector<unsigned> seeds= readSeeds(buffer);
    vector<pair<unsigned, unsigned>> seedsRange = readSeedsAsRange(buffer);
    MapReader mapReader;
    

    while (getline(inputFile, buffer)) {
        mapReader.processLine(buffer);
    }
    mapReader.printMaps();	
    inputFile.close();
    
    vector<unsigned> minimums;
    vector<thread> workers;
    for (int i = 0; i < seedsRange.size(); ++i) {
	unsigned int from, to;
	from = seedsRange[i].first;
	to = (seedsRange[i].first + seedsRange[i].second);
	cout << "From: " << from << " To: " << to << endl;
	workers.emplace_back([from, to, &mapReader, &minimums](){getMinimumLocationFromRange(from, to, mapReader, minimums);});
    }

    for (auto& currentThread : workers) {
	currentThread.join();
    }

    unsigned int minimum = minimums[0];
    for ( unsigned int u : minimums) {
	if ( u < minimum ) {
		minimum = u;
	}
    }
    cout << "Closest Location: " << minimum << endl;
    return 0;
}

void getMinimumLocationFromRange( unsigned start, unsigned finished, const MapReader& mapReader, std::vector<unsigned>& output) {
    using namespace std;
    unsigned minimum = mapReader.mapSeedToLocation(start);
    for (unsigned rangeIndex = start; rangeIndex < finished; ++rangeIndex) {
        unsigned int location = mapReader.mapSeedToLocation(rangeIndex);
        minimum = location < minimum ? location : minimum;
    }
    output.push_back(minimum);
}
