#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#ifndef TXTWRITER_H
#define TXTWRITER_H

using namespace std;

class txtWriter
{

public:
    ofstream TXTFile;

    TXTWriter() {
    }

    void createTXTFile() {
        TXTFile.open("ourCurve.txt");
    }

    void addPoint(float x, float y, float z){
        TXTFile << "v " << x << " " << z << " " << y << endl;
    }

    void closeTXTFile() {
        TXTFile.close();
    }
};

#endif