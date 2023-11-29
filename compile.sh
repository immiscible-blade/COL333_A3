#!/bin/bash
g++ -Wall src/inputmaker3.cpp src/orgstosat.cpp -o bin/orgstosat
g++ -Wall src/satorgs.cpp -o bin/satorgs
g++ -Wall src/satorgs_p2.cpp -o bin/satorgs_p2
g++ -Wall src/orgtosat_p2.cpp -o bin/orgtosat_p2