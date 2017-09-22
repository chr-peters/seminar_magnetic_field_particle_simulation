// Builds a graph with errors, displays it and saves it as
// image. First, include some header files
// (not necessary for Cling)

#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"
#include "TMath.h"
#include "TGraph.h"
#include "TGraphPolar.h"

void macro(){
    auto c = new TCanvas("myCanvas","myCanvas",600,600);
    Double_t rmin=0.;
    Double_t rmax=TMath::Pi()*6.;
    const Int_t npoints=1000;
    Double_t r[npoints];
    Double_t theta[npoints];
    for (Int_t ipt = 0; ipt < npoints; ipt++) {
        r[ipt] = ipt*(rmax-rmin)/npoints+rmin;
        theta[ipt] = TMath::Sin(r[ipt]);
    }
    TGraphPolar grP1 (npoints,r,theta);
    grP1.SetTitle("A Fan");
    grP1.SetLineWidth(3);
    grP1.SetLineColor(2);
    grP1.DrawClone("L");

    grP1.Print();
}

int main(){
    macro();
}
