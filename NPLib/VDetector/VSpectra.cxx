/*****************************************************************************
 * Copyright (C) 2009-2014   this file is part of the NPTool Project         *
 *                                                                           *
 * For the licensing terms see $NPTOOL/Licence/NPTool_Licence                *
 * For the list of contributors see $NPTOOL/Licence/Contributors             *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 *                                                                           *
 * Creation Date  : dec 2013                                                 *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription:                                                               *
 *  This class holds all the online spectra needed for Tiara/Hyball          *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *    + first version (not complete yet)                                     *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/

//STL
#include <iostream>
#include <cstdlib>
// NPL
#include "VSpectra.h"
#include "NPOptionManager.h"


// ROOT
#include "TDirectory.h"
#include "TFile.h"

////////////////////////////////////////////////////////////////////////////////
TH1* VSpectra::AddHisto1D(string name, string title, Int_t nbinsx, Double_t xlow, Double_t xup, string family){
  // create histo
  TH1 *hist = new TH1D(name.c_str(), title.c_str(), nbinsx, xlow, xup);

  vector<string> index;
  index.push_back(family);
  index.push_back(name);

  // fill map
  fMapHisto[index] = hist;

  return hist;
}

////////////////////////////////////////////////////////////////////////////////
TH1* VSpectra::AddHisto2D(string name, string title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup, string family){
  // create histo
  TH1 *hist = new TH2D(name.c_str(), title.c_str(), nbinsx, xlow, xup, nbinsy, ylow, yup);

  vector<string> index;
  index.push_back(family);
  index.push_back(name);

  // fill map
  fMapHisto[index] = hist;

  return hist;
}

////////////////////////////////////////////////////////////////////////////////
TH1* VSpectra::GetHisto(string& family, string& name){
  vector<string> index;
  index.reserve(2);
  index.push_back(family);
  index.push_back(name);
  TH1* histo ; 

  map< vector<string> , TH1*>::iterator it;
  it = fMapHisto.find(index);

  if(it == fMapHisto.end()){
    cout << "ERROR : the folowing Histo has been requested and does not exist: family:" << family << " name: "  << name << endl ;
    exit(1);
  }

  else
    histo = it->second; 

  return histo;
}

////////////////////////////////////////////////////////////////////////////////
void VSpectra::WriteHisto(string filename){
  TFile* f = NULL; 

  if (filename != "VOID") {
    f = new TFile(filename.c_str(),"RECREATE");
  }

  map< vector<string>, TH1* >::iterator it;
  for (it=fMapHisto.begin(); it!=fMapHisto.end(); ++it) {
    it->second->Write();
  }

  if (filename != "VOID") {
    f->Close();
    delete f;
  }
}
