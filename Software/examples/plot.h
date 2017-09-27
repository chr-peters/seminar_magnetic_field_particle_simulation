#include<vector>
#include <iostream>
#include "vector3d.h"
#include <string>
#include <fstream>

void plot(std::string title, const std::vector<Vector3D> &points){
  // first write the data points to a temporary file so gnuplot will be able to open it
  std::ofstream outFile;
  outFile.open("points.txt");
  if (outFile.is_open()) {
    for (auto curPoint : points) {
      outFile << curPoint << std::endl;
    }
  } else {
    std::cerr << "Could not write points to temporary file!" << std::endl;
    return;
  }
  outFile.close();

  // now create the instruction file for gnuplot
  std::ofstream gnuplotFile;
  gnuplotFile.open("plot.plt");
  if (gnuplotFile.is_open()) {
    std::string gnuplotScript = "set title '";
    gnuplotScript += title;
    gnuplotScript += "\n";
    gnuplotScript += "set xlabel 'x' \n\
                      set ylabel 'y' \n\
                      set zlabel 'z' \n\
                      splot 'points.txt' with linespoints";
    gnuplotFile << gnuplotScript << std::endl;
  } else {
    std::cerr << "Could not write points to temporary file!" << std::endl;
    return;
  }
  gnuplotFile.close();

  // now call gnuplot
  system("gnuplot plot.plt -");

  // remove the plot file
  system("rm plot.plt");
}

/**
 * Easy way to print points
 */
std::ostream &operator<<(std::ostream &os, std::vector<Vector3D>points) {
  for (auto curPoint : points) {
    os << curPoint << std::endl;
  }
  return os;
}
