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
// * Neither//ni tot ni drugoj// the authors of this software system, *
// * nor  their  employing  institutes, nor  the  agencies  providing *
// * financial support for this                                       *
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
// $Id: exampleN02.cc,v 1.14 2007/07/02 13:09:30 vnivanch Exp $
// GEANT4 tag $Name: geant4-09-01-patch-01 $
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN02DetectorConstruction.hh"
#include "ExN02PhysicsList.hh"
#include "ExN02PrimaryGeneratorAction.hh"
#include "ExN02RunAction.hh"
#include "ExN02EventAction.hh"
#include "ExN02SteppingAction.hh"
#include "ExN02SteppingVerbose.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "G4ParticleTable.hh"
#include "G4EmCalculator.hh"
#include "ExN02MaterialConstruction.hh"
#include "G4ParticleDefinition.hh"

#include "G4ProductionCutsTable.hh"

#include "G4Material.hh"

#include "TTree.h"
#include "TFile.h"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{

    /*
      Float_t dE1,dE2,dE3,dE4,Etot;    
      TFile f("rwer.root","recreate");
      TTree t1("t1","a simple Tree with simple variables");	
      t1.Branch("dE1",&dE1,"dE1/F");
      t1.Branch("dE2",&dE2,"dE2/F");
      dE1 = 10.;
      dE2 = 10000.;
      t1.Fill();
      t1.Write();
    */

    //G4cout<<argc<<G4endl;
    //G4cout<<(char**)argv<<G4endl;
    //return 0;

    // User Verbose output class
    //
    G4VSteppingVerbose* verbosity = new ExN02SteppingVerbose;
    G4VSteppingVerbose::SetInstance(verbosity);
    
    // Run manager
    //
    G4RunManager * runManager = new G4RunManager;
  
    // User Initialization classes (mandatory)
    //
    ExN02DetectorConstruction* detector = new ExN02DetectorConstruction;
    runManager->SetUserInitialization(detector);
    detector->SetRunManager(runManager);
    //
    G4VUserPhysicsList* physics = new ExN02PhysicsList;
    runManager->SetUserInitialization(physics);
   
    // User Action classes
    //
    ExN02PrimaryGeneratorAction* gen_action = new ExN02PrimaryGeneratorAction(detector);
    runManager->SetUserAction(gen_action);


    //
    ExN02RunAction* run_action = new ExN02RunAction;
    runManager->SetUserAction(run_action);


    //
    ExN02EventAction* event_action = new ExN02EventAction(run_action,gen_action);
    runManager->SetUserAction(event_action);


    //
    ExN02SteppingAction* stepping_action = new ExN02SteppingAction(detector,event_action,runManager,gen_action);
    runManager->SetUserAction(stepping_action);
    stepping_action->SetRunManager(runManager); 
    //stepping_action->SetRunManager();
    
    
    
      // G4UserSteppingAction* stepping_action = new ExN02SteppingAction;
      // G4cout<<" exampleN02.cc  "<<G4endl;
      // G4cout<<" runManager->SetUserAction(stepping_action) "<<G4endl;
      // G4cout<<" ------------------------------------------- "<<G4endl;
      // runManager->SetUserAction(stepping_action);
      // //stepping_action->SetRunManager(runManager); 
      // //stepping_action->SetRunManager();
      
    
    // Initialize G4 kernel
    //
    runManager->Initialize();

    // Get the pointer to the User Interface manager
    //
    G4UImanager * UI = G4UImanager::GetUIpointer();  
    
    
   //G4UIsession * session = 0;
   //UI->ApplyCommand("/control/execute vis.mac");     
   //session->SessionStart();
   //delete session;
    
    if (argc!=1)   // batch mode  
    {
	G4String command = "/control/execute ";
	G4String fileName = argv[1];
	UI->ApplyCommand(command+fileName);
    }    
    else           // interactive mode : define visualization and UI terminal
    { 
#ifdef G4VIS_USE
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
#endif    
     
	G4UIsession * session = 0;
#ifdef G4UI_USE_TCSH
	session = new G4UIterminal(new G4UItcsh);      
#else
	session = new G4UIterminal();
#endif

	UI->ApplyCommand("/control/execute vis.mac");     
	session->SessionStart();

	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	
	const G4ParticleDefinition* particle = particleTable->FindParticle("e-");
       	
	G4cout<<particle->GetPDGMass()<<G4endl;
	
	ExN02MaterialConstruction* consMat = new ExN02MaterialConstruction();
	const G4Material* material = consMat->ConstructPVC(); 
	
	G4double range  = 0.1*cm;
	G4EmCalculator *calc = new G4EmCalculator();
	G4double mycut;
	
	mycut = calc->ComputeEnergyCutFromRangeCut(range, particle, material);
	//G4cout<<mycut<<G4endl;


	G4ProductionCutsTable::GetProductionCutsTable()->DumpCouples();


	delete session;
     
#ifdef G4VIS_USE
	delete visManager;
#endif 
    }
    
    // Free the store: user actions, physics_list and detector_description are
    //                 owned and deleted by the run manager, so they should not
    //                 be deleted in the main() program !
    
    delete runManager;
    delete verbosity;
    
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
