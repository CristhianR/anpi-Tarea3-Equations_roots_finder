/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, TEC, Costa Rica
 *
 * This file is part of the CE3102 Numerical Analysis lecture at TEC
 *
 * @Author:
 * @Date  : 24.02.2018
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "PlotPy.hpp"
//#include "PlotPy.tpp"
using namespace std;


int main() {

  // Put your main code in here

    std::string legend = "ok";
    std::string color = "r";
    std::string title = "Ejemplo";
    std::string labelx = "EjeX";
    std::string labely = "EjeY";
    vector<double>EjeX(5);
    vector<double>EjeY(5);

    anpi::Plot2d<double> myPlot;
    myPlot.initialize(1);
    myPlot.setTitle(title);
    myPlot.setXLabel(labelx);
    myPlot.setYLabel(labely);
    myPlot.setGridSize(10);
    myPlot.setXRange(0,10);
    myPlot.setYRange(0,10);
    myPlot.plot(EjeX,EjeY,legend,color);
    myPlot.show();


    std::cout << "Nothing done yet!" << std::endl; // REMOVE-ME!

  return EXIT_FAILURE;
}
