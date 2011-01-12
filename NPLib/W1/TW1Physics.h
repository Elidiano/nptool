#ifndef __W1Physics__
#define __W1Physics__
/*****************************************************************************
 * Copyright (C) 2009-2010   this file is part of the NPTool Project         *
 *                                                                           *
 * For the licensing terms see $NPTOOL/Licence/NPTool_Licence                *
 * For the list of contributors see $NPTOOL/Licence/Contributors             *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 *                                                                           *
 * Creation Date  : january 2011                                             *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription:                                                               *
 *     This class holds the physics class for the W1 detector from Micron    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/
//	STL
#include <vector>
using namespace std ;

//	ROOT
#include "TObject.h"

//	NPL
#include "TW1Data.h"
#include "../include/VDetector.h"
#include "../include/CalibrationManager.h"


class TW1Physics : public TObject, public NPA::VDetector
{
 public:	//	Constructor and Destructor
   TW1Physics();
   ~TW1Physics();

 public:	//	Calibrated Data
   vector<UShort_t>	DetectorNumber;
   vector<UShort_t>	StripNumber;
   vector<Double_t>	Energy;
   vector<Double_t>	Time;

 public:	//	inherrited from VDetector
   // Read stream at ConfigFile to pick-up parameters of detector (Position,...) using Token
   void ReadConfiguration(string);
		
   // Add Parameter to the CalibrationManger
   void AddParameterToCalibrationManager();		
			
   // Activated associated Branches and link it to the private member DetectorData address
   // In this method mother Branches (Detector) AND daughter leaf (fDetector_parameter) have to be activated
   void InitializeRootInput();

   // Create associated branches and associated private member DetectorPhysics address
   void InitializeRootOutput();

   // This method is called at each event read from the Input Tree. Aime is to build treat Raw dat in order to extract physical parameter. 
   void BuildPhysicalEvent();
		
   // Same as above, but only the simplest event and/or simple method are used (low multiplicity, faster algorythm but less efficient ...).
   // This method aimed to be used for analysis performed during experiment, when speed is requiered.
   // NB: This method can eventually be the same as BuildPhysicalEvent.
   void BuildSimplePhysicalEvent();

   // Those two method all to clear the Event Physics or Data
   void ClearEventPhysics()   {Clear();}
   void ClearEventData()      {m_EventData->Clear();}


 public: //	Specific to W1
   // Clear The PreTeated object
   void ClearPreTreatedData()	{m_PreTreatedData->Clear();}
		
   // Remove bad channel, calibrate the data and apply threshold
   void PreTreat();

   // Initialize the standard parameter for analysis
   // ie: all channel enable, maximum multiplicity for strip = number of telescope
   void InitializeStandardParameter();
   
   //	Read the user configuration file; if no file found, load standard one
	 void ReadAnalysisConfig();


 private: // Data not written in the tree
   int         m_NumberOfDetector;     //!
   TW1Data*    m_EventData;            //!
   TW1Data*    m_PreTreatedData;       //!
   TW1Physics* m_EventPhysics;         //!

   double 		m_E_Threshold;          //!
   double 		m_Pedestal_Threshold;   //!
				

 private: // Map of activated Channel
   map< int, vector<bool> > ChannelStatus;   //!
    
 public:  //  Return True if the channel is activated
   // bool IsValidChannel(int DetectorNbr, int StripNbr) ;

   void Clear();
   void Clear(const Option_t*) {};
	
   ClassDef(TW1Physics,1)  // TW1Physics
};


namespace LOCAL
{
   double fSi_E( TW1Data* EventData , int i );
   double fSi_T( TW1Data* EventData , int i );
}

#endif