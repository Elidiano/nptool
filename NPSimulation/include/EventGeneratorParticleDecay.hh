#ifndef EventGeneratorParticleDecay_H
#define EventGeneratorParticleDecay_H
/*****************************************************************************
 * Copyright (C) 2009-2013   this file is part of the NPTool Project         *
 *                                                                           *
 * For the licensing terms see $NPTOOL/Licence/NPTool_Licence                *
 * For the list of contributors see $NPTOOL/Licence/Contributors             *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: Adrien MATTA  contact address: matta@ipno.in2p3.fr       *
 *                                                                           *
 * Creation Date  : May 2012                                                 *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription:                                                               *
 *  This event Generator is used to simulated the particle decay of nuclei   *
 * generated by previous event generator. Multiple cases are supported:      *
 *  - Only one particle is emmited, in this case a Cross section can be given*
 *  - If Multiple particle are emitted, a Phase Space generator is used      *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/

// STL
#include <string>
#include <iostream>
using namespace std;

// ROOT
#include "TGenPhaseSpace.h"
#include "TH1F.h"

// NPSimulation
#include "VEventGenerator.hh"
#include "Target.hh"
#include "ParticleStack.hh"

//NPL
#include "NPFunction.h"
using namespace NPL;

// Geant4
#include "G4ParticleDefinition.hh"

class EventGeneratorParticleDecay : public VEventGenerator{
public: // Constructor and destructor
  EventGeneratorParticleDecay();
  ~EventGeneratorParticleDecay();
  
public: // Inherit from VEventGenerator class
  void ReadConfiguration(string,int);
  void GenerateEvent(G4Event*);
  void SetTarget(Target* Target) ;
  
private: // Target Parameter
  Target* m_Target;
  
private: // The decaying nuclei
         // General used
  string m_MotherNucleiName;
  vector<G4ParticleDefinition*> m_DaughterNuclei;
  vector<string> m_DaughterName;
  vector<double> m_ExcitationEnergy;
  vector<bool>   m_shoot;
  
  // Used for cross section
  string  m_DifferentialCrossSection;
  string  m_CrossSectionPath;
  string  m_CrossSectionName;
  TH1F*   m_CrossSectionHist;
  
  // Used for the phase space
  TGenPhaseSpace m_TPhaseSpace ;
  double* m_Masses;
  
private: // Pointer to the Particle stack for faster acces
  ParticleStack* m_ParticleStack;
public: // Managing the decay
        // Set everything for the decay
  void SetDecay(vector<string> DaughterName, vector<bool> shoot, vector<double> ExcitationEnergy, string CSPath , string CSName);
};
#endif
