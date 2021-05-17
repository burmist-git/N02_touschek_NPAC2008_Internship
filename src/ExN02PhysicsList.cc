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
// $Id: ExN02PhysicsList.cc,v 1.22 2006/06/29 17:48:11 gunter Exp $
// GEANT4 tag $Name: geant4-09-01-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "globals.hh"
#include "ExN02PhysicsList.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"

#include "G4ProductionCutsTable.hh"

#include "G4Region.hh"
#include "G4RegionStore.hh"


#include "G4ParticleTable.hh"
#include "G4EmCalculator.hh"
#include "ExN02MaterialConstruction.hh"
#include "G4ParticleDefinition.hh"

#include "G4Material.hh"
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02PhysicsList::ExN02PhysicsList():  G4VUserPhysicsList()
{
  defaultCutValue = 1.0*cm;
   SetVerboseLevel(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02PhysicsList::~ExN02PhysicsList()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  ConstructBosons();
  ConstructLeptons();
  ConstructMesons();
  ConstructBaryons();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::ConstructBosons()
{
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();

  // gamma
  G4Gamma::GammaDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::ConstructLeptons()
{
  // leptons
  //  e+/-
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  // mu+/-
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();
  // nu_e
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  // nu_mu
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::ConstructMesons()
{
  //  mesons
  //    light mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4PionZero::PionZeroDefinition();
  G4Eta::EtaDefinition();
  G4EtaPrime::EtaPrimeDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();
  G4KaonZero::KaonZeroDefinition();
  G4AntiKaonZero::AntiKaonZeroDefinition();
  G4KaonZeroLong::KaonZeroLongDefinition();
  G4KaonZeroShort::KaonZeroShortDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::ConstructBaryons()
{
  //  barions
  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();

  G4Neutron::NeutronDefinition();
  G4AntiNeutron::AntiNeutronDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
  ConstructGeneral();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4MultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"

#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::ConstructEM()
{
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
     
    if (particleName == "gamma") {
      // gamma         
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      pmanager->AddDiscreteProcess(new G4ComptonScattering);
      pmanager->AddDiscreteProcess(new G4GammaConversion);
      
    } else if (particleName == "e-") {
      //electron
      pmanager->AddProcess(new G4MultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);
      
      pmanager->AddDiscreteProcess(new G4StepLimiter());
      pmanager->AddDiscreteProcess(new G4UserSpecialCuts());

    } else if (particleName == "e+") {
      //positron
      pmanager->AddProcess(new G4MultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);
      pmanager->AddProcess(new G4eplusAnnihilation,  0,-1,4);

    } else if( particleName == "mu+" || 
               particleName == "mu-"    ) {
      //muon  
      pmanager->AddProcess(new G4MultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4MuIonisation,      -1, 2,2);
      pmanager->AddProcess(new G4MuBremsstrahlung,  -1, 3,3);
      pmanager->AddProcess(new G4MuPairProduction,  -1, 4,4);       
     
    } else if ((!particle->IsShortLived()) &&
	       (particle->GetPDGCharge() != 0.0) && 
	       (particle->GetParticleName() != "chargedgeantino")) {
      //all others charged particles except geantino
      pmanager->AddProcess(new G4MultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4hIonisation,       -1, 2,2);
      //step limit
      pmanager->AddProcess(new G4StepLimiter,       -1,-1,3);         
      ///pmanager->AddProcess(new G4UserSpecialCuts,   -1,-1,4);  
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Decay.hh"
void ExN02PhysicsList::ConstructGeneral()
{
  // Add Decay Process
  G4Decay* theDecayProcess = new G4Decay();
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    if (theDecayProcess->IsApplicable(*particle)) { 
      pmanager ->AddProcess(theDecayProcess);
      // set ordering for PostStepDoIt and AtRestDoIt
      pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::SetCuts()
{
    //G4VUserPhysicsList::SetCutsWithDefault method sets 
    //the default cut value for all particle types 
    //
    //SetCutsWithDefault();

    SetCutValue(0.01*mm, "gamma");
    SetCutValue(0.1*mm, "e-");
    SetCutValue(0.1*mm, "e+");

//     SetCutValue(0.01*mm, "gamma");
//     SetCutValue(0.1*mm, "e-");
//     SetCutValue(0.1*mm, "e+");

    //G4cout<<"LLLLLLLLLLLLLLLLL"<<G4endl;
    DumpCutValuesTable();  
  
    
    // default production thresholds for the world volume
    //SetCutsWithDefault();

   //Production thresholds for detector regions
   // G4Region* region;
    //G4String regName;
    //G4ProductionCuts* cuts;

    //G4ProductionCutsTable::GetProductionCutsTable()->DumpCouples();

/*
    regName = "lowAngleDetR";
    region = G4RegionStore::GetInstance()->GetRegion(regName);
    cuts = new G4ProductionCuts;
    cuts->SetProductionCut(0.0001*mm); // same cuts for gamma, e- and e+
    region->SetProductionCuts(cuts);
*/

//    regName = "lowAngleDetR";
//    region = G4RegionStore::GetInstance()->GetRegion(regName);
//    cuts = new G4ProductionCuts;
//     cuts->SetProductionCut(0.06*mm,G4ProductionCuts::GetIndex("gamma"));
//     cuts->SetProductionCut(0.002*mm,G4ProductionCuts::GetIndex("e-"));
//     cuts->SetProductionCut(0.002*mm,G4ProductionCuts::GetIndex("e+"));
    
//     cuts->SetProductionCut(0.01*mm,G4ProductionCuts::GetIndex("gamma"));
//     cuts->SetProductionCut(1.*mm,G4ProductionCuts::GetIndex("e-"));
//     cuts->SetProductionCut(1.*mm,G4ProductionCuts::GetIndex("e+"));
    
//    region->SetProductionCuts(cuts);
    
    G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(0.1*keV, 100*GeV);  
    
    //G4ProductionCutsTable::GetProductionCutsTable()->StoreCutsTable("/home/leonid/",true);
    G4double lowEn  = G4ProductionCutsTable::GetProductionCutsTable()->GetLowEdgeEnergy();
    G4double HighEn  = G4ProductionCutsTable::GetProductionCutsTable()->GetHighEdgeEnergy();
    
    //G4ProductionCutsTable::GetProductionCutsTable()->DumpCouples();
    
    G4cout<<"LLLLLLLLLLLLLLLLL"<<G4endl;
    G4cout<<"lowEn = "<<lowEn<<G4endl;
    G4cout<<"HighEn = "<<HighEn<<G4endl;
    G4cout<<"LLLLLLLLLLLLLLLLL"<<G4endl;

    
    /*
      G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
      
      const G4ParticleDefinition* particle = particleTable->FindParticle("e-");
      
      
      
      G4cout<<particle->GetPDGMass()<<G4endl;
  
      
      ExN02MaterialConstruction* consMat = new ExN02MaterialConstruction();
      const G4Material* material = consMat->ConstructAir(); 
      
      
      G4double range  = 1.0*cm;
    */  
    
    
    //G4EmCalculator *calc = new G4EmCalculator();
    //G4cout<<material<<G4endl;
  
    //calc->ComputeEnergyCutFromRangeCut(range, particle, material);
    //G4cout<<mycut<<G4endl;
    
    
    //G4ProductionCutsTable *table = new G4ProductionCutsTable();
    //if (verboseLevel>0) DumpCutValuesTable();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

