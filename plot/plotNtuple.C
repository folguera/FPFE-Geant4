// ROOT macro file for plotting example B4 ntuple
// 
// Can be run from ROOT session:
// root[0] .x plotNtuple.C

{
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  // Draw histos filled by Geant4 simulation 
  //   

  // Open file filled by Geant4 simulation 
  TFile f("Test.root");

  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(1,2);
  
  // Get ntuple
  TNtuple* ntuple = (TNtuple*)f.Get("B4");

  // Draw Eabs histogram in the pad 1
  c1->cd(1);
  ntuple->Draw("Edep");
  
  // Draw Labs histogram in the pad 2
  c1->cd(2);
  ntuple->Draw("trackL");  
}  
