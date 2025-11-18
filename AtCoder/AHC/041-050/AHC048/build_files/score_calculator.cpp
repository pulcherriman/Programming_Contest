#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

struct Color {
    double c, m, y;
    Color() : c(0), m(0), y(0) {}
    Color(double c, double m, double y) : c(c), m(m), y(y) {}
    Color operator+(const Color& other) const {
        return Color(c + other.c, m + other.m, y + other.y);
    }
    Color operator*(double scale) const {
        return Color(c * scale, m * scale, y * scale);
    }
};

struct Well {
    double volume;
    Color color;
    Well() : volume(0), color() {}
};

class ScoreCalculator {
private:
    int N, K, H, T, D;
    vector<Color> tubeColors;
    vector<Color> targetColors;
    vector<Color> createdColors;
    vector<vector<Well>> wells;
    vector<vector<bool>> verticalWalls, horizontalWalls;
    int operationCount;
    int colorsCreated;

public:
    ScoreCalculator() {
        operationCount = 0;
        colorsCreated = 0;
    }

    void readInput(const string& filename) {
        ifstream file(filename);
        file >> N >> K >> H >> T >> D;
        
        tubeColors.resize(K);
        for (int i = 0; i < K; i++) {
            file >> tubeColors[i].c >> tubeColors[i].m >> tubeColors[i].y;
        }
        
        targetColors.resize(H);
        for (int i = 0; i < H; i++) {
            file >> targetColors[i].c >> targetColors[i].m >> targetColors[i].y;
        }
        
        createdColors.resize(H);
    }

    void initializePalette(const vector<string>& paletteLines) {
        wells.assign(N, vector<Well>(N));
        verticalWalls.assign(N, vector<bool>(N-1));
        horizontalWalls.assign(N-1, vector<bool>(N));
        
        // Parse vertical walls
        for (int i = 0; i < N; i++) {
            istringstream iss(paletteLines[i]);
            for (int j = 0; j < N-1; j++) {
                int wall;
                iss >> wall;
                verticalWalls[i][j] = (wall == 1);
            }
        }
        
        // Parse horizontal walls
        for (int i = 0; i < N-1; i++) {
            istringstream iss(paletteLines[N + i]);
            for (int j = 0; j < N; j++) {
                int wall;
                iss >> wall;
                horizontalWalls[i][j] = (wall == 1);
            }
        }
    }

    Well& getWell(int i, int j) {
        return wells[i][j];
    }

    void processOperation(const string& operation) {
        istringstream iss(operation);
        int opType;
        iss >> opType;
        
        switch (opType) {
            case 1: {
                int i, j, k;
                iss >> i >> j >> k;
                addTubeToWell(i, j, k);
                operationCount++;
                break;
            }
            case 2: {
                int i, j;
                iss >> i >> j;
                takeFromWell(i, j);
                break;
            }
            case 3: {
                int i, j;
                iss >> i >> j;
                discardFromWell(i, j);
                break;
            }
            case 4: {
                int i1, j1, i2, j2;
                iss >> i1 >> j1 >> i2 >> j2;
                toggleWall(i1, j1, i2, j2);
                break;
            }
        }
    }

private:
    void addTubeToWell(int i, int j, int k) {
        Well& well = getWell(i, j);
        int capacity = getWellCapacity(i, j);
        
        if (well.volume + 1.0 <= capacity + 1e-9) {
            // Mix colors
            Color newColor = (well.color * well.volume + tubeColors[k] * 1.0) * (1.0 / (well.volume + 1.0));
            well.color = newColor;
            well.volume += 1.0;
        }
        // Excess is discarded
    }

    void takeFromWell(int i, int j) {
        Well& well = getWell(i, j);
        if (well.volume >= 1.0 - 1e-6) {
            if (colorsCreated < H) {
                createdColors[colorsCreated] = well.color;
                colorsCreated++;
            }
            
            if (well.volume >= 1.0) {
                well.volume -= 1.0;
            } else {
                well.volume = 0.0;
                well.color = Color();
            }
        }
    }

    void discardFromWell(int i, int j) {
        Well& well = getWell(i, j);
        if (well.volume >= 1.0 - 1e-6) {
            if (well.volume >= 1.0) {
                well.volume -= 1.0;
            } else {
                well.volume = 0.0;
                well.color = Color();
            }
        }
    }

    void toggleWall(int i1, int j1, int i2, int j2) {
        // Wall manipulation (simplified for scoring)
        // This would need full implementation for accurate simulation
    }

