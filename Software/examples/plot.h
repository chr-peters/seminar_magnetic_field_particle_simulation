#include<vector>
#include <iostream>
#include "vector3d.h"
#include <string>
#include <fstream>
#include <sstream>

#include "plane3d.h"

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
    std::ostringstream gnuplotScript;
    gnuplotScript << "set title '" << title << "'" << std::endl;
    gnuplotScript << "set xlabel 'x'" << std::endl << "set ylabel 'y'" << std::endl << "set zlabel 'z'" << std::endl;
    gnuplotScript << "splot 'points.txt' with linespoints" << std::endl;

    gnuplotFile << gnuplotScript.str();
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

void plot(std::string title, const std::vector<Vector3D> &points, const std::vector<Vector3D> &intersectionPoints, const Plane3D &plane){
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

  // now write the intersectionPoints to a temporary file
  std::ofstream outIntersectionFile;
  outIntersectionFile.open("intersectionPoints.txt");
  if (outIntersectionFile.is_open()) {
    for (auto curPoint : intersectionPoints) {
      outIntersectionFile << curPoint << std::endl;
    }
  } else {
    std::cerr << "Could not write intersection points to temporary file!" << std::endl;
    return;
  }

  // now create the instruction file for gnuplot
  std::ofstream gnuplotFile;
  gnuplotFile.open("plot.plt");
  if (gnuplotFile.is_open()) {
    std::ostringstream gnuplotScript;
    gnuplotScript << "set title '" << title << "'" << std::endl;
    gnuplotScript << "\n";
    gnuplotScript << "set xlabel 'x'" << std::endl << "set ylabel 'y'" << std::endl << "set zlabel 'z'" << std::endl;

    // now get the equation that describes the plane
    // special treatment necessary when the z coordinate of the normal vector is zero
    Vector3D normalVector = plane.getNormalVector();
    Vector3D pointInPlane = plane.getPointInPlane();
    gnuplotScript << "z(x, y)=";
    gnuplotScript << (normalVector * pointInPlane) / normalVector.z;
    if (normalVector.x > 0)
      gnuplotScript << " - ";
    gnuplotScript << normalVector.x / normalVector.z << " * x";
    if (normalVector.y > 0)
      gnuplotScript << " - ";
    gnuplotScript << normalVector.y / normalVector.z << " * y" <<  std::endl;
    gnuplotScript << "splot 'points.txt' with linespoints, 'intersectionPoints.txt' with points pointtype 7 lc rgb 'red', z(x, y)" << std::endl;

    gnuplotFile << gnuplotScript.str() << std::endl;

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
