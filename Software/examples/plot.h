#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph2D.h"
#include "TAxis.h"

#include<vector>
#include "vector3d.h"

void plot(const std::vector<Vector3D> &points){
  int n = points.size();
  double x[n], y[n], z[n];
  for (int i = 0; i < n; i++) {
    x[i] = points[i].x;
    y[i] = points[i].y;
    z[i] = points[i].z;
  }
  // dummy values
  int argc = 0;
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wuninitialized"
  char **argv;
  TApplication app("ROOT Application", &argc, argv);
  #pragma GCC diagnostic pop
  // intentional memory leaks here to keep the objects alive even when
  // the rest of this method terminated
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wunused-variable"
  TCanvas *c = new TCanvas("c","Graph2D example",0,0,700,600);
  #pragma GCC diagnostic pop
  TGraph2D *graph = new TGraph2D(n, x, y, z);
  graph->Draw("p line");
  graph->GetXaxis()->SetTitle("X-Axis");
  graph->GetYaxis()->SetTitle("Y-Axis");
  graph->GetZaxis()->SetTitle("Z-Axis");
  app.Run();
}