    int getWellCapacity(int i, int j) {
        // For simplicity, assume each cell has capacity 1
        // In full implementation, this would calculate connected component size
        return 50; // Large well capacity as used in solutions
    }

public:
    double calculateScore() {
        double colorError = 0.0;
        
        for (int i = 0; i < H && i < colorsCreated; i++) {
            double dc = targetColors[i].c - createdColors[i].c;
            double dm = targetColors[i].m - createdColors[i].m;
            double dy = targetColors[i].y - createdColors[i].y;
            colorError += dc*dc + dm*dm + dy*dy;
        }
        
        // Add penalty for missing colors
        for (int i = colorsCreated; i < H; i++) {
            colorError += 3.0; // Maximum possible error per color
        }
        
        double absoluteScore = 1.0 + D * (operationCount - H) + round(10000.0 * colorError);
        return absoluteScore;
    }

    void outputDebugInfo(const string& filename) {
        ofstream debug(filename);
        debug << fixed << setprecision(6);
        
        debug << "=== AHC048 Score Calculator Debug Output ===" << endl;
        debug << "Input Parameters:" << endl;
        debug << "N=" << N << ", K=" << K << ", H=" << H << ", T=" << T << ", D=" << D << endl;
        debug << endl;
        
        debug << "Tube Colors:" << endl;
        for (int i = 0; i < K; i++) {
            debug << "Tube " << i << ": (" << tubeColors[i].c << ", " << tubeColors[i].m << ", " << tubeColors[i].y << ")" << endl;
        }
        debug << endl;
        
        debug << "Target vs Created Colors (first 10):" << endl;
        for (int i = 0; i < min(10, H); i++) {
            debug << "Color " << i << ":" << endl;
            debug << "  Target:  (" << targetColors[i].c << ", " << targetColors[i].m << ", " << targetColors[i].y << ")" << endl;
            if (i < colorsCreated) {
                debug << "  Created: (" << createdColors[i].c << ", " << createdColors[i].m << ", " << createdColors[i].y << ")" << endl;
                double dc = targetColors[i].c - createdColors[i].c;
                double dm = targetColors[i].m - createdColors[i].m;
                double dy = targetColors[i].y - createdColors[i].y;
                double error = dc*dc + dm*dm + dy*dy;
                debug << "  Error:   " << error << endl;
            } else {
                debug << "  Created: NOT CREATED (missing)" << endl;
                debug << "  Error:   3.0 (penalty)" << endl;
            }
            debug << endl;
        }
        
        debug << "Statistics:" << endl;
        debug << "Total operations (type 1): " << operationCount << endl;
        debug << "Colors created: " << colorsCreated << " / " << H << endl;
        debug << "Missing colors: " << max(0, H - colorsCreated) << endl;
        
        // Calculate color error
        double colorError = 0.0;
        for (int i = 0; i < H && i < colorsCreated; i++) {
            double dc = targetColors[i].c - createdColors[i].c;
            double dm = targetColors[i].m - createdColors[i].m;
            double dy = targetColors[i].y - createdColors[i].y;
            colorError += dc*dc + dm*dm + dy*dy;
        }
        for (int i = colorsCreated; i < H; i++) {
            colorError += 3.0;
        }
        
        debug << endl;
        debug << "Score Calculation:" << endl;
        debug << "Color Error (E): " << colorError << endl;
        debug << "Operation Cost: " << D << " * (" << operationCount << " - " << H << ") = " << D * (operationCount - H) << endl;
        debug << "Color Error Term: round(10^4 * " << colorError << ") = " << round(10000.0 * colorError) << endl;
        
        double absoluteScore = calculateScore();
        debug << "Absolute Score: 1 + " << D * (operationCount - H) << " + " << round(10000.0 * colorError) << " = " << absoluteScore << endl;
        
        debug.close();
    }

    void processOutput(const string& filename) {
        ifstream file(filename);
        string line;
        vector<string> paletteLines;
        
        // Read palette configuration (2*N-1 lines)
        for (int i = 0; i < 2*N-1; i++) {
            getline(file, line);
            paletteLines.push_back(line);
        }
        initializePalette(paletteLines);
        
        // Process operations
        while (getline(file, line)) {
            if (!line.empty()) {
                processOperation(line);
            }
        }
    }
};

int main(int argc, char* argv[]) {
    ScoreCalculator calculator;
    
    string inputFile = "in.txt";
    string outputFile = "out.txt";
    string debugFile = "debug.txt";
    
    if (argc >= 2) inputFile = argv[1];
    if (argc >= 3) outputFile = argv[2];
    if (argc >= 4) debugFile = argv[3];
    
    // Read input
    calculator.readInput(inputFile);
    
    // Process output
    calculator.processOutput(outputFile);
    
    // Calculate and output score
    double score = calculator.calculateScore();
    cout << "Absolute Score: " << score << endl;
    
    // Output debug information
    calculator.outputDebugInfo(debugFile);
    cout << "Debug information written to " << debugFile << endl;
    
    return 0;
}
