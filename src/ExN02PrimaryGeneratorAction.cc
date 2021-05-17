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
// $Id: ExN02PrimaryGeneratorAction.cc,v 1.7 2006/06/29 17:48:13 gunter Exp $
// GEANT4 tag $Name: geant4-09-01-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN02PrimaryGeneratorAction.hh"
#include "ExN02DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryParticle.hh"

#include "globals.hh"
//randoms distribution
#include "Randomize.hh"
//I/O to file
#include "iostream.h"
#include "fstream.h"
#include "string.h"
#include "iomanip.h"
#include <math.h>


#include "DetectorConstant.hh" 
using namespace DetConst;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02PrimaryGeneratorAction::ExN02PrimaryGeneratorAction(
                                               ExN02DetectorConstruction* myDC)
 :myDetector(myDC)
{

    //G4cout<<" ExN02PrimaryGeneratorAction.cc  "<<G4endl;
    //G4cout<<" ExN02PrimaryGeneratorAction::ExN02PrimaryGeneratorAction( ExN02DetectorConstruction) "<<G4endl;
    //G4cout<<" ------------------------------------------- "<<G4endl;

    G4int n_particle = 1;
    particleGun = new G4ParticleGun(n_particle);
    
    //default particle
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("e-");
    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    particleGun->SetParticleEnergy(0.51*GeV);
 
    //touschek data 
    //myfile.open("labtouschek.txt"); //mirror geometry
    //myfile.open("mirrorTouschekFieldOFF.txt");
    myfile.open("touschekG4InputFieldOFFfullGeom.txt");  

    //myTestfile.open("labdataTest.txt"); //test data are in this file
    //coordinates of the control points are in the file conpoin.txt  
    //myfile.open("conpoin.txt");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02PrimaryGeneratorAction::~ExN02PrimaryGeneratorAction()
{
    myfile.close();
    delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
  
    //control-of-the-geommetry--------------------------------------------------------
    //reading format of the "conpoin.txt" file
    //myfile.open("conpoin.txt");  
    /*G4float x, y, z;
      if(myfile.is_open()){
      myfile >> x>> y>> z;
      }
      else{
      G4cout<<" ExN02PrimaryGeneratorAction.cc  "<<G4endl;
      G4cout<<" ExN02PrimaryGeneratorAction::ExN02PrimaryGeneratorAction( ExN02DetectorConstruction) "<<G4endl;
      G4cout<<" ERROR : file "<< "conpoin.txt"<<"not open!!!"<<endl;
      G4cout<<" ------------------------------------------- "<<G4endl;
      
      }
    */

    /*//our own method to genetate many particles with different quality par one event
      G4PrimaryVertex* myvertex = 
      new G4PrimaryVertex(G4ThreeVector(0.0*cm,0.0*cm,54.38*cm),0.);
      for( G4int i=0; i<nOfParticlesInEvent; i++ ){
      G4PrimaryParticle* particle =
      new G4PrimaryParticle(particleDef,0.0 , 0.0, 1.0);
      //new G4PrimaryParticle(particleDef,G4UniformRand()-0.5 , (G4UniformRand()-0.5), (G4UniformRand()-0.5) );
      particleGun->SetParticleEnergy(5*GeV);
      myvertex->SetPrimary( particle );
      }
      anEvent->AddPrimaryVertex( myvertex );
    */

//------------------------------------------------------------------------------
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FLAGS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//------------------------------------------------------------------------------
    G4String flag_SetQD1Chek;
    //flag_SetQD1Chek = "SetQD1ChekOn";
    flag_SetQD1Chek = "SetQD1ChekOff";

    G4String flag_SetXDistortionON;
    //flag_SetXDistortionON = "SetXDistortionON";
    flag_SetXDistortionON = "SetXDistortionOFF";

    //--------------------------------
    G4String flag_SetXScanON;
    //flag_SetXScanON = "SetXScanON";
    flag_SetXScanON = "SetXScanOFF";

    G4String flag_SetYScanON;
    //flag_SetYScanON = "SetYScanON";
    flag_SetYScanON = "SetYScanOFF";

    G4String flag_SetScanQD1ON;
    //flag_SetScanQD1ON = "SetScanQD1ON";
    flag_SetScanQD1ON = "SetScanQD1OFF";
    //--------------------------------

    G4String flag_SetPositronON;
    //flag_SetPositronON = "SetPositronON";
    flag_SetPositronON = "SetPositronOFF";

    //-----------------------------------------------
    G4String flag_SetOneParticalON;
    flag_SetOneParticalON = "SetOneParticalON";
    //flag_SetOneParticalON = "SetOneParticalOFF";

         G4String flag_SetOneParticalON01;
         flag_SetOneParticalON01 = "SetOneParticalON01";
	 //flag_SetOneParticalON01 = "SetOneParticalOOFF1";

         G4String flag_SetOneParticalON02;
         //flag_SetOneParticalON02 = "SetOneParticalON02";
	 flag_SetOneParticalON02 = "SetOneParticalOOFF2";

         G4String flag_SetOneParticalON03;
         //flag_SetOneParticalON03 = "SetOneParticalON03";
	 flag_SetOneParticalON03 = "SetOneParticalOOFF3";

    //-----------------------------------------------


    G4String flag_SetReadFromFileON;
    //flag_SetReadFromFileON = "SetReadFromFileON";
    flag_SetReadFromFileON = "SetReadFromFileOFF";

    G4String flag_SetReadFromFileMirrorON;
    //flag_SetReadFromFileMirrorON = "SetReadFromFileMirrorON";
    flag_SetReadFromFileMirrorON = "SetReadFromFileMirrorOFF";

    G4String flag_SetScanBeamPipeON;
    //flag_SetScanBeamPipeON = "SetScanBeamPipeON";
    flag_SetScanBeamPipeON = "SetScanBeamPipeOFF";

    G4String flag_SetTestReadFromFileON;
    //flag_SetTestReadFromFileON = "SetTestReadFromFileON";
    flag_SetTestReadFromFileON = "SetTestReadFromFileOFF";

    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//------------------------------------------------------------------------------

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle;
    G4int nOfParticlesInEvent = 1;
    G4double EkinOfPartikle = 0.511*GeV;

    G4double amplOfScaning = -999.; //cm
    G4double amplOfDistortion = -999.; //cm

    G4double fWorldLength;
    G4double fWorldDX;    
    G4double fWorldDY;    


    if(flag_SetXScanON == "SetXScanON" && flag_SetYScanON == "SetYScanOFF" 
       && flag_SetXDistortionON == "SetXDistortionOFF" && flag_SetOneParticalON == "SetOneParticalOFF"){
	G4int nOfXScaning = 20; //!!!!!!!!!!! >1 
	amplOfScaning = 1.12; //cm
	nOfParticlesInEvent = nOfXScaning;
    }

    if(flag_SetYScanON == "SetYScanON" && flag_SetXScanON == "SetXScanOFF" 
       && flag_SetXDistortionON == "SetXDistortionOFF" && flag_SetOneParticalON == "SetOneParticalOFF"){
	G4int nOfYScaning = 20; //!!!!!!!!!!! >1 
	amplOfScaning = 2.5; //cm
	nOfParticlesInEvent = nOfYScaning;
    }

    if(flag_SetXDistortionON == "SetXDistortionON" && flag_SetYScanON == "SetYScanOFF" 
       && flag_SetXScanON == "SetXScanOFF" && flag_SetOneParticalON == "SetOneParticalOFF"){	
	G4int nOfDistortion = 10;
	amplOfDistortion = 1.; //cm
	nOfParticlesInEvent = nOfDistortion;
    }

    if(flag_SetOneParticalON == "SetOneParticalON" && flag_SetYScanON == "SetYScanOFF"
       && flag_SetXScanON == "SetXScanOFF" && flag_SetXDistortionON == "SetXDistortionOFF"){
	nOfParticlesInEvent = 1;
    }

    if(flag_SetScanBeamPipeON == "SetScanBeamPipeON" && flag_SetReadFromFileON == "SetReadFromFileOFF" 
       && flag_SetOneParticalON == "SetOneParticalOFF" && flag_SetXScanON == "SetXScanOFF" 
       && flag_SetXDistortionON == "SetXDistortionOFF"){
	G4int nOfYScaning = 10000;
	fWorldLength = 2.2*(length_Tube1/2+length_Tube2+length_Tube3+length_Tube4+length_Tube5)*cm;
	fWorldDX     = 3*(x_Tube5_Co_R_U + length_Tube5_Co/2*sin4_07)*cm;  
	fWorldDY     = 0.5*m;
	nOfParticlesInEvent = nOfYScaning;
    }
    
    //particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
    //particleGun->SetParticlePosition(G4ThreeVector(x_Tube5_C_L_D*cm,y_Tube5_C_L_D*cm,z_Tube5_C_L_D*cm));
    //particleGun->SetParticleMomentumDirection(G4ThreeVector(tan4_07,0.0,1.0));
    //particleGun->SetParticlePosition(G4ThreeVector((-outerRadius_QD0_T-1.)*cm,y_QD0_T_R*cm,z_QD0_T_R*cm));
    //particleGun->SetParticleMomentumDirection(G4ThreeVector(0.0,0.0,1.0));
    //particleGun->SetParticleMomentumDirection(G4ThreeVector(G4UniformRand()-0.5 ,G4UniformRand()-0.5 ,G4UniformRand()-0.5 ));
    //particleGun->SetParticlePosition(G4ThreeVector(x_Tube5_C_L_U*cm,y_Tube5_C_L_U*cm,z_Tube5_C_L_U*cm));

    if(flag_SetQD1Chek == "SetQD1ChekOff"){
	for( G4int i=0; i<nOfParticlesInEvent; i++ ){
	    if(flag_SetXDistortionON == "SetXDistortionON" && flag_SetYScanON == "SetYScanOFF"
	       && flag_SetXScanON == "SetXScanOFF" && flag_SetOneParticalON == "SetOneParticalOFF" ){
		particle = particleTable->FindParticle("e-");
		particleGun->SetParticleDefinition(particle);
		particleGun->SetParticlePosition(G4ThreeVector((x_Tube5_C_R_U + amplOfDistortion*(-0.5+G4UniformRand()))*cm,y_Tube5_C_R_U*cm,z_Tube5_C_R_U*cm));
		particleGun->SetParticleMomentumDirection(G4ThreeVector(-tan4_07,0.0,-1.0));
		particleGun->SetParticleEnergy(EkinOfPartikle);
		particleGun->GeneratePrimaryVertex(anEvent);
		if(flag_SetPositronON == "SetPositronON"){
		    particle = particleTable->FindParticle("e+");
		    particleGun->SetParticleDefinition(particle);
		    particleGun->SetParticlePosition(G4ThreeVector((x_Tube5_C_L_U + amplOfDistortion*(-0.5+G4UniformRand()))*cm,y_Tube5_C_L_U*cm,z_Tube5_C_L_U*cm));
		    particleGun->SetParticleMomentumDirection(G4ThreeVector(-tan4_07,0.0,1.0));
		    particleGun->SetParticleEnergy(EkinOfPartikle);
		    particleGun->GeneratePrimaryVertex(anEvent);
		}
	    }

	    if(flag_SetXScanON == "SetXScanON"|| flag_SetYScanON == "SetYScanON" 
	       && flag_SetXDistortionON == "SetXDistortionOFF" && flag_SetOneParticalON == "SetOneParticalOFF"){
		particle = particleTable->FindParticle("e-");
		particleGun->SetParticleDefinition(particle);
		if(flag_SetXScanON == "SetXScanON")
		    particleGun->SetParticlePosition(G4ThreeVector((x_Tube5_C_R_U + amplOfScaning*(-0.5+i*1.0/(nOfParticlesInEvent)))*cm,y_Tube5_C_R_U*cm,z_Tube5_C_R_U*cm));
		if(flag_SetYScanON == "SetYScanON")
		    particleGun->SetParticlePosition(G4ThreeVector(x_Tube5_C_R_U*cm,(y_Tube5_C_R_U + amplOfScaning*(-0.5+i*1.0/(nOfParticlesInEvent)))*cm,z_Tube5_C_R_U*cm));
		particleGun->SetParticleMomentumDirection(G4ThreeVector(-tan4_07,0.0,-1.0));
		if(flag_SetScanQD1ON == "SetScanQD1ON"){
		    if(flag_SetXScanON == "SetXScanON")
			particleGun->SetParticlePosition(G4ThreeVector((0.0 + amplOfScaning*(-0.5+i*1.0/(nOfParticlesInEvent)))*cm,0.0*cm,(z_Tube2_E_CRU + zlength_Tube2_E/2)*cm));
		    if(flag_SetYScanON == "SetYScanON")
			particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,(0.0 + amplOfScaning*(-0.5+i*1.0/(nOfParticlesInEvent)))*cm,(z_Tube2_E_CRU + zlength_Tube2_E/2)*cm));
		    particleGun->SetParticleMomentumDirection(G4ThreeVector(0.0,0.0,-1.0));
		}
		particleGun->SetParticleEnergy(EkinOfPartikle);
		particleGun->GeneratePrimaryVertex(anEvent);
		if(flag_SetPositronON == "SetPositronON"){
		    particle = particleTable->FindParticle("e+");
		    particleGun->SetParticleDefinition(particle);
		    if(flag_SetXScanON == "SetXScanON")
			particleGun->SetParticlePosition(G4ThreeVector((x_Tube5_C_L_U + amplOfScaning*(-0.5+i*1.0/(nOfParticlesInEvent)))*cm,y_Tube5_C_L_U*cm,z_Tube5_C_L_U*cm));
		    if(flag_SetYScanON == "SetYScanON")
			particleGun->SetParticlePosition(G4ThreeVector(x_Tube5_C_L_U*cm,(y_Tube5_C_L_U + amplOfScaning*(-0.5+i*1.0/(nOfParticlesInEvent)))*cm,z_Tube5_C_L_U*cm));
		    particleGun->SetParticleMomentumDirection(G4ThreeVector(tan4_07,0.0,1.0));
		    particleGun->SetParticleEnergy(EkinOfPartikle);
		    particleGun->GeneratePrimaryVertex(anEvent);
		}
	    }

	    if(flag_SetOneParticalON == "SetOneParticalON" && flag_SetXScanON == "SetXScanOFF" 
	       && flag_SetXDistortionON == "SetXDistortionOFF"){

                //-------------------------------------

		if(flag_SetOneParticalON01 == "SetOneParticalON01"){
		    particle = particleTable->FindParticle("e-");
		    particleGun->SetParticleDefinition(particle);
		    EkinOfPartikle = 510*MeV;
		    particleGun->SetParticleEnergy(EkinOfPartikle);
		    particleGun->SetParticlePosition(G4ThreeVector((x_Tube5_C_R_U+2)*cm,y_Tube5_C_R_U*cm,z_Tube5_C_R_U*cm));
		    particleGun->SetParticleMomentumDirection(G4ThreeVector(-tan4_07,0.0,-1.0));
		    particleGun->GeneratePrimaryVertex(anEvent);
		}

		if(flag_SetOneParticalON02 == "SetOneParticalON02"){
		    particle = particleTable->FindParticle("e-");
		    particleGun->SetParticleDefinition(particle);
		    EkinOfPartikle = 1*MeV;
		    particleGun->SetParticleEnergy(EkinOfPartikle);
		    particleGun->SetParticlePosition(G4ThreeVector(x_Tube2_E_CRU*cm,y_Tube2_E_CRU*cm,z_Tube2_E_CRU*cm));
		    particleGun->SetParticleMomentumDirection(G4ThreeVector(1,0.0,0.0));
		    particleGun->GeneratePrimaryVertex(anEvent);
		}

		if(flag_SetOneParticalON03 == "SetOneParticalON03"){
		    particle = particleTable->FindParticle("e-");
		    particleGun->SetParticleDefinition(particle);
		    EkinOfPartikle = 1*MeV;
		    particleGun->SetParticleEnergy(EkinOfPartikle);
		    particleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0*cm,0.0*cm));
		    particleGun->SetParticleMomentumDirection(G4ThreeVector(1,0.0,0.0));
		    particleGun->GeneratePrimaryVertex(anEvent);
		}

		//------------------------------------------------------------
//              particle = particleTable->FindParticle("e-");
//   		particleGun->SetParticleDefinition(particle);
//   		EkinOfPartikle = 10*MeV;
//   		particleGun->SetParticleEnergy(EkinOfPartikle);
// 		particleGun->SetParticlePosition(G4ThreeVector(x_Tube5_C_R_U*cm,y_Tube5_C_R_U*cm,z_Tube5_C_R_U*cm));
// 		particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
// 		particleGun->SetParticlePosition(G4ThreeVector( (x_Tube3_par2_TR + 2)*cm, y_Tube3_par2_TR*cm, (z_Tube3_par2_TR - 4)*cm));
// 		particleGun->SetParticlePosition(G4ThreeVector( (x_PbBoxForPhot-3)*cm, 0.0*cm, z_PbBoxForPhot*cm));
// 		particleGun->SetParticleMomentumDirection(G4ThreeVector(-tan4_07,0.0,1.0));
// 		particleGun->SetParticleMomentumDirection(G4ThreeVector(-tan4_07,0.0,-1.0));
// 		particleGun->SetParticleMomentumDirection(G4ThreeVector(-1.0,0.0,0.0));
// 		particleGun->SetParticleMomentumDirection(G4ThreeVector(G4UniformRand()-0.5,G4UniformRand()-0.5,G4UniformRand()-0.5));	
//     	        particleGun->GeneratePrimaryVertex(anEvent);
		//-----------------------------------
                // Benoit check 
		// X=-2.85 cm
		// Y=0.
		// Z=-137
		// With E = 0.510 GeV
		//          phi = 180
		//          theta = 176
//     		particle = particleTable->FindParticle("e-");
//     		particleGun->SetParticleDefinition(particle);
//     		EkinOfPartikle = 20*MeV;
//     		particleGun->SetParticleEnergy(EkinOfPartikle);
//    		particleGun->SetParticlePosition(G4ThreeVector(-2.85*cm, 0.0, 137*cm));
//     		particleGun->SetParticleMomentumDirection(G4ThreeVector(-tan(4*Pi/180.),0.0,1.0));
//     		particleGun->GeneratePrimaryVertex(anEvent);
		//-----------------------------------

		//-----------------------------------
                // Benoit check 
//    		particle = particleTable->FindParticle("e-");
//    		particleGun->SetParticleDefinition(particle);
//    		EkinOfPartikle = 0.5*MeV;
//    		particleGun->SetParticleEnergy(EkinOfPartikle);
//   		particleGun->SetParticlePosition(G4ThreeVector((-2.85 + 5*tan(4*Pi/180.))*cm, 0.0, (-137 + 5)*cm));
//    		particleGun->SetParticleMomentumDirection(G4ThreeVector(-tan(4*Pi/180.),0.0,-1.0));
//    		particleGun->GeneratePrimaryVertex(anEvent);
		//-----------------------------------

		//-----------------------------------
                // Benoit check 
//  		particle = particleTable->FindParticle("e-");
//   		particleGun->SetParticleDefinition(particle);
//   		EkinOfPartikle = 0.511*GeV;
//   		particleGun->SetParticleEnergy(EkinOfPartikle);

  		//particleGun->SetParticlePosition(G4ThreeVector(xP1*cm, 0.0, zP1*cm));
  		//particleGun->SetParticleMomentumDirection(G4ThreeVector((x_WinPhot - xP1),0.0,(z_WinPhot - zP1)));
  		//particleGun->GeneratePrimaryVertex(anEvent);

//              particleGun->SetParticlePosition(G4ThreeVector(xP2*cm, 0.0, zP2*cm));
//  		particleGun->SetParticleMomentumDirection(G4ThreeVector((x_WinPhot - xP2),0.0,(z_WinPhot - zP2)));
//  		particleGun->GeneratePrimaryVertex(anEvent);

//  		particleGun->SetParticlePosition(G4ThreeVector(xP3*cm, 0.0, zP3*cm));
//  		particleGun->SetParticleMomentumDirection(G4ThreeVector((x_WinPhot - xP3),0.0,(z_WinPhot - zP3)));
//  		particleGun->GeneratePrimaryVertex(anEvent);

//   		particleGun->SetParticlePosition(G4ThreeVector(xP4*cm, 0.0, -zP4*cm));
//   		particleGun->SetParticleMomentumDirection(G4ThreeVector((x_WinPhot - xP4),0.0,-(z_WinPhot - zP4)));
//   		particleGun->GeneratePrimaryVertex(anEvent);

//  		particleGun->SetParticlePosition(G4ThreeVector(xP5*cm, 0.0, zP5*cm));
//  		particleGun->SetParticleMomentumDirection(G4ThreeVector((x_WinPhot - xP5),0.0,(z_WinPhot - zP5)));
//  		particleGun->GeneratePrimaryVertex(anEvent);

//  		particleGun->SetParticlePosition(G4ThreeVector(xP6*cm, 0.0, zP6*cm));
//  		particleGun->SetParticleMomentumDirection(G4ThreeVector((x_WinPhot - xP6),0.0,(z_WinPhot - zP6)));
//  		particleGun->GeneratePrimaryVertex(anEvent);

		//print out the of the 6 points
// 		G4cout<<setw(9)<<" x1 = "<<setw(10)<<xP1<<setw(9)<<" z1 = "<<setw(10)<<zP1<<endl;
// 		G4cout<<setw(9)<<"Px1 = "<<setw(10)<<(x_WinPhot - xP1)/(z_WinPhot - zP1)<<setw(9)<<"Pz1 = "<<setw(10)<<1.<<endl;

// 		G4cout<<setw(9)<<" x2 = "<<setw(10)<<xP2<<setw(9)<<" z2 = "<<setw(10)<<zP2<<endl;
// 		G4cout<<setw(9)<<"Px2 = "<<setw(10)<<(x_WinPhot - xP2)/(z_WinPhot - zP2)<<setw(9)<<"Pz2 = "<<setw(10)<<1.<<endl;

// 		G4cout<<setw(9)<<" x3 = "<<setw(10)<<xP3<<setw(9)<<" z3 = "<<setw(10)<<zP3<<endl;
// 		G4cout<<setw(9)<<"Px3 = "<<setw(10)<<(x_WinPhot - xP3)/(z_WinPhot - zP3)<<setw(9)<<"Pz3 = "<<setw(10)<<1.<<endl;

// 		G4cout<<setw(9)<<" x4 = "<<setw(10)<<xP4<<setw(4)<<" z4 = "<<setw(10)<<zP4<<endl;
// 		G4cout<<setw(9)<<"Px4 = "<<setw(10)<<(x_WinPhot - xP4)/(z_WinPhot - zP4)<<setw(9)<<"Pz4 = "<<setw(10)<<1.<<endl;

// 		G4cout<<setw(9)<<" x5 = "<<setw(10)<<xP5<<setw(9)<<" z5 = "<<setw(10)<<zP5<<endl;
// 		G4cout<<setw(9)<<"Px5 = "<<setw(10)<<(x_WinPhot - xP5)/(z_WinPhot - zP5)<<setw(9)<<"Pz5 = "<<setw(10)<<1.<<endl;

// 		G4cout<<setw(9)<<" x6 = "<<setw(10)<<xP6<<setw(9)<<" z6 = "<<setw(10)<<zP6<<endl;
// 		G4cout<<setw(9)<<"Px6 = "<<setw(10)<<(x_WinPhot - xP6)/(z_WinPhot - zP6)<<setw(9)<<"Pz6 = "<<setw(10)<<1.<<endl;

		//-----------------------------------

		//-----------------------------------
                // Benoit check 
//   		particle = particleTable->FindParticle("e+");
//   		particleGun->SetParticleDefinition(particle);
//   		EkinOfPartikle = 0.511*GeV;
//   		particleGun->SetParticleEnergy(EkinOfPartikle);
//   		particleGun->SetParticlePosition(G4ThreeVector(xP1*cm, 0.0, zP1*cm));
//   		particleGun->SetParticleMomentumDirection(G4ThreeVector((x_WinPhot - xP1),0.0,(z_WinPhot - zP1)));
//   		particleGun->GeneratePrimaryVertex(anEvent);
		//-----------------------------------

		//-----------------------------------
		// field chack !!!!!
		//-----------------------------------
/*
		G4double xfc = x_Tube4_R_U;
		G4double yfc = y_Tube4_R_U;
		G4double zfc = z_Tube4_R_U;

		particle = particleTable->FindParticle("e-");
		particleGun->SetParticleDefinition(particle);
   		EkinOfPartikle = 0.511*GeV;
   		particleGun->SetParticleEnergy(EkinOfPartikle);
		particleGun->SetParticlePosition(G4ThreeVector(xfc*cm,yfc*cm,zfc*cm));
		particleGun->SetParticleMomentumDirection(G4ThreeVector(-tan4_07,0.0,-1.0));
		particleGun->GeneratePrimaryVertex(anEvent);
*/
		if(flag_SetPositronON == "SetPositronON"){
		    particle = particleTable->FindParticle("e+");
		    particleGun->SetParticleDefinition(particle);
		    particleGun->SetParticlePosition(G4ThreeVector(x_Tube5_C_L_U*cm,y_Tube5_C_L_U*cm,z_Tube5_C_L_U*cm));
		    particleGun->SetParticleMomentumDirection(G4ThreeVector(-tan4_07,0.0,1.0));
		    particleGun->SetParticleEnergy(EkinOfPartikle);
		    particleGun->GeneratePrimaryVertex(anEvent);
		}
	    }

	    if( flag_SetReadFromFileON == "SetReadFromFileON" && flag_SetOneParticalON == "SetOneParticalOFF" 
	       && flag_SetXScanON == "SetXScanOFF" && flag_SetXDistortionON == "SetXDistortionOFF"){
		//reading format of the labtouschek.txt file
		G4float x, y, z, px, py, pz, fr;
		if(myfile.is_open()){
		    myfile >> x>> y>> z>> px>> py>> pz>>fr;
		}
		else{
		    G4cout<<" ExN02PrimaryGeneratorAction.cc  "<<G4endl;
		    G4cout<<" ExN02PrimaryGeneratorAction::ExN02PrimaryGeneratorAction( ExN02DetectorConstruction) "<<G4endl;
		    G4cout<<" ERROR : file "<< "labdata.txt"<<"not open!!!"<<endl;
		    G4cout<<" ------------------------------------------- "<<G4endl;
		}
		particle = particleTable->FindParticle("e-");
		particleGun->SetParticleDefinition(particle);
		particleGun->SetParticlePosition(G4ThreeVector(x*cm,y*cm,z*cm));
		//G4cout<<" x = "<< x<<" y = "<< y<<" z = "<< z<<G4endl;
		particleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
		EkinOfPartikle = sqrt(px*px + py*py + pz*pz + 0.000511*0.000511)*GeV - 0.511*MeV;	
		particleGun->SetParticleEnergy(EkinOfPartikle);
		SetEkin(EkinOfPartikle);
		SetFr(fr);
		//G4cout<<" EkinOfPartikle = "<< EkinOfPartikle<<"(MeV)"<<G4endl;
		particleGun->GeneratePrimaryVertex(anEvent);
	    }

	    if( flag_SetReadFromFileMirrorON == "SetReadFromFileMirrorON" 
		&& flag_SetOneParticalON == "SetOneParticalOFF" && flag_SetXScanON == "SetXScanOFF" 
		&& flag_SetXDistortionON == "SetXDistortionOFF" && flag_SetReadFromFileON == "SetReadFromFileOFF"){
		//reading format of the labtouschek.txt file
		G4float x, y, z, px, py, pz, E1,E2,fr;
		if(myfile.is_open()){
		    myfile >> x>> y>> z>> px>> py>> pz>>E1>>E2>>fr;
		}
		else{
		    G4cout<<" ExN02PrimaryGeneratorAction.cc  "<<G4endl;
		    G4cout<<" ExN02PrimaryGeneratorAction::ExN02PrimaryGeneratorAction( ExN02DetectorConstruction) "<<G4endl;
		    G4cout<<" ERROR : file "<< "labdata.txt"<<"not open!!!"<<endl;
		    G4cout<<" ------------------------------------------- "<<G4endl;
		}
		particle = particleTable->FindParticle("e-");
		particleGun->SetParticleDefinition(particle);
		particleGun->SetParticlePosition(G4ThreeVector(x,y,z));
		//G4cout<<" x = "<< x<<" y = "<< y<<" z = "<< z<<G4endl;
		particleGun->SetParticleMomentumDirection(G4ThreeVector(-px,-py,-pz));
		EkinOfPartikle = E1*MeV;
		if((E1-E2)/E1 > 0.00001 ){
		    G4cout<<"Error in mirror touschek !!!!!!!!!!!!"<<G4endl;
		    G4cout<<"E1 = "<<E1<<G4endl;
		    G4cout<<"E2 = "<<E2<<G4endl;
		    G4cout<<(E1-E2)/E1<<G4endl;
		}
		particleGun->SetParticleEnergy(EkinOfPartikle);
		SetEkin(EkinOfPartikle);
		SetFr(fr);
		//G4cout<<" EkinOfPartikle = "<< EkinOfPartikle<<"(MeV)"<<G4endl;
		particleGun->GeneratePrimaryVertex(anEvent);
	    }



	    if(flag_SetScanBeamPipeON == "SetScanBeamPipeON" && flag_SetReadFromFileON == "SetReadFromFileOFF" 
	       && flag_SetOneParticalON == "SetOneParticalOFF" && flag_SetXScanON == "SetXScanOFF" 
	       && flag_SetXDistortionON == "SetXDistortionOFF"){

		particle = particleTable->FindParticle("e-");
		particleGun->SetParticleDefinition(particle);
		particleGun->SetParticlePosition(G4ThreeVector(fWorldDX/2-1,0.0*cm,(fWorldLength-10.)*(i*1./nOfParticlesInEvent -1./2)));
		particleGun->SetParticleMomentumDirection(G4ThreeVector(-1.,0.,0.));
		EkinOfPartikle = 0.5*MeV;	
		particleGun->SetParticleEnergy(EkinOfPartikle);
		particleGun->GeneratePrimaryVertex(anEvent);

		particle = particleTable->FindParticle("e-");
		particleGun->SetParticleDefinition(particle);
		particleGun->SetParticlePosition(G4ThreeVector(-fWorldDX/2+1,0.0*cm,(fWorldLength-10.)*(i*1./nOfParticlesInEvent -1./2)));
		particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
		EkinOfPartikle = 0.5*MeV;	
		particleGun->SetParticleEnergy(EkinOfPartikle);
		particleGun->GeneratePrimaryVertex(anEvent);

		particle = particleTable->FindParticle("e-");
		particleGun->SetParticleDefinition(particle);
		particleGun->SetParticlePosition(G4ThreeVector(0.0,0.0*cm,(fWorldLength-10.)*(i*1./nOfParticlesInEvent -1./2)));
		particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
		EkinOfPartikle = 0.5*MeV;	
		particleGun->SetParticleEnergy(EkinOfPartikle);
		particleGun->GeneratePrimaryVertex(anEvent);

		particle = particleTable->FindParticle("e-");
		particleGun->SetParticleDefinition(particle);
		particleGun->SetParticlePosition(G4ThreeVector(0.0,0.0*cm,(fWorldLength-10.)*(i*1./nOfParticlesInEvent -1./2)));
		particleGun->SetParticleMomentumDirection(G4ThreeVector(-1.,0.,0.));
		EkinOfPartikle = 0.5*MeV;	
		particleGun->SetParticleEnergy(EkinOfPartikle);
		particleGun->GeneratePrimaryVertex(anEvent);	
       	    }

	    if( flag_SetTestReadFromFileON == "SetTestReadFromFileON" && flag_SetScanBeamPipeON == "SetScanBeamPipeOFF" 
		&& flag_SetReadFromFileON == "SetReadFromFileOFF" && flag_SetOneParticalON == "SetOneParticalOFF"
		&& flag_SetXScanON == "SetXScanOFF" && flag_SetXDistortionON == "SetXDistortionOFF"){
		
		//reading format of the labdata.txt file
		G4float x, y, z, px, py, pz;
		if(myTestfile.is_open()){
		    myTestfile >> x>> y>> z>> px>> py>> pz;
		}
		else{
		    G4cout<<" ExN02PrimaryGeneratorAction.cc  "<<G4endl;
		    G4cout<<" ExN02PrimaryGeneratorAction::ExN02PrimaryGeneratorAction( ExN02DetectorConstruction) "<<G4endl;
		    G4cout<<" ERROR : file "<< "labdataTest.txt"<<"not open!!!"<<endl;
		    G4cout<<" ------------------------------------------- "<<G4endl;
		}

		particle = particleTable->FindParticle("e-");
		particleGun->SetParticleDefinition(particle);
		particleGun->SetParticlePosition(G4ThreeVector(x*cm,y*cm,z*cm));
		particleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
		EkinOfPartikle = (sqrt( sqr(px) + sqr(py) + sqr(pz) + 0.511*0.511) - 0.511)*MeV;	
		particleGun->SetParticleEnergy(EkinOfPartikle);
		particleGun->GeneratePrimaryVertex(anEvent);
	   
	    }
	}
    }

    if(flag_SetQD1Chek == "SetQD1ChekOn"){
/*	
	G4double x;
	G4double y;
	G4double z;

	G4double x_; //cm
	G4double y_; //cm
	G4double z_; //cm

	G4double z_max_QD1_R_U_;
	G4double x_max_QD1_R_U_;
	G4double z_min_QD1_R_U_;
	G4double x_min_QD1_R_U_;

	G4double z_max_QD1_R_D_;
	G4double x_max_QD1_R_D_;
	G4double z_min_QD1_R_D_;
	G4double x_min_QD1_R_D_;

	G4double z_max_QD1_L_U_;
	G4double x_max_QD1_L_U_;
	G4double z_min_QD1_L_U_;
	G4double x_min_QD1_L_U_;

	G4double z_max_QD1_L_D_;
	G4double x_max_QD1_L_D_;
	G4double z_min_QD1_L_D_;
	G4double x_min_QD1_L_D_;
*/
	//for( G4int i=0; i<nOfParticlesInEvent; i++ ){
	    
	    //---------------
	    //QD0
	    //---------------

	    //R
	    /*
	      x = x_min_QD0_R + (x_max_QD0_R - x_min_QD0_R)*G4UniformRand();
	      y = y_min_QD0_R + (y_max_QD0_R - y_min_QD0_R)*G4UniformRand();
	      z = z_min_QD0_R + (z_max_QD0_R - z_min_QD0_R)*G4UniformRand();
	      
	      if( (z*cm < z_max_QD0_R*cm) && (z*cm > z_min_QD0_R*cm) && ((sqr(x*cm)+sqr(y*cm))<sqr(innerRadius_QD0_T*cm)) ){
	      particleGun->SetParticleDefinition(particle);
	      particleGun->SetParticlePosition(G4ThreeVector(x*cm, y*cm, z*cm));
	      particleGun->SetParticleMomentumDirection(G4ThreeVector((G4UniformRand()-0.5),0.0,0.0));
	      particleGun->SetParticleEnergy(0.05*MeV);
	      particleGun->GeneratePrimaryVertex(anEvent);
	      }
	      else{
	      particleGun->SetParticleDefinition(particle);
	      particleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0, 0.0));
	      particleGun->SetParticleMomentumDirection(G4ThreeVector((G4UniformRand()-0.5),0.0,0.0));
	      particleGun->SetParticleEnergy(0.05*MeV);
	      particleGun->GeneratePrimaryVertex(anEvent);
	      }
	    */
	    
	    //L
	    /*
	      x = x_min_QD0_L + (x_max_QD0_L - x_min_QD0_L)*G4UniformRand();
	      y = y_min_QD0_L + (y_max_QD0_L - y_min_QD0_L)*G4UniformRand();
	      z = z_min_QD0_L + (z_max_QD0_L - z_min_QD0_L)*G4UniformRand();
	      
	      if( (z*cm > z_max_QD0_L*cm) && (z*cm < z_min_QD0_L*cm) && ((sqr(x*cm)+sqr(y*cm))<sqr(innerRadius_QD0_T*cm)) ){
	      particleGun->SetParticleDefinition(particle);
	      particleGun->SetParticlePosition(G4ThreeVector(x*cm, y*cm, z*cm));
	      particleGun->SetParticleMomentumDirection(G4ThreeVector((G4UniformRand()-0.5),0.0,0.0));
	      particleGun->SetParticleEnergy(0.51*GeV);
	      particleGun->GeneratePrimaryVertex(anEvent);
	      }
	      else{
	      particleGun->SetParticleDefinition(particle);
	      particleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0, 0.0));
	      particleGun->SetParticleMomentumDirection(G4ThreeVector((G4UniformRand()-0.5),0.0,0.0));
	      particleGun->SetParticleEnergy(0.51*GeV);
	      particleGun->GeneratePrimaryVertex(anEvent);
	      }
	    */


	    //----------------
	    //QD1
            //----------------

	    //R U
	    /*
	      x = x_min_QD1_R_U + (x_max_QD1_R_U - x_min_QD1_R_U)*G4UniformRand();
	      y = y_min_QD1_R_U + (y_max_QD1_R_U - y_min_QD1_R_U)*G4UniformRand();
	      z = z_min_QD1_R_U + (z_max_QD1_R_U - z_min_QD1_R_U)*G4UniformRand();
	      
	      z_max_QD1_R_U_ = RotationZ(z_maxAxis_QD1_R_U,x_maxAxis_QD1_R_U,1);
	      x_max_QD1_R_U_ = RotationX(z_maxAxis_QD1_R_U,x_maxAxis_QD1_R_U,1);
	      z_min_QD1_R_U_ = RotationZ(z_minAxis_QD1_R_U,x_minAxis_QD1_R_U,1);
	      x_min_QD1_R_U_ = RotationX(z_minAxis_QD1_R_U,x_minAxis_QD1_R_U,1);
	      
	      x_ = RotationX(z,x,1);
	      y_ = y;
	      z_ = RotationZ(z,x,1);
	      
	      if( ((x_max_QD1_R_U_-x_min_QD1_R_U_)*(x_max_QD1_R_U_-x_min_QD1_R_U_))>0.01 ){
	      G4cout<<"ExN02PrimaryGeneratorAction.cc-------------------"<<G4endl;
	      G4cout<<" void ExN02PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)"<<G4endl;
	      G4cout<<"!!!!!!!!!!!!!ERORR check rotation!!!!!!!!!!!!!!!!"<<G4endl;
	      G4cout<<" x_max_QD1_R_U_ = "<< x_max_QD1_R_U_ <<G4endl;
	      G4cout<<" x_min_QD1_R_U_ = "<< x_min_QD1_R_U_ <<G4endl;
	      G4cout<<"-------------------------------------------------"<<G4endl;
	      }
	      else if( (z_*cm < z_max_QD1_R_U_*cm) && (z_*cm > z_min_QD1_R_U_*cm) && ((sqr(x_*cm-x_max_QD1_R_U_*cm)+sqr(y_*cm))<sqr(innerRadius_QD1*cm)) ){
	      particleGun->SetParticleDefinition(particle);
	      particleGun->SetParticlePosition(G4ThreeVector(x*cm, y*cm, z*cm));
	      particleGun->SetParticleMomentumDirection(G4ThreeVector(sin4_07*(G4UniformRand()-0.5),0.0,0.0));
	      particleGun->SetParticleEnergy(0.05*MeV);
	      particleGun->GeneratePrimaryVertex(anEvent);
	      }
	    */
	    
	    //R D
	    /*
	      x = x_min_QD1_R_D + (x_max_QD1_R_D - x_min_QD1_R_D)*G4UniformRand();
	      y = y_min_QD1_R_D + (y_max_QD1_R_D - y_min_QD1_R_D)*G4UniformRand();
	      z = z_min_QD1_R_D + (z_max_QD1_R_D - z_min_QD1_R_D)*G4UniformRand();
	      
	      z_max_QD1_R_D_ = RotationZ(z_maxAxis_QD1_R_D,x_maxAxis_QD1_R_D,-1);
	      x_max_QD1_R_D_ = RotationX(z_maxAxis_QD1_R_D,x_maxAxis_QD1_R_D,-1);
	      z_min_QD1_R_D_ = RotationZ(z_minAxis_QD1_R_D,x_minAxis_QD1_R_D,-1);
	      x_min_QD1_R_D_ = RotationX(z_minAxis_QD1_R_D,x_minAxis_QD1_R_D,-1);
	      
	      x_ = RotationX(z,x,-1);
	      y_ = y;
	      z_ = RotationZ(z,x,-1);
	      
	      if( ((x_max_QD1_R_D_-x_min_QD1_R_D_)*(x_max_QD1_R_D_-x_min_QD1_R_D_))>0.01 ){
	      G4cout<<"ExN02PrimaryGeneratorAction.cc-------------------"<<G4endl;
	      G4cout<<" void ExN02PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)"<<G4endl;
	      G4cout<<"!!!!!!!!!!!!!ERORR check rotation!!!!!!!!!!!!!!!!"<<G4endl;
	      G4cout<<"-------------------------------------------------"<<G4endl;
	      }
	      else if( (z_*cm < z_max_QD1_R_D_*cm) && (z_*cm > z_min_QD1_R_D_*cm) && ((sqr(x_*cm-x_max_QD1_R_D_*cm)+sqr(y_*cm))<sqr(innerRadius_QD1*cm)) ){
	      particleGun->SetParticleDefinition(particle);
	      particleGun->SetParticlePosition(G4ThreeVector(x*cm, y*cm, z*cm));
	      particleGun->SetParticleMomentumDirection(G4ThreeVector(sin4_07*(G4UniformRand()-0.5),0.0,0.0));
	      particleGun->SetParticleEnergy(0.05*MeV);
	      particleGun->GeneratePrimaryVertex(anEvent);
	      }
	    */	   

	    //L U
	    /*
	      x = x_min_QD1_L_U + (x_max_QD1_L_U - x_min_QD1_L_U)*G4UniformRand();
	      y = y_min_QD1_L_U + (y_max_QD1_L_U - y_min_QD1_L_U)*G4UniformRand();
	      z = z_min_QD1_L_U + (z_max_QD1_L_U - z_min_QD1_L_U)*G4UniformRand();
	      
	      z_max_QD1_L_U_ = RotationZ(z_maxAxis_QD1_L_U,x_maxAxis_QD1_L_U,-1);
	      x_max_QD1_L_U_ = RotationX(z_maxAxis_QD1_L_U,x_maxAxis_QD1_L_U,-1);
	      z_min_QD1_L_U_ = RotationZ(z_minAxis_QD1_L_U,x_minAxis_QD1_L_U,-1);
	      x_min_QD1_L_U_ = RotationX(z_minAxis_QD1_L_U,x_minAxis_QD1_L_U,-1);
	      
	      x_ = RotationX(z,x,-1);
	      y_ = y;
	      z_ = RotationZ(z,x,-1);
	      
	      if( ((x_max_QD1_L_U_-x_min_QD1_L_U_)*(x_max_QD1_L_U_-x_min_QD1_L_U_))>0.01 ){
	      G4cout<<"ExN02PrimaryGeneratorAction.cc-------------------"<<G4endl;
	      G4cout<<" void ExN02PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)"<<G4endl;
	      G4cout<<"!!!!!!!!!!!!!ERORR check rotation!!!!!!!!!!!!!!!!"<<G4endl;
	      G4cout<<"-------------------------------------------------"<<G4endl;
	      }
	      else if( (z_*cm > z_max_QD1_L_U_*cm) && (z_*cm < z_min_QD1_L_U_*cm) && ((sqr(x_*cm-x_max_QD1_L_U_*cm)+sqr(y_*cm))<sqr(innerRadius_QD1*cm)) ){
	      particleGun->SetParticleDefinition(particle);
	      particleGun->SetParticlePosition(G4ThreeVector(x*cm, y*cm, z*cm));
	      particleGun->SetParticleMomentumDirection(G4ThreeVector(sin4_07*(G4UniformRand()-0.5),0.0,0.0));
	      particleGun->SetParticleEnergy(0.05*MeV);
	      particleGun->GeneratePrimaryVertex(anEvent);
	      }   
	    */	 

	    //L D
	    /*
	      x = x_min_QD1_L_D + (x_max_QD1_L_D - x_min_QD1_L_D)*G4UniformRand();
	      y = y_min_QD1_L_D + (y_max_QD1_L_D - y_min_QD1_L_D)*G4UniformRand();
	      z = z_min_QD1_L_D + (z_max_QD1_L_D - z_min_QD1_L_D)*G4UniformRand();
	      
	      z_max_QD1_L_D_ = RotationZ(z_maxAxis_QD1_L_D,x_maxAxis_QD1_L_D,1);
	      x_max_QD1_L_D_ = RotationX(z_maxAxis_QD1_L_D,x_maxAxis_QD1_L_D,1);
	      z_min_QD1_L_D_ = RotationZ(z_minAxis_QD1_L_D,x_minAxis_QD1_L_D,1);
	      x_min_QD1_L_D_ = RotationX(z_minAxis_QD1_L_D,x_minAxis_QD1_L_D,1);
	      
	      x_ = RotationX(z,x,1);
	      y_ = y;
	      z_ = RotationZ(z,x,1);
	      
	      if( ((x_max_QD1_L_D_-x_min_QD1_L_D_)*(x_max_QD1_L_D_-x_min_QD1_L_D_))>0.01 ){
	      G4cout<<"ExN02PrimaryGeneratorAction.cc-------------------"<<G4endl;
	      G4cout<<" void ExN02PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)"<<G4endl;
	      G4cout<<"!!!!!!!!!!!!!ERORR check rotation!!!!!!!!!!!!!!!!"<<G4endl;
	      G4cout<<"-------------------------------------------------"<<G4endl;
	      }
	      else if( (z_*cm > z_max_QD1_L_D_*cm) && (z_*cm < z_min_QD1_L_D_*cm) && ((sqr(x_*cm-x_max_QD1_L_D_*cm)+sqr(y_*cm))<sqr(innerRadius_QD1*cm)) ){
	      particleGun->SetParticleDefinition(particle);
	      particleGun->SetParticlePosition(G4ThreeVector(x*cm, y*cm, z*cm));
	      particleGun->SetParticleMomentumDirection(G4ThreeVector(sin4_07*(G4UniformRand()-0.5),0.0,0.0));
	      particleGun->SetParticleEnergy(0.05*MeV);
	      particleGun->GeneratePrimaryVertex(anEvent);
	      }
	    */   
	    //}
    }

    //-----------------------------------------------------------------------------------  
	   
    //G4double position = 0.1*(myDetector->GetWorldFullLength());
    //G4double position = 0.;//mm
    //G4cout<<" ExN02PrimaryGeneratorAction.cc  "<<G4endl;
    //G4cout<<" ExN02PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) "<<G4endl;
    //G4cout<<" (myDetector->GetWorldFullLength()) "<< (myDetector->GetWorldFullLength())<<G4endl;    
    //G4cout<<" ------------------------------------------- "<<G4endl;
    
    //particleGun->SetParticlePosition(G4ThreeVector(x*cm,y*cm,z*cm));
    //particleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
    
    //particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,64.0*cm));
    //particleGun->SetParticleMomentumDirection(G4ThreeVector( (G4UniformRand()-0.5) ,0. , (G4UniformRand()-0.5) ));
    
    //particleGun->GeneratePrimaryVertex(anEvent);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double ExN02PrimaryGeneratorAction::RotationZ(G4double z, G4double x, G4int Ind){
     G4double cos4_07 = 0.997478082176520564;
     G4double sin4_07 = 0.0709751757831599134;

     if(Ind == 1){
	 return z*cos4_07+x*sin4_07;
     }

     if(Ind == -1){
	 return z*cos4_07-x*sin4_07;
     }
}

G4double ExN02PrimaryGeneratorAction::RotationX(G4double z, G4double x, G4int Ind){
     G4double cos4_07 = 0.997478082176520564;
     G4double sin4_07 = 0.0709751757831599134;

     if(Ind ==1){
	 return -z*sin4_07+x*cos4_07;
     }

     if(Ind ==-1){
	 return z*sin4_07+x*cos4_07;
     }

}
