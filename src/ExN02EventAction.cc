//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: ExN02EventAction.cc,v 1.11 2006/06/29 17:48:05 gunter Exp $
// GEANT4 tag $Name: geant4-09-01-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#include "ExN02EventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "ExN02RunAction.hh"
#include "ExN02PrimaryGeneratorAction.hh"

#include "G4VTrajectory.hh"
#include "G4VVisManager.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

#include "ExN02RunAction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
ExN02EventAction::ExN02EventAction(ExN02RunAction* run,ExN02PrimaryGeneratorAction* primaryGenerator)
    :runAct(run), primaryGenerator(primaryGenerator)		 
{
    pFile = fopen ("spectrum.txt" , "w");
    if (pFile == NULL) G4cout<<("Error opening file")<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
ExN02EventAction::~ExN02EventAction()
{
    fclose (pFile);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void ExN02EventAction::BeginOfEventAction(const G4Event * evt)
{
    G4int evtNb = evt->GetEventID();
/*
  if (evtNb%printModulo == 0) { 
  G4cout << "\n---> Begin of event: " << evtNb << G4endl;
  CLHEP::HepRandom::showEngineStatus();
  }
*/ 
    // initialisation per event
    //EnergyDet = EnergyTarget = 0.;
    EnergyDet1R = 0.; 
    EnergyDet2R = 0.;
    EnergyDet3R = 0.;
    EnergyDet4R = 0.;
    TrackLDet = TrackLTarget = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void ExN02EventAction::EndOfEventAction(const G4Event* evt)
{
    G4int event_id = evt->GetEventID();
    G4double Ereal = primaryGenerator->GetEkin();
    G4double Fr = primaryGenerator->GetFr();
    //if (event_id%100 == 0) {
//	G4cout << "---> End of event: " << event_id << G4endl;	
    //   }
    
    // get number of stored trajectories
    //
    //G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
    //G4int n_trajectories = 0;
    //if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
    
    //G4cout<<" ExN02EventAction.cc "<<G4endl;
    //G4cout<<" ExN02EventAction::EndOfEventAction(const G4Event* evt) "<<G4endl;
    //G4cout<<" ------------------------------------------- "<<G4endl;
    //// periodic printing
    //
    //if (event_id < 100 || event_id%100 == 0) {
    //   G4cout << ">>> Event " << evt->GetEventID() << G4endl;
    //  G4cout << "    " << n_trajectories 
    //	 << " trajectories stored in this event." << G4endl;
    //}

    G4double Etot;
    Etot = EnergyDet1R + EnergyDet2R + EnergyDet3R + EnergyDet4R;

    static int count = 0;
    static G4double Ecount = 0.;

    if(Etot!=0){
	count = count + 1; 
	fprintf (pFile, "%10d %15.5f %15.5f %15.5f %15.5f %15.5f %15.5f \n ",event_id, EnergyDet1R, EnergyDet2R, EnergyDet3R, EnergyDet4R,Ereal,Fr);
	Ecount = Ecount + Etot;
	//if(EnergyDet1R!=0) printf(" Ev ID %7d    E = %10.3f (MeV) \n",event_id,EnergyDet1R);

	//if (event_id%1000 == 0) {
	//printf(" Ev ID %7d    E = %10.3f (MeV) \n",event_id,Etot);
	    //G4cout << EnergyDet1R<< G4endl;
	//}
    }

    //if (event_id%100 == 0) {
    //printf(" Ev ID %7d    E = %10.3f (MeV)  E mean = %10.3f (MeV)  signal = %10.3f (%) \n",event_id,Etot, Ecount/(event_id+1), count/(double(event_id + 1.))*100.);
    //}

    if (event_id%1000 == 0) {
	printf(" Ev ID %10d \n",event_id);
    }

	//G4cout << "---> End of event: " << evtNb << G4endl;
	//G4cout << "           E Det = " << EnergyDet << G4endl;
	//G4cout << "        E Target = " << EnergyTarget << G4endl;
	//G4cout << "           sum E = " << (EnergyTarget + EnergyDet) << G4endl;
	//G4cout << " Namber of event   " << count << G4endl;
	//}    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
