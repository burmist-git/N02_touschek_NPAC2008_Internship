#include<G4Step.hh>
#include<fstream>
#include<iostream>
#include"ExN02SensitiveDetector.hh"
#include "DetectorConstant.hh"

using namespace DetConst;
using namespace std;

ExN02SensitiveDetector::ExN02SensitiveDetector(G4String name): G4VSensitiveDetector(name),
						     HIST_MAX(0.60*GeV),
						     HIST_MIN(0 *MeV)
{
    //G4double Etot = 0.;
    //for(int i = 0; i<NOBINS; i++)
    //histogram[i] = 0;
    //evtID = 0;
}

G4bool ExN02SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *hist)
{

//   G4cout<<" x out = "<<step->GetTrack()->GetPosition().getX()<<G4endl;
//   G4cout<<" y out = "<<step->GetTrack()->GetPosition().getY()<<G4endl;
//   G4cout<<" z out = "<<step->GetTrack()->GetPosition().getZ()<<G4endl;

//   G4cout<<" Px out = "<<step->GetTrack()->GetMomentumDirection().getX()<<G4endl;
//   G4cout<<" Py out = "<<step->GetTrack()->GetMomentumDirection().getY()<<G4endl;
//   G4cout<<" Pz out = "<<step->GetTrack()->GetMomentumDirection().getZ()<<G4endl;

  //step->GetTrack()->SetTrackStatus(fStopAndKill);



/*
    G4double dE = 0.;
    G4String paName = "NON"; 

    paName = step->GetTrack()->GetDefinition()->GetParticleName();
 
    dE = step->GetTotalEnergyDeposit();
    Etot += dE;


   if (evtID != runManager->GetCurrentEvent()->GetEventID()){
       //G4cout<<" paName = "<<paName<<G4endl;
       //G4cout<<" Etot   = "<<Etot<<G4endl;
	double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
	int index = int(floor((Etot-HIST_MIN)/bin_width));
	if(index >= 0 && index < NOBINS)
	    histogram[index]++;
	Etot = 0;
	evtID = runManager->GetCurrentEvent()->GetEventID();
    }
*/
/*
  G4String paName = "NON"; 
  double energy = step->GetTrack()->GetDynamicParticle()->GetTotalEnergy();
  double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
  int index = int(floor((energy-HIST_MIN)/bin_width));
  if(index >= 0 && index < NOBINS)
    histogram[index]++;

  double Px = step->GetTrack()->GetMomentumDirection().getX();
  double Pz = step->GetTrack()->GetMomentumDirection().getZ();

  G4cout<<" x out = "<<step->GetTrack()->GetPosition().getX()<<G4endl;
  G4cout<<" y out = "<<step->GetTrack()->GetPosition().getY()<<G4endl;
  G4cout<<" z out = "<<step->GetTrack()->GetPosition().getZ()<<G4endl;

  G4cout<<" Px out = "<<step->GetTrack()->GetMomentumDirection().getX()<<G4endl;
  G4cout<<" Py out = "<<step->GetTrack()->GetMomentumDirection().getY()<<G4endl;
  G4cout<<" Pz out = "<<step->GetTrack()->GetMomentumDirection().getZ()<<G4endl;

  G4cout<<" Px / Py = "<<  Px/Pz   <<G4endl;

  G4cout<<" x in  = "<< x_Tube5_C_R_U*cm<<G4endl;
  G4cout<<" y in  = "<< y_Tube5_C_R_U*cm<<G4endl;
  G4cout<<" z in  = "<< z_Tube5_C_R_U*cm<<G4endl;

  //G4cout<<" x out = "<< x_Tube5_C_L_D*cm<<G4endl;
  //G4cout<<" y out = "<< y_Tube5_C_L_D*cm<<G4endl;
  //G4cout<<" z out = "<< z_Tube5_C_L_D*cm<<G4endl;
  

  G4cout<<" E = "<<energy<<G4endl;

  step->GetTrack()->SetTrackStatus(fStopAndKill);
 

  paName = step->GetTrack()->GetDefinition()->GetParticleName();

  //G4cout<<" paName = "<<paName<<G4endl;
*/
  return true;
}

void ExN02SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
}

ExN02SensitiveDetector::~ExN02SensitiveDetector()
{
    //std::ofstream file("spectrumPhotRight.dat");
/*  
  double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
  for(int i = 0; i<NOBINS; i++)
  {
    double energy = i*bin_width + HIST_MIN;
    file << std::setw(15) << energy/MeV << " "
	 << std::setw(15) << histogram[i] << std::endl;
  }
*/
}
