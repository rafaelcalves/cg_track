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

class TXTWriter
{

public:
    ofstream myfile;

    TXTWriter() {
    }

    void createTXTFile() {
        myfile.open("../../obj_load/resources/curve/ourCurve.txt");
    }

    void addPoint(float x, float y, float z){
        myfile << "v " << x << " " << z << " " << y << endl;
    }

    void closeTXTFile() {
        myfile.close();
    }
};

#endif