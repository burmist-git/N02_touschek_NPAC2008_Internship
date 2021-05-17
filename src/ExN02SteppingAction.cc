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
// $Id: ExN02SteppingAction.cc,v 1.9 2006/06/29 17:48:18 gunter Exp $
// GEANT4 tag $Name: geant4-09-01-patch-01 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN02SteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4StepPoint.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4Material.hh"
#include "G4VPhysicalVolume.hh"
#include "stdio.h"
#include <string>
#include "ExN02DetectorConstruction.hh"
#include "ExN02EventAction.hh"
#include "ExN02PrimaryGeneratorAction.hh"
#include "G4RunManager.hh"
#include <iomanip>
#include <iostream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02SteppingAction::ExN02SteppingAction(ExN02DetectorConstruction* det,
                                         ExN02EventAction* evt, 
					 G4RunManager *runManager, 
					 ExN02PrimaryGeneratorAction* primaryAction)
    :detector(det), eventaction(evt), runManager(runManager), primaryAction(primaryAction)					 
{
    G4cout<<" ExN02SteppingAction.cc"<<G4endl;
    G4cout<<" ExN02SteppingAction::ExN02SteppingAction()"<<G4endl;
    G4cout<<" -------------------------------------------"<<G4endl;
    streamStep = fopen("ShowerSD1.txt","w");
    //streamStep = fopen("mirrorTouschek.txt","w");
    streamStep2 = fopen("ShowerSD2.txt","w");
    //fprintf(streamStep," %15s %15s %15s %15s %15s %15s %15s %15s\n", "x", "y", "z", "Px", "Py", "Pz", "Ekin","particleID");
    evtID = 1;
    beginOfEvent = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02SteppingAction::~ExN02SteppingAction()
{
    fclose(streamStep);
    fclose(streamStep2);
}

void ExN02SteppingAction::UserSteppingAction(const G4Step* step)
{

    //for mirror geometry
    //writeMirrorEv(streamStep, step);

//for normal working!!!
   
    // get volume of the current step
    G4VPhysicalVolume* volume 
	= step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    
    // collect energy and track length step by step
    G4double edep = step->GetTotalEnergyDeposit();
    
    G4double stepl = 0.;
    if (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
	stepl = step->GetStepLength();
    
    
    //if (volume == detector->GetPbWO1Box_R()) eventaction->AddDet(edep,0.,0.,0.,stepl);
    //if (volume == detector->GetPbWO2Box_R()) eventaction->AddDet(0.,edep,0.,0.,stepl);
    //if (volume == detector->GetPbWO3Box_R()) eventaction->AddDet(0.,0.,edep,0.,stepl);
    //if (volume == detector->GetPbWO4Box_R()) eventaction->AddDet(0.,0.,0.,edep,stepl);
    
    
    if (volume == detector->GetPbWO1Box_L()) eventaction->AddDet(edep,0.,0.,0.,stepl);
    if (volume == detector->GetPbWO2Box_L()) eventaction->AddDet(0.,edep,0.,0.,stepl);
    if (volume == detector->GetPbWO3Box_L()) eventaction->AddDet(0.,0.,edep,0.,stepl);
    if (volume == detector->GetPbWO4Box_L()) eventaction->AddDet(0.,0.,0.,edep,stepl);
    
    if (volume == detector->GetSenDetShower_L()){
	writeEv(streamStep, step);
    }
    
    if (volume == detector->GetSenDetShower1_L()){
	writeEv(streamStep2, step);
    }

    //static G4int counter = 0;
    //if (volume == detector->GetSenDetTube4_R_U_v()){
    //printParticleInfo(step);
    //counter++;
    //G4cout<<"  "<<counter<<" OK"<<G4endl;
    //}

    //example of saving random number seed of this event, under condition
    //// if (condition) G4RunManager::GetRunManager()->rndmSaveThisEvent(); 
    
}

void ExN02SteppingAction::writeEv(FILE* streamStep, const G4Step* step){
	G4StepPoint* StepPoint;
	G4ThreeVector position;
	G4ThreeVector momentum;
	G4double Ekin;
	G4Track* trek;
	G4int particlID;
	std::string particleName;

	G4int evID = runManager->GetCurrentEvent()->GetEventID();

	StepPoint = step->GetPreStepPoint();
	position = StepPoint->GetPosition();
	momentum = StepPoint->GetMomentum();
	Ekin = StepPoint->GetKineticEnergy();
	trek = step->GetTrack();
	particleName = trek->GetDefinition()->GetParticleName();
	if(particleName == "gamma") particlID = 0;
	if(particleName == "e+")    particlID = 1;
	if(particleName == "e-")    particlID = -1;

	fprintf(streamStep," %11d %15.5f %15.5f %15.5f %15.5f %15.5f %15.5f %15.5f %11d\n", 
		evID,
		position.getX(), 
		position.getY(), 
		position.getZ(), 
		momentum.getX(), 
		momentum.getY(), 
		momentum.getZ(),
		Ekin,
		particlID);
	//step->GetTrack()->SetTrackStatus(fStopAndKill);
}


void ExN02SteppingAction::writeMirrorEv(FILE* streamStep, const G4Step* step){

    G4StepPoint* StepPoint;
    G4ThreeVector position;
    G4ThreeVector direction;
    G4double Ekin;
    G4Track* trek;
    G4VPhysicalVolume* PhysVolume;
    G4String VolumeName;
    G4Material *mat;
    std::string vol;
    std::string materialName;
    std::string particleName;

    static G4int i = 0;    

    StepPoint = step->GetPreStepPoint();
    position = StepPoint->GetPosition();
    //direction = StepPoint->GetMomentumDirection();
    direction = StepPoint->GetMomentum();
    Ekin = StepPoint->GetKineticEnergy();
    
    trek = step->GetTrack();
    PhysVolume = trek->GetVolume();
    mat = trek->GetMaterial();
    particleName = trek->GetDefinition()->GetParticleName();    


    VolumeName = PhysVolume->GetName();
    vol = PhysVolume->GetName();
    materialName = mat->GetName();

    G4double Ekinet = primaryAction->GetEkin();
    G4double fr = primaryAction->GetFr();

//G4bool IsFirstStepInVolume() const
    
    if(materialName == "Lead" && evtID != runManager->GetCurrentEvent()->GetEventID()){
    //i++;
	//if(beginOfEvent == true){	    
        step->GetTrack()->SetTrackStatus(fStopAndKill);
	//fprintf(streamStep," %15.5f %15.5f %15.5f %15.5f %15.5f %15.5f %15.5f %15s %10s %10s %10d \n", 
	fprintf(streamStep," %15.5f %15.5f %15.5f %15.5f %15.5f %15.5f %15.5f %15.5f %15.5f \n", 
		position.getX(), 
		position.getY(), 
		position.getZ(), 
		direction.getX(), 
		direction.getY(), 
		direction.getZ(),
		Ekin,
		Ekinet,
		fr); 
		//,vol.c_str(),
		//materialName.c_str(),
		//particleName.c_str(), 
		//runManager->GetCurrentEvent()->GetEventID());
	evtID = runManager->GetCurrentEvent()->GetEventID();
	//fprintf(streamStep," %10.5f %10.5f %10.5f \n", position.getX(), position.getY(), position.getZ());
	//beginOfEvent = false;
	//} 
	//if (i%100 == 0){
	//    G4cout<<i<<G4endl;    
	//}
	// }
	}


    //step->GetTrack()->SetTrackStatus(fStopAndKill);
//    step->GetTrack()->SetTrackStatus(fStopAndKill);
/*
    if(evtID != runManager->GetCurrentEvent()->GetEventID()){
	G4cout<<evtID<<G4endl;
	beginOfEvent == true;
	evtID = runManager->GetCurrentEvent()->GetEventID();
    }
    
*/
}


void ExN02SteppingAction::printParticleInfo(const G4Step* step){

	G4StepPoint* StepPoint;
	G4ThreeVector position;
	G4ThreeVector momentum;
	G4double Ekin;
	G4Track* trek;
	G4int particlID;
	std::string particleName;

	G4int evID = runManager->GetCurrentEvent()->GetEventID();

	StepPoint = step->GetPreStepPoint();
	position = StepPoint->GetPosition();
	momentum = StepPoint->GetMomentum();
	Ekin = StepPoint->GetKineticEnergy();
	trek = step->GetTrack();
	particleName = trek->GetDefinition()->GetParticleName();

	//if(particleName == "gamma") particlID = 0;
	//if(particleName == "e+")    particlID = 1;
	//if(particleName == "e-")    particlID = -1;

	printf(" pos %15.5f %15.5f %15.5f \n imp %15.5f %15.5f %15.5f \n Ekin =  %9.5f \n", 
		position.getX(), 
		position.getY(), 
		position.getZ(), 
		momentum.getX(), 
		momentum.getY(), 
		momentum.getZ(),
		Ekin);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

