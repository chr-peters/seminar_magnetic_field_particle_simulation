#include "TF1.h"
#include "TApplication.h"
#include "TMath.h"
#include "TGraphPolar.h"
#include "TCanvas.h"
#include "TGraph2D.h"
#include "TAxis.h"
#include "TF2.h"
#include "TRandom3.h"
#include "TGraph2DErrors.h"
#include "TH1.h"
#include "TStyle.h"
#include "TColor.h"

void plot(){
  gStyle->SetPalette(kBird);
  const double e = 0.3;
  const int nd = 500;

  TRandom3 my_random_generator;
  TF2 f2("f2",
	 "1000*(([0]*sin(x)/x)*([1]*sin(y)/y))+200",
	 -6,6,-6,6);
  f2.SetParameters(1,1);
  TGraph2DErrors dte(nd);
  // Fill the 2D graph
  double rnd, x, y, z, ex, ey, ez;
  for (Int_t i=0; i<nd; i++) {
    f2.GetRandom2(x,y);
    // A random number in [-e,e]
    rnd = my_random_generator.Uniform(-e,e);
    z = f2.Eval(x,y)*(1+rnd);
    dte.SetPoint(i,x,y,z);
    ex = 0.05*my_random_generator.Uniform();
    ey = 0.05*my_random_generator.Uniform();
    ez = fabs(z*rnd);
    dte.SetPointError(i,ex,ey,ez);
  }
  // Fit function to generated data
  f2.SetParameters(0.7,1.5);  // set initial values for fit
  f2.SetTitle("Fitted 2D function");
  dte.Fit(&f2);
  // Plot the result
  auto c1 = new TCanvas();
  f2.SetLineWidth(1);
  f2.SetLineColor(kBlue-5);
  TF2   *f2c = (TF2*)f2.DrawClone("Surf1");
  TAxis *Xaxis = f2c->GetXaxis();
  TAxis *Yaxis = f2c->GetYaxis();
  TAxis *Zaxis = f2c->GetZaxis();
  Xaxis->SetTitle("X Title"); Xaxis->SetTitleOffset(1.5);
  Yaxis->SetTitle("Y Title"); Yaxis->SetTitleOffset(1.5);
  Zaxis->SetTitle("Z Title"); Zaxis->SetTitleOffset(1.5);
  dte.DrawClone("P0 Same");
}

int main(int argc, char**argv){
  TApplication app("ROOT Application", &argc, argv);
  plot();
  app.Run();
}
