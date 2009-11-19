#ifndef __SSSDDATA__
#define __SSSDDATA__
/*****************************************************************************
 * Copyright (C) 2009   this file is part of the NPTool Project              *
 *                                                                           *
 * For the licensing terms see $NPTOOL/Licence/NPTool_Licence                *
 * For the list of contributors see $NPTOOL/Licence/Contributors             *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: Adrien MATTA  contact address: matta@ipno.in2p3.fr       *
 *                                                                           *
 * Creation Date  : febuary 2009                                             *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription:                                                               *
 *  This class hold the Single Side Striped Detector raw data                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/
#include <vector>
#include "TObject.h"

using namespace std ;
class TSSSDData : public TObject {
	private:
		// SSSD
		// Energy
		vector<UShort_t>	fSSSD_StripE_DetectorNbr;
		vector<UShort_t>	fSSSD_StripE_StripNbr;
		vector<Double_t>	fSSSD_StripE_Energy;
		// Time
		vector<UShort_t>	fSSSD_StripT_DetectorNbr;
		vector<UShort_t>	fSSSD_StripT_StripNbr;
		vector<Double_t>	fSSSD_StripT_Time;


	public:
		TSSSDData();
		virtual ~TSSSDData();

		void	Clear();
                void    Clear(const Option_t*) {};
		void	Dump() const;

		/////////////////////           SETTERS           ////////////////////////
		// DSSD
		// (X,E)
		void	SetEnergyDetectorNbr	(UShort_t DetNbr) 	{ fSSSD_StripE_DetectorNbr.push_back(DetNbr)	;}
		void	SetEnergyStripNbr			(UShort_t StripNbr) { fSSSD_StripE_StripNbr.push_back(StripNbr)		;}
		void	SetEnergy							(Double_t Energy)   { fSSSD_StripE_Energy.push_back(Energy)				;}
		// (X,T)
		void	SetTimeDetectorNbr		(UShort_t DetNbr) 	{ fSSSD_StripT_DetectorNbr.push_back(DetNbr)	;}
		void	SetTimeStripNbr				(UShort_t StripNbr) { fSSSD_StripT_StripNbr.push_back(StripNbr)		;}
		void	SetTime								(Double_t Time)     { fSSSD_StripT_Time.push_back(Time)						;}

		/////////////////////           GETTERS           ////////////////////////
		// DSSD
		// (X,E)
		UShort_t	GetEnergyMult					()           	{	return fSSSD_StripE_DetectorNbr.size()	;}
		UShort_t	GetEnergyDetectorNbr	(Int_t i) 		{	return fSSSD_StripE_DetectorNbr.at(i)		;}
		UShort_t	GetEnergyStripNbr			(Int_t i)    	{	return fSSSD_StripE_StripNbr.at(i)			;}
		Double_t	GetEnergy							(Int_t i)     {	return fSSSD_StripE_Energy.at(i)				;}
		// (X,T)
		UShort_t	GetTimeMult						()            {	return fSSSD_StripT_DetectorNbr.size()	;}
		UShort_t	GetTimeDetectorNbr		(Int_t i) 		{	return fSSSD_StripT_DetectorNbr.at(i)		;}
		UShort_t	GetTimeStripNbr				(Int_t i)   	{	return fSSSD_StripT_StripNbr.at(i)			;}
		Double_t	GetTime								(Int_t i)     {	return fSSSD_StripT_Time.at(i)					;}
	
		ClassDef(TSSSDData,1)  // SSSDData structure
};

#endif