#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

class outputmaker
{
private:
    std::string outfile;
    std::ofstream aout;
public:
    int graphsize;
    int k1;
    int k2;
    outputmaker(/* args */);
    ~outputmaker();
};

outputmaker::outputmaker(/* args */)
{
}

outputmaker::~outputmaker()
{
}
