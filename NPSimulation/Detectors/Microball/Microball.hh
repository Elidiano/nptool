#ifndef Microball_h
#define Microball_h 1
/*****************************************************************************
 * Copyright (C) 2009-2016   this file is part of the NPTool Project       *
 *                                                                           *
 * For the licensing terms see $NPTOOL/Licence/NPTool_Licence                *
 * For the list of contributors see $NPTOOL/Licence/Contributors             *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: Pierre Morfouace  contact address: morfouac@nscl.msu.edu                        *
 *                                                                           *
 * Creation Date  : June 2016                                           *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription:                                                               *
 *  This class describe  Microball simulation                             *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/

// C++ header
#include <string>
#include <vector>
using namespace std;

// G4 headers
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4LogicalVolume.hh"
#include "G4MultiFunctionalDetector.hh"

// NPTool header
#include "NPSVDetector.hh"
#include "TMicroballData.h"

class Microball : public NPS::VDetector{
  ////////////////////////////////////////////////////
  /////// Default Constructor and Destructor /////////
  ////////////////////////////////////////////////////
  public:
    Microball() ;
    virtual ~Microball() ;

    ////////////////////////////////////////////////////
    /////// Specific Function of this Class ///////////
    ////////////////////////////////////////////////////
  public:
    // Cylindric plastic
    void AddMicroball(double R,
        double Theta,
        double Phi,
        string Shape);  

    G4LogicalVolume* BuildSquareDetector();
    G4LogicalVolume* BuildCylindricalDetector();
  
  private:
    G4LogicalVolume* m_SquareDetector;
    G4LogicalVolume* m_CylindricalDetector;
    
    ////////////////////////////////////////////////////
    //////  Inherite from NPS::VDetector class /////////
    ////////////////////////////////////////////////////
  public:
    // Read stream at Configfile to pick-up parameters of detector (Position,...)
    // Called in DetecorConstruction::ReadDetextorConfiguration Method
    void ReadConfiguration(string Path) ;

    // Construct detector and inialise sensitive part.
    // Called After DetecorConstruction::AddDetector Method
    void ConstructDetector(G4LogicalVolume* world) ;

    // Add Detector branch to the EventTree.
    // Called After DetecorConstruction::AddDetector Method
    void InitializeRootOutput() ;

    // Read sensitive part and fill the Root tree.
    // Called at in the EventAction::EndOfEventAvtion
    void ReadSensitive(const G4Event* event) ;

  public:   // Scorer
    //   Initialize all Scorer used by the MUST2Array
    void InitializeScorers() ;

    //   Associated Scorer
    G4MultiFunctionalDetector* m_MicroballScorer ;
    ////////////////////////////////////////////////////
    ///////////Event class to store Data////////////////
    ////////////////////////////////////////////////////
  private:
    TMicroballData* m_Event ;

    ////////////////////////////////////////////////////
    ///////////////Private intern Data//////////////////
    ////////////////////////////////////////////////////
  private: // Geometry
    // Detector Coordinate 
    vector<double>  m_R; 
    vector<double>  m_Theta;
    vector<double>  m_Phi; 
    
    //   Shape type
    vector<string> m_Shape ;
   
    // Visualisation Attribute
    G4VisAttributes* m_VisSquare;
    G4VisAttributes* m_VisCylinder;

  // Needed for dynamic loading of the library
  public:
    static NPS::VDetector* Construct();
};
#endif