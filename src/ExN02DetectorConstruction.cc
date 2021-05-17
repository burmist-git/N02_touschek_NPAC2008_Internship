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
// *              es                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all termVs of the Geant4 Software license.         *
// ********************************************************************
//   
//
// $Id: ExN02DetectorConstruction.cc,v 1.20 2007/10/17 08:50:35 gcosmo Exp $
// GEANT4 tag $Name: geant4-09-01-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN02DetectorConstruction.hh"

#include "ExN02DetectorMessenger.hh"
#include "ExN02ChamberParameterisation.hh"

#include "ExN02TrackerSD.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Trd.hh"
#include "G4Orb.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4SDManager.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4UserLimits.hh"
 
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"

#include "DetectorConstant.hh"

#include "ExN02SenDetShower_L.hh"

#include "ExN02DetectorConstruction_World.hh"
#include "ExN02DetectorConstruction_QD0.hh"
#include "ExN02DetectorConstruction_Tube.hh"
#include "ExN02DetectorConstruction_Cone.hh"
#include "ExN02DetectorConstruction_VTube.hh"
#include "ExN02DetectorConstruction_Box.hh"
#include "ExN02MaterialConstruction.hh"
#include "ExN02DetectorConstruction_Sp.hh"
#include "ExN02SensitiveDetector.hh"

#include "G4Region.hh"

//magnetic field
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4ClassicalRK4.hh"
#include "ExN02MagneticField.hh"
//----------------------------------

//coordinat transformation
#define RotZm(z,x) (z*cos4_07+x*sin4_07)  // rotation anti clock
#define RotXm(z,x) (-z*sin4_07+x*cos4_07) // rotation anti clock

#define RotZp(z,x) (z*cos4_07-x*sin4_07)  // rotation clock
#define RotXp(z,x) (z*sin4_07+x*cos4_07)  // rotation clock

#define RotZTube2m(z,x) (z*cos2_87+x*sin2_87)  // rotation anti clock
#define RotXTube2m(z,x) (-z*sin2_87+x*cos2_87) // rotation anti clock

#define RotZTube2p(z,x) (z*cos2_87-x*sin2_87)  // rotation clock
#define RotXTube2p(z,x) (z*sin2_87+x*cos2_87)  // rotation clock

#define RotZoldP(z0,x0,dz,dx) ( (RotZm(z0,x0) + dz)*cos4_07 - (RotXm(z0,x0) + dx)*sin4_07)
#define RotXoldP(z0,x0,dz,dx) ( (RotZm(z0,x0) + dz)*sin4_07 + (RotXm(z0,x0) + dx)*cos4_07)

#define RotZoldM(z0,x0,dz,dx) ( (RotZp(z0,x0) + dz)*cos4_07 + (RotXp(z0,x0) + dx)*sin4_07)
#define RotXoldM(z0,x0,dz,dx) (-(RotZp(z0,x0) + dz)*sin4_07 + (RotXp(z0,x0) + dx)*cos4_07)

#define RotZoldTube2P(z0,x0,dz,dx) ( (RotZTube2m(z0,x0) + dz)*cos2_87 - (RotXTube2m(z0,x0) + dx)*sin2_87)
#define RotXoldTube2P(z0,x0,dz,dx) ( (RotZTube2m(z0,x0) + dz)*sin2_87 + (RotXTube2m(z0,x0) + dx)*cos2_87)

#define RotZoldTube2M(z0,x0,dz,dx) ( (RotZTube2p(z0,x0) + dz)*cos2_87 + (RotXTube2p(z0,x0) + dx)*sin2_87)
#define RotXoldTube2M(z0,x0,dz,dx) (-(RotZTube2p(z0,x0) + dz)*sin2_87 + (RotXTube2p(z0,x0) + dx)*cos2_87)

#define RotXTube3m(z,x) (-z*sinAngleT3+x*cosAngleT3) // rotation anti clock

//------------


using namespace DetConst;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

     //fTargetLength(0.), fTrackerLength(0.),
     //NbOfChambers(0),  ChamberWidth(0.),  ChamberSpacing(0.),


     //solidTarget(0), logicTarget(0), physiTarget(0), 
     //solidChamber(0),logicChamber(0),physiChamber(0), 
     //TargetMater(0), ChamberMater(0),chamberParam(0),
     //stepLimit(0), 

 
ExN02DetectorConstruction::ExN02DetectorConstruction()
    :solidWorld(0),  logicWorld(0),  physiWorld(0),

     stepLimit(0), 
     fpMagField(0),
     fWorldLength(0.),

     solidBP1(0),logicBP1(0),physiBP1(0),  
     solidBP1_v(0),logicBP1_v(0),physiBP1_v(0), 

     solidTube2_C_R(0), logicTube2_C_R(0), physiTube2_C_R(0),
     solidTube2_C_R_v(0), logicTube2_C_R_v(0), physiTube2_C_R_v(0), 
     solidTube2_C_L(0), logicTube2_C_L(0), physiTube2_C_L(0),
     solidTube2_C_L_v(0), logicTube2_C_L_v(0), physiTube2_C_L_v(0), 
  
     solidTube2_E_CR(0), logicTube2_E_CR(0), physiTube2_E_CR(0),
     solidTube2_E_CR_v(0), logicTube2_E_CR_v(0), physiTube2_E_CR_v(0),
     solidTube2_E_CRU(0), logicTube2_E_CRU(0), physiTube2_E_CRU(0),
     solidTube2_E_CRU_v(0), logicTube2_E_CRU_v(0), physiTube2_E_CRU_v(0),
     solidTube2_E_TRRU(0), logicTube2_E_TRRU(0), physiTube2_E_TRRU(0),
     solidTube2_E_TRRD(0), logicTube2_E_TRRD(0), physiTube2_E_TRRD(0),
     solidTube2_E_TRR_v(0), logicTube2_E_TRR_v(0), physiTube2_E_TRR_v(0),

     solidTube2_E_CL(0), logicTube2_E_CL(0), physiTube2_E_CL(0),
     solidTube2_E_CL_v(0), logicTube2_E_CL_v(0), physiTube2_E_CL_v(0),
     solidTube2_E_CLU(0), logicTube2_E_CLU(0), physiTube2_E_CLU(0),
     solidTube2_E_CLU_v(0), logicTube2_E_CLU_v(0), physiTube2_E_CLU_v(0),
     solidTube2_E_TRLU(0), logicTube2_E_TRLU(0), physiTube2_E_TRLU(0),
     solidTube2_E_TRLD(0), logicTube2_E_TRLD(0), physiTube2_E_TRLD(0),
     solidTube2_E_TRL_v(0), logicTube2_E_TRL_v(0), physiTube2_E_TRL_v(0),

     solidTube3_TR1_R(0), logicTube3_TR1_R(0), physiTube3_TR1_R(0),
     solidTube3_TR2_R(0), logicTube3_TR2_R(0), physiTube3_TR2_R(0), 
     solidTube3_TU_R_U(0), logicTube3_TU_R_U(0), physiTube3_TU_R_U(0),
     solidTube3_TU_R_D(0), logicTube3_TU_R_D(0), physiTube3_TU_R_D(0),

     solidTube3_TR1_L(0), logicTube3_TR1_L(0), physiTube3_TR1_L(0),
     solidTube3_TR2_L(0), logicTube3_TR2_L(0), physiTube3_TR2_L(0), 
     solidTube3_TU_L_U(0), logicTube3_TU_L_U(0), physiTube3_TU_L_U(0),
     solidTube3_TU_L_D(0), logicTube3_TU_L_D(0), physiTube3_TU_L_D(0),    

     solidTube4_R_U(0), logicTube4_R_U(0), physiTube4_R_U(0), 
     solidTube4_R_U_v(0), logicTube4_R_U_v(0), physiTube4_R_U_v(0), 
     solidTube4_R_D(0), logicTube4_R_D(0), physiTube4_R_D(0), 
     solidTube4_R_D_v(0), logicTube4_R_D_v(0), physiTube4_R_D_v(0), 
  
     solidTube5_C_R_U(0), logicTube5_C_R_U(0), physiTube5_C_R_U(0), 
     solidTube5_C_R_U_v(0), logicTube5_C_R_U_v(0), physiTube5_C_R_U_v(0), 
     solidTube5_C_R_D(0), logicTube5_C_R_D(0), physiTube5_C_R_D(0), 
     solidTube5_C_R_D_v(0), logicTube5_C_R_D_v(0), physiTube5_C_R_D_v(0), 
  
     solidTube5_Co_R_U(0), logicTube5_Co_R_U(0), physiTube5_Co_R_U(0), 
     solidTube5_Co_R_U_v(0), logicTube5_Co_R_U_v(0), physiTube5_Co_R_U_v(0),
     solidTube5_Co_R_D(0), logicTube5_Co_R_D(0), physiTube5_Co_R_D(0), 
     solidTube5_Co_R_D_v(0), logicTube5_Co_R_D_v(0), physiTube5_Co_R_D_v(0),

     solidTube5_C_L_U(0), logicTube5_C_L_U(0), physiTube5_C_L_U(0), 
     solidTube5_C_L_U_v(0), logicTube5_C_L_U_v(0), physiTube5_C_L_U_v(0), 
     solidTube5_C_L_D(0), logicTube5_C_L_D(0), physiTube5_C_L_D(0), 
     solidTube5_C_L_D_v(0), logicTube5_C_L_D_v(0), physiTube5_C_L_D_v(0), 
  
     solidTube5_Co_L_U(0), logicTube5_Co_L_U(0), physiTube5_Co_L_U(0), 
     solidTube5_Co_L_U_v(0), logicTube5_Co_L_U_v(0), physiTube5_Co_L_U_v(0),
     solidTube5_Co_L_D(0), logicTube5_Co_L_D(0), physiTube5_Co_L_D(0), 
     solidTube5_Co_L_D_v(0), logicTube5_Co_L_D_v(0), physiTube5_Co_L_D_v(0),

     solidQD0_Co_R(0), logicQD0_Co_R(0), physiQD0_Co_R(0),
     solidQD0_T_R(0),  logicQD0_T_R(0), physiQD0_T_R(0),
     solidQD0_Co_L(0), logicQD0_Co_L(0), physiQD0_Co_L(0),
     solidQD0_T_L(0),  logicQD0_T_L(0), physiQD0_T_L(0),

     solidQD1_SRCO_R_U(0), logicQD1_SRCO_R_U(0), physiQD1_SRCO_R_U(0),
     solidQD1_Al_R_U(0), logicQD1_Al_R_U(0), physiQD1_Al_R_U(0),
     solidQD1_SRCO_R_D(0), logicQD1_SRCO_R_D(0), physiQD1_SRCO_R_D(0),
     solidQD1_Al_R_D(0), logicQD1_Al_R_D(0), physiQD1_Al_R_D(0),
     
     solidQD1_SRCO_L_U(0), logicQD1_SRCO_L_U(0), physiQD1_SRCO_L_U(0),
     solidQD1_Al_L_U(0), logicQD1_Al_L_U(0), physiQD1_Al_L_U(0),
     solidQD1_SRCO_L_D(0), logicQD1_SRCO_L_D(0), physiQD1_SRCO_L_D(0),
     solidQD1_Al_L_D(0), logicQD1_Al_L_D(0), physiQD1_Al_L_D(0),

     solidSOY_T1_R(0), logicSOY_T1_R(0), physiSOY_T1_R(0),
     solidSOY_T1_L(0), logicSOY_T1_L(0), physiSOY_T1_L(0),

     solidSOY_T2_R(0), logicSOY_T2_R(0), physiSOY_T2_R(0),
     solidSOY_T2_L(0), logicSOY_T2_L(0), physiSOY_T2_L(0),

     solidSOY_Co3_R(0), logicSOY_Co3_R(0), physiSOY_Co3_R(0),
     solidSOY_Co3_L(0), logicSOY_Co3_L(0), physiSOY_Co3_L(0),

     solidSOY_Co4_R(0), logicSOY_Co4_R(0), physiSOY_Co4_R(0),
     solidSOY_Co4_L(0), logicSOY_Co4_L(0), physiSOY_Co4_L(0),

     solidSOY_T5_R(0), logicSOY_T5_R(0), physiSOY_T5_R(0),
     solidSOY_T5_L(0), logicSOY_T5_L(0), physiSOY_T5_L(0),

     solidSOY_T6_R(0), logicSOY_T6_R(0), physiSOY_T6_R(0),
     solidSOY_T6_L(0), logicSOY_T6_L(0), physiSOY_T6_L(0),

     solidSOY_Co7_R(0), logicSOY_Co7_R(0), physiSOY_Co7_R(0),
     solidSOY_Co7_L(0), logicSOY_Co7_L(0), physiSOY_Co7_L(0),

     solidBoxShield1_R(0), logicBoxShield1_R(0), physiBoxShield1_R(0),
     solidBoxShield1_L(0), logicBoxShield1_L(0), physiBoxShield1_L(0), 

     solidBoxShield2_R(0), logicBoxShield2_R(0), physiBoxShield2_R(0),
     solidBoxShield2_L(0), logicBoxShield2_L(0), physiBoxShield2_L(0), 

     solidBoxShield3_R(0), logicBoxShield3_R(0), physiBoxShield3_R(0),
     solidBoxShield3_L(0), logicBoxShield3_L(0), physiBoxShield3_L(0), 

     solidBoxShield4_R(0), logicBoxShield4_R(0), physiBoxShield4_R(0),
     solidBoxShield4_L(0), logicBoxShield4_L(0), physiBoxShield4_L(0), 

     solidIron1Box_R(0), logicIron1Box_R(0), physiIron1Box_R(0),
     solidIron2Box_R(0), logicIron2Box_R(0), physiIron2Box_R(0),
     solidIron3Box_R(0), logicIron3Box_R(0), physiIron3Box_R(0),
     solidIron4Box_R(0), logicIron4Box_R(0), physiIron4Box_R(0),

     solidIron1Box_L(0), logicIron1Box_L(0), physiIron1Box_L(0),
     solidIron2Box_L(0), logicIron2Box_L(0), physiIron2Box_L(0),
     solidIron3Box_L(0), logicIron3Box_L(0), physiIron3Box_L(0),
     solidIron4Box_L(0), logicIron4Box_L(0), physiIron4Box_L(0),

     solidPbWO1Box_R(0), logicPbWO1Box_R(0), physiPbWO1Box_R(0),
     solidPbWO2Box_R(0), logicPbWO2Box_R(0), physiPbWO2Box_R(0),
     solidPbWO3Box_R(0), logicPbWO3Box_R(0), physiPbWO3Box_R(0),
     solidPbWO4Box_R(0), logicPbWO4Box_R(0), physiPbWO4Box_R(0),

     solidPbWO1Box_L(0), logicPbWO1Box_L(0), physiPbWO1Box_L(0),
     solidPbWO2Box_L(0), logicPbWO2Box_L(0), physiPbWO2Box_L(0),
     solidPbWO3Box_L(0), logicPbWO3Box_L(0), physiPbWO3Box_L(0),
     solidPbWO4Box_L(0), logicPbWO4Box_L(0), physiPbWO4Box_L(0)

{
    //G4cout<<" ExN02DetectorConstruction.cc "<<G4endl;
    //G4cout<<" ExN02DetectorConstruction::ExN02DetectorConstruction() "<<G4endl;
    //G4cout<<" ------------------------------------------- "<<G4endl;

    //Test with uniformal field 
    //fpMagField = new G4UniformElectricField(G4ThreeVector(0.0,1000.0*kilovolt/cm,0.0));

    fpMagField = new ExN02MagneticField();
    
    detectorMessenger = new ExN02DetectorMessenger(this);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
ExN02DetectorConstruction::~ExN02DetectorConstruction()
{
  delete fpMagField;
  //delete stepLimit;
  //delete chamberParam;
  delete detectorMessenger;             
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
G4VPhysicalVolume* ExN02DetectorConstruction::Construct()
{
    G4cout << " ExN02DetectorConstruction::Construct() : start" << G4endl;

    //magnetic field
    G4cout << " ExN02DetectorConstruction::Construct() module with magnetic field : start" << G4endl;
    static G4bool fieldIsInitialized = false;
    if(!fieldIsInitialized){

	G4FieldManager* fieldMgr
	    = G4TransportationManager::GetTransportationManager()->GetFieldManager();
	fieldMgr->SetDetectorField(fpMagField);
	fieldMgr->CreateChordFinder(fpMagField);
	fieldMgr->GetChordFinder()->SetDeltaChord(0.001*mm);
	fieldIsInitialized = true;


/*
	//constract magnetik field with corection of the MagIntegratorDriver
	       
	// Create an equation of motion for this field
	fEquation = new G4EqMagElectricField(fpMagField);
	G4int nvar = 8;
	fStepper = new G4ClassicalRK4( fEquation, nvar );
	
	G4FieldManager* fieldMgr
	= G4TransportationManager::GetTransportationManager()->GetFieldManager();
	fieldMgr->SetDetectorField(fpMagField);
	
	fMinStep     = 1.*mm ; // minimal step
	fIntgrDriver = new G4MagInt_Driver(fMinStep,
					   fStepper,
					   fStepper->GetNumberOfVariables() );

	fChordFinder = new G4ChordFinder(fIntgrDriver);
	fieldMgr->SetChordFinder( fChordFinder );

	//fieldMgr->CreateChordFinder(fpMagField);
	fieldIsInitialized = true;
*/  

    }
    G4cout << " ExN02DetectorConstruction::Construct() module with magnetic field : end" << G4endl;
    //-------------------------------------------------------
    
    //----------------------------------------------------------------------
    //Inicialithation of the flags
    //----------------------------------------------------------------------
    G4String flag_tube2EllipticalPart;
    flag_tube2EllipticalPart = "mytube2EllipticalPart";
    //flag_tube2EllipticalPart = "circletube2EllipticalPart";

    G4String flagcheckingGeom1;
    //flagcheckingGeom1 = "checkingGeom1ON";
    flagcheckingGeom1 = "checkingGeom1OFF";

    G4String flagcheckingGeom2;
    //flagcheckingGeom2 = "checkingGeom2ON";
    flagcheckingGeom2 = "checkingGeom2OFF";

    G4String flagcheckingGeom3;
    //flagcheckingGeom3 = "checkingGeom3ON";
    flagcheckingGeom3 = "checkingGeom3OFF";

    G4String flagcheckingGeom4;
    //flagcheckingGeom4 = "checkingGeom4ON";
    flagcheckingGeom4 = "checkingGeom4OFF";

    G4String flagcheckingGeom5;
    //flagcheckingGeom5 = "checkingGeom5ON";
    flagcheckingGeom5 = "checkingGeom5OFF";

    //-------------------------------------------

    G4String flagcheckingGeom0201;
    //flagcheckingGeom0201 = "checkingGeom0201ON";
    flagcheckingGeom0201 = "checkingGeom0201OFF";

    G4String flagcheckingGeom0202;
    //flagcheckingGeom0202 = "checkingGeom0202ON";
    flagcheckingGeom0202 = "checkingGeom0202OFF";

    G4String flagcheckingGeom0203;
    //flagcheckingGeom0203 = "checkingGeom0203ON";
    flagcheckingGeom0203 = "checkingGeom0203OFF";

    G4String flagcheckingGeom0204;
    //flagcheckingGeom0204 = "checkingGeom0204ON";
    flagcheckingGeom0204 = "checkingGeom0204OFF";

    G4String flagcheckingGeom0205;
    //flagcheckingGeom0205 = "checkingGeom0205ON";
    flagcheckingGeom0205 = "checkingGeom0205OFF";

    G4String flagcheckingGeom0206;
    //flagcheckingGeom0206 = "checkingGeom0206ON";
    flagcheckingGeom0206 = "checkingGeom0206OFF";

    G4String flagcheckingGeom0207;
    //flagcheckingGeom0207 = "checkingGeom0207ON";
    flagcheckingGeom0207 = "checkingGeom0207OFF";

    G4String flagcheckingGeom0208;
    //flagcheckingGeom0208 = "checkingGeom0208ON";
    flagcheckingGeom0208 = "checkingGeom0208OFF";

    G4String flagcheckingGeom0209;
    //flagcheckingGeom0209 = "checkingGeom0209ON";
    flagcheckingGeom0209 = "checkingGeom0209OFF";
    //--------------------------------------------

    G4String flagcheckingGeomBenoit;
    //flagcheckingGeomBenoit = "checkingGeomBenoitON";
    flagcheckingGeomBenoit = "checkingGeomBenoitOFF";

    //--------------------------------------------

    //--------------------------------------------


    G4String flagcheckingGeomFieldStuck;
    //flagcheckingGeomFieldStuck = "checkingGeomFieldStuckON";
    flagcheckingGeomFieldStuck = "checkingGeomFieldStuckOFF";


    //--------------------------------------------


    
    G4String flag_DetConstInfo;
    //flag_DetConstInfo = "DetConstInfoON";
    flag_DetConstInfo = "DetConstInfoOFF";

    //turm off geomery 
    G4String flag_turnOffGeometry;
    flag_turnOffGeometry = "flag_turnOnGeometry";
    //flag_turnOffGeometry = "flag_turnOffGeometry";

    // turn on particle momentum output--------------------------
    G4String fleg_checkingOutputElecrton1; 
    //fleg_checkingOutputElecrton1 = "checkingOutputElecrton1ON";
    fleg_checkingOutputElecrton1 = "checkingOutputElecrton1OFF";

    G4String fleg_checkingOutputElecrton2; 
    // fleg_checkingOutputElecrton2 = "checkingOutputElecrton2ON";
    fleg_checkingOutputElecrton2 = "checkingOutputElecrton2OFF";
    //------------------------------------------------------------

    G4String fleg_SensativePbWO4RightON; 
    fleg_SensativePbWO4RightON = "SensativePbWO4RightON";
    //fleg_SensativePbWO4RightON = "SensativePbWO4RightOFF";

    G4String fleg_SensativePbWO4LeftON; 
    fleg_SensativePbWO4LeftON = "SensativePbWO4LeftON";
    //fleg_SensativePbWO4LeftON = "SensativePbWO4LeftOFF";

    G4String fleg_mirrorGeometryON; 
    //fleg_mirrorGeometryON = "mirrorGeometryON";
    fleg_mirrorGeometryON = "mirrorGeometryOFF"; 



    //------------------------------------------------------------

    G4String fleg_SenDetShower_R;
    //fleg_SenDetShower_R = "SenDetShower_RON";
    //fleg_SenDetShower_R = "SenDetShower_ROFF";

    G4String fleg_SenDetShower_L;
    fleg_SenDetShower_L = "SenDetShower_LON";
    //fleg_SenDetShower_L = "SenDetShower_LOFF";

    //------------------------------------------------------------

    FILE *stream;
    stream = fopen("result.txt","w");

/*
    fprintf( stream, " x1 = %10.5f y1 = %10.5f z1 = %10.5f \n", xP1, 0.0,zP1);
    fprintf( stream, " xP1 = %10.5f yP1 = %10.5f zP1 = %10.5f \n", (x_WinPhot - xP1)/(z_WinPhot - zP1), 0.0,1.0);
    fprintf( stream, " x2 = %10.5f y2 = %10.5f z2 = %10.5f \n", xP2, 0.0,zP2);
    fprintf( stream, " xP2 = %10.5f yP2 = %10.5f zP2 = %10.5f \n", (x_WinPhot - xP2)/(z_WinPhot - zP2), 0.0,1.0);
    fprintf( stream, " x3 = %10.5f y3 = %10.5f z3 = %10.5f \n", xP3, 0.0,zP3);
    fprintf( stream, " xP3 = %10.5f yP3 = %10.5f zP3 = %10.5f \n", (x_WinPhot - xP3)/(z_WinPhot - zP3), 0.0,1.0);

    fprintf( stream, " x4 = %10.5f y4 = %10.5f z4 = %10.5f \n", xP4, 0.0,zP4);
    fprintf( stream, " xP4 = %10.5f yP4 = %10.5f zP4 = %10.5f \n", (x_WinPhot - xP4)/(z_WinPhot - zP4), 0.0,1.0);
    fprintf( stream, " x5 = %10.5f y5 = %10.5f z5 = %10.5f \n", xP5, 0.0,zP5);
    fprintf( stream, " xP5 = %10.5f yP5 = %10.5f zP5 = %10.5f \n", (x_WinPhot - xP5)/(z_WinPhot - zP5), 0.0,1.0);
    fprintf( stream, " x6 = %10.5f y6 = %10.5f z6 = %10.5f \n", xP6, 0.0,zP6);
    fprintf( stream, " xP6 = %10.5f yP6 = %10.5f zP6 = %10.5f \n", (x_WinPhot - xP6)/(z_WinPhot - zP6), 0.0,1.0);
*/

    //----------------------------------------------------------------------


    //----------------------------------------------------------------------
    // Material definition        
    //----------------------------------------------------------------------
    ExN02MaterialConstruction* materialConst = new ExN02MaterialConstruction();

    if(fleg_mirrorGeometryON == "mirrorGeometryOFF"){

// 	BP1Mater     = materialConst->ConstructAluminium();
// 	BP1Mater_v   = materialConst->ConstructBeamVacuum();
// 	Air          = materialConst->ConstructAir();
// 	QDMater      = materialConst->ConstructSmCo();
// 	ShieldsMater = materialConst->ConstructLead();
// 	PVCMater     = materialConst->ConstructPVC();
// 	IronMater    = materialConst->ConstructAluminium();
// 	PbWOMater    = materialConst->ConstructPbWO();

 	BP1Mater     = materialConst->ConstructBeamVacuum();
 	BP1Mater_v   = materialConst->ConstructLead();
 	Air          = materialConst->ConstructBeamVacuum();
 	QDMater      = materialConst->ConstructBeamVacuum();
 	ShieldsMater = materialConst->ConstructBeamVacuum();
 	PVCMater     = materialConst->ConstructBeamVacuum();
 	IronMater    = materialConst->ConstructBeamVacuum();
 	PbWOMater    = materialConst->ConstructBeamVacuum();
   
	G4cout<<"---------------- full geom -------------------------"<<G4endl;
	G4cout<<"      BP1Mater "<<BP1Mater<<G4endl;
	G4cout<<"      BP1Mater_v "<<BP1Mater_v<<G4endl;
	G4cout<<"      Air "<<Air<<G4endl;
	G4cout<<"      QDMater "<<QDMater<<G4endl;
	G4cout<<"      ShieldsMater "<<ShieldsMater<<G4endl;
	G4cout<<"      PVCMater "<<PVCMater<<G4endl;
	G4cout<<"      IronMater "<<IronMater<<G4endl;
	G4cout<<"      PbWOMater "<<PbWOMater<<G4endl;
	G4cout<<"----------------------------------------------------"<<G4endl;
    }
   
    if(fleg_mirrorGeometryON == "mirrorGeometryON"){
	G4cout << G4endl << "______________________________" << G4endl << G4endl;
	G4cout << "fleg_mirrorGeometryON == mirrorGeometryON"<< G4endl;
	G4cout << G4endl << "------------------------------" << G4endl << G4endl;
	BP1Mater = materialConst->ConstructBeamVacuum();
	BP1Mater_v = materialConst->ConstructLead();
	Air = materialConst->ConstructBeamVacuum();
	QDMater = materialConst->ConstructBeamVacuum();
	ShieldsMater = materialConst->ConstructBeamVacuum();
	PVCMater = materialConst->ConstructBeamVacuum();
	IronMater = materialConst->ConstructBeamVacuum();
	PbWOMater = materialConst->ConstructBeamVacuum();
    }


    // Print all the materials defined.
    //G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
    //G4cout << *(G4Material::GetMaterialTable()) << G4endl;
    //----------------------------------------------------------------------



    if(flag_DetConstInfo == "DetConstInfoON"){
	G4cout<<" z_max_QD0_R = "<< z_max_QD0_R<<G4endl;
	G4cout<<" z_min_QD0_R = "<< z_min_QD0_R<<G4endl;
	G4cout<<" z_max_QD0_L = "<< z_max_QD0_L<<G4endl;
	G4cout<<" z_min_QD0_L = "<< z_min_QD0_L<<G4endl;

        G4cout<<"-----------------------------"<<G4endl;
	G4double zQD1SMend = z_QD1_SRCO_R_U + length_QD1_SRCO/2*cos4_07;
  	G4double xQD1SMend = x_QD1_SRCO_R_U + length_QD1_SRCO/2*sin4_07;
	G4double zQD1SMStart = z_QD1_Al_R_U - length_QD1_Al/2*cos4_07;
  	G4double xQD1SMStart = x_QD1_Al_R_U - length_QD1_Al/2*sin4_07;
	G4double zQD1 = zQD1SMStart + (length_QD1_SRCO + length_QD1_Al)/2*cos4_07;
  	G4double xQD1 = xQD1SMStart + (length_QD1_SRCO + length_QD1_Al)/2*sin4_07;
	G4cout<<" zQD1SMend "<< zQD1SMend <<G4endl;     
	G4cout<<" xQD1SMend "<< xQD1SMend <<G4endl;     
	G4cout<<" zQD1SMStart "<< zQD1SMStart <<G4endl;     
	G4cout<<" xQD1SMStart "<< xQD1SMStart <<G4endl;
	G4cout<<" zQD1 "<< zQD1 <<G4endl;     
	G4cout<<" xQD1 "<< xQD1 <<G4endl;
	G4cout<<"-----------------------------"<<G4endl;
	G4cout<<" x_Tube5_C_R_U = "<< x_Tube5_C_R_U <<G4endl;
	G4cout<<" y_Tube5_C_R_U = "<< y_Tube5_C_R_U <<G4endl;
	G4cout<<" z_Tube5_C_R_U = "<< z_Tube5_C_R_U <<G4endl;

	G4cout<<" z_maxAxis_QD1_R_U = "<<z_maxAxis_QD1_R_U<<G4endl;
	G4cout<<" z_minAxis_QD1_R_U = "<<z_minAxis_QD1_R_U<<G4endl;
	G4cout<<" x_maxAxis_QD1_R_U = "<<x_maxAxis_QD1_R_U<<G4endl;	
	G4cout<<" x_minAxis_QD1_R_U = "<<x_minAxis_QD1_R_U<<G4endl;

	G4cout<<"-----------------------------"<<G4endl;
	G4cout<<"-----------------------------"<<G4endl;
	G4cout<<"+++++++++++++++++++++++++++++"<<G4endl;
	G4cout<<" x_QD1_L_Umy = "<< x_QD1_L_Umy <<G4endl;
	G4cout<<" x_QD1_R_Umy = "<< x_QD1_R_Umy<<G4endl;
	G4cout<<"+++++++++++++++++++++++++++++"<<G4endl;

	//G4cout<< dx1_Tube3_par2_TR/2.*cm<<G4endl;
	//G4cout<< dx2_Tube3_par2_TR/2.*cm<<G4endl;
	//G4cout<< dy1_Tube3_par2_TR/2.*cm<<G4endl;
	//G4cout<< dy2_Tube3_par2_TR/2.*cm<<G4endl;
	G4cout<< dz_Tube3_par2_TR<<G4endl;

	G4cout<<dz_Tube3_par3_TR<<G4endl;

	G4cout<<"---"<<z_QD1_R_Umy<<G4endl;
	G4cout<<"---"<<x_QD1_R_Umy<<G4endl;
	
	G4cout<<"---"<<z_QD1_SRCO_R_U<<G4endl;
	G4cout<<"---"<<x_QD1_SRCO_R_U<<G4endl;

	return 0;   
    }
 

    //------------------------------ 
    // World
    //------------------------------ 

    ExN02DetectorConstruction_World* world = new ExN02DetectorConstruction_World(Air);
    physiWorld = world->Construct();
    logicWorld = world->GetlogicVol();

    //------------------------------
    // QD0
    //------------------------------

    //QD0 right
    G4ThreeVector positionQD0_Co_R = G4ThreeVector(x_QD0_Co_R*cm,y_QD0_Co_R*cm,z_QD0_Co_R*cm);
    G4ThreeVector positionQD0_T_R = G4ThreeVector(x_QD0_T_R*cm,y_QD0_T_R*cm,z_QD0_T_R*cm);   
    G4String nCo = "QD0_Co_R";
    G4String nT = "QD0_T_R";
    ExN02DetectorConstruction_QD0* QD0_R = 
	new ExN02DetectorConstruction_QD0(logicWorld,
					  positionQD0_Co_R,
					  positionQD0_T_R,
					  innerRadius1_QD0_Co*cm,
					  outerRadius1_QD0_Co*cm,
					  innerRadius2_QD0_Co*cm,
					  outerRadius2_QD0_Co*cm,
					  innerRadius_QD0_T*cm,
					  outerRadius_QD0_T*cm,
					  QDMater,
					  nCo,
					  nT);
    QD0_R->Construct();
    //logicQD0_T_R = QD0_R->GetLogicQD0_T();
    //logicQD0_Co_R = QD0_R->GetLogicQD0_Co();

    //GD0 left
    G4ThreeVector positionQD0_Co_L = G4ThreeVector(x_QD0_Co_L*cm,y_QD0_Co_L*cm,z_QD0_Co_L*cm);
    G4ThreeVector positionQD0_T_L = G4ThreeVector(x_QD0_T_L*cm,y_QD0_T_L*cm,z_QD0_T_L*cm);
    nCo = "QD0_Co_L";
    nT = "QD0_T_L";
    ExN02DetectorConstruction_QD0* QD0_L = 
	new ExN02DetectorConstruction_QD0(logicWorld,
					  positionQD0_Co_L,
					  positionQD0_T_L,
					  innerRadius2_QD0_Co*cm,
					  outerRadius2_QD0_Co*cm,
					  innerRadius1_QD0_Co*cm,
					  outerRadius1_QD0_Co*cm,
					  innerRadius_QD0_T*cm,
					  outerRadius_QD0_T*cm,
					  QDMater,
					  nCo,
					  nT);
    QD0_L->Construct();
    logicQD0_T_L = QD0_L->GetLogicQD0_T();
    logicQD0_Co_L = QD0_L->GetLogicQD0_Co();
    QD0_L->PrintInfo();

    //--------------------------------------------
    // QD1 QF1
    //-------------------------------------------- 

    // QD1 right upper made of SmCo
    G4ThreeVector positionQD1_SmCo_R_U = G4ThreeVector(x_QD1_SRCO_R_U*cm,y_QD1_SRCO_R_U*cm,z_QD1_SRCO_R_U*cm);
    G4String name = "QD1_SmCo_R_U";
    ExN02DetectorConstruction_Tube* QD1_SmCo_R_U = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					  positionQD1_SmCo_R_U,
					  -alpha*deg,
					  innerRadius_QD1*cm,
					  outerRadius_QD1*cm,
					  length_QD1_SRCO*cm,
					  QDMater,
					  0.,
					  360*deg,
					  name);
    QD1_SmCo_R_U->Construct();
    logicQD1_SRCO_R_U = QD1_SmCo_R_U->GetlogicVol();


    // QD1 aluminium rings
    G4ThreeVector positionQD1_Al_P_R_U = G4ThreeVector(x_QD1_new_Al_R*cm,y_QD1_new_Al_R*cm,z_QD1_new_Al_R*cm);
       G4ThreeVector positionQD1_Al_P_L_U = G4ThreeVector(x_QD1_new_Al_L*cm,y_QD1_new_Al_L*cm,z_QD1_new_Al_L*cm);
       G4ThreeVector positionQD1_Al_P_R_D = G4ThreeVector(-x_QD1_new_Al_R*cm,y_QD1_new_Al_R*cm,z_QD1_new_Al_R*cm);
       G4ThreeVector positionQD1_Al_P_L_D = G4ThreeVector(-x_QD1_new_Al_L*cm,y_QD1_new_Al_L*cm,z_QD1_new_Al_L*cm);

       G4ThreeVector positionQD1_Al_M_R_U = G4ThreeVector(x_QD1_new_Al_R*cm,y_QD1_new_Al_R*cm,-z_QD1_new_Al_R*cm);
       G4ThreeVector positionQD1_Al_M_L_U = G4ThreeVector(x_QD1_new_Al_L*cm,y_QD1_new_Al_L*cm,-z_QD1_new_Al_L*cm);
       G4ThreeVector positionQD1_Al_M_R_D = G4ThreeVector(-x_QD1_new_Al_R*cm,y_QD1_new_Al_R*cm,-z_QD1_new_Al_R*cm);
       G4ThreeVector positionQD1_Al_M_L_D = G4ThreeVector(-x_QD1_new_Al_L*cm,y_QD1_new_Al_L*cm,-z_QD1_new_Al_L*cm);

       
 
       name = "QD1_Al_P_R_U";
       ExN02DetectorConstruction_Tube* QD1_Al_P_R_U = 
	   new ExN02DetectorConstruction_Tube(logicWorld,
					      positionQD1_Al_P_R_U,
					      -alpha*deg,
					      innerRadius_QD1*cm,
					      outerRadius_QD1*cm,
					      length_QD1_new_Al*cm,
					      BP1Mater,
					      0.,
					      360*deg,
					      name);
       QD1_Al_P_R_U->Construct();
       G4LogicalVolume* logicQD1_Al_P_R_U = QD1_Al_P_R_U->GetlogicVol();
       
       name = "QD1_Al_P_L_U";
       ExN02DetectorConstruction_Tube* QD1_Al_P_L_U = 
	   new ExN02DetectorConstruction_Tube(logicWorld,
					      positionQD1_Al_P_L_U,
					      -alpha*deg,
					      innerRadius_QD1*cm,
					      outerRadius_QD1*cm,
					      length_QD1_new_Al*cm,
					      BP1Mater,
					      0.,
					      360*deg,
					      name);
       QD1_Al_P_L_U->Construct();
       G4LogicalVolume* logicQD1_Al_P_L_U = QD1_Al_P_L_U->GetlogicVol();

       name = "QD1_Al_P_R_D";
       ExN02DetectorConstruction_Tube* QD1_Al_P_R_D = 
	   new ExN02DetectorConstruction_Tube(logicWorld,
					      positionQD1_Al_P_R_D,
					      alpha*deg,
					      innerRadius_QD1*cm,
					      outerRadius_QD1*cm,
					      length_QD1_new_Al*cm,
					      BP1Mater,
					      0.,
					      360*deg,
					      name);
       QD1_Al_P_R_D->Construct();
       G4LogicalVolume* logicQD1_Al_P_R_D = QD1_Al_P_R_D->GetlogicVol();
       
       name = "QD1_Al_P_L_D";
       ExN02DetectorConstruction_Tube* QD1_Al_P_L_D = 
	   new ExN02DetectorConstruction_Tube(logicWorld,
					      positionQD1_Al_P_L_D,
					      alpha*deg,
					      innerRadius_QD1*cm,
					      outerRadius_QD1*cm,
					      length_QD1_new_Al*cm,
					      BP1Mater,
					      0.,
					      360*deg,
					      name);
       QD1_Al_P_L_D->Construct();
       G4LogicalVolume* logicQD1_Al_P_L_D = QD1_Al_P_L_D->GetlogicVol();
       

       name = "QD1_Al_M_R_U";
       ExN02DetectorConstruction_Tube* QD1_Al_M_R_U = 
	   new ExN02DetectorConstruction_Tube(logicWorld,
					      positionQD1_Al_M_R_U,
					      alpha*deg,
					      innerRadius_QD1*cm,
					      outerRadius_QD1*cm,
					      length_QD1_new_Al*cm,
					      BP1Mater,
					      0.,
					      360*deg,
					      name);
       QD1_Al_M_R_U->Construct();
       G4LogicalVolume* logicQD1_Al_M_R_U = QD1_Al_M_R_U->GetlogicVol();
       
       name = "QD1_Al_M_L_U";
       ExN02DetectorConstruction_Tube* QD1_Al_M_L_U = 
	   new ExN02DetectorConstruction_Tube(logicWorld,
					      positionQD1_Al_M_L_U,
					      alpha*deg,
					      innerRadius_QD1*cm,
					      outerRadius_QD1*cm,
					      length_QD1_new_Al*cm,
					      BP1Mater,
					      0.,
					      360*deg,
					      name);
       QD1_Al_M_L_U->Construct();
       G4LogicalVolume* logicQD1_Al_M_L_U = QD1_Al_M_L_U->GetlogicVol();

       name = "QD1_Al_M_R_D";
       ExN02DetectorConstruction_Tube* QD1_Al_M_R_D = 
	   new ExN02DetectorConstruction_Tube(logicWorld,
					      positionQD1_Al_M_R_D,
					      -alpha*deg,
					      innerRadius_QD1*cm,
					      outerRadius_QD1*cm,
					      length_QD1_new_Al*cm,
					      BP1Mater,
					      0.,
					      360*deg,
					      name);
       QD1_Al_M_R_D->Construct();
       G4LogicalVolume* logicQD1_Al_M_R_D = QD1_Al_M_R_D->GetlogicVol();
       
       name = "QD1_Al_M_L_D";
       ExN02DetectorConstruction_Tube* QD1_Al_M_L_D = 
	   new ExN02DetectorConstruction_Tube(logicWorld,
					      positionQD1_Al_M_L_D,
					      -alpha*deg,
					      innerRadius_QD1*cm,
					      outerRadius_QD1*cm,
					      length_QD1_new_Al*cm,
					      BP1Mater,
					      0.,
					      360*deg,
					      name);
       QD1_Al_M_L_D->Construct();
       G4LogicalVolume* logicQD1_Al_M_L_D = QD1_Al_M_L_D->GetlogicVol();




/*
    // QD1 right upper made of aluminium
    G4ThreeVector positionQD1_Al_R_U = G4ThreeVector(x_QD1_Al_R_U*cm,y_QD1_Al_R_U*cm,z_QD1_Al_R_U*cm);
    name = "QD1_Al_R_U";
    ExN02DetectorConstruction_Tube* QD1_Al_R_U = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					  positionQD1_Al_R_U,
					  -alpha*deg,
					  innerRadius_QD1*cm,
					  outerRadius_QD1*cm,
					  length_QD1_Al*cm,
					  BP1Mater,
					  0.,
					  360*deg,
					  name);
    QD1_Al_R_U->Construct();
    logicQD1_Al_R_U = QD1_Al_R_U->GetlogicVol();
*/

    // QD1 right bottom  made of SmCo
    G4ThreeVector positionQD1_SmCo_R_D = G4ThreeVector(x_QD1_SRCO_R_D*cm,y_QD1_SRCO_R_D*cm,z_QD1_SRCO_R_D*cm);
    name = "QD1_SmCo_R_D";
    ExN02DetectorConstruction_Tube* QD1_SmCo_R_D = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					  positionQD1_SmCo_R_D,
					  alpha*deg,
					  innerRadius_QD1*cm,
					  outerRadius_QD1*cm,
					  length_QD1_SRCO*cm,
					  QDMater,
					  0.,
					  360*deg,
					  name);
    QD1_SmCo_R_D->Construct();
    logicQD1_SRCO_R_D = QD1_SmCo_R_D->GetlogicVol();
/*
    // QD1 right bottom  made of aluminium
    G4ThreeVector positionQD1_Al_R_D = G4ThreeVector(x_QD1_Al_R_D*cm,y_QD1_Al_R_D*cm,z_QD1_Al_R_D*cm);
    name = "QD1_Al_R_D";
    ExN02DetectorConstruction_Tube* QD1_Al_R_D = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					  positionQD1_Al_R_D,
					  alpha*deg,
					  innerRadius_QD1*cm,
					  outerRadius_QD1*cm,
					  length_QD1_Al*cm,
					  BP1Mater,
					  0.,
					  360*deg,
					  name);
    QD1_Al_R_D->Construct();
    logicQD1_Al_R_D = QD1_Al_R_D->GetlogicVol();
*/

    //QD1 left upper made of SmCo
    G4ThreeVector positionQD1_SmCo_L_U = G4ThreeVector(x_QD1_SRCO_L_U*cm,y_QD1_SRCO_L_U*cm,z_QD1_SRCO_L_U*cm);
    name = "QD1_SmCo_L_U";
    ExN02DetectorConstruction_Tube* QD1_SmCo_L_U = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					  positionQD1_SmCo_L_U,
					  alpha*deg,
					  innerRadius_QD1*cm,
					  outerRadius_QD1*cm,
					  length_QD1_SRCO*cm,
					  QDMater,
					  0.,
					  360*deg,
					  name);
    QD1_SmCo_L_U->Construct();
    logicQD1_SRCO_L_U = QD1_SmCo_L_U->GetlogicVol();    

/*
    //QD1 left upper made of Al
    G4ThreeVector positionQD1_Al_L_U = G4ThreeVector(x_QD1_Al_L_U*cm,y_QD1_Al_L_U*cm,z_QD1_Al_L_U*cm);
    name = "QD1_Al_L_U";
    ExN02DetectorConstruction_Tube* QD1_Al_L_U = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					  positionQD1_Al_L_U,
					  alpha*deg,
					  innerRadius_QD1*cm,
					  outerRadius_QD1*cm,
					  length_QD1_Al*cm,
					  BP1Mater,
					  0.,
					  360*deg,
					  name);
    QD1_Al_L_U->Construct();
    logicQD1_Al_L_U = QD1_Al_L_U->GetlogicVol(); 
*/

    // QD1 left bottom  made of SmCo
    G4ThreeVector positionQD1_SmCo_L_D = G4ThreeVector(x_QD1_SRCO_L_D*cm,y_QD1_SRCO_L_D*cm,z_QD1_SRCO_L_D*cm);
    name = "QD1_SmCo_L_D";
    ExN02DetectorConstruction_Tube* QD1_SmCo_L_D = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					  positionQD1_SmCo_L_D,
					  -alpha*deg,
					  innerRadius_QD1*cm,
					  outerRadius_QD1*cm,
					  length_QD1_SRCO*cm,
					  QDMater,
					  0.,
					  360*deg,
					  name);
    QD1_SmCo_L_D->Construct();
    logicQD1_SRCO_L_D = QD1_SmCo_L_D->GetlogicVol();

/*
    //QD1 left bottom  made of Al
    G4ThreeVector positionQD1_Al_L_D = G4ThreeVector(x_QD1_Al_L_D*cm,y_QD1_Al_L_D*cm,z_QD1_Al_L_D*cm);
    name = "QD1_Al_L_D";
    ExN02DetectorConstruction_Tube* QD1_Al_L_D = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					  positionQD1_Al_L_D,
					  -alpha*deg,
					  innerRadius_QD1*cm,
					  outerRadius_QD1*cm,
					  length_QD1_Al*cm,
					  BP1Mater,
					  0.,
					  360*deg,
					  name);
    QD1_Al_L_D->Construct();
   logicQD1_Al_L_D = QD1_Al_L_D->GetlogicVol();
*/
   
    if(flag_turnOffGeometry == "flag_turnOnGeometry"){
    //--------------------------------------------
    // tube1 
    // Central beampipe definition (aka section 1)
    //--------------------------------------------
 
    //BP1
    G4ThreeVector positionBP1 = G4ThreeVector(x_Tube1*cm,y_Tube1*cm,z_Tube1*cm);
    name = "BP1";
    ExN02DetectorConstruction_Tube* BP1 = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					  positionBP1,
					   0.*deg,
					  innerRadius_Tube1*cm,
					  outerRadius_Tube1*cm,
					  length_Tube1*cm,
					  BP1Mater,
					  0.,
					  360*deg,
					  name);
    BP1->Construct();
    logicBP1 = BP1->GetlogicVol();

    //BP1 central beampipe tube1 vacuum within
    name = "BP1_v";
    ExN02DetectorConstruction_Tube* BP1_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					  positionBP1,
					   0.*deg,
					   0.,
					  innerRadius_Tube1*cm,
					  length_Tube1*cm,
					  BP1Mater_v,
					  0.,
					  360*deg,
					  name);
    BP1_v->Construct();
    logicBP1_v = BP1_v->GetlogicVol(); 

    //--------------------------------------------
    // connecting rings around the BP1
    //--------------------------------------------
    G4ThreeVector positionBP1Con_R = G4ThreeVector(x_Tube1Con_R*cm, y_Tube1Con_R*cm,z_Tube1Con_R*cm);
    name = "BP1Con_R";
    ExN02DetectorConstruction_Tube* BP1Con_R = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionBP1Con_R,
					   0.*deg,
					   innerRadius_Tube1Con*cm,
					   outerRadius_Tube1Con*cm,
					   length_Tube1Con*cm,
					   BP1Mater,
					   0.,
					   360*deg,
					   name);
    BP1Con_R->Construct();
    logicBP1Con_R = BP1Con_R->GetlogicVol();

    G4ThreeVector positionBP1Con_L = G4ThreeVector(x_Tube1Con_L*cm, y_Tube1Con_L*cm,z_Tube1Con_L*cm);
    name = "BP1Con_L";
    ExN02DetectorConstruction_Tube* BP1Con_L = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionBP1Con_L,
					   0.*deg,
					   innerRadius_Tube1Con*cm,
					   outerRadius_Tube1Con*cm,
					   length_Tube1Con*cm,
					   BP1Mater,
					   0.,
					   360*deg,
					   name);
    BP1Con_L->Construct();
    logicBP1Con_L = BP1Con_L->GetlogicVol();
    
    //--------------------------------------------
    // tube2 
    // Conecter between central tube of the beampipe and V-like tube
    // tube2 consist of two part : circular, and non circular shape
    // in section 
    //--------------------------------------------

    //tube2 right circular part in section
    G4ThreeVector positionTube2_C_R = G4ThreeVector(x_Tube2_C_R*cm,y_Tube2_C_R*cm,z_Tube2_C_R*cm);
    name = "Tube2_C_R";
    ExN02DetectorConstruction_Tube* Tube2_C_R = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube2_C_R,
					   0.*deg,
					   innerRadius_Tube1*cm,
					   outerRadius_Tube1*cm,
					   length_Tube2_C*cm,
					   BP1Mater,
					   0.,
					   360*deg,
					   name);
    Tube2_C_R->Construct();
    logicTube2_C_R = Tube2_C_R->GetlogicVol();

    //tube2 right circular part vacuum
    name = "Tube2_C_R_v";
    ExN02DetectorConstruction_Tube* Tube2_C_R_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube2_C_R,
					   0.*deg,
					   0.,
					   innerRadius_Tube1*cm,
					   length_Tube2_C*cm,
					   BP1Mater_v,
					   0.,
					   360*deg,
					   name);
    Tube2_C_R_v->Construct();
    logicTube2_C_R_v = Tube2_C_R_v->GetlogicVol();

    //tube2 left circular part in section
    G4ThreeVector positionTube2_C_L = G4ThreeVector(x_Tube2_C_L*cm,y_Tube2_C_L*cm,z_Tube2_C_L*cm);
    name = "Tube2_C_L";
    ExN02DetectorConstruction_Tube* Tube2_C_L = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube2_C_L,
					   0.*deg,
					   innerRadius_Tube1*cm,
					   outerRadius_Tube1*cm,
					   length_Tube2_C*cm,
					   BP1Mater,
					   0.,
					   360*deg,
					   name);
    Tube2_C_L->Construct();
    logicTube2_C_L = Tube2_C_L->GetlogicVol();

    //tube2 left circular part vacuum
    name = "Tube2_C_L_v";
    ExN02DetectorConstruction_Tube* Tube2_C_L_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube2_C_L,
					   0.*deg,
					   0.,
					   innerRadius_Tube1*cm,
					   length_Tube2_C*cm,
					   BP1Mater_v,
					   0.,
					   360*deg,
					   name);
    Tube2_C_L_v->Construct();
    logicTube2_C_L_v = Tube2_C_L_v->GetlogicVol();


    //-------------------------------------------------------------
    // rings around the Tube2 circular part which conected to the BP1
    //-------------------------------------------------------------
    G4ThreeVector positionTube2Con_R = G4ThreeVector(x_Tube2Con_R*cm, y_Tube2Con_R*cm,z_Tube2Con_R*cm);
    name = "Tube2Con_R";
    ExN02DetectorConstruction_Tube* Tube2Con_R = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube2Con_R,
					   0.*deg,
					   innerRadius_Tube2Con*cm,
					   outerRadius_Tube2Con*cm,
					   length_Tube2Con*cm,
					   BP1Mater,
					   0.,
					   360*deg,
					   name);
    Tube2Con_R->Construct();
    logicTube2Con_R = Tube2Con_R->GetlogicVol();

    G4ThreeVector positionTube2Con_L = G4ThreeVector(x_Tube2Con_L*cm, y_Tube2Con_L*cm,z_Tube2Con_L*cm);
    name = "Tube2Con_L";
    ExN02DetectorConstruction_Tube* Tube2Con_L = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube2Con_L,
					   0.*deg,
					   innerRadius_Tube2Con*cm,
					   outerRadius_Tube2Con*cm,
					   length_Tube2Con*cm,
					   BP1Mater,
					   0.,
					   360*deg,
					   name);
    Tube2Con_L->Construct();
    logicTube2Con_L = Tube2Con_L->GetlogicVol();



    //--------------------------------------------
    // tube2 
    // Connector between central tube of the beampipe and V-like tube
    // non circular part
    //non circular part consist of two half circles(left and right) 
    //and two trapezoid up and down
    //--------------------------------------------
   
    // right upper half tube2
    G4ThreeVector positionTube2_E_CRU = G4ThreeVector(x_Tube2_E_CRU*cm,y_Tube2_E_CRU*cm,z_Tube2_E_CRU*cm);
    name = "Tube2_E_CRU";
    ExN02DetectorConstruction_Tube* Tube2_E_CRU = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube2_E_CRU,
					   -alpha2_87*deg,
					   innerRadiusTube2_E*cm,
					   outerRadiusTube2_E*cm,
					   length_Tube2_E*cm,
					   BP1Mater,
					   270.*deg,
					   180.*deg,
					   name);
    Tube2_E_CRU->Construct();
    logicTube2_E_CRU = Tube2_E_CRU->GetlogicVol();
    
    // vacuum in right upper half tube2
    name = "Tube2_E_CRU_v";
    ExN02DetectorConstruction_Tube* Tube2_E_CRU_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube2_E_CRU,
					   -alpha2_87*deg,
					   0.,
					   innerRadiusTube2_E*cm,
					   length_Tube2_E*cm,
					   BP1Mater_v,
					   270.*deg,
					   180.*deg,
					   name);
    Tube2_E_CRU_v->Construct();
    logicTube2_E_CRU_v = Tube2_E_CRU_v->GetlogicVol();  

    // right bottom half tube2
    G4ThreeVector positionTube2_E_CRD = G4ThreeVector(x_Tube2_E_CRD*cm,y_Tube2_E_CRD*cm,z_Tube2_E_CRD*cm);
    name = "Tube2_E_CRD";
    ExN02DetectorConstruction_Tube* Tube2_E_CRD = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube2_E_CRD,
					   alpha2_87*deg,
					   innerRadiusTube2_E*cm,
					   outerRadiusTube2_E*cm,
					   length_Tube2_E*cm,
					   BP1Mater,
					   90.*deg,
					   180.*deg,
					   name);
    Tube2_E_CRD->Construct();
    logicTube2_E_CRD = Tube2_E_CRD->GetlogicVol();
    
    // vacuum in right upper half tube2
    name = "Tube2_E_CRD_v";
    ExN02DetectorConstruction_Tube* Tube2_E_CRD_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube2_E_CRD,
					   alpha2_87*deg,
					   0.,
					   innerRadiusTube2_E*cm,
					   length_Tube2_E*cm,
					   BP1Mater_v,
					   90.*deg,
					   180.*deg,
					   name);
    Tube2_E_CRD_v->Construct();
    logicTube2_E_CRD_v = Tube2_E_CRD_v->GetlogicVol();  
   
    //-----------------
    // upper right Trapezoid
    //----------------- 
    G4ThreeVector positionTube2_E_TRRU = G4ThreeVector(x_Tube2_E_TRRU*cm,y_Tube2_E_TRRU*cm,z_Tube2_E_TRRU*cm);
    solidTube2_E_TRRU = new G4Trd("Tube2_E_TRRU",
				  dx1_Tube2_E_TR/2.*cm,
				  dx2_Tube2_E_TR/2.*cm,
				  dy1_Tube2_E_TR/2.*cm,
				  dy2_Tube2_E_TR/2.*cm,
				  dz_Tube2_E_TR/2.*cm);
    logicTube2_E_TRRU = new G4LogicalVolume(solidTube2_E_TRRU,BP1Mater,"Tube2_E_TRRU",0,0,0);
    physiTube2_E_TRRU = new G4PVPlacement(0,                   // no rotation
					  positionTube2_E_TRRU, // at (x,y,z)
					  logicTube2_E_TRRU,    // its logical volume
					  "Tube2_E_TRRU",       // its name
					  logicWorld,           // its mother  volume
					  false,                // no boolean operations
					  0);                   // copy number 

    //-------------------------------------------------------------------------------------------------------
    // lower right Trapezoid
    //----------------- 
    G4ThreeVector positionTube2_E_TRRD = G4ThreeVector(x_Tube2_E_TRRD*cm,y_Tube2_E_TRRD*cm,z_Tube2_E_TRRD*cm);
    solidTube2_E_TRRD = new G4Trd("Tube2_E_TRRD",
				  dx1_Tube2_E_TR/2.*cm,
				  dx2_Tube2_E_TR/2.*cm,
				  dy1_Tube2_E_TR/2.*cm,
				  dy2_Tube2_E_TR/2.*cm,
				  dz_Tube2_E_TR/2.*cm);
    logicTube2_E_TRRD= new G4LogicalVolume(solidTube2_E_TRRD,BP1Mater,"Tube2_E_TRRD",0,0,0);
    physiTube2_E_TRRD = new G4PVPlacement(0,                   // no rotation
					  positionTube2_E_TRRD, // at (x,y,z)
					  logicTube2_E_TRRD,    // its logical volume
					  "Tube2_E_TRRD",       // its name
					  logicWorld,           // its mother  volume
					  false,                // no boolean operations
					  0);                   // copy number 
   
    //------------------------
    // right trapezoid vacuum within
    //------------------------
    G4ThreeVector positionTube2_E_TRR_v = G4ThreeVector(x_Tube2_E_TRR_v*cm,y_Tube2_E_TRR_v*cm,z_Tube2_E_TRR_v*cm);
    solidTube2_E_TRR_v = new G4Trd("Tube2_E_TRR_v",
				   dx1_Tube2_E_TR_v/2.*cm,
				   dx2_Tube2_E_TR_v/2.*cm,
				   dy1_Tube2_E_TR_v/2.*cm,
				   dy2_Tube2_E_TR_v/2.*cm,
				   dz_Tube2_E_TR_v/2.*cm);
    logicTube2_E_TRR_v = new G4LogicalVolume(solidTube2_E_TRR_v,BP1Mater_v,"Tube2_E_TRR_v",0,0,0);
    physiTube2_E_TRR_v = new G4PVPlacement(0,                   // no rotation
					   positionTube2_E_TRR_v, // at (x,y,z)
					   logicTube2_E_TRR_v,    // its logical volume
					   "Tube2_E_TRR_v",       // its name
					   logicWorld,           // its mother  volume
					   false,                // no boolean operations
					   0);                   // copy number 
    //--------------------------------------------------------------------------------------------------
  
    //G4double startAngleTube2_E_CRD = 90.*deg;
    //G4double spanningAngleTube2_E_CRD = 180.*deg;

    // left upper half tube2
    G4ThreeVector positionTube2_E_CLU = G4ThreeVector(x_Tube2_E_CLU*cm,y_Tube2_E_CLU*cm,z_Tube2_E_CLU*cm);
    name = "Tube2_E_CLU";
    ExN02DetectorConstruction_Tube* Tube2_E_CLU = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube2_E_CLU,
					   alpha2_87*deg,
					   innerRadiusTube2_E*cm,
					   outerRadiusTube2_E*cm,
					   length_Tube2_E*cm,
					   BP1Mater,
					   270.*deg,
					   180.*deg,
					   name);
    Tube2_E_CLU->Construct();
    logicTube2_E_CLU = Tube2_E_CLU->GetlogicVol();
    
    // vacuum in left upper half tube2
    name = "Tube2_E_CLU_v";
    ExN02DetectorConstruction_Tube* Tube2_E_CLU_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube2_E_CLU,
					   alpha2_87*deg,
					   0.,
					   innerRadiusTube2_E*cm,
					   length_Tube2_E*cm,
					   BP1Mater_v,
					   270.*deg,
					   180.*deg,
					   name);
    Tube2_E_CLU_v->Construct();
    logicTube2_E_CLU_v = Tube2_E_CLU_v->GetlogicVol();  

    // left bottom half tube2
    G4ThreeVector positionTube2_E_CLD = G4ThreeVector(x_Tube2_E_CLD*cm,y_Tube2_E_CLD*cm,z_Tube2_E_CLD*cm);
    name = "Tube2_E_CLD";
    ExN02DetectorConstruction_Tube* Tube2_E_CLD = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube2_E_CLD,
					   -alpha2_87*deg,
					   innerRadiusTube2_E*cm,
					   outerRadiusTube2_E*cm,
					   length_Tube2_E*cm,
					   BP1Mater,
					   90.*deg,
					   180.*deg,
					   name);
    Tube2_E_CLD->Construct();
    logicTube2_E_CLD = Tube2_E_CLD->GetlogicVol();
    
    // vacuum in left upper half tube2
    name = "Tube2_E_CLD_v";
    ExN02DetectorConstruction_Tube* Tube2_E_CLD_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube2_E_CLD,
					   -alpha2_87*deg,
					   0.,
					   innerRadiusTube2_E*cm,
					   length_Tube2_E*cm,
					   BP1Mater_v,
					   90.*deg,
					   180.*deg,
					   name);
    Tube2_E_CLD_v->Construct();
    logicTube2_E_CLD_v = Tube2_E_CLD_v->GetlogicVol();  

    //-------------------------------------------------------------------------------------------------------
    // left upper Trapezoid
    //----------------- 
    G4ThreeVector positionTube2_E_TRLU = G4ThreeVector(x_Tube2_E_TRLU*cm,y_Tube2_E_TRLU*cm,z_Tube2_E_TRLU*cm);
    solidTube2_E_TRLU = new G4Trd("Tube2_E_TRRU",
				  dx2_Tube2_E_TR/2.*cm,
				  dx1_Tube2_E_TR/2.*cm,
				  dy2_Tube2_E_TR/2.*cm,
				  dy1_Tube2_E_TR/2.*cm,
				  dz_Tube2_E_TR/2.*cm);
    logicTube2_E_TRLU = new G4LogicalVolume(solidTube2_E_TRLU,BP1Mater,"Tube2_E_TRLU",0,0,0);
    physiTube2_E_TRLU = new G4PVPlacement(0,                   // no rotation
					  positionTube2_E_TRLU, // at (x,y,z)
					  logicTube2_E_TRLU,    // its logical volume
					  "Tube2_E_TRLU",       // its name
					  logicWorld,           // its mother  volume
					  false,                // no boolean operations
					  0);                   // copy number 
    
    //-----------------
    // left lower  Trapezoid
    //----------------- 
    G4ThreeVector positionTube2_E_TRLD = G4ThreeVector(x_Tube2_E_TRLD*cm,y_Tube2_E_TRLD*cm,z_Tube2_E_TRLD*cm);
    solidTube2_E_TRLD = new G4Trd("Tube2_E_TRLD",
				  dx2_Tube2_E_TR/2.*cm,
				  dx1_Tube2_E_TR/2.*cm,
				  dy2_Tube2_E_TR/2.*cm,
				  dy1_Tube2_E_TR/2.*cm,
				  dz_Tube2_E_TR/2.*cm);
    logicTube2_E_TRLD = new G4LogicalVolume(solidTube2_E_TRLD,BP1Mater,"Tube2_E_TRLD",0,0,0);
    physiTube2_E_TRLD = new G4PVPlacement(0,                   // no rotation
					  positionTube2_E_TRLD, // at (x,y,z)
					  logicTube2_E_TRLD,    // its logical volume
					  "Tube2_E_TRLD",       // its name
					  logicWorld,           // its mother  volume
					  false,                // no boolean operations
					  0);                   // copy number 

    //------------------------
    // Trapezoid vacuum within
    //------------------------
    G4cout<<"     Create tube2 trepezoid vacuum within : begin"<<G4endl;
    G4ThreeVector positionTube2_E_TRL_v = G4ThreeVector(x_Tube2_E_TRL_v*cm,y_Tube2_E_TRL_v*cm,z_Tube2_E_TRL_v*cm);
    solidTube2_E_TRL_v = new G4Trd("Tube2_E_TRL_v",
				   dx2_Tube2_E_TR_v/2.*cm,
				   dx1_Tube2_E_TR_v/2.*cm,
				   dy2_Tube2_E_TR_v/2.*cm,
				   dy1_Tube2_E_TR_v/2.*cm,
				   dz_Tube2_E_TR_v/2.*cm);
    logicTube2_E_TRL_v = new G4LogicalVolume(solidTube2_E_TRL_v,BP1Mater_v,"Tube2_E_TRL_v",0,0,0);
    physiTube2_E_TRL_v = new G4PVPlacement(0,                   // no rotation
					   positionTube2_E_TRL_v, // at (x,y,z)
					   logicTube2_E_TRL_v,    // its logical volume
					   "Tube2_E_TRL_v",       // its name
					   logicWorld,           // its mother  volume
					   false,                // no boolean operations
					   0);                   // copy number 
    //------------------------------------------------------------------------------------------------------------
    
    //--------------------------------------------
    // V-like tube!!!!!!!! right
    // Consist of big and little trapezoids made of aluminium
    // and two tubes vacuum within
    //--------------------------------------------


    //------------------------------------------------------------------------------------------------------------
    // right big trapezoid 
    //------------------------


    ExN02DetectorConstruction_VTube *V_like_Tube3 = new ExN02DetectorConstruction_VTube(logicWorld,BP1Mater,BP1Mater_v);
    
    V_like_Tube3->ConstructVlikeTube("right",BP1Mater,BP1Mater_v);
    V_like_Tube3->ConstructVlikeTube("left",BP1Mater,BP1Mater_v);


/*
    G4ThreeVector positionTube3_TR1_R = G4ThreeVector(x_Tube3_Center_TR1_R*cm,y_Tube3_Center_TR1_R*cm,z_Tube3_Center_TR1_R*cm);
    solidTube3_TR1_R = new G4Trd("Tube3_TR1_R",
				 dx1_Tube3_TR1/2.*cm,
				 dx2_Tube3_TR1/2.*cm,
				 dy1_Tube3_TR1/2.*cm,
				 dy2_Tube3_TR1/2.*cm,
				 dz_Tube3_TR1/2.*cm);
    logicTube3_TR1_R = new G4LogicalVolume(solidTube3_TR1_R,BP1Mater,"Tube3_TR1_R",0,0,0);
    physiTube3_TR1_R = new G4PVPlacement(0,                   // no rotation
					 positionTube3_TR1_R, // at (x,y,z)
					 logicTube3_TR1_R,    // its logical volume
					 "Tube3_TR_R",        // its name
					 logicWorld,          // its mother  volume
					 false,               // no boolean operations
					 0);                  // copy number 
    
    //------------------------
    // right little trapezoid 
    //------------------------
    G4ThreeVector positionTube3_TR2_R = G4ThreeVector(x_Tube3_Center_TR2_R*cm,y_Tube3_Center_TR2_R*cm,z_Tube3_Center_TR2_R*cm);
    solidTube3_TR2_R = new G4Trd("Tube3_TR2_R",
				 dx1_Tube3_TR2/2.*cm,
				 dx2_Tube3_TR2/2.*cm,
				 dy1_Tube3_TR2/2.*cm,
				 dy2_Tube3_TR2/2.*cm,
				 dz_Tube3_TR2/2.*cm);
    logicTube3_TR2_R = new G4LogicalVolume(solidTube3_TR2_R,BP1Mater,"Tube3_TR2_R",0,0,0);
    physiTube3_TR2_R = new G4PVPlacement(0,                   // no rotation
					 positionTube3_TR2_R, // at (x,y,z)
					 logicTube3_TR2_R,    // its logical volume
					 "Tube3_TR_R",        // its name
					 logicWorld,          // its mother  volume
					 false,               // no boolean operations
					 0);                  // copy number 
    //-----------------------------------------------------------------------------------------------------------------------

    //tube3 right upper vacuum within
    G4ThreeVector positionTube3_TU_R_U = G4ThreeVector(x_Tube3_Center_TU_R_U*cm,y_Tube3_Center_TU_R_U*cm,z_Tube3_Center_TU_R_U*cm);
    name = "Tube3_TU_R_U";
    ExN02DetectorConstruction_Tube* Tube3_TU_R_U = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube3_TU_R_U,
					   -alpha7_104*deg,
					   innerradius_Tube3_TU*cm,
					   outerradius_Tube3_TU*cm,
					   length_Tube3_TU*cm,
					   BP1Mater_v,
					   0.,
					   360*deg,
					   name);
    Tube3_TU_R_U->Construct();
    logicTube3_TU_R_U = Tube3_TU_R_U->GetlogicVol();

    //tube3 right bottom vacuum within
    G4ThreeVector positionTube3_TU_R_D = G4ThreeVector(x_Tube3_Center_TU_R_D*cm,y_Tube3_Center_TU_R_D*cm,z_Tube3_Center_TU_R_D*cm);
    name = "Tube3_TU_R_D";
    ExN02DetectorConstruction_Tube* Tube3_TU_R_D = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube3_TU_R_D,
					   alpha7_104*deg,
					   innerradius_Tube3_TU*cm,
					   outerradius_Tube3_TU*cm,
					   length_Tube3_TU*cm,
					   BP1Mater_v,
					   0.,
					   360*deg,
					   name);
    Tube3_TU_R_D->Construct();
    logicTube3_TU_R_D = Tube3_TU_R_D->GetlogicVol();

    //--------------------------------------------
    // V-like tube!!!!!!!! left
    //--------------------------------------------

    //------------------------------------------------------------------------------------------------------------
    // right big trapezoid 
    //------------------------
    G4ThreeVector positionTube3_TR1_L = G4ThreeVector(x_Tube3_Center_TR1_L*cm,y_Tube3_Center_TR1_L*cm,z_Tube3_Center_TR1_L*cm);
    solidTube3_TR1_L = new G4Trd("Tube3_TR1_L",
				 dx2_Tube3_TR1/2.*cm,
				 dx1_Tube3_TR1/2.*cm,
				 dy2_Tube3_TR1/2.*cm,
				 dy1_Tube3_TR1/2.*cm,
				 dz_Tube3_TR1/2.*cm);
    logicTube3_TR1_L = new G4LogicalVolume(solidTube3_TR1_L,BP1Mater,"Tube3_TR1_L",0,0,0);
    physiTube3_TR1_L = new G4PVPlacement(0,                 // no rotation
					 positionTube3_TR1_L, // at (x,y,z)
					 logicTube3_TR1_L,    // its logical volume
					 "Tube3_TR_L",       // its name
					 logicWorld,         // its mother  volume
					 false,              // no boolean operations
					 0);                 // copy number 
    
    //------------------------
    // right little trapezoid 
    //------------------------
    G4ThreeVector positionTube3_TR2_L = G4ThreeVector(x_Tube3_Center_TR2_L*cm,y_Tube3_Center_TR2_L*cm,z_Tube3_Center_TR2_L*cm);
    solidTube3_TR2_L = new G4Trd("Tube3_TR2_L",
				 dx2_Tube3_TR2/2.*cm,
				 dx1_Tube3_TR2/2.*cm,
				 dy2_Tube3_TR2/2.*cm,
				 dy1_Tube3_TR2/2.*cm,
				 dz_Tube3_TR2/2.*cm);
    logicTube3_TR2_L = new G4LogicalVolume(solidTube3_TR2_L,BP1Mater,"Tube3_TR2_L",0,0,0);
    physiTube3_TR2_L = new G4PVPlacement(0,                 // no rotation
					 positionTube3_TR2_L, // at (x,y,z)
					 logicTube3_TR2_L,    // its logical volume
					 "Tube3_TR_L",       // its name
					 logicWorld,         // its mother  volume
					 false,              // no boolean operations
					 0);                 // copy number 
    //----------------------------------------------------------------------------------
  
    //tube3 right upper vacuum within
    G4ThreeVector positionTube3_TU_L_U = G4ThreeVector(x_Tube3_Center_TU_L_U*cm,y_Tube3_Center_TU_L_U*cm,z_Tube3_Center_TU_L_U*cm);
    name = "Tube3_TU_L_U";
    ExN02DetectorConstruction_Tube* Tube3_TU_L_U = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube3_TU_L_U,
					   alpha7_104*deg,
					   innerradius_Tube3_TU*cm,
					   outerradius_Tube3_TU*cm,
					   length_Tube3_TU*cm,
					   BP1Mater_v,
					   0.,
					   360*deg,
					   name);
    Tube3_TU_L_U->Construct();
    logicTube3_TU_L_U = Tube3_TU_L_U->GetlogicVol();

    //tube3 right bottom vacuum within
    G4ThreeVector positionTube3_TU_L_D = G4ThreeVector(x_Tube3_Center_TU_L_D*cm,y_Tube3_Center_TU_L_D*cm,z_Tube3_Center_TU_L_D*cm);
    name = "Tube3_TU_L_D";
    ExN02DetectorConstruction_Tube* Tube3_TU_L_D = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube3_TU_L_D,
					   -alpha7_104*deg,
					   innerradius_Tube3_TU*cm,
					   outerradius_Tube3_TU*cm,
					   length_Tube3_TU*cm,
					   BP1Mater_v,
					   0.,
					   360*deg,
					   name);
    Tube3_TU_L_D->Construct();
    logicTube3_TU_L_D = Tube3_TU_L_D->GetlogicVol();
*/
    //--------------------------------------------
    // tube4 
    // Tube conect to the V-like tube
    //--------------------------------------------
   
    // tube4 right uper
    G4ThreeVector positionTube4_R_U = G4ThreeVector(x_Tube4_R_U*cm,y_Tube4_R_U*cm,z_Tube4_R_U*cm);
    name = "Tube4_R_U";
    ExN02DetectorConstruction_Tube* Tube4_R_U = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube4_R_U,
					   -alpha*deg,
					   innerRadius_Tube1*cm,
					   outerRadius_Tube1*cm,
					   length_Tube4*cm,
					   BP1Mater,
					   0.,
					   360*deg,
					   name);
    physiTube4_R_U_v = Tube4_R_U->Construct();
    logicTube4_R_U = Tube4_R_U->GetlogicVol();

    //tube4 right uper vacuum
    name = "Tube4_R_U_v";
    ExN02DetectorConstruction_Tube* Tube4_R_U_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube4_R_U,
					   -alpha*deg,
					   0.,
					   innerRadius_Tube1*cm,
					   length_Tube4*cm,
					   BP1Mater_v,
					   0.,
					   360*deg,
					   name);
    Tube4_R_U_v->Construct();
    logicTube4_R_U_v = Tube4_R_U_v->GetlogicVol();

    // tube4 right bottom
    G4ThreeVector positionTube4_R_D = G4ThreeVector(x_Tube4_R_D*cm,y_Tube4_R_D*cm,z_Tube4_R_D*cm);
    name = "Tube4_R_D";
    ExN02DetectorConstruction_Tube* Tube4_R_D = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube4_R_D,
					   alpha*deg,
					   innerRadius_Tube1*cm,
					   outerRadius_Tube1*cm,
					   length_Tube4*cm,
					   BP1Mater,
					   0.,
					   360*deg,
					   name);
    Tube4_R_D->Construct();
    logicTube4_R_D = Tube4_R_D->GetlogicVol();

    //tube4 right bottom vacuum
    name = "Tube4_R_D_v";
    ExN02DetectorConstruction_Tube* Tube4_R_D_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube4_R_D,
					   alpha*deg,
					   0.,
					   innerRadius_Tube1*cm,
					   length_Tube4*cm,
					   BP1Mater_v,
					   0.,
					   360*deg,
					   name);
    Tube4_R_D_v->Construct();
    logicTube4_R_D_v = Tube4_R_D_v->GetlogicVol();
    
    //tubes4 lefrt upper
    G4ThreeVector positionTube4_L_U = G4ThreeVector(x_Tube4_L_U*cm,y_Tube4_L_U*cm,z_Tube4_L_U*cm);
    name = "Tube4_L_U";
    ExN02DetectorConstruction_Tube* Tube4_L_U = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube4_L_U,
					   alpha*deg,
					   innerRadius_Tube1*cm,
					   outerRadius_Tube1*cm,
					   length_Tube4*cm,
					   BP1Mater,
					   0.,
					   360*deg,
					   name);
    Tube4_L_U->Construct();
    logicTube4_L_U = Tube4_L_U->GetlogicVol();

    //tube4 left uper vacuum
    name = "Tube4_L_U_v";
    ExN02DetectorConstruction_Tube* Tube4_L_U_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube4_L_U,
					   alpha*deg,
					   0.,
					   innerRadius_Tube1*cm,
					   length_Tube4*cm,
					   BP1Mater_v,
					   0.,
					   360*deg,
					   name);
    Tube4_L_U_v->Construct();
    logicTube4_L_U_v = Tube4_L_U_v->GetlogicVol();

    // tube4 left bottom
    G4ThreeVector positionTube4_L_D = G4ThreeVector(x_Tube4_L_D*cm,y_Tube4_L_D*cm,z_Tube4_L_D*cm);
    name = "Tube4_L_D";
    ExN02DetectorConstruction_Tube* Tube4_L_D = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube4_L_D,
					   -alpha*deg,
					   innerRadius_Tube1*cm,
					   outerRadius_Tube1*cm,
					   length_Tube4*cm,
					   BP1Mater,
					   0.,
					   360*deg,
					   name);
    Tube4_L_D->Construct();
    logicTube4_L_D = Tube4_L_D->GetlogicVol();

    //tube4 left bottom vacuum
    name = "Tube4_L_D_v";
    ExN02DetectorConstruction_Tube* Tube4_L_D_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube4_L_D,
					   -alpha*deg,
					   0.,
					   innerRadius_Tube1*cm,
					   length_Tube4*cm,
					   BP1Mater_v,
					   0.,
					   360*deg,
					   name);
    Tube4_L_D_v->Construct();
    logicTube4_L_D_v = Tube4_L_D_v->GetlogicVol();

    //--------------------------------------------
    // tube5 
    // End of the BP
    // tube5 consist of two parts: cylindrical and conical tubes
    //--------------------------------------------

    //tube5 right upper cylindrical part 
    G4ThreeVector positionTube5_C_R_U = G4ThreeVector(x_Tube5_C_R_U*cm,y_Tube5_C_R_U*cm,z_Tube5_C_R_U*cm);
    name = "Tube5_C_R_U";
    ExN02DetectorConstruction_Tube* Tube5_C_R_U = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube5_C_R_U,
					   -alpha*deg,
					   innerRadius_Tube1*cm,
					   outerRadius_Tube1*cm,
					   length_Tube5_C*cm,
					   BP1Mater,
					   0.,
					   360*deg,
					   name);
    Tube5_C_R_U->Construct();
    logicTube5_C_R_U = Tube5_C_R_U->GetlogicVol();

    //tube5 right uper vacuum
    name = "Tube5_C_R_U_v";
    ExN02DetectorConstruction_Tube* Tube5_C_R_U_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube5_C_R_U,
					   -alpha*deg,
					   0.,
					   innerRadius_Tube1*cm,
					   length_Tube5_C*cm,
					   BP1Mater_v,
					   0.,
					   360*deg,
					   name);
    Tube5_C_R_U_v->Construct();
    logicTube5_C_R_U_v = Tube5_C_R_U_v->GetlogicVol();

    // tube5 right bottom
    G4ThreeVector positionTube5_C_R_D = G4ThreeVector(x_Tube5_C_R_D*cm,y_Tube5_C_R_D*cm,z_Tube5_C_R_D*cm);
    name = "Tube5_C_R_D";
    ExN02DetectorConstruction_Tube* Tube5_C_R_D = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube5_C_R_D,
					   alpha*deg,
					   innerRadius_Tube1*cm,
					   outerRadius_Tube1*cm,
					   length_Tube5_C*cm,
					   BP1Mater,
					   0.,
					   360*deg,
					   name);
    Tube5_C_R_D->Construct();
    logicTube5_C_R_D = Tube5_C_R_D->GetlogicVol();

    //tube5 right bottom vacuum
    name = "Tube5_C_R_D_v";
    ExN02DetectorConstruction_Tube* Tube5_C_R_D_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube5_C_R_D,
					   alpha*deg,
					   0.,
					   innerRadius_Tube1*cm,
					   length_Tube5_C*cm,
					   BP1Mater_v,
					   0.,
					   360*deg,
					   name);
    Tube5_C_R_D_v->Construct();
    logicTube5_C_R_D_v = Tube5_C_R_D_v->GetlogicVol();
    
    //tubes5 lefrt upper
    G4ThreeVector positionTube5_C_L_U = G4ThreeVector(x_Tube5_C_L_U*cm,y_Tube5_C_L_U*cm,z_Tube5_C_L_U*cm);
    name = "Tube5_C_L_U";
    ExN02DetectorConstruction_Tube* Tube5_C_L_U = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube5_C_L_U,
					   alpha*deg,
					   innerRadius_Tube1*cm,
					   outerRadius_Tube1*cm,
					   length_Tube5_C*cm,
					   BP1Mater,
					   0.,
					   360*deg,
					   name);
    Tube5_C_L_U->Construct();
    logicTube5_C_L_U = Tube5_C_L_U->GetlogicVol();

    //tube5 left uper vacuum
    name = "Tube5_C_L_U_v";
    ExN02DetectorConstruction_Tube* Tube5_C_L_U_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube5_C_L_U,
					   alpha*deg,
					   0.,
					   innerRadius_Tube1*cm,
					   length_Tube5_C*cm,
					   BP1Mater_v,
					   0.,
					   360*deg,
					   name);
    Tube5_C_L_U_v->Construct();
    logicTube5_C_L_U_v = Tube5_C_L_U_v->GetlogicVol();

    // tube5 left bottom
    G4ThreeVector positionTube5_C_L_D = G4ThreeVector(x_Tube5_C_L_D*cm,y_Tube5_C_L_D*cm,z_Tube5_C_L_D*cm);
    name = "Tube5_C_L_D";
    ExN02DetectorConstruction_Tube* Tube5_C_L_D = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube5_C_L_D,
					   -alpha*deg,
					   innerRadius_Tube1*cm,
					   outerRadius_Tube1*cm,
					   length_Tube5_C*cm,
					   BP1Mater,
					   0.,
					   360*deg,
					   name);
    Tube5_C_L_D->Construct();
    logicTube5_C_L_D = Tube5_C_L_D->GetlogicVol();

    //tube4 left bottom vacuum
    name = "Tube5_C_L_D_v";
    ExN02DetectorConstruction_Tube* Tube5_C_L_D_v = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionTube5_C_L_D,
					   -alpha*deg,
					   0.,
					   innerRadius_Tube1*cm,
					   length_Tube5_C*cm,
					   BP1Mater_v,
					   0.,
					   360*deg,
					   name);
    Tube5_C_L_D_v->Construct();
    logicTube5_C_L_D_v = Tube5_C_L_D_v->GetlogicVol();

   
    //--------------------------------------------
    // tube5 cone part
    //--------------------------------------------

    //tube5 cone R U 
    G4ThreeVector positionTube5_Co_R_U = G4ThreeVector(x_Tube5_Co_R_U*cm,y_Tube5_Co_R_U*cm,z_Tube5_Co_R_U*cm);
    G4double innerRadius1Tube5_Co_R_U = r1min_Tube5_Co*cm;
    G4double innerRadius2Tube5_Co_R_U = r2min_Tube5_Co*cm;
    G4double outerRadius1Tube5_Co_R_U = r1max_Tube5_Co*cm;
    G4double outerRadius2Tube5_Co_R_U = r2max_Tube5_Co*cm;
    G4double heightTube5_Co_R_U = 0.5*length_Tube5_Co*cm;
    G4double startAngleTube5_Co_R_U = 0.*deg;
    G4double spanningAngleTube5_Co_R_U = 360.*deg;    
    solidTube5_Co_R_U = new G4Cons("Tube5_Co_R_U",
				   innerRadius1Tube5_Co_R_U,
				   outerRadius1Tube5_Co_R_U,
				   innerRadius2Tube5_Co_R_U,
				   outerRadius2Tube5_Co_R_U,
				   heightTube5_Co_R_U,
				   startAngleTube5_Co_R_U,
				   spanningAngleTube5_Co_R_U);    
    G4RotationMatrix *pRotTube5_Co_R_U = new G4RotationMatrix();// Rotates X and Z axes only
    pRotTube5_Co_R_U->rotateY(-alpha*deg);                       // Rotates 4.07 degrees
    logicTube5_Co_R_U = new G4LogicalVolume(solidTube5_Co_R_U,BP1Mater,"Tube5_Co_R_U",0,0,0);
    physiTube5_Co_R_U = new G4PVPlacement(pRotTube5_Co_R_U,   // rotation
					  positionTube5_Co_R_U,  // at (x,y,z)
					  logicTube5_Co_R_U,     // its logical volume
					  "Tube5_Co_R_U",        // its name
					  logicWorld,            // its mother  volume
					  false,                 // no boolean operations
					  0);                    // copy number 
   
    //tube5 cone right apper vacuum
    G4double innerRadius1Tube5_Co_R_U_v = 0.*cm;
    G4double outerRadius1Tube5_Co_R_U_v = innerRadius1Tube5_Co_R_U;
    G4double innerRadius2Tube5_Co_R_U_v = 0.*cm;
    G4double outerRadius2Tube5_Co_R_U_v = innerRadius2Tube5_Co_R_U;
    solidTube5_Co_R_U_v = new G4Cons("Tube5_Co_R_U",
				     innerRadius1Tube5_Co_R_U_v,
				     outerRadius1Tube5_Co_R_U_v,
				     innerRadius2Tube5_Co_R_U_v,
				     outerRadius2Tube5_Co_R_U_v,
				     heightTube5_Co_R_U,
				     startAngleTube5_Co_R_U,
				     spanningAngleTube5_Co_R_U);    
    logicTube5_Co_R_U_v = new G4LogicalVolume(solidTube5_Co_R_U_v,BP1Mater_v,"Tube5_Co_R_U_v",0,0,0);
    physiTube5_Co_R_U_v = new G4PVPlacement(pRotTube5_Co_R_U, // rotation
					    positionTube5_Co_R_U,  // at (x,y,z)
					    logicTube5_Co_R_U_v,   // its logical volume
					    "Tube5_C_R_U_v",       // its name
					    logicWorld,            // its mother  volume
					    false,                 // no boolean operations
					    0);                    // copy number 
   
    //tube5 cone right bottom
    G4ThreeVector positionTube5_Co_R_D = G4ThreeVector(x_Tube5_Co_R_D*cm,y_Tube5_Co_R_D*cm,z_Tube5_Co_R_D*cm);
    G4double innerRadius1Tube5_Co_R_D = r1min_Tube5_Co*cm;
    G4double innerRadius2Tube5_Co_R_D = r2min_Tube5_Co*cm;
    G4double outerRadius1Tube5_Co_R_D = r1max_Tube5_Co*cm;
    G4double outerRadius2Tube5_Co_R_D = r2max_Tube5_Co*cm;
    G4double heightTube5_Co_R_D = 0.5*length_Tube5_Co*cm;
    G4double startAngleTube5_Co_R_D = 0.*deg;
    G4double spanningAngleTube5_Co_R_D = 360.*deg;    
    solidTube5_Co_R_D = new G4Cons("Tube5_Co_R_D",
				   innerRadius1Tube5_Co_R_D,
				   outerRadius1Tube5_Co_R_D,
				   innerRadius2Tube5_Co_R_D,
				   outerRadius2Tube5_Co_R_D,
				   heightTube5_Co_R_D,
				   startAngleTube5_Co_R_D,
				   spanningAngleTube5_Co_R_D);    
    G4RotationMatrix *pRotTube5_Co_R_D = new G4RotationMatrix();// Rotates X and Z axes only
    pRotTube5_Co_R_D->rotateY(alpha*deg);                       // Rotates 4.07 degrees
    logicTube5_Co_R_D = new G4LogicalVolume(solidTube5_Co_R_D,BP1Mater,"Tube5_Co_R_D",0,0,0);
    physiTube5_Co_R_D = new G4PVPlacement(pRotTube5_Co_R_D,   // rotation
					  positionTube5_Co_R_D,  // at (x,y,z)
					  logicTube5_Co_R_D,     // its logical volume
					  "Tube5_Co_R_D",        // its name
					  logicWorld,            // its mother  volume
					  false,                 // no boolean operations
					  0);                    // copy number 
   
    //tube5 cone right bottom vacuum
    G4double innerRadius1Tube5_Co_R_D_v = 0.*cm;
    G4double outerRadius1Tube5_Co_R_D_v = innerRadius1Tube5_Co_R_D;
    G4double innerRadius2Tube5_Co_R_D_v = 0.*cm;
    G4double outerRadius2Tube5_Co_R_D_v = innerRadius2Tube5_Co_R_D;
    solidTube5_Co_R_D_v = new G4Cons("Tube5_Co_R_D",
				     innerRadius1Tube5_Co_R_D_v,
				     outerRadius1Tube5_Co_R_D_v,
				     innerRadius2Tube5_Co_R_D_v,
				     outerRadius2Tube5_Co_R_D_v,
				     heightTube5_Co_R_D,
				     startAngleTube5_Co_R_D,
				     spanningAngleTube5_Co_R_D);    
    logicTube5_Co_R_D_v = new G4LogicalVolume(solidTube5_Co_R_D_v,BP1Mater_v,"Tube5_Co_R_D_v",0,0,0);
    physiTube5_Co_R_D_v = new G4PVPlacement(pRotTube5_Co_R_D, // rotation
					    positionTube5_Co_R_D,  // at (x,y,z)
					    logicTube5_Co_R_D_v,   // its logical volume
					    "Tube5_C_R_D_v",       // its name
					    logicWorld,            // its mother  volume
					    false,                 // no boolean operations
					    0);                    // copy number 

    // tube5 cone left upper 
    G4ThreeVector positionTube5_Co_L_U = G4ThreeVector(x_Tube5_Co_L_U*cm,y_Tube5_Co_L_U*cm,z_Tube5_Co_L_U*cm);
    G4double innerRadius1Tube5_Co_L_U = r1min_Tube5_Co*cm;
    G4double innerRadius2Tube5_Co_L_U = r2min_Tube5_Co*cm;
    G4double outerRadius1Tube5_Co_L_U = r1max_Tube5_Co*cm;
    G4double outerRadius2Tube5_Co_L_U = r2max_Tube5_Co*cm;
    G4double heightTube5_Co_L_U = 0.5*length_Tube5_Co*cm;
    G4double startAngleTube5_Co_L_U = 0.*deg;
    G4double spanningAngleTube5_Co_L_U = 360.*deg;    
    solidTube5_Co_L_U = new G4Cons("Tube5_Co_L_U",
	   innerRadius2Tube5_Co_L_U,
	   outerRadius2Tube5_Co_L_U,
	   innerRadius1Tube5_Co_L_U,
	   outerRadius1Tube5_Co_L_U,
	   heightTube5_Co_L_U,
	   startAngleTube5_Co_L_U,
	   spanningAngleTube5_Co_L_U);    
    G4RotationMatrix *pRotTube5_Co_L_U = new G4RotationMatrix();// Rotates X and Z axes only
    pRotTube5_Co_L_U->rotateY(alpha*deg);                       // Rotates 4.07 degrees
    logicTube5_Co_L_U = new G4LogicalVolume(solidTube5_Co_L_U,BP1Mater,"Tube5_Co_L_U",0,0,0);
    physiTube5_Co_L_U = new G4PVPlacement(pRotTube5_Co_L_U,   // rotation
					  positionTube5_Co_L_U,  // at (x,y,z)
					  logicTube5_Co_L_U,     // its logical volume
					  "Tube5_Co_L_U",        // its name
					  logicWorld,            // its mother  volume
					  false,                 // no boolean operations
					  0);                    // copy number 
   
    //tube5 cone left upper vacuum
    G4double innerRadius1Tube5_Co_L_U_v = 0.*cm;
    G4double outerRadius1Tube5_Co_L_U_v = innerRadius1Tube5_Co_R_U;
    G4double innerRadius2Tube5_Co_L_U_v = 0.*cm;
    G4double outerRadius2Tube5_Co_L_U_v = innerRadius2Tube5_Co_R_U;
    solidTube5_Co_L_U_v = new G4Cons("Tube5_Co_L_U",
				     innerRadius2Tube5_Co_L_U_v,
				     outerRadius2Tube5_Co_L_U_v,
				     innerRadius1Tube5_Co_L_U_v,
				     outerRadius1Tube5_Co_L_U_v,
				     heightTube5_Co_L_U,
				     startAngleTube5_Co_L_U,
				     spanningAngleTube5_Co_L_U);    
    logicTube5_Co_L_U_v = new G4LogicalVolume(solidTube5_Co_L_U_v,BP1Mater_v,"Tube5_Co_L_U_v",0,0,0);
    physiTube5_Co_L_U_v = new G4PVPlacement(pRotTube5_Co_L_U, // rotation
					    positionTube5_Co_L_U,  // at (x,y,z)
					    logicTube5_Co_L_U_v,   // its logical volume
					    "Tube5_C_L_U_v",       // its name
					    logicWorld,            // its mother  volume
					    false,                 // no boolean operations
					    0);                    // copy number 

    //tube5 cone left bottom
    G4ThreeVector positionTube5_Co_L_D = G4ThreeVector(x_Tube5_Co_L_D*cm,y_Tube5_Co_L_D*cm,z_Tube5_Co_L_D*cm);
    G4double innerRadius1Tube5_Co_L_D = r1min_Tube5_Co*cm;
    G4double innerRadius2Tube5_Co_L_D = r2min_Tube5_Co*cm;
    G4double outerRadius1Tube5_Co_L_D = r1max_Tube5_Co*cm;
    G4double outerRadius2Tube5_Co_L_D = r2max_Tube5_Co*cm;
    G4double heightTube5_Co_L_D = 0.5*length_Tube5_Co*cm;
    G4double startAngleTube5_Co_L_D = 0.*deg;
    G4double spanningAngleTube5_Co_L_D = 360.*deg;    
    solidTube5_Co_L_D = new G4Cons("Tube5_Co_L_D",
	   innerRadius2Tube5_Co_L_D,
	   outerRadius2Tube5_Co_L_D,
	   innerRadius1Tube5_Co_L_D,
	   outerRadius1Tube5_Co_L_D,
	   heightTube5_Co_L_D,
	   startAngleTube5_Co_L_D,
	   spanningAngleTube5_Co_L_D);    
    G4RotationMatrix *pRotTube5_Co_L_D = new G4RotationMatrix();// Rotates X and Z axes only
    pRotTube5_Co_L_D->rotateY(-alpha*deg);                       // Rotates 4.07 degrees
    logicTube5_Co_L_D = new G4LogicalVolume(solidTube5_Co_L_D,BP1Mater,"Tube5_Co_L_D",0,0,0);
    physiTube5_Co_L_D = new G4PVPlacement(pRotTube5_Co_L_D,   // rotation
					  positionTube5_Co_L_D,  // at (x,y,z)
					  logicTube5_Co_L_D,     // its logical volume
					  "Tube5_Co_L_D",        // its name
					  logicWorld,            // its mother  volume
					  false,                 // no boolean operations
					  0);                    // copy number 

    // tube5 cone left bottom vacuum
    G4double innerRadius1Tube5_Co_L_D_v = 0.*cm;
    G4double outerRadius1Tube5_Co_L_D_v = innerRadius1Tube5_Co_L_D;
    G4double innerRadius2Tube5_Co_L_D_v = 0.*cm;
    G4double outerRadius2Tube5_Co_L_D_v = innerRadius2Tube5_Co_L_D;
    solidTube5_Co_L_D_v = new G4Cons("Tube5_Co_L_D",
				     innerRadius2Tube5_Co_L_D_v,
				     outerRadius2Tube5_Co_L_D_v,
				     innerRadius1Tube5_Co_L_D_v,
				     outerRadius1Tube5_Co_L_D_v,
				     heightTube5_Co_L_D,
				     startAngleTube5_Co_L_D,
				     spanningAngleTube5_Co_L_D);    
    logicTube5_Co_L_D_v = new G4LogicalVolume(solidTube5_Co_L_D_v,BP1Mater_v,"Tube5_Co_L_D_v",0,0,0);
    physiTube5_Co_L_D_v = new G4PVPlacement(pRotTube5_Co_L_D, // rotation
					    positionTube5_Co_L_D,  // at (x,y,z)
					    logicTube5_Co_L_D_v,   // its logical volume
					    "Tube5_C_R_D_v",       // its name
					    logicWorld,            // its mother  volume
					    false,                 // no boolean operations
					    0);                    // copy number 
    

    //--------------------------------------------------------------- 
    // !!!!!!!!!!!! construction of the SOYUZ shielding !!!!!!!!!!!
    //---------------------------------------------------------------

    // Tube part 1 right
    G4ThreeVector positionSOY_T1_R = G4ThreeVector(x_SOY_T1_R*cm, y_SOY_T1_R*cm, z_SOY_T1_R*cm);
    name = "SOY_T1_R";
    ExN02DetectorConstruction_Tube* SOY_T1_R = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionSOY_T1_R,
					   0.0*deg,
					   innerRadius_SOY_T1*cm,
					   outerRadius_SOY_T1*cm,
					   length_SOY_T1*cm,
					   ShieldsMater,
					   0.,
					   360*deg,
					   name);
    SOY_T1_R->Construct();
    logicSOY_T1_R = SOY_T1_R->GetlogicVol();

    // Tube part 1 left
    G4ThreeVector positionSOY_T1_L = G4ThreeVector(x_SOY_T1_L*cm, y_SOY_T1_L*cm, z_SOY_T1_L*cm);
    name = "SOY_T1_L";
    ExN02DetectorConstruction_Tube* SOY_T1_L = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionSOY_T1_L,
					   0.0*deg,
					   innerRadius_SOY_T1*cm,
					   outerRadius_SOY_T1*cm,
					   length_SOY_T1*cm,
					   ShieldsMater,
					   0.,
					   360*deg,
					   name);
    SOY_T1_L->Construct();
    logicSOY_T1_L = SOY_T1_L->GetlogicVol();

    // Tube part 2 right
    G4ThreeVector positionSOY_T2_R = G4ThreeVector(x_SOY_T2_R*cm, y_SOY_T2_R*cm, z_SOY_T2_R*cm);
    name = "SOY_T2_R";
    ExN02DetectorConstruction_Tube* SOY_T2_R = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionSOY_T2_R,
					   0.0*deg,
					   innerRadius_SOY_T2*cm,
					   outerRadius_SOY_T2*cm,
					   length_SOY_T2*cm,
					   ShieldsMater,
					   0.,
					   360*deg,
					   name);
    SOY_T2_R->Construct();
    logicSOY_T2_R = SOY_T2_R->GetlogicVol();
 
    // Tube part 2 left
    G4ThreeVector positionSOY_T2_L = G4ThreeVector(x_SOY_T2_L*cm, y_SOY_T2_L*cm, z_SOY_T2_L*cm);
    name = "SOY_T2_L";
    ExN02DetectorConstruction_Tube* SOY_T2_L = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionSOY_T2_L,
					   0.0*deg,
					   innerRadius_SOY_T2*cm,
					   outerRadius_SOY_T2*cm,
					   length_SOY_T2*cm,
					   ShieldsMater,
					   0.,
					   360*deg,
					   name);
    SOY_T2_L->Construct();
    logicSOY_T2_L = SOY_T2_L->GetlogicVol();

    // Cone part 3 right
    G4ThreeVector positionSOY_Co3_R = G4ThreeVector(x_SOY_Co3_R*cm, y_SOY_Co3_R*cm, z_SOY_Co3_R*cm);
    name = "SOY_Co3_R";
    ExN02DetectorConstruction_Cone* SOY_Co3_R = 
	new ExN02DetectorConstruction_Cone(logicWorld,
					   positionSOY_Co3_R,
					   0.0*deg,
					   innerRadius1_SOY_Co3*cm,
					   outerRadius1_SOY_Co3*cm,
					   innerRadius2_SOY_Co3*cm,
					   outerRadius2_SOY_Co3*cm,
					   length_SOY_Co3*cm,
					   ShieldsMater,
					   0.,
					   360*deg,
					   name);
    SOY_Co3_R->Construct();
    logicSOY_Co3_R = SOY_Co3_R->GetlogicVol();

    // Cone part 3 left
    G4ThreeVector positionSOY_Co3_L = G4ThreeVector(x_SOY_Co3_L*cm, y_SOY_Co3_L*cm, z_SOY_Co3_L*cm);
    name = "SOY_Co3_L";
    ExN02DetectorConstruction_Cone* SOY_Co3_L = 
	new ExN02DetectorConstruction_Cone(logicWorld,
					   positionSOY_Co3_L,
					   0.0*deg,
					   innerRadius2_SOY_Co3*cm,
					   outerRadius2_SOY_Co3*cm,
					   innerRadius1_SOY_Co3*cm,
					   outerRadius1_SOY_Co3*cm,
					   length_SOY_Co3*cm,
					   ShieldsMater,
					   0.,
					   360*deg,
					   name);
    SOY_Co3_L->Construct();
    logicSOY_Co3_L = SOY_Co3_L->GetlogicVol();

    // Cone part 4 right
    G4ThreeVector positionSOY_Co4_R = G4ThreeVector(x_SOY_Co4_R*cm, y_SOY_Co4_R*cm, z_SOY_Co4_R*cm);
    name = "SOY_Co4_R";
    ExN02DetectorConstruction_Cone* SOY_Co4_R = 
	new ExN02DetectorConstruction_Cone(logicWorld,
					   positionSOY_Co4_R,
					   0.0*deg,
					   innerRadius1_SOY_Co4*cm,
					   outerRadius1_SOY_Co4*cm,
					   innerRadius2_SOY_Co4*cm,
					   outerRadius2_SOY_Co4*cm,
					   length_SOY_Co4*cm,
					   ShieldsMater,
					   0.,
					   360*deg,
					   name);
    SOY_Co4_R->Construct();
    logicSOY_Co4_R = SOY_Co4_R->GetlogicVol();

    // Cone part 4 left
    G4ThreeVector positionSOY_Co4_L = G4ThreeVector(x_SOY_Co4_L*cm, y_SOY_Co4_L*cm, z_SOY_Co4_L*cm);
    name = "SOY_Co4_L";
    ExN02DetectorConstruction_Cone* SOY_Co4_L = 
	new ExN02DetectorConstruction_Cone(logicWorld,
					   positionSOY_Co4_L,
					   0.0*deg,
					   innerRadius2_SOY_Co4*cm,
					   outerRadius2_SOY_Co4*cm,
					   innerRadius1_SOY_Co4*cm,
					   outerRadius1_SOY_Co4*cm,
					   length_SOY_Co4*cm,
					   ShieldsMater,
					   0.,
					   360*deg,
					   name);
    SOY_Co4_L->Construct();
    logicSOY_Co4_L = SOY_Co4_L->GetlogicVol();

    // Tube part 5 right
    G4ThreeVector positionSOY_T5_R = G4ThreeVector(x_SOY_T5_R*cm, y_SOY_T5_R*cm, z_SOY_T5_R*cm);
    name = "SOY_T5_R";
    ExN02DetectorConstruction_Tube* SOY_T5_R = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionSOY_T5_R,
					   0.0*deg,
					   innerRadius_SOY_T5*cm,
					   outerRadius_SOY_T5*cm,
					   length_SOY_T5*cm,
					   ShieldsMater,
					   0.,
					   360*deg,
					   name);
    SOY_T5_R->Construct();
    logicSOY_T5_R = SOY_T5_R->GetlogicVol();
    SOY_T5_R->PrintInfo();

    // Tube part 5 left
    G4ThreeVector positionSOY_T5_L = G4ThreeVector(x_SOY_T5_L*cm, y_SOY_T5_L*cm, z_SOY_T5_L*cm);
    name = "SOY_T5_L";
    ExN02DetectorConstruction_Tube* SOY_T5_L = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionSOY_T5_L,
					   0.0*deg,
					   innerRadius_SOY_T5*cm,
					   outerRadius_SOY_T5*cm,
					   length_SOY_T5*cm,
					   ShieldsMater,
					   0.,
					   360*deg,
					   name);
    SOY_T5_L->Construct();
    logicSOY_T5_L = SOY_T5_L->GetlogicVol();
    SOY_T5_L->PrintInfo();

    // Tube part 6 right
    G4ThreeVector positionSOY_T6_R = G4ThreeVector(x_SOY_T6_R*cm, y_SOY_T6_R*cm, z_SOY_T6_R*cm);
    name = "SOY_T6_R";
    ExN02DetectorConstruction_Tube* SOY_T6_R = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionSOY_T6_R,
					   0.0*deg,
					   innerRadius_SOY_T6*cm,
					   outerRadius_SOY_T6*cm,
					   length_SOY_T6*cm,
					   ShieldsMater,
					   0.,
					   360*deg,
					   name);
    SOY_T6_R->Construct();
    logicSOY_T6_R = SOY_T6_R->GetlogicVol();
 
    // Tube part 6 left
    G4ThreeVector positionSOY_T6_L = G4ThreeVector(x_SOY_T6_L*cm, y_SOY_T6_L*cm, z_SOY_T6_L*cm);
    name = "SOY_T6_L";
    ExN02DetectorConstruction_Tube* SOY_T6_L = 
	new ExN02DetectorConstruction_Tube(logicWorld,
					   positionSOY_T6_L,
					   0.0*deg,
					   innerRadius_SOY_T6*cm,
					   outerRadius_SOY_T6*cm,
					   length_SOY_T6*cm,
					   ShieldsMater,
					   0.,
					   360*deg,
					   name);
    SOY_T6_L->Construct();
    logicSOY_T6_L = SOY_T6_L->GetlogicVol();
    
    // Cone part 7 right
    G4ThreeVector positionSOY_Co7_R = G4ThreeVector(x_SOY_Co7_R*cm, y_SOY_Co7_R*cm, z_SOY_Co7_R*cm);
    name = "SOY_Co7_R";
    ExN02DetectorConstruction_Cone* SOY_Co7_R = 
	new ExN02DetectorConstruction_Cone(logicWorld,
					   positionSOY_Co7_R,
					   0.0*deg,
					   innerRadius1_SOY_Co7*cm,
					   outerRadius1_SOY_Co7*cm,
					   innerRadius2_SOY_Co7*cm,
					   outerRadius2_SOY_Co7*cm,
					   length_SOY_Co7*cm,
					   ShieldsMater,
					   0.,
					   360*deg,
					   name);
    SOY_Co7_R->Construct();
    logicSOY_Co7_R = SOY_Co7_R->GetlogicVol();

    // Cone part 7 left
    G4ThreeVector positionSOY_Co7_L = G4ThreeVector(x_SOY_Co7_L*cm, y_SOY_Co7_L*cm, z_SOY_Co7_L*cm);
    name = "SOY_Co7_L";
    ExN02DetectorConstruction_Cone* SOY_Co7_L = 
	new ExN02DetectorConstruction_Cone(logicWorld,
					   positionSOY_Co7_L,
					   0.0*deg,
					   innerRadius2_SOY_Co7*cm,
					   outerRadius2_SOY_Co7*cm,
					   innerRadius1_SOY_Co7*cm,
					   outerRadius1_SOY_Co7*cm,
					   length_SOY_Co7*cm,
					   ShieldsMater,
					   0.,
					   360*deg,
					   name);
    SOY_Co7_L->Construct();
    logicSOY_Co7_L = SOY_Co7_L->GetlogicVol();

    //---------------------------------------------------------------
    // Shielding in the back of the calo module 
    //---------------------------------------------------------------

    // brick 1 right
    G4ThreeVector positionBoxShield1_R = G4ThreeVector(x_BoxShield1_R*cm, y_BoxShield1_R*cm, z_BoxShield1_R*cm);
    name = "BoxShield1_R";
    ExN02DetectorConstruction_Box* BoxShield1_R = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionBoxShield1_R,
					  0.0*deg,
					  lengthBoxShield1X*cm,
					  lengthBoxShield1Y*cm,
					  lengthBoxShield1Z*cm,
					  ShieldsMater,
					  name);
    BoxShield1_R->Construct();
    BoxShield1_R->PrintInfo();   
    logicBoxShield1_R = BoxShield1_R->GetlogicVol();

    // brick 1 left
    G4ThreeVector positionBoxShield1_L = G4ThreeVector(x_BoxShield1_L*cm, y_BoxShield1_L*cm, z_BoxShield1_L*cm);
    name = "BoxShield1_L";
    ExN02DetectorConstruction_Box* BoxShield1_L = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionBoxShield1_L,
					  0.0*deg,
					  lengthBoxShield1X*cm,
					  lengthBoxShield1Y*cm,
					  lengthBoxShield1Z*cm,
					  ShieldsMater,
					  name);
    BoxShield1_L->Construct();
    BoxShield1_L->PrintInfo();   
    logicBoxShield1_L = BoxShield1_L->GetlogicVol();

    // brick 2 right
    G4ThreeVector positionBoxShield2_R = G4ThreeVector(x_BoxShield2_R*cm, y_BoxShield2_R*cm, z_BoxShield2_R*cm);
    name = "BoxShield2_R";
    ExN02DetectorConstruction_Box* BoxShield2_R = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionBoxShield2_R,
					  0.0*deg,
					  lengthBoxShield1X*cm,
					  lengthBoxShield1Y*cm,
					  lengthBoxShield1Z*cm,
					  ShieldsMater,
					  name);
    BoxShield2_R->Construct();
    BoxShield2_R->PrintInfo();   
    logicBoxShield2_R = BoxShield2_R->GetlogicVol();

    // brick 2 left
    G4ThreeVector positionBoxShield2_L = G4ThreeVector(x_BoxShield2_L*cm, y_BoxShield2_L*cm, z_BoxShield2_L*cm);
    name = "BoxShield2_L";
    ExN02DetectorConstruction_Box* BoxShield2_L = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionBoxShield2_L,
					  0.0*deg,
					  lengthBoxShield2X*cm,
					  lengthBoxShield2Y*cm,
					  lengthBoxShield2Z*cm,
					  ShieldsMater,
					  name);
    BoxShield2_L->Construct();
    BoxShield2_L->PrintInfo();   
    logicBoxShield2_L = BoxShield2_L->GetlogicVol();

    // brick 3 right
    G4ThreeVector positionBoxShield3_R = G4ThreeVector(x_BoxShield3_R*cm, y_BoxShield3_R*cm, z_BoxShield3_R*cm);
    name = "BoxShield3_R";
    ExN02DetectorConstruction_Box* BoxShield3_R = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionBoxShield3_R,
					  0.0*deg,
					  lengthBoxShield3X*cm,
					  lengthBoxShield3Y*cm,
					  lengthBoxShield3Z*cm,
					  ShieldsMater,
					  name);
    BoxShield3_R->Construct();
    BoxShield3_R->PrintInfo();   
    logicBoxShield3_R = BoxShield3_R->GetlogicVol();

    // brick 3 left
    G4ThreeVector positionBoxShield3_L = G4ThreeVector(x_BoxShield3_L*cm, y_BoxShield3_L*cm, z_BoxShield3_L*cm);
    name = "BoxShield3_L";
    ExN02DetectorConstruction_Box* BoxShield3_L = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionBoxShield3_L,
					  0.0*deg,
					  lengthBoxShield3X*cm,
					  lengthBoxShield3Y*cm,
					  lengthBoxShield3Z*cm,
					  ShieldsMater,
					  name);
    BoxShield3_L->Construct();
    BoxShield3_L->PrintInfo();   
    logicBoxShield3_L = BoxShield3_L->GetlogicVol();

    // brick 4 right
    G4ThreeVector positionBoxShield4_R = G4ThreeVector(x_BoxShield4_R*cm, y_BoxShield4_R*cm, z_BoxShield4_R*cm);
    name = "BoxShield4_R";
    ExN02DetectorConstruction_Box* BoxShield4_R = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionBoxShield4_R,
					  0.0*deg,
					  lengthBoxShield4X*cm,
					  lengthBoxShield4Y*cm,
					  lengthBoxShield4Z*cm,
					  ShieldsMater,
					  name);
    BoxShield4_R->Construct();
    BoxShield4_R->PrintInfo();   
    logicBoxShield4_R = BoxShield4_R->GetlogicVol();

    // brick 4 left
    G4ThreeVector positionBoxShield4_L = G4ThreeVector(x_BoxShield4_L*cm, y_BoxShield4_L*cm, z_BoxShield4_L*cm);
    name = "BoxShield4_L";
    ExN02DetectorConstruction_Box* BoxShield4_L = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionBoxShield4_L,
					  0.0*deg,
					  lengthBoxShield4X*cm,
					  lengthBoxShield4Y*cm,
					  lengthBoxShield4Z*cm,
					  ShieldsMater,
					  name);
    BoxShield4_L->Construct();
    BoxShield4_L->PrintInfo();   
    logicBoxShield4_L = BoxShield4_L->GetlogicVol();






    //-------------------------------------------------------------------
    // photon detector
    //-------------------------------------------------------------------

    G4ThreeVector positionBox1Pl = G4ThreeVector(x_Box1Pl*cm, y_Box1Pl*cm, z_Box1Pl*cm);
    G4ThreeVector positionBox2Pl = G4ThreeVector(x_Box2Pl*cm, y_Box2Pl*cm, z_Box2Pl*cm);
    G4ThreeVector positionBox3Pl = G4ThreeVector(x_Box3Pl*cm, y_Box3Pl*cm, z_Box3Pl*cm);
    G4ThreeVector positionBox4Pl = G4ThreeVector(x_Box4Pl*cm, y_Box4Pl*cm, z_Box4Pl*cm);

    G4ThreeVector positionZero = G4ThreeVector( 0.0, 0.0, 0.0);

    // Plastic box right (the photon detektor is inside)
    G4ThreeVector positionPlasticBox_R = G4ThreeVector(x_PlasticBox_R*cm, y_PlasticBox_R*cm, z_PlasticBox_R*cm);
    name = "PlasticBox_R";
    ExN02DetectorConstruction_Box* PlasticBox_R = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionPlasticBox_R,
					  alpha*deg,
					  lengthX_PlasticBox*cm,
					  lengthY_PlasticBox*cm,
					  lengthZ_PlasticBox*cm,
					  PVCMater,
					  name);
    PlasticBox_R->Construct();
    PlasticBox_R->PrintInfo();   
    logicPlasticBox_R = PlasticBox_R->GetlogicVol();

    // Plastic box left (the photon detektor is inside)
    G4ThreeVector positionPlasticBox_L = G4ThreeVector(x_PlasticBox_L*cm, y_PlasticBox_L*cm, z_PlasticBox_L*cm);
    name = "PlasticBox_L";
    ExN02DetectorConstruction_Box* PlasticBox_L = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionPlasticBox_L,
					  -alpha*deg,
					  lengthX_PlasticBox*cm,
					  lengthY_PlasticBox*cm,
					  lengthZ_PlasticBox*cm,
					  PVCMater,
					  name);
    PlasticBox_L->Construct();
    PlasticBox_L->PrintInfo();   
    logicPlasticBox_L = PlasticBox_L->GetlogicVol();


    // Iron box1 right
    name = "Iron1Box_R";
    ExN02DetectorConstruction_Box* Iron1Box_R = 
	new ExN02DetectorConstruction_Box(logicPlasticBox_R,
					  positionBox1Pl,
					  0.,
					  lengthX_IronBox*cm,
					  lengthY_IronBox*cm,
					  lengthZ_IronBox*cm,
					  IronMater,
					  name);
     Iron1Box_R->Construct();
     Iron1Box_R->PrintInfo();   
     logicIron1Box_R = Iron1Box_R->GetlogicVol();


    // Iron box2 right
    name = "Iron2Box_R";
    ExN02DetectorConstruction_Box* Iron2Box_R = 
	new ExN02DetectorConstruction_Box(logicPlasticBox_R,
					  positionBox2Pl,
					  0.,
					  lengthX_IronBox*cm,
					  lengthY_IronBox*cm,
					  lengthZ_IronBox*cm,
					  IronMater,
					  name);
    Iron2Box_R->Construct();
    Iron2Box_R->PrintInfo();   
    logicIron2Box_R = Iron2Box_R->GetlogicVol();

    // Iron box3 right
    name = "Iron3Box_R";
    ExN02DetectorConstruction_Box* Iron3Box_R = 
	new ExN02DetectorConstruction_Box(logicPlasticBox_R,
					  positionBox3Pl,
					  0.,
					  lengthX_IronBox*cm,
					  lengthY_IronBox*cm,
					  lengthZ_IronBox*cm,
					  IronMater,
					  name);
    Iron3Box_R->Construct();
    Iron3Box_R->PrintInfo();   
    logicIron3Box_R = Iron3Box_R->GetlogicVol();

    // Iron box4 right
    name = "Iron4Box_R";
    ExN02DetectorConstruction_Box* Iron4Box_R = 
	new ExN02DetectorConstruction_Box(logicPlasticBox_R,
					  positionBox4Pl,
					  0.,
					  lengthX_IronBox*cm,
					  lengthY_IronBox*cm,
					  lengthZ_IronBox*cm,
					  IronMater,
					  name);
    Iron4Box_R->Construct();
    Iron4Box_R->PrintInfo();   
    logicIron4Box_R = Iron4Box_R->GetlogicVol();


    // Iron box1 left
    name = "Iron1Box_L";
    ExN02DetectorConstruction_Box* Iron1Box_L = 
	new ExN02DetectorConstruction_Box(logicPlasticBox_L,
					  positionBox1Pl,
					  0.,
					  lengthX_IronBox*cm,
					  lengthY_IronBox*cm,
					  lengthZ_IronBox*cm,
					  IronMater,
					  name);
     Iron1Box_L->Construct();
     Iron1Box_L->PrintInfo();   
     logicIron1Box_L = Iron1Box_L->GetlogicVol();

    // Iron box2 left
    name = "Iron2Box_L";
    ExN02DetectorConstruction_Box* Iron2Box_L = 
	new ExN02DetectorConstruction_Box(logicPlasticBox_L,
					  positionBox2Pl,
					  0.,
					  lengthX_IronBox*cm,
					  lengthY_IronBox*cm,
					  lengthZ_IronBox*cm,
					  IronMater,
					  name);
    Iron2Box_L->Construct();
    Iron2Box_L->PrintInfo();   
    logicIron2Box_L = Iron2Box_L->GetlogicVol();

    // Iron box3 left
    name = "Iron3Box_L";
    ExN02DetectorConstruction_Box* Iron3Box_L= 
	new ExN02DetectorConstruction_Box(logicPlasticBox_L,
					  positionBox3Pl,
					  0.,
					  lengthX_IronBox*cm,
					  lengthY_IronBox*cm,
					  lengthZ_IronBox*cm,
					  IronMater,
					  name);
    Iron3Box_L->Construct();
    Iron3Box_L->PrintInfo();   
    logicIron3Box_L = Iron3Box_L->GetlogicVol();

    // Iron box4 left
    name = "Iron4Box_L";
    ExN02DetectorConstruction_Box* Iron4Box_L = 
	new ExN02DetectorConstruction_Box(logicPlasticBox_L,
					  positionBox4Pl,
					  0.,
					  lengthX_IronBox*cm,
					  lengthY_IronBox*cm,
					  lengthZ_IronBox*cm,
					  IronMater,
					  name);
    Iron4Box_L->Construct();
    Iron4Box_L->PrintInfo();   
    logicIron4Box_L = Iron4Box_L->GetlogicVol();

    //construct scintilator (PbWO4)
    // PbWO box1 right
    name = "PbWO1Box_R";
    ExN02DetectorConstruction_Box* PbWO1Box_R = 
	new ExN02DetectorConstruction_Box(logicIron1Box_R,
					  positionZero,
					  0.,
					  lengthX_PbWOBox*cm,
					  lengthY_PbWOBox*cm,
					  lengthZ_PbWOBox*cm,
					  PbWOMater,
					  name);

     physiPbWO1Box_R = PbWO1Box_R->Construct();
     PbWO1Box_R->PrintInfo();   
     logicPbWO1Box_R = PbWO1Box_R->GetlogicVol();

     // PbWO box2 right
     name = "PbWO2Box_R";
     ExN02DetectorConstruction_Box* PbWO2Box_R = 
	 new ExN02DetectorConstruction_Box(logicIron2Box_R,
					  positionZero,
					  0.,
					  lengthX_PbWOBox*cm,
					  lengthY_PbWOBox*cm,
					  lengthZ_PbWOBox*cm,
					  PbWOMater,
					  name);
 
    physiPbWO2Box_R = PbWO2Box_R->Construct();
    PbWO2Box_R->PrintInfo();   
    logicPbWO2Box_R = PbWO2Box_R->GetlogicVol();    

    // PbWO box3 right
    name = "PbWO3Box_R";
    ExN02DetectorConstruction_Box* PbWO3Box_R = 
	new ExN02DetectorConstruction_Box(logicIron3Box_R,
					  positionZero,
					  0.,
					  lengthX_PbWOBox*cm,
					  lengthY_PbWOBox*cm,
					  lengthZ_PbWOBox*cm,
					  PbWOMater,
					  name);

    physiPbWO3Box_R = PbWO3Box_R->Construct();
    PbWO3Box_R->PrintInfo();   
    logicPbWO3Box_R = PbWO3Box_R->GetlogicVol(); 

    // PbWO box4 right
    name = "PbWO4Box_R";
    ExN02DetectorConstruction_Box* PbWO4Box_R = 
	new ExN02DetectorConstruction_Box(logicIron4Box_R,
					  positionZero,
					  0.,
					  lengthX_PbWOBox*cm,
					  lengthY_PbWOBox*cm,
					  lengthZ_PbWOBox*cm,
					  PbWOMater,
					  name);

    physiPbWO4Box_R = PbWO4Box_R->Construct();
    PbWO4Box_R->PrintInfo();   
    logicPbWO4Box_R = PbWO4Box_R->GetlogicVol();
 
   // PbWO box1 left
    name = "PbWO1Box_L";
    ExN02DetectorConstruction_Box* PbWO1Box_L = 
	new ExN02DetectorConstruction_Box(logicIron1Box_L,
					  positionZero,
					  0.,
					  lengthX_PbWOBox*cm,
					  lengthY_PbWOBox*cm,
					  lengthZ_PbWOBox*cm,
					  PbWOMater,
					  name);
 
 physiPbWO1Box_L =  PbWO1Box_L->Construct();
     PbWO1Box_L->PrintInfo();   
     logicPbWO1Box_L = PbWO1Box_L->GetlogicVol();

    // PbWO box2 left
    name = "PbWO2Box_L";
    ExN02DetectorConstruction_Box* PbWO2Box_L = 
	new ExN02DetectorConstruction_Box(logicIron2Box_L,
					  positionZero,
					  0.,
					  lengthX_PbWOBox*cm,
					  lengthY_PbWOBox*cm,
					  lengthZ_PbWOBox*cm,
					  PbWOMater,
					  name);

   physiPbWO2Box_L =  PbWO2Box_L->Construct();
    PbWO2Box_L->PrintInfo();   
    logicPbWO2Box_L = PbWO2Box_L->GetlogicVol();

    // PbWO box3 left
    name = "PbWO3Box_L";
    ExN02DetectorConstruction_Box* PbWO3Box_L= 
	new ExN02DetectorConstruction_Box(logicIron3Box_L,
					  positionZero,
					  0.,
					  lengthX_PbWOBox*cm,
					  lengthY_PbWOBox*cm,
					  lengthZ_PbWOBox*cm,
					  PbWOMater,
					  name);
   
       physiPbWO3Box_L = PbWO3Box_L->Construct();
       PbWO3Box_L->PrintInfo();   
       logicPbWO3Box_L = PbWO3Box_L->GetlogicVol();

    // PbWO box4 left
    name = "PbWO4Box_L";
    ExN02DetectorConstruction_Box* PbWO4Box_L = 
	new ExN02DetectorConstruction_Box(logicIron4Box_L,
					  positionZero,
					  0.,
					  lengthX_PbWOBox*cm,
					  lengthY_PbWOBox*cm,
					  lengthZ_PbWOBox*cm,
					  PbWOMater,
					  name);

    physiPbWO4Box_L = PbWO4Box_L->Construct();
    PbWO4Box_L->PrintInfo();   
    logicPbWO4Box_L = PbWO4Box_L->GetlogicVol();

    
    G4Region* photonDet_R = new G4Region("lowAngleDetR");
    //photonDet->AddRootLogicalVolume(photonDet);
    photonDet_R->AddRootLogicalVolume(logicPbWO1Box_R);
    photonDet_R->AddRootLogicalVolume(logicPbWO2Box_R);
    photonDet_R->AddRootLogicalVolume(logicPbWO3Box_R);
    photonDet_R->AddRootLogicalVolume(logicPbWO4Box_R);

    G4Region* beamPipe_R = new G4Region("beamPipeR");
    beamPipe_R->AddRootLogicalVolume(logicTube4_R_U);
    beamPipe_R->AddRootLogicalVolume(logicTube4_R_D);

    //photonDet->AddRootLogicalVolume(logicWorld);

    //-------------------------------------------------------------------
    // Shielding of the photon detector
    // 3 lead brick
    // 1 small cylindrical window
    //-------------------------------------------------------------------

    //G4Box* solid;
    //G4LogicalVolume* logic;
    //G4PVPlacement* physi;
 
    G4Box* solidB = new G4Box("B", lengthX_PbBoxPhot/2*cm, lengthY_PbBoxPhot/2*cm, lengthZ_PbBoxPhot/2*cm);

    G4Tubs* solidT = new G4Tubs("T",innerRadiusWinPhot*cm,outerRadiusWinPhot*cm,length_WinPhot*1.3*cm, 0.,360.*deg);    

    G4ThreeVector zTrans = G4ThreeVector(x_WinPhotN*cm,y_WinPhotN*cm,z_WinPhotN*cm);
 

//   G4UnionSolid* solidPbBoxForPhot_R  =
    //new G4UnionSolid*("PbBoxForPhot_R", solidB, solidT,0,zTrans);

     G4SubtractionSolid* solidPbBoxForPhot_R  =
	 new G4SubtractionSolid("PbBoxForPhot_R", solidB, solidT,0,zTrans);

    G4LogicalVolume* logicPbBoxForPhot = new G4LogicalVolume( solidPbBoxForPhot_R, ShieldsMater, "PbBoxForPhot_R", 0, 0, 0);
    G4RotationMatrix *pRot_R = new G4RotationMatrix();// Rotates X and Z axes only
    pRot_R->rotateY(alpha*deg);                           // Rotates 4.07 degrees
    G4ThreeVector positionPbBoxForPhot_R = G4ThreeVector(x_PbBoxForPhot*cm, y_PbBoxForPhot*cm, z_PbBoxForPhot*cm);
    G4PVPlacement* physiPbBoxForPhot_R = new G4PVPlacement(pRot_R,    // no rotation
			      positionPbBoxForPhot_R,// at (0,0,0)
			      logicPbBoxForPhot,   // its logical volume
			      "PbBoxForPhot_R",      // its name
			      logicWorld,            // its mother  volume
			      false,                 // no boolean operations
			      0);                    // copy number      

    G4RotationMatrix *pRot_L = new G4RotationMatrix();// Rotates X and Z axes only
    pRot_L->rotateY(-alpha*deg);                           // Rotates 4.07 degrees
    G4ThreeVector positionPbBoxForPhot_L = G4ThreeVector(x_PbBoxForPhot*cm, y_PbBoxForPhot*cm, -z_PbBoxForPhot*cm);
    G4PVPlacement* physiPbBoxForPhot_L = new G4PVPlacement(pRot_L,    // no rotation
			      positionPbBoxForPhot_L,// at (0,0,0)
			      logicPbBoxForPhot,   // its logical volume
			      "PbBoxForPhot_L",      // its name
			      logicWorld,            // its mother  volume
			      false,                 // no boolean operations
			      0);                    // copy number      


/*
    // Pb forward brick right
    G4ThreeVector positionPbBoxForPhot_R = G4ThreeVector(x_PbBoxForPhot*cm, y_PbBoxForPhot*cm, z_PbBoxForPhot*cm);
    name = "PbBoxForPhot_R";
    ExN02DetectorConstruction_Box* PbBoxForPhot_R = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionPbBoxForPhot_R,
					  alpha*deg,
					  lengthX_PbBoxPhot*cm,
					  lengthY_PbBoxPhot*cm,
					  lengthZ_PbBoxPhot*cm,
					  ShieldsMater,
					  name);
     PbBoxForPhot_R->Construct();
     PbBoxForPhot_R->PrintInfo();   
     logicPbBoxForPhot_R =PbBoxForPhot_R->GetlogicVol();

    //small cylindrical window right
    G4ThreeVector positionWinPhot_R = G4ThreeVector(x_WinPhotN*cm,y_WinPhotN*cm,z_WinPhotN*cm);
    name = "WinPhot_R";
    ExN02DetectorConstruction_Tube* WinPhot_R = 
	new ExN02DetectorConstruction_Tube(logicPbBoxForPhot_R,
					   positionWinPhot_R,
					   0.0*deg,
					   innerRadiusWinPhot*cm,
					   outerRadiusWinPhot*cm,
					   length_WinPhot*cm,
					   Air,
					   0.*deg,
					   360.*deg,
					   name);
    WinPhot_R->Construct();
    G4LogicalVolume* logicWinPhot_R = WinPhot_R->GetlogicVol();
*/


    // Pb backward brick right
    G4ThreeVector positionPbBoxBackPhot_R = G4ThreeVector(x_PbBoxBackPhot*cm, y_PbBoxBackPhot*cm, z_PbBoxBackPhot*cm);
    name = "PbBoxBackPhot_R";
    ExN02DetectorConstruction_Box* PbBoxBackPhot_R = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionPbBoxBackPhot_R,
					  alpha*deg,
					  lengthX_PbBoxPhot*cm,
					  lengthY_PbBoxPhot*cm,
					  lengthZ_PbBoxPhot*cm,
					  ShieldsMater,
					  name);
     PbBoxBackPhot_R->Construct();
     PbBoxBackPhot_R->PrintInfo();   
     logicPbBoxBackPhot_R =PbBoxBackPhot_R->GetlogicVol();




/*
    // Pb forward brick left
    G4ThreeVector positionPbBoxForPhot_L = G4ThreeVector(x_PbBoxForPhot*cm, y_PbBoxForPhot*cm, -z_PbBoxForPhot*cm);
    name = "PbBoxForPhot_L";
    ExN02DetectorConstruction_Box* PbBoxForPhot_L = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionPbBoxForPhot_L,
					  -alpha*deg,
					  lengthX_PbBoxPhot*cm,
					  lengthY_PbBoxPhot*cm,
					  lengthZ_PbBoxPhot*cm,
					  ShieldsMater,
					  name);
     PbBoxForPhot_L->Construct();
     PbBoxForPhot_L->PrintInfo();   
     logicPbBoxForPhot_L =PbBoxForPhot_L->GetlogicVol();

    //small cylindrical window left
    G4ThreeVector positionWinPhot_L = G4ThreeVector(x_WinPhotN*cm,y_WinPhotN*cm,z_WinPhotN*cm);
    name = "WinPhot_L";
    ExN02DetectorConstruction_Tube* WinPhot_L = 
	new ExN02DetectorConstruction_Tube(logicPbBoxForPhot_L,
					   positionWinPhot_L,
					   0.0*deg,
					   innerRadiusWinPhot*cm,
					   outerRadiusWinPhot*cm,
					   length_WinPhot*cm,
					   Air,
					   0.*deg,
					   360.*deg,
					   name);
    WinPhot_L->Construct();
    G4LogicalVolume* logicWinPhot_L = WinPhot_L->GetlogicVol();   
*/


    // Pb backward brick left
    G4ThreeVector positionPbBoxBackPhot_L = G4ThreeVector(x_PbBoxBackPhot*cm, y_PbBoxBackPhot*cm, -z_PbBoxBackPhot*cm);
    name = "PbBoxBackPhot_L";
    ExN02DetectorConstruction_Box* PbBoxBackPhot_L = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionPbBoxBackPhot_L,
					  -alpha*deg,
					  lengthX_PbBoxPhot*cm,
					  lengthY_PbBoxPhot*cm,
					  lengthZ_PbBoxPhot*cm,
					  ShieldsMater,
					  name);
     PbBoxBackPhot_L->Construct();
     PbBoxBackPhot_L->PrintInfo();
     logicPbBoxBackPhot_L =PbBoxBackPhot_L->GetlogicVol();


    // Pb central brick right
    G4ThreeVector positionPbBoxCenPhot_R = G4ThreeVector(x_PbBoxCenPhot*cm, y_PbBoxCenPhot*cm, z_PbBoxCenPhot*cm);
    name = "PbBoxCenPhot_R";
    ExN02DetectorConstruction_Box* PbBoxCenPhot_R = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionPbBoxCenPhot_R,
					  alpha*deg,
					  lengthX_PbBoxCenPhot*cm,
					  lengthY_PbBoxCenPhot*cm,
					  lengthZ_PbBoxCenPhot*cm,
					  ShieldsMater,
					  name);
     PbBoxCenPhot_R->Construct();
     PbBoxCenPhot_R->PrintInfo();   
     logicPbBoxCenPhot_R =PbBoxCenPhot_R->GetlogicVol();


    // Pb central brick left
    G4ThreeVector positionPbBoxCenPhot_L = G4ThreeVector(x_PbBoxCenPhot*cm, y_PbBoxCenPhot*cm, -z_PbBoxCenPhot*cm);
    name = "PbBoxCenPhot_L";
    ExN02DetectorConstruction_Box* PbBoxCenPhot_L = 
	new ExN02DetectorConstruction_Box(logicWorld,
					  positionPbBoxCenPhot_L,
					  -alpha*deg,
					  lengthX_PbBoxCenPhot*cm,
					  lengthY_PbBoxCenPhot*cm,
					  lengthZ_PbBoxCenPhot*cm,
					  ShieldsMater,
					  name);
     PbBoxCenPhot_L->Construct();
     PbBoxCenPhot_L->PrintInfo();   
     logicPbBoxCenPhot_L =PbBoxCenPhot_L->GetlogicVol();



    //-------------------------------------------------------------------
    //!!!!!!!!!!create SensitiveDetector !!!!!!!!
    // for checking energy and momentu of the shower created by electrons 
    //-------------------------------------------------------------------

/*
     name = "SenDetShower_R";
     G4ThreeVector positionSenDetShower_R = G4ThreeVector(0.0*cm,0.0*cm,(-z_S54-3.)*cm); 

     if (fleg_SenDetShower_R == "SenDetShower_RON"){
	 ExN02DetectorConstruction_Tube* SenDetShower_R = 
	     new ExN02DetectorConstruction_Tube(logicWorld,
						positionSenDetShower_R,
						0.0,
						0.0*cm,
						5.0*cm,
						2*mm,
						Air,
						0.*deg,
						360.*deg,
						name);
	 
	 physiSenDetShower_R = SenDetShower_R->Construct();
	 G4LogicalVolume *logicSenDetShower_R = SenDetShower_R->GetlogicVol();	 
 
	 //ExN02SensitiveDetector *detector = new ExN02SensitiveDetector("hi there");
	 //G4SDManager* SDman = G4SDManager::GetSDMpointer();
	 //SDman->AddNewDetector(detector);
	 //logicSenDetShower01_R->SetSensitiveDetector(detector);
	 //ShieldsMater,
    }

     name = "SenDetShower_L";
     G4ThreeVector positionSenDetShower_L = G4ThreeVector(0.0*cm,0.0*cm,(z_S54+3.)*cm); 

     if (fleg_SenDetShower_L == "SenDetShower_LON"){
	 ExN02DetectorConstruction_Tube* SenDetShower_L = 
	     new ExN02DetectorConstruction_Tube(logicWorld,
						positionSenDetShower_L,
						0.0,
						0.0*cm,
						5.0*cm,
						2*mm,
						Air,
						0.*deg,
						360.*deg,
						name);
	 
	 physiSenDetShower_L = SenDetShower_L->Construct();
	 G4LogicalVolume *logicSenDetShower_L = SenDetShower_L->GetlogicVol();	 
 
	 //ExN02SensitiveDetector *detector = new ExN02SensitiveDetector("hi there");
	 //G4SDManager* SDman = G4SDManager::GetSDMpointer();
	 //SDman->AddNewDetector(detector);
	 //logicSenDetShower01_R->SetSensitiveDetector(detector);
	 //ShieldsMater,
    }
*/
     //------------------------------------------------ 
     // Sensitive detectors with class SD!!! more precise
     //------------------------------------------------ 

     name = "SenDetShower_L";
     G4ThreeVector positionSenDetShower_L = G4ThreeVector(0.0*cm,0.0*cm,(z_S54+3.)*cm); 

     if (fleg_SenDetShower_L == "SenDetShower_LON"){
	 ExN02DetectorConstruction_Tube* SenDetShower_L = 
	     new ExN02DetectorConstruction_Tube(logicWorld,
						positionSenDetShower_L,
						0.0,
						0.0*cm,
						5.0*cm,
						2*mm,
						Air,
						0.*deg,
						360.*deg,
						name);
	 
	 physiSenDetShower_L = SenDetShower_L->Construct();
	 logicSenDetShower_L = SenDetShower_L->GetlogicVol();	 
 
	 G4SDManager* SDman = G4SDManager::GetSDMpointer();
	 
	 G4String trackerChamberSDname = "ExN02/Shower_LSD";
	 ExN02SenDetShower_L* aSenDetShower_L = new ExN02SenDetShower_L( trackerChamberSDname );
	 SDman->AddNewDetector( aSenDetShower_L );
	 logicSenDetShower_L->SetSensitiveDetector(aSenDetShower_L);

	 name = "SenDetShower1_L";
	 G4ThreeVector positionSenDetShower1_L = G4ThreeVector(x_SD1_L*cm,0.0*cm,z_SD1_L*cm); 
     	 ExN02DetectorConstruction_Tube* SenDetShower1_L = 
	     new ExN02DetectorConstruction_Tube(logicWorld,
						positionSenDetShower1_L,
						-alpha*deg,
						0.0*cm,
						outerRadiusWinPhot*cm,
						2*mm,
						Air,
						0.*deg,
						360.*deg,
						name);
	 
	 physiSenDetShower1_L = SenDetShower1_L->Construct();
	 logicSenDetShower1_L = SenDetShower1_L->GetlogicVol();	 
 
	 logicSenDetShower1_L->SetSensitiveDetector(aSenDetShower_L);

    }



    //---------------------------------------------------------------
    //!!!!!!!!!!create SensitiveDetector !!!!!!!!
    // for checking energy and momentu of the output electron
    //---------------------------------------------------------------

    G4ThreeVector positionSenDetElectMom_L_U = G4ThreeVector(0.0*cm,0.0*cm,0.0*cm); 
    if (fleg_checkingOutputElecrton1 == "checkingOutputElecrton1ON"){
	
	ExN02DetectorConstruction_Tube* SenDetElectMom_L_U = 
	    new ExN02DetectorConstruction_Tube(logicTube5_C_L_D_v,
					       positionSenDetElectMom_L_U,
					       0.0,
					       0.0*cm,
					       innerRadius_Tube1*cm,
					       0.01*cm,
					       Air,
					       0.*deg,
					       360.*deg,
					       name);
	SenDetElectMom_L_U->Construct();
	logicSenDetElectMom_L_U = SenDetElectMom_L_U->GetlogicVol();


 	// G4SDManager* SDman = G4SDManager::GetSDMpointer();
	 
// 	 G4String trackerChamberSDname = "ExN02/Shower_LSD";
// 	 ExN02SenDetShower_L* aSenDetShower_L = new ExN02SenDetShower_L( trackerChamberSDname );
// 	 SDman->AddNewDetector( aSenDetShower_L );
// 	 logicSenDetShower_L->SetSensitiveDetector(aSenDetShower_L);



	ExN02SensitiveDetector *senDetector = new ExN02SensitiveDetector("hi there");
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	SDman->AddNewDetector(senDetector);

	logicSenDetElectMom_L_U->SetSensitiveDetector(senDetector);
	logicTube4_R_U_v->SetSensitiveDetector(senDetector);
	logicTube4_R_U_v->SetUserLimits(new G4UserLimits(0.001*mm));

    }

    if (fleg_checkingOutputElecrton2 == "checkingOutputElecrton2ON"){
	
	G4ThreeVector positionSenDetElectMomCentre = G4ThreeVector(0.0*cm,0.0*cm,0.0*cm); 
	ExN02DetectorConstruction_Tube* SenDetElectMom_Centre = 
	    new ExN02DetectorConstruction_Tube(logicBP1_v,
					       positionSenDetElectMomCentre,
					       0.0,
					       0.0*cm,
					       innerRadius_Tube1*cm,
					       0.01*cm,
					       Air,
					       0.*deg,
					       360.*deg,
					       name);
	SenDetElectMom_Centre->Construct();
	logicSenDetElectMom_Centre = SenDetElectMom_Centre->GetlogicVol();


	ExN02SensitiveDetector *detector = new ExN02SensitiveDetector("hi there");
  
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	SDman->AddNewDetector(detector);
	logicSenDetElectMom_Centre->SetSensitiveDetector(detector);
    }

/*
	ExN02SensitiveDetector *detector = new ExN02SensitiveDetector("hi there");
  
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	SDman->AddNewDetector(detector);
	logicPbWO1Box_R->SetSensitiveDetector(detector);
	logicPbWO2Box_R->SetSensitiveDetector(detector);
	logicPbWO3Box_R->SetSensitiveDetector(detector);
	logicPbWO4Box_R->SetSensitiveDetector(detector);
*/


    //---------------------------------------------------------------
    //  balls for checking geometry  
    //  if flagchecking == checkingGeomON
    //---------------------------------------------------------------
    //1 
    if(flagcheckingGeom1 == "checkingGeom1ON"){

	G4ThreeVector positionSp1 = G4ThreeVector(x_Sp1*cm,y_Sp1*cm,z_Sp1*cm);
   	G4ThreeVector positionSp2 = G4ThreeVector(x_Sp2*cm,y_Sp2*cm,z_Sp2*cm);
	G4ThreeVector positionSp3 = G4ThreeVector(x_Sp3*cm,y_Sp3*cm,z_Sp3*cm);
   	G4ThreeVector positionSp4 = G4ThreeVector(x_Sp4*cm,y_Sp4*cm,z_Sp4*cm);
   	G4ThreeVector positionSp5 = G4ThreeVector(x_Sp5*cm,y_Sp5*cm,z_Sp5*cm);
   	G4ThreeVector positionSp6 = G4ThreeVector(x_Sp6*cm,y_Sp6*cm,z_Sp6*cm);
   	G4ThreeVector positionSp7 = G4ThreeVector(x_Sp7*cm,y_Sp7*cm,z_Sp7*cm);
   	G4ThreeVector positionSp8 = G4ThreeVector(x_Sp8*cm,y_Sp8*cm,z_Sp8*cm);
   	G4ThreeVector positionSp9 = G4ThreeVector(x_Sp9*cm,y_Sp9*cm,z_Sp9*cm);
   	G4ThreeVector positionSp10 = G4ThreeVector(x_Sp10*cm,y_Sp10*cm,z_Sp10*cm);
   	G4ThreeVector positionSp11 = G4ThreeVector(x_Sp11*cm,y_Sp11*cm,z_Sp11*cm);
	G4ThreeVector positionSp12 = G4ThreeVector(x_Sp12*cm,y_Sp12*cm,z_Sp12*cm);
	G4ThreeVector positionSp13 = G4ThreeVector(x_Sp13*cm,y_Sp13*cm,z_Sp13*cm);
	G4ThreeVector positionSp14 = G4ThreeVector(x_Sp14*cm,y_Sp14*cm,z_Sp14*cm);
	G4ThreeVector positionSp15 = G4ThreeVector(x_Sp15*cm,y_Sp15*cm,z_Sp15*cm);
	//G4ThreeVector positionSp16 = G4ThreeVector(x_Sp16*cm,y_Sp16*cm,z_Sp16*cm);


	PrintToFile(stream,positionSp1,1);
	PrintToFile(stream,positionSp2,2);
	PrintToFile(stream,positionSp3,3);
	PrintToFile(stream,positionSp4,4);
	PrintToFile(stream,positionSp5,5);
	PrintToFile(stream,positionSp6,6);
	PrintToFile(stream,positionSp7,7);
	PrintToFile(stream,positionSp8,8);
	PrintToFile(stream,positionSp9,9);
	PrintToFile(stream,positionSp10,10);
	PrintToFile(stream,positionSp11,11);
	PrintToFile(stream,positionSp12,12);
	PrintToFile(stream,positionSp12,12);
	PrintToFile(stream,positionSp13,13);
	PrintToFile(stream,positionSp14,14);
	PrintToFile(stream,positionSp15,15);

	name = "Sp1";
	ExN02DetectorConstruction_Sp *Sp1 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp1,name,1.0*cm); 
	Sp1->Construct();

	name = "Sp2";
	ExN02DetectorConstruction_Sp *Sp2 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp2,name,1.0*cm); 
	Sp2->Construct();

	name = "Sp3";
	ExN02DetectorConstruction_Sp *Sp3 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp3,name, 1.0*cm); 
	Sp3->Construct();

	name = "Sp4";
	ExN02DetectorConstruction_Sp *Sp4 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp4,name, 1.0*cm); 
	Sp4->Construct();

	name = "Sp5";
	ExN02DetectorConstruction_Sp *Sp5 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp5,name, 1.0*cm); 
	Sp5->Construct();

	name = "Sp6";
	ExN02DetectorConstruction_Sp *Sp6 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp6,name, 1.0*cm); 
	Sp6->Construct();

	name = "Sp7";
	ExN02DetectorConstruction_Sp *Sp7 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp7,name, 1.0*cm); 
	Sp7->Construct();

	name = "Sp8";
	ExN02DetectorConstruction_Sp *Sp8 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp8,name, 1.0*cm); 
	Sp8->Construct();

	name = "Sp9";
	ExN02DetectorConstruction_Sp *Sp9 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp9,name, 1.0*cm); 
	Sp9->Construct();

	name = "Sp10";
	ExN02DetectorConstruction_Sp *Sp10 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp10,name, 1.0*cm); 
	Sp10->Construct();

	name = "Sp11";
	ExN02DetectorConstruction_Sp *Sp11 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp11,name, 1.0*cm); 
	Sp11->Construct();

	name = "Sp12";
	ExN02DetectorConstruction_Sp *Sp12 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp12,name, 1.0*cm); 
	Sp12->Construct();

	name = "Sp13";
	ExN02DetectorConstruction_Sp *Sp13 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp13,name, 1.0*cm); 
	Sp13->Construct();

	name = "Sp14";
	ExN02DetectorConstruction_Sp *Sp14 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp14,name, 1.0*cm); 
	Sp14->Construct();

	name = "Sp15";
	ExN02DetectorConstruction_Sp *Sp15 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp15,name, 1.0*cm); 
	Sp15->Construct();
	//name = "Sp16";
	//ExN02DetectorConstruction_Sp *Sp16 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp15,name, 1.0*cm); 
	//Sp16->Construct();

	//left photon monitor
	G4ThreeVector positionSp17 = G4ThreeVector(x_Sp17*cm,0.0*cm,z_Sp17*cm);
	G4ThreeVector positionSp18 = G4ThreeVector(x_Sp18*cm,0.0*cm,z_Sp18*cm);
	G4ThreeVector positionSp19 = G4ThreeVector(x_Sp19*cm,0.0*cm,z_Sp19*cm);
	G4ThreeVector positionSp20 = G4ThreeVector(x_Sp20*cm,0.0*cm,z_Sp20*cm);
	G4ThreeVector positionSp21 = G4ThreeVector(x_Sp21*cm,0.0*cm,z_Sp21*cm);
	G4ThreeVector positionSp22 = G4ThreeVector(x_Sp22*cm,0.0*cm,z_Sp22*cm);
	G4ThreeVector positionSp23 = G4ThreeVector(x_Sp23*cm,0.0*cm,z_Sp23*cm);
	G4ThreeVector positionSp24 = G4ThreeVector(x_Sp24*cm,0.0*cm,z_Sp24*cm);
	G4ThreeVector positionSp25 = G4ThreeVector(x_Sp25*cm,0.0*cm,z_Sp25*cm);
	G4ThreeVector positionSp26 = G4ThreeVector(x_Sp26*cm,0.0*cm,z_Sp26*cm);

	PrintToFile(stream,positionSp17,17);
	PrintToFile(stream,positionSp18,18);
	PrintToFile(stream,positionSp19,19);
	PrintToFile(stream,positionSp20,20);
	PrintToFile(stream,positionSp21,21);

	PrintToFile(stream,positionSp22,22);
	PrintToFile(stream,positionSp23,23);
	PrintToFile(stream,positionSp24,24);
	PrintToFile(stream,positionSp25,25);
	PrintToFile(stream,positionSp26,26);

 	name = "Sp17";
  	ExN02DetectorConstruction_Sp *Sp17 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp17,name, 0.5*cm); 
 	Sp17->Construct();
	logicSp17 = Sp17->GetlogicVol();

 	name = "Sp18";
 	ExN02DetectorConstruction_Sp *Sp18 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp18,name, 0.5*cm); 
	Sp18->Construct();
	logicSp18 = Sp18->GetlogicVol();

 	name = "Sp19";
 	ExN02DetectorConstruction_Sp *Sp19 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp19,name, 0.5*cm); 
	Sp19->Construct();

 	name = "Sp20";
 	ExN02DetectorConstruction_Sp *Sp20 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp20,name, 0.5*cm); 
	Sp20->Construct();

 	name = "Sp21";
 	ExN02DetectorConstruction_Sp *Sp21 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp21,name, 0.5*cm); 
	Sp21->Construct();

 	name = "Sp22";
 	ExN02DetectorConstruction_Sp *Sp22 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp22,name, 0.5*cm); 
	Sp22->Construct();

 	name = "Sp23";
 	ExN02DetectorConstruction_Sp *Sp23 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp23,name, 0.5*cm); 
	Sp23->Construct();

 	name = "Sp24";
 	ExN02DetectorConstruction_Sp *Sp24 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp24,name, 0.5*cm); 
	Sp24->Construct();

	name = "Sp25";
 	ExN02DetectorConstruction_Sp *Sp25 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp25,name, 0.5*cm); 
	Sp25->Construct();

	name = "Sp26";
 	ExN02DetectorConstruction_Sp *Sp26 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp26,name, 0.5*cm); 
	Sp26->Construct();

	//left QDF1
	G4ThreeVector positionSp27 = G4ThreeVector(x_Sp27*cm,0.0*cm,z_Sp27*cm);
	G4ThreeVector positionSp28 = G4ThreeVector(x_Sp28*cm,0.0*cm,z_Sp28*cm);
	G4ThreeVector positionSp29 = G4ThreeVector(x_Sp29*cm,0.0*cm,z_Sp29*cm);
	G4ThreeVector positionSp30 = G4ThreeVector(x_Sp30*cm,0.0*cm,z_Sp30*cm);
	G4ThreeVector positionSp31 = G4ThreeVector(x_Sp31*cm,0.0*cm,z_Sp31*cm);
	G4ThreeVector positionSp32 = G4ThreeVector(x_Sp32*cm,0.0*cm,z_Sp32*cm);
	G4ThreeVector positionSp33 = G4ThreeVector(x_Sp33*cm,0.0*cm,z_Sp33*cm);
	G4ThreeVector positionSp34 = G4ThreeVector(x_Sp34*cm,0.0*cm,z_Sp34*cm);

	PrintToFile(stream,positionSp27,27);
	PrintToFile(stream,positionSp28,28);
	PrintToFile(stream,positionSp29,29);
	PrintToFile(stream,positionSp30,30);
	PrintToFile(stream,positionSp31,31);
	PrintToFile(stream,positionSp32,32);
	PrintToFile(stream,positionSp33,33);
	PrintToFile(stream,positionSp34,34);



 	name = "Sp27";
  	ExN02DetectorConstruction_Sp *Sp27 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp27,name, 0.5*cm); 
 	Sp27->Construct();
 
	name = "Sp28";
  	ExN02DetectorConstruction_Sp *Sp28 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp28,name, 0.5*cm); 
 	Sp28->Construct();

 	name = "Sp29";
  	ExN02DetectorConstruction_Sp *Sp29 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp29,name, 0.5*cm); 
 	Sp29->Construct();

 	name = "Sp30";
  	ExN02DetectorConstruction_Sp *Sp30 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp30,name, 0.5*cm); 
 	Sp30->Construct();

 	name = "Sp31";
  	ExN02DetectorConstruction_Sp *Sp31 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp31,name, 0.5*cm); 
 	Sp31->Construct();

 	name = "Sp32";
  	ExN02DetectorConstruction_Sp *Sp32 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp32,name, 0.5*cm); 
 	Sp32->Construct();

  	name = "Sp33";
   	ExN02DetectorConstruction_Sp *Sp33 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp33,name, 0.5*cm); 
  	Sp33->Construct();

 	name = "Sp34";
  	ExN02DetectorConstruction_Sp *Sp34 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp34,name, 0.5*cm); 
 	Sp34->Construct();

	//left lead shielding(1)
	G4ThreeVector positionSp35 = G4ThreeVector( x_Sp35*cm, y_Sp35*cm, z_Sp35*cm);
	G4ThreeVector positionSp36 = G4ThreeVector( x_Sp36*cm, y_Sp36*cm, z_Sp36*cm);
	G4ThreeVector positionSp37 = G4ThreeVector( x_Sp37*cm, y_Sp37*cm, z_Sp37*cm);

	PrintToFile(stream,positionSp35,35);
	PrintToFile(stream,positionSp36,36);
	PrintToFile(stream,positionSp37,37);

 	name = "Sp35";
  	ExN02DetectorConstruction_Sp *Sp35 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp35,name, 0.5*cm); 
 	Sp35->Construct();
 
	name = "Sp36";
  	ExN02DetectorConstruction_Sp *Sp36 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp36,name, 0.5*cm); 
 	Sp36->Construct();

 	name = "Sp37";
  	ExN02DetectorConstruction_Sp *Sp37 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp37,name, 0.5*cm); 
 	Sp37->Construct();


	//left lead shielding(2)
	G4ThreeVector positionSp38 = G4ThreeVector(x_Sp38*cm,y_Sp38*cm,z_Sp38*cm);
	G4ThreeVector positionSp39 = G4ThreeVector(x_Sp39*cm,y_Sp39*cm,z_Sp39*cm);
	G4ThreeVector positionSp40 = G4ThreeVector(x_Sp40*cm,y_Sp40*cm,z_Sp40*cm);

	PrintToFile(stream,positionSp38,38);
	PrintToFile(stream,positionSp39,39);
	PrintToFile(stream,positionSp40,40);

	G4ThreeVector positionSp41 = G4ThreeVector(x_Sp41*cm,y_Sp41*cm,z_Sp41*cm);
	G4ThreeVector positionSp42 = G4ThreeVector(x_Sp42*cm,y_Sp42*cm,z_Sp42*cm);
	G4ThreeVector positionSp43 = G4ThreeVector(x_Sp43*cm,y_Sp43*cm,z_Sp43*cm);

	PrintToFile(stream,positionSp41,41);
	PrintToFile(stream,positionSp42,42);
	PrintToFile(stream,positionSp43,43);

 	name = "Sp38";
  	ExN02DetectorConstruction_Sp *Sp38 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp38,name, 0.5*cm); 
 	Sp38->Construct();
 
	name = "Sp39";
  	ExN02DetectorConstruction_Sp *Sp39 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp39,name, 0.5*cm); 
 	Sp39->Construct();

 	name = "Sp40";
  	ExN02DetectorConstruction_Sp *Sp40 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp40,name, 0.5*cm); 
 	Sp40->Construct();

 	name = "Sp41";
  	ExN02DetectorConstruction_Sp *Sp41 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp41,name, 0.5*cm); 
 	Sp41->Construct();
 
	name = "Sp42";
  	ExN02DetectorConstruction_Sp *Sp42 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp42,name, 0.5*cm); 
 	Sp42->Construct();

//  	name = "Sp43";
//   	ExN02DetectorConstruction_Sp *Sp43 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp43,name, 0.5*cm); 
//  	Sp4->Construct();

	//left lead shielding(2)
	G4ThreeVector positionSp44 = G4ThreeVector(0.0*cm,y_Sp44*cm,z_Sp44*cm);
	G4ThreeVector positionSp45 = G4ThreeVector(0.0*cm,y_Sp45*cm,z_Sp45*cm);
	G4ThreeVector positionSp46 = G4ThreeVector(0.0*cm,y_Sp46*cm,z_Sp46*cm);
	G4ThreeVector positionSp47 = G4ThreeVector(0.0*cm, 0.0*cm,z_Sp47*cm);
	G4ThreeVector positionSp48 = G4ThreeVector(0.0*cm, 0.0*cm,z_Sp48*cm);

	PrintToFile(stream,positionSp44,44);
	PrintToFile(stream,positionSp45,45);
	PrintToFile(stream,positionSp46,46);
	PrintToFile(stream,positionSp47,47);
	PrintToFile(stream,positionSp48,48);

 	name = "Sp44";
  	ExN02DetectorConstruction_Sp *Sp44 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp44,name, 0.5*cm); 
 	Sp44->Construct();
 
	name = "Sp45";
  	ExN02DetectorConstruction_Sp *Sp45 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp45,name, 0.5*cm); 
 	Sp45->Construct();

 	name = "Sp46";
  	ExN02DetectorConstruction_Sp *Sp46 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp46,name, 0.5*cm); 
 	Sp46->Construct();

 	name = "Sp47";
  	ExN02DetectorConstruction_Sp *Sp47 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp47,name, 0.5*cm); 
 	Sp47->Construct();
 
	name = "Sp48";
  	ExN02DetectorConstruction_Sp *Sp48 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp48,name, 0.5*cm); 
 	Sp48->Construct();
    }

 G4cout<<"01 ((-)) ((-)) ((-)) ((-)) ((-)) ((-)) ((-))"<<G4endl;

    if(flagcheckingGeom2 == "checkingGeom2ON"){

	//left SOYUZ

        //Cone part 7
	G4ThreeVector positionSp49 = G4ThreeVector(x_Sp49*cm, y_Sp49*cm, z_Sp49*cm);
	G4ThreeVector positionSp50 = G4ThreeVector(x_Sp50*cm, y_Sp50*cm, z_Sp50*cm);
	G4ThreeVector positionSp51 = G4ThreeVector(x_Sp51*cm, y_Sp51*cm, z_Sp51*cm);
	G4ThreeVector positionSp52 = G4ThreeVector(x_Sp52*cm, y_Sp52*cm, z_Sp52*cm);

	PrintToFile(stream,positionSp49,49);
	PrintToFile(stream,positionSp50,50);
	PrintToFile(stream,positionSp51,51);
	PrintToFile(stream,positionSp52,52);


 	name = "Sp49";
  	ExN02DetectorConstruction_Sp *Sp49 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp49,name, 0.5*cm); 
 	Sp49->Construct();

 	name = "Sp50";
  	ExN02DetectorConstruction_Sp *Sp50 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp50,name, 0.5*cm); 
 	Sp50->Construct();

 	name = "Sp51";
  	ExN02DetectorConstruction_Sp *Sp51 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp51,name, 0.5*cm); 
 	Sp51->Construct();

 	name = "Sp52";
  	ExN02DetectorConstruction_Sp *Sp52 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp52,name, 0.5*cm); 
 	Sp52->Construct();



	//Tube part 6
	G4ThreeVector positionSp53 = G4ThreeVector(x_Sp53*cm, y_Sp53*cm, z_Sp53*cm);
	G4ThreeVector positionSp54 = G4ThreeVector(x_Sp54*cm, y_Sp54*cm, z_Sp54*cm);

	PrintToFile(stream,positionSp53,53);
	PrintToFile(stream,positionSp54,54);


 	name = "Sp53";
  	ExN02DetectorConstruction_Sp *Sp53 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp53,name, 0.5*cm); 
 	Sp53->Construct();

 	name = "Sp54";
  	ExN02DetectorConstruction_Sp *Sp54 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp54,name, 0.5*cm); 
 	Sp54->Construct();


	//Tube part 5
	G4ThreeVector positionSp55 = G4ThreeVector(x_Sp55*cm, y_Sp55*cm, z_Sp55*cm);
	G4ThreeVector positionSp56 = G4ThreeVector(x_Sp56*cm, y_Sp56*cm, z_Sp56*cm);

	PrintToFile(stream,positionSp55,55);
	PrintToFile(stream,positionSp56,56);


 	name = "Sp55";
  	ExN02DetectorConstruction_Sp *Sp55 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp55,name, 0.3*cm); 
 	Sp55->Construct();

 	name = "Sp56";
  	ExN02DetectorConstruction_Sp *Sp56 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp56,name, 0.3*cm); 
 	Sp56->Construct();

	//rings
	G4ThreeVector positionSp57 = G4ThreeVector(x_Sp57*cm, y_Sp57*cm, z_Sp57*cm);
	G4ThreeVector positionSp59 = G4ThreeVector(x_Sp59*cm, y_Sp59*cm, z_Sp59*cm);

	PrintToFile(stream,positionSp57,57);
	PrintToFile(stream,positionSp59,59);

 	name = "Sp57";
  	ExN02DetectorConstruction_Sp *Sp57 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp57,name, 0.3*cm); 
 	Sp57->Construct();

 	name = "Sp59";
  	ExN02DetectorConstruction_Sp *Sp59 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp59,name, 0.3*cm); 
 	Sp59->Construct();

	//Cone part 4
	G4ThreeVector positionSp58 = G4ThreeVector(x_Sp58*cm, y_Sp58*cm, z_Sp58*cm);
	G4ThreeVector positionSp60 = G4ThreeVector(x_Sp60*cm, y_Sp60*cm, z_Sp60*cm);
	G4ThreeVector positionSp61 = G4ThreeVector(x_Sp61*cm, y_Sp61*cm, z_Sp61*cm);
	G4ThreeVector positionSp62 = G4ThreeVector(x_Sp62*cm, y_Sp62*cm, z_Sp62*cm);

	PrintToFile(stream,positionSp58,58);
	PrintToFile(stream,positionSp60,60);
	PrintToFile(stream,positionSp61,61);
	PrintToFile(stream,positionSp62,62);


 	name = "Sp58";
  	ExN02DetectorConstruction_Sp *Sp58 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp58,name, 0.2*cm); 
 	Sp58->Construct();

 	name = "Sp60";
  	ExN02DetectorConstruction_Sp *Sp60 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp60,name, 0.2*cm); 
 	Sp60->Construct();

 	name = "Sp61";
  	ExN02DetectorConstruction_Sp *Sp61 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp61,name, 0.2*cm); 
 	Sp61->Construct();

 	name = "Sp62";
  	ExN02DetectorConstruction_Sp *Sp62 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp62,name, 0.2*cm); 
 	Sp62->Construct();
        //----------

	//cone  part 3
	G4ThreeVector positionSp63 = G4ThreeVector(x_Sp63*cm, y_Sp63*cm, z_Sp63*cm);
	G4ThreeVector positionSp64 = G4ThreeVector(x_Sp64*cm, y_Sp64*cm, z_Sp64*cm);
	G4ThreeVector positionSp65 = G4ThreeVector(x_Sp65*cm, y_Sp65*cm, z_Sp65*cm);
	G4ThreeVector positionSp71 = G4ThreeVector(x_Sp71*cm, y_Sp71*cm, z_Sp71*cm);

	PrintToFile(stream,positionSp63,63);
	PrintToFile(stream,positionSp64,64);
	PrintToFile(stream,positionSp65,65);
	PrintToFile(stream,positionSp71,71);

 	name = "Sp63";
  	ExN02DetectorConstruction_Sp *Sp63 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp63,name, 0.2*cm); 
 	Sp63->Construct();

 	name = "Sp64";
  	ExN02DetectorConstruction_Sp *Sp64 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp64,name, 0.2*cm); 
 	Sp64->Construct();

 	name = "Sp65";
  	ExN02DetectorConstruction_Sp *Sp65 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp65,name, 0.2*cm); 
 	Sp65->Construct();

 	name = "Sp71";
  	ExN02DetectorConstruction_Sp *Sp71 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp71,name, 0.2*cm); 
 	Sp71->Construct();
        //----------

	// part 2
	G4ThreeVector positionSp66 = G4ThreeVector(x_Sp66*cm, y_Sp66*cm, z_Sp66*cm);
	G4ThreeVector positionSp69 = G4ThreeVector(x_Sp69*cm, y_Sp69*cm, z_Sp69*cm);
	G4ThreeVector positionSp70 = G4ThreeVector(x_Sp70*cm, y_Sp70*cm, z_Sp70*cm);

	PrintToFile(stream,positionSp66,66);
	PrintToFile(stream,positionSp69,69);
	PrintToFile(stream,positionSp70,70);


 	name = "Sp66";
  	ExN02DetectorConstruction_Sp *Sp66 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp66,name, 0.2*cm); 
 	Sp66->Construct();

 	name = "Sp69";
  	ExN02DetectorConstruction_Sp *Sp69 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp69,name, 0.2*cm); 
 	Sp69->Construct();

 	name = "Sp70";
  	ExN02DetectorConstruction_Sp *Sp70 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp70,name, 0.2*cm); 
 	Sp70->Construct();
        //----------

	//Cone part 1
	G4ThreeVector positionSp67 = G4ThreeVector(x_Sp67*cm, y_Sp67*cm, z_Sp67*cm);
	G4ThreeVector positionSp68 = G4ThreeVector(x_Sp68*cm, y_Sp68*cm, z_Sp68*cm);
	G4ThreeVector positionSp72 = G4ThreeVector(x_Sp72*cm, y_Sp72*cm, z_Sp72*cm);

	PrintToFile(stream,positionSp67,67);
	PrintToFile(stream,positionSp68,68);
	PrintToFile(stream,positionSp72,72);

 	name = "Sp67";
  	ExN02DetectorConstruction_Sp *Sp67 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp67,name, 0.2*cm); 
 	Sp67->Construct();

 	name = "Sp68";
  	ExN02DetectorConstruction_Sp *Sp68 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp68,name, 0.2*cm); 
 	Sp68->Construct();

 	name = "Sp72";
  	ExN02DetectorConstruction_Sp *Sp72 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp72,name, 0.2*cm); 
 	Sp72->Construct();
        //----------

	//Right SOYUZ

        //Cone part 1
	G4ThreeVector positionSp74 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp74*cm);
	G4ThreeVector positionSp75 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp75*cm);
	G4ThreeVector positionSp76 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp76*cm);
	G4ThreeVector positionSp77 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp77*cm);

	G4ThreeVector positionSp78 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp78*cm);
	G4ThreeVector positionSp79 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp79*cm);
	G4ThreeVector positionSp80 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp80*cm);
	G4ThreeVector positionSp81 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp81*cm);

	G4ThreeVector positionSp82 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp82*cm);
	G4ThreeVector positionSp83 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp83*cm);
	G4ThreeVector positionSp84 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp84*cm);
	G4ThreeVector positionSp85 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp85*cm);

	G4ThreeVector positionSp86 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp86*cm);
	G4ThreeVector positionSp87 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp87*cm);
	G4ThreeVector positionSp88 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp88*cm);
	G4ThreeVector positionSp89 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp89*cm);

	G4ThreeVector positionSp90 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp90*cm);
	G4ThreeVector positionSp91 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp91*cm);
	G4ThreeVector positionSp92 = G4ThreeVector(0.0*cm, 0.0*cm, z_Sp92*cm);

	PrintToFile(stream,positionSp74,74);
	PrintToFile(stream,positionSp75,75);
	PrintToFile(stream,positionSp76,76);
	PrintToFile(stream,positionSp77,77);

	PrintToFile(stream,positionSp78,78);
	PrintToFile(stream,positionSp79,79);
	PrintToFile(stream,positionSp80,80);
	PrintToFile(stream,positionSp81,81);

	PrintToFile(stream,positionSp82,82);
	PrintToFile(stream,positionSp83,83);
	PrintToFile(stream,positionSp84,84);
	PrintToFile(stream,positionSp85,85);

	PrintToFile(stream,positionSp86,86);
	PrintToFile(stream,positionSp87,87);
	PrintToFile(stream,positionSp88,88);
	PrintToFile(stream,positionSp89,89);

	PrintToFile(stream,positionSp90,90);
	PrintToFile(stream,positionSp91,91);	
	PrintToFile(stream,positionSp92,92);


 	name = "Sp74";
  	ExN02DetectorConstruction_Sp *Sp74 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp74,name, 0.2*cm); 
 	Sp74->Construct();

 	name = "Sp75";
  	ExN02DetectorConstruction_Sp *Sp75 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp75,name, 0.2*cm); 
 	Sp75->Construct();

 	name = "Sp76";
  	ExN02DetectorConstruction_Sp *Sp76 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp76,name, 0.2*cm); 
 	Sp76->Construct();

 	name = "Sp77";
  	ExN02DetectorConstruction_Sp *Sp77 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp77,name, 0.2*cm); 
 	Sp77->Construct();

 	name = "Sp78";
  	ExN02DetectorConstruction_Sp *Sp78 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp78,name, 0.2*cm); 
 	Sp78->Construct();

 	name = "Sp79";
  	ExN02DetectorConstruction_Sp *Sp79 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp79,name, 0.2*cm); 
 	Sp79->Construct();

 	name = "Sp80";
  	ExN02DetectorConstruction_Sp *Sp80 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp80,name, 0.2*cm); 
 	Sp80->Construct();

 	name = "Sp81";
  	ExN02DetectorConstruction_Sp *Sp81 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp81,name, 0.2*cm); 
 	Sp81->Construct();

 	name = "Sp82";
  	ExN02DetectorConstruction_Sp *Sp82 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp82,name, 0.2*cm); 
 	Sp82->Construct();

 	name = "Sp83";
  	ExN02DetectorConstruction_Sp *Sp83 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp83,name, 0.2*cm); 
 	Sp83->Construct();

 	name = "Sp84";
  	ExN02DetectorConstruction_Sp *Sp84 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp84,name, 0.2*cm); 
 	Sp84->Construct();

 	name = "Sp85";
  	ExN02DetectorConstruction_Sp *Sp85 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp85,name, 0.2*cm); 
 	Sp85->Construct();

 	name = "Sp86";
  	ExN02DetectorConstruction_Sp *Sp86 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp86,name, 0.2*cm); 
 	Sp86->Construct();

 	name = "Sp87";
  	ExN02DetectorConstruction_Sp *Sp87 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp87,name, 0.2*cm); 
 	Sp87->Construct();

 	name = "Sp88";
  	ExN02DetectorConstruction_Sp *Sp88 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp88,name, 0.2*cm); 
 	Sp88->Construct();

 	name = "Sp89";
  	ExN02DetectorConstruction_Sp *Sp89 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp89,name, 0.2*cm); 
 	Sp89->Construct();

 	name = "Sp90";
  	ExN02DetectorConstruction_Sp *Sp90 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp90,name, 0.2*cm); 
 	Sp90->Construct();

 	name = "Sp91";
  	ExN02DetectorConstruction_Sp *Sp91 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp91,name, 0.2*cm); 
 	Sp91->Construct();

 	name = "Sp92";
  	ExN02DetectorConstruction_Sp *Sp92 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp92,name, 0.2*cm); 
 	Sp92->Construct();

    }
    
    if (flagcheckingGeom3 == "checkingGeom3ON"){

	G4cout<<"-----------------------------"<<G4endl;
	G4cout<<"  flagcheckingGeom3 == checkingGeom3ON   "<<G4endl;
	G4cout<<"-----------------------------"<<G4endl;

	//lead shield (1)
	G4ThreeVector positionSp93 = G4ThreeVector(x_Sp93*cm, y_Sp93*cm, z_Sp93*cm);
	G4ThreeVector positionSp94 = G4ThreeVector(x_Sp94*cm, y_Sp94*cm, z_Sp94*cm);
	G4ThreeVector positionSp95 = G4ThreeVector(x_Sp95*cm, y_Sp95*cm, z_Sp95*cm);
	G4ThreeVector positionSp96 = G4ThreeVector(x_Sp96*cm, y_Sp96*cm, z_Sp96*cm);
	G4ThreeVector positionSp97 = G4ThreeVector(x_Sp97*cm, y_Sp97*cm, z_Sp97*cm);

	PrintToFile(stream,positionSp93,93);
	PrintToFile(stream,positionSp94,94);
	PrintToFile(stream,positionSp95,95);
	PrintToFile(stream,positionSp96,96);
	PrintToFile(stream,positionSp97,97);

 	name = "Sp93";
  	ExN02DetectorConstruction_Sp *Sp93 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp93,name, 0.2*cm); 
 	Sp93->Construct();

 	name = "Sp94";
  	ExN02DetectorConstruction_Sp *Sp94 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp94,name, 0.2*cm); 
 	Sp94->Construct();

 	name = "Sp95";
  	ExN02DetectorConstruction_Sp *Sp95 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp95,name, 0.2*cm); 
 	Sp95->Construct();

 	name = "Sp96";
  	ExN02DetectorConstruction_Sp *Sp96 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp96,name, 0.2*cm); 
 	Sp96->Construct();

 	name = "Sp97";
  	ExN02DetectorConstruction_Sp *Sp97 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp97,name, 0.2*cm); 
 	Sp97->Construct();

	//lead shield (2)
	G4ThreeVector positionSp98 = G4ThreeVector(x_Sp98*cm, y_Sp98*cm, z_Sp98*cm);
	G4ThreeVector positionSp99 = G4ThreeVector(x_Sp99*cm, y_Sp99*cm, z_Sp99*cm);
	G4ThreeVector positionSp100 = G4ThreeVector(x_Sp100*cm, y_Sp100*cm, z_Sp100*cm);
	G4ThreeVector positionSp101 = G4ThreeVector(x_Sp101*cm, y_Sp101*cm, z_Sp101*cm);
	G4ThreeVector positionSp102 = G4ThreeVector(x_Sp102*cm, y_Sp102*cm, z_Sp102*cm);
	G4ThreeVector positionSp103 = G4ThreeVector(x_Sp103*cm, y_Sp103*cm, z_Sp103*cm);

	PrintToFile(stream,positionSp98,98);
	PrintToFile(stream,positionSp99,99);
	PrintToFile(stream,positionSp100,100);
	PrintToFile(stream,positionSp101,101);
	PrintToFile(stream,positionSp102,102);
	PrintToFile(stream,positionSp103,103);

// 	name = "Sp98";
//   	ExN02DetectorConstruction_Sp *Sp98 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp98,name, 0.2*cm); 
//  	Sp98->Construct();

 	name = "Sp99";
  	ExN02DetectorConstruction_Sp *Sp99 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp99,name, 0.2*cm); 
 	Sp99->Construct();

 	name = "Sp100";
  	ExN02DetectorConstruction_Sp *Sp100 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp100,name, 0.2*cm); 
 	Sp100->Construct();

 	name = "Sp101";
  	ExN02DetectorConstruction_Sp *Sp101 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp101,name, 0.2*cm); 
 	Sp101->Construct();

//  	name = "Sp102";
//   	ExN02DetectorConstruction_Sp *Sp102 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp102,name, 0.2*cm); 
//  	Sp102->Construct();
    } 

    if (flagcheckingGeom4 == "checkingGeom4ON"){
	G4ThreeVector positionSp104 = G4ThreeVector(x_Sp104*cm, y_Sp104*cm, z_Sp104*cm);
	G4ThreeVector positionSp105 = G4ThreeVector(x_Sp105*cm, y_Sp105*cm, z_Sp105*cm);
	G4ThreeVector positionSp106 = G4ThreeVector(x_Sp106*cm, y_Sp106*cm, z_Sp106*cm);
	G4ThreeVector positionSp107 = G4ThreeVector(x_Sp107*cm, y_Sp107*cm, z_Sp107*cm);
	G4ThreeVector positionSp108 = G4ThreeVector(x_Sp108*cm, y_Sp108*cm, z_Sp108*cm);
	G4ThreeVector positionSp109 = G4ThreeVector(x_Sp109*cm, y_Sp109*cm, z_Sp109*cm);
	G4ThreeVector positionSp110 = G4ThreeVector(x_Sp110*cm, y_Sp110*cm, z_Sp110*cm);
	G4ThreeVector positionSp111 = G4ThreeVector(x_Sp111*cm, y_Sp111*cm, z_Sp111*cm);
	G4ThreeVector positionSp112 = G4ThreeVector(x_Sp112*cm, y_Sp112*cm, z_Sp112*cm);
	G4ThreeVector positionSp113 = G4ThreeVector(x_Sp113*cm, y_Sp113*cm, z_Sp113*cm);

	PrintToFile(stream,positionSp104,104);
	PrintToFile(stream,positionSp105,105);

	PrintToFile(stream,positionSp106,106);
	PrintToFile(stream,positionSp107,107);

	PrintToFile(stream,positionSp108,108);
	PrintToFile(stream,positionSp109,109);

	PrintToFile(stream,positionSp110,110);
	PrintToFile(stream,positionSp111,111);

	PrintToFile(stream,positionSp112,112);
	PrintToFile(stream,positionSp113,113);

	name = "Sp104";
	ExN02DetectorConstruction_Sp *Sp104 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp104,name, 0.2*cm); 
	Sp104->Construct();

	name = "Sp105";
	ExN02DetectorConstruction_Sp *Sp105 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp105,name, 0.2*cm); 
	Sp105->Construct();

	name = "Sp106";
	ExN02DetectorConstruction_Sp *Sp106 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp106,name, 0.2*cm); 
	Sp106->Construct();

	name = "Sp107";
	ExN02DetectorConstruction_Sp *Sp107 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp107,name, 0.2*cm); 
	Sp107->Construct();

	name = "Sp108";
	ExN02DetectorConstruction_Sp *Sp108 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp108,name, 0.2*cm); 
	Sp108->Construct();

	name = "Sp109";
	ExN02DetectorConstruction_Sp *Sp109 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp109,name, 0.2*cm); 
	Sp109->Construct();

	name = "Sp110";
	ExN02DetectorConstruction_Sp *Sp110 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp110,name, 0.2*cm); 
	Sp110->Construct();

	name = "Sp111";
	ExN02DetectorConstruction_Sp *Sp111 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp111,name, 0.2*cm); 
	Sp111->Construct();

	name = "Sp112";
	ExN02DetectorConstruction_Sp *Sp112 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp112,name, 0.2*cm); 
	Sp112->Construct();

	name = "Sp113";
	ExN02DetectorConstruction_Sp *Sp113 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp113,name, 0.2*cm); 
	Sp113->Construct();
    }

    if (flagcheckingGeom5 == "checkingGeom5ON"){

	G4ThreeVector positionSp114 = G4ThreeVector(x_Sp114*cm, y_Sp114*cm, z_Sp114*cm);
	G4ThreeVector positionSp115 = G4ThreeVector(x_Sp115*cm, y_Sp115*cm, z_Sp115*cm);
	G4ThreeVector positionSp116 = G4ThreeVector(x_Sp116*cm, y_Sp116*cm, z_Sp116*cm);
	G4ThreeVector positionSp117 = G4ThreeVector(x_Sp117*cm, y_Sp117*cm, z_Sp117*cm);
	G4ThreeVector positionSp118 = G4ThreeVector(x_Sp118*cm, y_Sp118*cm, z_Sp118*cm);
	G4ThreeVector positionSp119 = G4ThreeVector(x_Sp119*cm, y_Sp119*cm, z_Sp119*cm);
	G4ThreeVector positionSp120 = G4ThreeVector(x_Sp120*cm, y_Sp120*cm, z_Sp120*cm);
	G4ThreeVector positionSp121 = G4ThreeVector(x_Sp121*cm, y_Sp121*cm, z_Sp121*cm);
	G4ThreeVector positionSp122 = G4ThreeVector(x_Sp122*cm, y_Sp122*cm, z_Sp122*cm);
	G4ThreeVector positionSp123 = G4ThreeVector(x_Sp123*cm, y_Sp123*cm, z_Sp123*cm);
	G4ThreeVector positionSp124 = G4ThreeVector(x_Sp124*cm, y_Sp124*cm, z_Sp124*cm);
	G4ThreeVector positionSp125 = G4ThreeVector(x_Sp125*cm, y_Sp125*cm, z_Sp125*cm);
	G4ThreeVector positionSp126 = G4ThreeVector(x_Sp126*cm, y_Sp126*cm, z_Sp126*cm);
	G4ThreeVector positionSp127 = G4ThreeVector(x_Sp127*cm, y_Sp127*cm, z_Sp127*cm);
	G4ThreeVector positionSp128 = G4ThreeVector(x_Sp128*cm, y_Sp128*cm, z_Sp128*cm);
	G4ThreeVector positionSp129 = G4ThreeVector(x_Sp129*cm, y_Sp129*cm, z_Sp129*cm);

	PrintToFile(stream,positionSp114,114);
	PrintToFile(stream,positionSp115,115);
	PrintToFile(stream,positionSp116,116);
	PrintToFile(stream,positionSp117,117);
	PrintToFile(stream,positionSp118,118);
	PrintToFile(stream,positionSp119,119);
	PrintToFile(stream,positionSp120,120);
	PrintToFile(stream,positionSp121,121);
	PrintToFile(stream,positionSp122,122);
	PrintToFile(stream,positionSp123,123);
	PrintToFile(stream,positionSp124,124);	
	PrintToFile(stream,positionSp125,125);
	PrintToFile(stream,positionSp126,126);
	PrintToFile(stream,positionSp127,127);
	PrintToFile(stream,positionSp128,128);	
	PrintToFile(stream,positionSp129,129);

	name = "Sp114";
	ExN02DetectorConstruction_Sp *Sp114 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp114,name, 0.2*cm); 
	Sp114->Construct();

	name = "Sp115";
	ExN02DetectorConstruction_Sp *Sp115 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp115,name, 0.2*cm); 
	Sp115->Construct();

	name = "Sp116";
	ExN02DetectorConstruction_Sp *Sp116 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp116,name, 0.2*cm); 
	Sp116->Construct();

	name = "Sp117";
	ExN02DetectorConstruction_Sp *Sp117 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp117,name, 0.2*cm); 
	Sp117->Construct();

	name = "Sp118";
	ExN02DetectorConstruction_Sp *Sp118 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp118,name, 0.2*cm); 
	Sp118->Construct();

	name = "Sp119";
	ExN02DetectorConstruction_Sp *Sp119 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp119,name, 0.2*cm); 
	Sp119->Construct();

	name = "Sp120";
	ExN02DetectorConstruction_Sp *Sp120 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp120,name, 0.2*cm); 
	Sp120->Construct();

	name = "Sp121";
	ExN02DetectorConstruction_Sp *Sp121 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp121,name, 0.2*cm); 
	Sp121->Construct();

	name = "Sp122";
	ExN02DetectorConstruction_Sp *Sp122 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp122,name, 0.2*cm); 
	Sp122->Construct();

	name = "Sp123";
	ExN02DetectorConstruction_Sp *Sp123 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp123,name, 0.2*cm); 
	Sp123->Construct();

	name = "Sp124";
	ExN02DetectorConstruction_Sp *Sp124 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp124,name, 0.2*cm); 
	Sp124->Construct();

	name = "Sp125";
	ExN02DetectorConstruction_Sp *Sp125 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp125,name, 0.2*cm); 
	Sp125->Construct();

	name = "Sp126";
	ExN02DetectorConstruction_Sp *Sp126 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp126,name, 0.2*cm); 
	Sp126->Construct();

	name = "Sp127";
	ExN02DetectorConstruction_Sp *Sp127 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp127,name, 0.2*cm); 
	Sp127->Construct();

	name = "Sp128";
	ExN02DetectorConstruction_Sp *Sp128 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp128,name, 0.2*cm); 
	Sp128->Construct();

	name = "Sp129";
	ExN02DetectorConstruction_Sp *Sp129 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp129,name, 0.2*cm); 
	Sp129->Construct();

    }


    if (flagcheckingGeom0201 == "checkingGeom0201ON"){

	G4ThreeVector positionSp1 = G4ThreeVector(x_S1*cm, 0.0, z_S1*cm);
	G4ThreeVector positionSp2 = G4ThreeVector(x_S2*cm, 0.0, z_S2*cm);
	G4ThreeVector positionSp3 = G4ThreeVector(x_S3*cm, 0.0, z_S3*cm);
	G4ThreeVector positionSp4 = G4ThreeVector(x_S4*cm, 0.0, z_S4*cm);
	G4ThreeVector positionSp5 = G4ThreeVector(x_S5*cm, 0.0, z_S5*cm);
	G4ThreeVector positionSp6 = G4ThreeVector(x_S6*cm, 0.0, z_S6*cm);
	G4ThreeVector positionSp7 = G4ThreeVector(x_S7*cm, 0.0, z_S7*cm);
	G4ThreeVector positionSp8 = G4ThreeVector(x_S8*cm, 0.0, z_S8*cm);
	G4ThreeVector positionSp9 = G4ThreeVector(x_S9*cm, 0.0, z_S9*cm);
	G4ThreeVector positionSp10 = G4ThreeVector(x_S10*cm, 0.0, z_S10*cm);

	PrintToFile(stream,positionSp1,1);
	PrintToFile(stream,positionSp2,2);
	PrintToFile(stream,positionSp3,3);
	PrintToFile(stream,positionSp4,4);
	PrintToFile(stream,positionSp5,5);
	PrintToFile(stream,positionSp6,6);
	PrintToFile(stream,positionSp7,7);
	PrintToFile(stream,positionSp8,8);
	PrintToFile(stream,positionSp9,9);
	PrintToFile(stream,positionSp10,10);


	name = "Sp1";
	ExN02DetectorConstruction_Sp *Sp1 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp1,name, .3*cm); 
	Sp1->Construct();

	name = "Sp2";
	ExN02DetectorConstruction_Sp *Sp2 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp2,name, .3*cm); 
	Sp2->Construct();

	name = "Sp3";
	ExN02DetectorConstruction_Sp *Sp3 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp3,name, .3*cm); 
	Sp3->Construct();

	name = "Sp4";
	ExN02DetectorConstruction_Sp *Sp4 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp4,name, .3*cm); 
	Sp4->Construct();

	name = "Sp5";
	ExN02DetectorConstruction_Sp *Sp5 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp5,name, .3*cm); 
	Sp5->Construct();

	name = "Sp6";
	ExN02DetectorConstruction_Sp *Sp6 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp6,name, .3*cm); 
	Sp6->Construct();

	name = "Sp7";
	ExN02DetectorConstruction_Sp *Sp7 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp7,name, .3*cm); 
	Sp7->Construct();

	name = "Sp8";
	ExN02DetectorConstruction_Sp *Sp8 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp8,name, .3*cm); 
	Sp8->Construct();

	name = "Sp9";
	ExN02DetectorConstruction_Sp *Sp9 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp9,name, .3*cm); 
	Sp9->Construct();

	name = "Sp10";
	ExN02DetectorConstruction_Sp *Sp10 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp10,name, .3*cm); 
	Sp10->Construct();
    
    }


    if (flagcheckingGeom0202 == "checkingGeom0202ON"){

	G4ThreeVector positionSp11 = G4ThreeVector(x_S11*cm, y_S11*cm, z_S11*cm);
	G4ThreeVector positionSp12 = G4ThreeVector(x_S12*cm, y_S12*cm, z_S12*cm);
	G4ThreeVector positionSp13 = G4ThreeVector(x_S13*cm, y_S13*cm, z_S13*cm);
	G4ThreeVector positionSp14 = G4ThreeVector(x_S14*cm, y_S14*cm, z_S14*cm);

	PrintToFile(stream,positionSp11,11);
	PrintToFile(stream,positionSp12,12);
	PrintToFile(stream,positionSp13,13);
	PrintToFile(stream,positionSp14,14);


	name = "Sp11";
	ExN02DetectorConstruction_Sp *Sp11 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp11,name, .3*cm); 
	Sp11->Construct();

	name = "Sp12";
	ExN02DetectorConstruction_Sp *Sp12 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp12,name, .3*cm); 
	Sp12->Construct();

	name = "Sp13";
	ExN02DetectorConstruction_Sp *Sp13 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp13,name, .3*cm); 
	Sp13->Construct();

	name = "Sp14";
	ExN02DetectorConstruction_Sp *Sp14 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp14,name, .3*cm); 
	Sp14->Construct();
    }

    if (flagcheckingGeom0203 == "checkingGeom0203ON"){
       
	G4ThreeVector positionSp15 = G4ThreeVector(x_S15*cm, 0.0*cm, z_S15*cm);
	G4ThreeVector positionSp16 = G4ThreeVector(x_S16*cm, 0.0*cm, z_S16*cm);
	G4ThreeVector positionSp17 = G4ThreeVector(x_S17*cm, 0.0*cm, z_S17*cm);
	G4ThreeVector positionSp18 = G4ThreeVector(x_S18*cm, 0.0*cm, z_S18*cm);
	G4ThreeVector positionSp19 = G4ThreeVector(x_S19*cm, 0.0*cm, z_S19*cm);
	G4ThreeVector positionSp20 = G4ThreeVector(x_S20*cm, 0.0*cm, z_S20*cm);
	G4ThreeVector positionSp21 = G4ThreeVector(x_S21*cm, 0.0*cm, z_S21*cm);
	G4ThreeVector positionSp22 = G4ThreeVector(x_S22*cm, 0.0*cm, z_S22*cm);
	G4ThreeVector positionSp23 = G4ThreeVector(x_S23*cm, 0.0*cm, z_S23*cm);
	G4ThreeVector positionSp24 = G4ThreeVector(x_S24*cm, 0.0*cm, z_S24*cm);
	G4ThreeVector positionSp25 = G4ThreeVector(x_S25*cm, 0.0*cm, z_S25*cm);

	PrintToFile(stream,positionSp15,15);
	PrintToFile(stream,positionSp16,16);
	PrintToFile(stream,positionSp17,17);
	PrintToFile(stream,positionSp18,18);
	PrintToFile(stream,positionSp19,19);
	PrintToFile(stream,positionSp20,20);
	PrintToFile(stream,positionSp21,21);
	PrintToFile(stream,positionSp22,22);
	PrintToFile(stream,positionSp23,23);
	PrintToFile(stream,positionSp24,24);
	PrintToFile(stream,positionSp25,25);


	name = "Sp15";
	ExN02DetectorConstruction_Sp *Sp15 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp15,name, .3*cm); 
	Sp15->Construct();

	name = "Sp16";
	ExN02DetectorConstruction_Sp *Sp16 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp16,name, .3*cm); 
	Sp16->Construct();

	name = "Sp17";
	ExN02DetectorConstruction_Sp *Sp17 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp17,name, .3*cm); 
	Sp17->Construct();

	name = "Sp18";
	ExN02DetectorConstruction_Sp *Sp18 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp18,name, .3*cm); 
	Sp18->Construct();

	name = "Sp19";
	ExN02DetectorConstruction_Sp *Sp19 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp19,name, .3*cm); 
	Sp19->Construct();

	name = "Sp20";
	ExN02DetectorConstruction_Sp *Sp20 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp20,name, .3*cm); 
	Sp20->Construct();

	name = "Sp21";
	ExN02DetectorConstruction_Sp *Sp21 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp21,name, .3*cm); 
	Sp21->Construct();

	name = "Sp22";
	ExN02DetectorConstruction_Sp *Sp22 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp22,name, .3*cm); 
	Sp22->Construct();

	name = "Sp23";
	ExN02DetectorConstruction_Sp *Sp23 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp23,name, .3*cm); 
	Sp23->Construct();

	name = "Sp24";
	ExN02DetectorConstruction_Sp *Sp24 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp24,name, .3*cm); 
	Sp24->Construct();

	name = "Sp25";
	ExN02DetectorConstruction_Sp *Sp25 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp25,name, .3*cm); 
	Sp25->Construct();
    }

    if (flagcheckingGeom0204 == "checkingGeom0204ON"){
       
	G4ThreeVector positionSp26 = G4ThreeVector(x_S26*cm, 0.0*cm, z_S26*cm);
	G4ThreeVector positionSp27 = G4ThreeVector(x_S27*cm, 0.0*cm, z_S27*cm);
	G4ThreeVector positionSp28 = G4ThreeVector(x_S28*cm, 0.0*cm, z_S28*cm);

	PrintToFile(stream,positionSp26,26);
	PrintToFile(stream,positionSp27,27);
	PrintToFile(stream,positionSp28,28);


	name = "Sp26";
	ExN02DetectorConstruction_Sp *Sp26 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp26,name, .3*cm); 
	Sp26->Construct();

	name = "Sp27";
	ExN02DetectorConstruction_Sp *Sp27 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp27,name, .3*cm); 
	Sp27->Construct();

	name = "Sp28";
	ExN02DetectorConstruction_Sp *Sp28 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp28,name, .3*cm); 
	Sp28->Construct();

    }

    if (flagcheckingGeom0205 == "checkingGeom0205ON"){
              
	G4ThreeVector positionSp29 = G4ThreeVector(x_S29*cm, 0.0*cm, z_S29*cm);	
	G4ThreeVector positionSp30 = G4ThreeVector(x_S30*cm, 0.0*cm, z_S30*cm);	
	G4ThreeVector positionSp31 = G4ThreeVector(x_S31*cm, 0.0*cm, z_S31*cm);	
	G4ThreeVector positionSp32 = G4ThreeVector(x_S32*cm, 0.0*cm, z_S32*cm);	
	G4ThreeVector positionSp33 = G4ThreeVector(x_S33*cm, 0.0*cm, z_S33*cm);	
	G4ThreeVector positionSp34 = G4ThreeVector(x_S34*cm, 0.0*cm, z_S34*cm);	
	G4ThreeVector positionSp35 = G4ThreeVector(x_S35*cm, 0.0*cm, z_S35*cm);	

	PrintToFile(stream,positionSp29,29);
	PrintToFile(stream,positionSp30,30);
	PrintToFile(stream,positionSp31,31);
	PrintToFile(stream,positionSp32,32);
	PrintToFile(stream,positionSp33,33);
	PrintToFile(stream,positionSp34,34);
	PrintToFile(stream,positionSp35,35);

	name = "Sp29";
	ExN02DetectorConstruction_Sp *Sp29 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp29,name, .3*cm); 
	Sp29->Construct();

	name = "Sp30";
	ExN02DetectorConstruction_Sp *Sp30 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp30,name, .3*cm); 
	Sp30->Construct();

	name = "Sp31";
	ExN02DetectorConstruction_Sp *Sp31 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp31,name, .3*cm); 
	Sp31->Construct();

	name = "Sp32";
	ExN02DetectorConstruction_Sp *Sp32 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp32,name, .3*cm); 
	Sp32->Construct();

	name = "Sp33";
	ExN02DetectorConstruction_Sp *Sp33 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp33,name, .3*cm); 
	Sp33->Construct();

	name = "Sp34";
	ExN02DetectorConstruction_Sp *Sp34 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp34,name, .3*cm); 
	Sp34->Construct();

	name = "Sp35";
	ExN02DetectorConstruction_Sp *Sp35= new ExN02DetectorConstruction_Sp(logicWorld,positionSp35,name, .3*cm); 
	Sp35->Construct();
    }

    if (flagcheckingGeom0206 == "checkingGeom0206ON"){
       
	G4ThreeVector positionSp36 = G4ThreeVector(x_S36*cm, 0.0*cm, z_S36*cm);	
	G4ThreeVector positionSp37 = G4ThreeVector(x_S37*cm, 0.0*cm, z_S37*cm);	
	G4ThreeVector positionSp38 = G4ThreeVector(x_S38*cm, 0.0*cm, z_S38*cm);	
	G4ThreeVector positionSp39 = G4ThreeVector(x_S39*cm, 0.0*cm, z_S39*cm);	

	PrintToFile(stream,positionSp36,36);
	PrintToFile(stream,positionSp37,37);
	PrintToFile(stream,positionSp38,38);
	PrintToFile(stream,positionSp39,39);

	name = "Sp36";
	ExN02DetectorConstruction_Sp *Sp36 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp36,name, .3*cm); 
	Sp36->Construct();

	name = "Sp37";
	ExN02DetectorConstruction_Sp *Sp37 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp37,name, .3*cm); 
	Sp37->Construct();

	name = "Sp38";
	ExN02DetectorConstruction_Sp *Sp38 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp38,name, .3*cm); 
	Sp38->Construct();

	name = "Sp39";
	ExN02DetectorConstruction_Sp *Sp39 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp39,name, .3*cm); 
	Sp39->Construct();

    }

    if (flagcheckingGeom0207 == "checkingGeom0207ON"){
       
	G4ThreeVector positionSp40 = G4ThreeVector(x_S40*cm, 0.0*cm, z_S40*cm);	
	G4ThreeVector positionSp41 = G4ThreeVector(x_S41*cm, 0.0*cm, z_S41*cm);	
	G4ThreeVector positionSp42 = G4ThreeVector(x_S42*cm, 0.0*cm, z_S42*cm);	
	G4ThreeVector positionSp43 = G4ThreeVector(x_S43*cm, 0.0*cm, z_S43*cm);	
	G4ThreeVector positionSp44 = G4ThreeVector(x_S44*cm, 0.0*cm, z_S44*cm);	
	G4ThreeVector positionSp45 = G4ThreeVector(x_S45*cm, 0.0*cm, z_S45*cm);	

	PrintToFile(stream,positionSp40,40);
	PrintToFile(stream,positionSp41,41);
	PrintToFile(stream,positionSp42,42);
	PrintToFile(stream,positionSp43,43);
	PrintToFile(stream,positionSp44,44);
	PrintToFile(stream,positionSp45,45);
	
	name = "Sp40";
	ExN02DetectorConstruction_Sp *Sp40 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp40,name, .3*cm); 
	Sp40->Construct();

	name = "Sp41";
	ExN02DetectorConstruction_Sp *Sp41 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp41,name, .3*cm); 
	Sp41->Construct();

	name = "Sp42";
	ExN02DetectorConstruction_Sp *Sp42 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp42,name, .3*cm); 
	Sp42->Construct();

	name = "Sp43";
	ExN02DetectorConstruction_Sp *Sp43 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp43,name, .3*cm); 
	Sp43->Construct();

	name = "Sp44";
	ExN02DetectorConstruction_Sp *Sp44 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp44,name, .3*cm); 
	Sp44->Construct();

	name = "Sp45";
	ExN02DetectorConstruction_Sp *Sp45 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp45,name, .3*cm); 
	Sp45->Construct();

    }

    if (flagcheckingGeom0208 == "checkingGeom0208ON"){ 

	G4ThreeVector positionSp46 = G4ThreeVector(x_S46*cm, 0.0*cm, z_S46*cm);	
	G4ThreeVector positionSp47 = G4ThreeVector(x_S47*cm, 0.0*cm, z_S47*cm);	
	G4ThreeVector positionSp48 = G4ThreeVector(x_S48*cm, 0.0*cm, z_S48*cm);	
	G4ThreeVector positionSp49 = G4ThreeVector(x_S49*cm, 0.0*cm, z_S49*cm);	
	G4ThreeVector positionSp50 = G4ThreeVector(x_S50*cm, 0.0*cm, z_S50*cm);	
	G4ThreeVector positionSp51 = G4ThreeVector(x_S51*cm, 0.0*cm, z_S51*cm);	
	G4ThreeVector positionSp52 = G4ThreeVector(x_S52*cm, 0.0*cm, z_S52*cm);	
	G4ThreeVector positionSp53 = G4ThreeVector(x_S53*cm, 0.0*cm, z_S53*cm);	
	G4ThreeVector positionSp54 = G4ThreeVector(x_S54*cm, 0.0*cm, z_S54*cm);	
	G4ThreeVector positionSp55 = G4ThreeVector(x_S55*cm, 0.0*cm, z_S55*cm);	
	G4ThreeVector positionSp56 = G4ThreeVector(x_S56*cm, 0.0*cm, z_S56*cm);	
	G4ThreeVector positionSp57 = G4ThreeVector(x_S57*cm, 0.0*cm, z_S57*cm);	
	G4ThreeVector positionSp58 = G4ThreeVector(x_S58*cm, 0.0*cm, z_S58*cm);	
	G4ThreeVector positionSp59 = G4ThreeVector(x_S59*cm, 0.0*cm, z_S59*cm);	
	G4ThreeVector positionSp60 = G4ThreeVector(x_S60*cm, 0.0*cm, z_S60*cm);	
	G4ThreeVector positionSp61 = G4ThreeVector(x_S61*cm, 0.0*cm, z_S61*cm);	
	G4ThreeVector positionSp62 = G4ThreeVector(x_S62*cm, 0.0*cm, z_S62*cm);	
	G4ThreeVector positionSp63 = G4ThreeVector(x_S63*cm, 0.0*cm, z_S63*cm);	
	G4ThreeVector positionSp64 = G4ThreeVector(x_S64*cm, 0.0*cm, z_S64*cm);	

	PrintToFile(stream,positionSp46,46);
	PrintToFile(stream,positionSp47,47);
	PrintToFile(stream,positionSp48,48);
	PrintToFile(stream,positionSp49,49);
	PrintToFile(stream,positionSp50,50);
	PrintToFile(stream,positionSp51,51);
	PrintToFile(stream,positionSp52,52);
	PrintToFile(stream,positionSp53,53);
	PrintToFile(stream,positionSp54,54);
	PrintToFile(stream,positionSp55,55);
	PrintToFile(stream,positionSp56,56);
	PrintToFile(stream,positionSp57,57);
	PrintToFile(stream,positionSp58,58);
	PrintToFile(stream,positionSp59,59);
	PrintToFile(stream,positionSp60,60);
	PrintToFile(stream,positionSp61,61);
	PrintToFile(stream,positionSp62,62);
	PrintToFile(stream,positionSp63,63);
	PrintToFile(stream,positionSp64,64);


	name = "Sp46";
	ExN02DetectorConstruction_Sp *Sp46 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp46,name, .3*cm); 
	Sp46->Construct();

	name = "Sp47";
	ExN02DetectorConstruction_Sp *Sp47 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp47,name, .3*cm); 
	Sp47->Construct();

	name = "Sp48";
	ExN02DetectorConstruction_Sp *Sp48 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp48,name, .3*cm); 
	Sp48->Construct();

	name = "Sp49";
	ExN02DetectorConstruction_Sp *Sp49 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp49,name, .3*cm); 
	Sp49->Construct();

	name = "Sp50";
	ExN02DetectorConstruction_Sp *Sp50 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp50,name, .3*cm); 
	Sp50->Construct();

	name = "Sp51";
	ExN02DetectorConstruction_Sp *Sp51 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp51,name, .3*cm); 
	Sp51->Construct();

	name = "Sp52";
	ExN02DetectorConstruction_Sp *Sp52 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp52,name, .3*cm); 
	Sp52->Construct();

	name = "Sp53";
	ExN02DetectorConstruction_Sp *Sp53 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp53,name, .3*cm);
	Sp53->Construct();

	name = "Sp54";
	ExN02DetectorConstruction_Sp *Sp54 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp54,name, .3*cm);
	Sp54->Construct();

	name = "Sp55";
	ExN02DetectorConstruction_Sp *Sp55 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp55,name, .3*cm); 
	Sp55->Construct();

	name = "Sp56";
	ExN02DetectorConstruction_Sp *Sp56 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp56,name, .3*cm);
	Sp56->Construct();

	name = "Sp57";
	ExN02DetectorConstruction_Sp *Sp57 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp57,name, .3*cm);
	Sp57->Construct();

	name = "Sp58";
	ExN02DetectorConstruction_Sp *Sp58 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp58,name, .3*cm);
	Sp58->Construct();

	name = "Sp59";
	ExN02DetectorConstruction_Sp *Sp59 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp59,name, .3*cm);
	Sp59->Construct();

	name = "Sp60";
	ExN02DetectorConstruction_Sp *Sp60 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp60,name, .3*cm);
	Sp60->Construct();

	name = "Sp61";
	ExN02DetectorConstruction_Sp *Sp61 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp61,name, .3*cm);
	Sp61->Construct();

	name = "Sp62";
	ExN02DetectorConstruction_Sp *Sp62 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp62,name, .3*cm);
	Sp62->Construct();

	name = "Sp63";
	ExN02DetectorConstruction_Sp *Sp63 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp63,name, .3*cm);
	Sp63->Construct();

	name = "Sp64";
	ExN02DetectorConstruction_Sp *Sp64 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp64,name, .3*cm);
	Sp64->Construct();
    }


    if (flagcheckingGeom0209 == "checkingGeom0209ON"){ 

	G4ThreeVector positionSp65 = G4ThreeVector(x_S54*cm, 0.0*cm,-z_S54*cm);	
	G4ThreeVector positionSp66 = G4ThreeVector(x_S23*cm, 0.0*cm,-z_S23*cm);
	G4ThreeVector positionSp67 = G4ThreeVector(0.0*cm, 0.0*cm,(-z_S54-3.)*cm);	
	
	PrintToFile(stream,positionSp65,65);
	PrintToFile(stream,positionSp66,66);
	PrintToFile(stream,positionSp67,67);


	name = "Sp65";
	ExN02DetectorConstruction_Sp *Sp65 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp65,name, .3*cm); 
	Sp65->Construct();

	name = "Sp66";
	ExN02DetectorConstruction_Sp *Sp66 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp66,name, .3*cm); 
	Sp66->Construct();

	name = "Sp67";
	ExN02DetectorConstruction_Sp *Sp67 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp67,name, .3*cm); 
	Sp67->Construct();

    }


    if (flagcheckingGeomBenoit == "checkingGeomBenoitON"){
       
        //coners ofth V-like tube
	G4ThreeVector positionSp1 = G4ThreeVector(78.27/2*mm, 0.0*mm, (-543.8-12.5)*mm);
	G4ThreeVector positionSp2 = G4ThreeVector(-78.27/2*mm, 0.0*mm, (-543.8-12.5)*mm);
	G4ThreeVector positionSp3 = G4ThreeVector(72.22*mm, 0.0*mm, -809.24*mm);
	G4ThreeVector positionSp4 = G4ThreeVector(-72.22*mm, 0.0*mm, -809.24*mm);
	G4ThreeVector positionSp5 = G4ThreeVector(0.0*mm, 0.0*mm, -814.38*mm);

	//G4ThreeVector positionSp1 = G4ThreeVector((78.27/2 -5)*mm, 0.0*mm, (-543.8-12.5)*mm);
	//G4ThreeVector positionSp2 = G4ThreeVector((-78.27/2 +5)*mm, 0.0*mm, (-543.8-12.5)*mm);
	//G4ThreeVector positionSp3 = G4ThreeVector((72.22-5)*mm, 0.0*mm, -809.24*mm);
	//G4ThreeVector positionSp4 = G4ThreeVector((-72.22+5)*mm, 0.0*mm, -809.24*mm);


	//--
	//position of the middle of the Y-tube face the closest to the IP
	G4ThreeVector positionSp6 = G4ThreeVector(0.0*mm, 0.0*mm, (-543.8-12.5)*mm);
	//--
	//position of the junction between the Y tube and the previous section 
        //of the beampipe
	G4ThreeVector positionSp7 = G4ThreeVector(0.0*mm, 0.0*mm, (-543.8*mm));

	name = "Sp1";
	ExN02DetectorConstruction_Sp *Sp1 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp1,name, .3*cm); 
	Sp1->Construct();
	name = "Sp2";
	ExN02DetectorConstruction_Sp *Sp2 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp2,name, .3*cm); 
	Sp2->Construct();
	name = "Sp3";
	ExN02DetectorConstruction_Sp *Sp3 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp3,name, .3*cm); 
	Sp3->Construct();
	name = "Sp4";
	ExN02DetectorConstruction_Sp *Sp4 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp4,name, .3*cm); 
	Sp4->Construct();
	name = "Sp5";
	ExN02DetectorConstruction_Sp *Sp5 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp5,name, .3*cm); 
	Sp5->Construct();
	name = "Sp6";
	ExN02DetectorConstruction_Sp *Sp6 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp6,name, .3*cm); 
	Sp6->Construct();
	name = "Sp7";
	ExN02DetectorConstruction_Sp *Sp7 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp7,name, .3*cm); 
	Sp7->Construct();

    }


    

    if (flagcheckingGeomFieldStuck == "checkingGeomFieldStuckON"){
       
	G4ThreeVector positionSp1 = G4ThreeVector(-18.95485431,-0.2719868143,-958.8936882);
	G4ThreeVector positionSp2 = G4ThreeVector(-18.95760986,-0.3583101116,-958.9194205);
	G4ThreeVector positionSp3 = G4ThreeVector(-18.95954534,-0.4274249731,-958.9336519);

	G4ThreeVector positionSp4 = G4ThreeVector(-18.96315443,-0.5316107669,-958.9605097);
	G4ThreeVector positionSp5 = G4ThreeVector(-18.96567374,-0.6102129739,-958.9744793);
	G4ThreeVector positionSp6 = G4ThreeVector(-18.97214099,-0.7246349764,-959.0288859);

	G4ThreeVector positionSp7 = G4ThreeVector(-14.68419554,1.367171339,-898.4453375);
	G4ThreeVector positionSp8 = G4ThreeVector(-18.87446914,-1.531569533,-957.2210876);
	G4ThreeVector positionSp9 = G4ThreeVector(-25.99734679,-2.526403613,-1056.358823);

	name = "Sp1";
	ExN02DetectorConstruction_Sp *Sp1 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp1,name, .3*mm); 
	Sp1->Construct();

	name = "Sp2";
	ExN02DetectorConstruction_Sp *Sp2 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp2,name, .3*mm); 
	Sp2->Construct();

	name = "Sp3";
	ExN02DetectorConstruction_Sp *Sp3 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp3,name, .3*mm); 
	Sp3->Construct();

	name = "Sp4";
	ExN02DetectorConstruction_Sp *Sp4 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp4,name, .3*mm); 
	Sp4->Construct();

	name = "Sp5";
	ExN02DetectorConstruction_Sp *Sp5 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp5,name, .3*mm); 
	Sp5->Construct();

	name = "Sp6";
	ExN02DetectorConstruction_Sp *Sp6 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp6,name, .3*mm); 
	Sp6->Construct();

	name = "Sp7";
	ExN02DetectorConstruction_Sp *Sp7 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp7,name, .3*mm); 
	Sp7->Construct();

	name = "Sp8";
	ExN02DetectorConstruction_Sp *Sp8 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp8,name, .3*mm); 
	Sp8->Construct();

	name = "Sp9";
	ExN02DetectorConstruction_Sp *Sp9 = new ExN02DetectorConstruction_Sp(logicWorld,positionSp9,name, .3*mm); 
	Sp9->Construct();

    }

/*	
 	fprintf(stream," Sp1  : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp1, y_Sp1, z_Sp1);
 	fprintf(stream," Sp2  : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp2, y_Sp2, z_Sp2);
 	fprintf(stream," Sp3  : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp3, y_Sp3, z_Sp3);
 	fprintf(stream," Sp4  : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp4, y_Sp4, z_Sp4);
 	fprintf(stream," Sp5  : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp5, y_Sp5, z_Sp5);
 	fprintf(stream," Sp6  : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp6, y_Sp6, z_Sp6);
 	fprintf(stream," Sp7  : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp7, y_Sp7, z_Sp7);
 	fprintf(stream," Sp8  : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp8, y_Sp8, z_Sp8);
 	fprintf(stream," Sp9  : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp9, y_Sp9, z_Sp9);
 	fprintf(stream," Sp10 : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp10, y_Sp10, z_Sp10);
 	fprintf(stream," Sp11 : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp11, y_Sp11, z_Sp11);
 	fprintf(stream," Sp12 : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp12, y_Sp12, z_Sp12);
 	fprintf(stream," Sp13 : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp13, y_Sp13, z_Sp13);
 	fprintf(stream," Sp14 : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp14, y_Sp14, z_Sp14);
 	fprintf(stream," Sp15 : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp15, y_Sp15, z_Sp15);
 	fprintf(stream," Sp16 : x = %10.5f, y = %10.5f, z = %10.5f \n", x_Sp16, y_Sp16, z_Sp16);
*/

//---------------------------------------------------------------
    //------------------------------------------------ 
    // Sensitive detectors
    //------------------------------------------------ 
    
    //   G4SDManager* SDman = G4SDManager::GetSDMpointer();
    
    //   G4String trackerChamberSDname = "ExN02/TrackerChamberSD";
    //   ExN02TrackerSD* aTrackerSD = new ExN02TrackerSD( trackerChamberSDname );
    //   SDman->AddNewDetector( aTrackerSD );
    //   logicChamber->SetSensitiveDetector( aTrackerSD );


    if( fleg_SensativePbWO4RightON == "SensativePbWO4RightON"){
	ExN02SensitiveDetector *SenDetector = new ExN02SensitiveDetector("hi there");
	SenDetector->SetRunManager(runManager);  
	
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	SDman->AddNewDetector(SenDetector);
	logicPbWO1Box_R->SetSensitiveDetector(SenDetector);
	logicPbWO2Box_R->SetSensitiveDetector(SenDetector);
	logicPbWO3Box_R->SetSensitiveDetector(SenDetector);
	logicPbWO4Box_R->SetSensitiveDetector(SenDetector);
    }

    if( fleg_SensativePbWO4LeftON == "SensativePbWO4LeftON"){
	ExN02SensitiveDetector *SenDetector = new ExN02SensitiveDetector("hi there");
	SenDetector->SetRunManager(runManager);  
	
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	SDman->AddNewDetector(SenDetector);
	logicPbWO1Box_L->SetSensitiveDetector(SenDetector);
	logicPbWO2Box_L->SetSensitiveDetector(SenDetector);
	logicPbWO3Box_L->SetSensitiveDetector(SenDetector);
	logicPbWO4Box_L->SetSensitiveDetector(SenDetector);
    }

    
//--------- Visualization attributes -------------------------------
    
    G4VisAttributes* TubsVisAtt =   new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    G4VisAttributes* TubsVisAtt_v = new G4VisAttributes(G4Colour(0.0,1.0,0.0));
    logicBP1   ->SetVisAttributes(TubsVisAtt);
    logicBP1_v->SetVisAttributes(TubsVisAtt_v);
    logicBP1Con_R->SetVisAttributes(TubsVisAtt);
    logicBP1Con_L->SetVisAttributes(TubsVisAtt);
    logicTube2Con_L->SetVisAttributes(TubsVisAtt);
    logicTube2Con_R->SetVisAttributes(TubsVisAtt);


    G4VisAttributes* Tubs2CRVisAtt =   new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    G4VisAttributes* Tubs2CRVisAtt_v = new G4VisAttributes(G4Colour(0.0,1.0,0.0));
    logicTube2_C_R->SetVisAttributes(Tubs2CRVisAtt);
    logicTube2_C_R_v->SetVisAttributes(Tubs2CRVisAtt_v);
    logicTube2_C_L->SetVisAttributes(Tubs2CRVisAtt);
    logicTube2_C_L_v->SetVisAttributes(Tubs2CRVisAtt_v);

    if(flag_tube2EllipticalPart == "circletube2EllipticalPart"){    
	G4VisAttributes* Tubs2ERVisAtt =   new G4VisAttributes(G4Colour(0.0,0.0,1.0));
	G4VisAttributes* Tubs2ERVisAtt_v = new G4VisAttributes(G4Colour(0.0,1.0,0.0));
	logicTube2_E_CR->SetVisAttributes(Tubs2ERVisAtt);
	logicTube2_E_CR_v->SetVisAttributes(Tubs2ERVisAtt_v);
    }

    if(flag_tube2EllipticalPart == "mytube2EllipticalPart"){    
	G4VisAttributes* Tubs2ERUVisAtt =   new G4VisAttributes(G4Colour(0.0,0.0,1.0));
	G4VisAttributes* Tubs2ERUVisAtt_v = new G4VisAttributes(G4Colour(0.0,1.0,0.0));
	logicTube2_E_CRU->SetVisAttributes(Tubs2ERUVisAtt);
	logicTube2_E_CRU_v->SetVisAttributes(Tubs2ERUVisAtt_v);
	logicTube2_E_CLU->SetVisAttributes(Tubs2ERUVisAtt);
	logicTube2_E_CLU_v->SetVisAttributes(Tubs2ERUVisAtt_v);
	G4VisAttributes* Tubs2ERDVisAtt =   new G4VisAttributes(G4Colour(0.0,0.0,1.0));
	G4VisAttributes* Tubs2ERDVisAtt_v = new G4VisAttributes(G4Colour(0.0,1.0,0.0));
	logicTube2_E_CRD->SetVisAttributes(Tubs2ERDVisAtt);
	logicTube2_E_CRD_v->SetVisAttributes(Tubs2ERDVisAtt_v);
	logicTube2_E_CLD->SetVisAttributes(Tubs2ERDVisAtt);
	logicTube2_E_CLD_v->SetVisAttributes(Tubs2ERDVisAtt_v);
	G4VisAttributes* Tubs2ETRRUVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
	logicTube2_E_TRRU->SetVisAttributes(Tubs2ETRRUVisAtt);
	logicTube2_E_TRLU->SetVisAttributes(Tubs2ETRRUVisAtt);
	G4VisAttributes* Tubs2ETRRDVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
	logicTube2_E_TRRD->SetVisAttributes(Tubs2ETRRDVisAtt);
	logicTube2_E_TRLD->SetVisAttributes(Tubs2ETRRDVisAtt);
	G4VisAttributes* Tubs2ETRRVisAtt_v = new G4VisAttributes(G4Colour(0.0,1.0,0.0));
	logicTube2_E_TRR_v->SetVisAttributes(Tubs2ETRRVisAtt_v);
	logicTube2_E_TRL_v->SetVisAttributes(Tubs2ETRRVisAtt_v);
    }

    G4VisAttributes* QF1VisAtt = new G4VisAttributes(G4Colour(1.0,0.0,0.0));
    logicQD1_SRCO_R_U->SetVisAttributes(QF1VisAtt);
    logicQD1_SRCO_L_U->SetVisAttributes(QF1VisAtt);
    logicQD1_SRCO_R_D->SetVisAttributes(QF1VisAtt);
    logicQD1_SRCO_L_D->SetVisAttributes(QF1VisAtt);
    logicQD1_Al_P_R_U->SetVisAttributes(TubsVisAtt);
    logicQD1_Al_P_L_U->SetVisAttributes(TubsVisAtt);
    logicQD1_Al_P_R_D->SetVisAttributes(TubsVisAtt);
    logicQD1_Al_P_L_D->SetVisAttributes(TubsVisAtt);
    logicQD1_Al_M_R_U->SetVisAttributes(TubsVisAtt);
    logicQD1_Al_M_L_U->SetVisAttributes(TubsVisAtt);
    logicQD1_Al_M_R_D->SetVisAttributes(TubsVisAtt);
    logicQD1_Al_M_L_D->SetVisAttributes(TubsVisAtt);

/*
    G4VisAttributes* Tubs3TR1VisAtt = new G4VisAttributes(G4Colour(1.0,0.0,0.0));
    G4VisAttributes* Tubs3RUVisAtt = new G4VisAttributes(G4Colour(0.0,1.0,0.0));   
    logicTube3_TR1_R->SetVisAttributes(Tubs3TR1VisAtt);
    logicTube3_TR2_R->SetVisAttributes(Tubs3TR1VisAtt);
    logicTube3_TU_R_U->SetVisAttributes(Tubs3RUVisAtt);
    logicTube3_TU_R_D->SetVisAttributes(Tubs3RUVisAtt);   
    logicTube3_TR1_L->SetVisAttributes(Tubs3TR1VisAtt);
    logicTube3_TR2_L->SetVisAttributes(Tubs3TR1VisAtt);
    logicTube3_TU_L_U->SetVisAttributes(Tubs3RUVisAtt);
    logicTube3_TU_L_D->SetVisAttributes(Tubs3RUVisAtt);   
*/   


    G4VisAttributes* Tubs4RVisAtt =   new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    G4VisAttributes* Tubs4RVisAtt_v = new G4VisAttributes(G4Colour(0.0,1.0,0.0));
    logicTube4_R_U->SetVisAttributes(Tubs4RVisAtt);
    logicTube4_R_U_v->SetVisAttributes(Tubs4RVisAtt_v);
    logicTube4_R_D->SetVisAttributes(Tubs4RVisAtt);
    logicTube4_R_D_v->SetVisAttributes(Tubs4RVisAtt_v);
    logicTube4_L_U->SetVisAttributes(Tubs4RVisAtt);
    logicTube4_L_U_v->SetVisAttributes(Tubs4RVisAtt_v);
    logicTube4_L_D->SetVisAttributes(Tubs4RVisAtt);
    logicTube4_L_D_v->SetVisAttributes(Tubs4RVisAtt_v);
   
    G4VisAttributes* Tubs5CRVisAtt =   new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    G4VisAttributes* Tubs5CRVisAtt_v = new G4VisAttributes(G4Colour(0.0,1.0,0.0));
    logicTube5_C_R_U->SetVisAttributes(Tubs5CRVisAtt);
    logicTube5_C_R_U_v->SetVisAttributes(Tubs5CRVisAtt_v);
    logicTube5_C_R_D->SetVisAttributes(Tubs5CRVisAtt);
    logicTube5_C_R_D_v->SetVisAttributes(Tubs5CRVisAtt_v);
    logicTube5_C_L_U->SetVisAttributes(Tubs5CRVisAtt);
    logicTube5_C_L_U_v->SetVisAttributes(Tubs5CRVisAtt_v);
    logicTube5_C_L_D->SetVisAttributes(Tubs5CRVisAtt);
    logicTube5_C_L_D_v->SetVisAttributes(Tubs5CRVisAtt_v);
    
    G4VisAttributes* Tubs5CoRVisAtt =   new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    G4VisAttributes* Tubs5CoRVisAtt_v = new G4VisAttributes(G4Colour(0.0,1.0,0.0));
    logicTube5_Co_R_U->SetVisAttributes(Tubs5CoRVisAtt);
    logicTube5_Co_R_U_v->SetVisAttributes(Tubs5CoRVisAtt_v);
    logicTube5_Co_R_D->SetVisAttributes(Tubs5CoRVisAtt);
    logicTube5_Co_R_D_v->SetVisAttributes(Tubs5CoRVisAtt_v);
    logicTube5_Co_L_U->SetVisAttributes(Tubs5CoRVisAtt);
    logicTube5_Co_L_U_v->SetVisAttributes(Tubs5CoRVisAtt_v);
    logicTube5_Co_L_D->SetVisAttributes(Tubs5CoRVisAtt);
    logicTube5_Co_L_D_v->SetVisAttributes(Tubs5CoRVisAtt_v);

    //G4VisAttributes* Tubs3TR1VisAtt = new G4VisAttributes(G4Colour(1.0,0.0,0.0));
    //G4VisAttributes* Tubs3RUVisAtt = new G4VisAttributes(G4Colour(0.0,1.0,0.0));   
    
    G4VisAttributes* shielding = new G4VisAttributes(G4Colour(0.8,0.0,1.0));
    logicSOY_T1_R->SetVisAttributes(shielding);
    logicSOY_T1_L->SetVisAttributes(shielding);

    logicSOY_T2_R->SetVisAttributes(shielding);
    logicSOY_T2_L->SetVisAttributes(shielding);
    
    logicSOY_Co3_R->SetVisAttributes(shielding);
    logicSOY_Co3_L->SetVisAttributes(shielding);
    
    logicSOY_Co4_R->SetVisAttributes(shielding);
    logicSOY_Co4_L->SetVisAttributes(shielding);
    
    logicSOY_T5_R->SetVisAttributes(shielding);
    logicSOY_T5_L->SetVisAttributes(shielding);
    
    logicSOY_T6_R->SetVisAttributes(shielding);
    logicSOY_T6_L->SetVisAttributes(shielding);
    
    logicSOY_Co7_R->SetVisAttributes(shielding);
    logicSOY_Co7_L->SetVisAttributes(shielding);

    G4cout<<"((-)) ((-)) ((-)) ((-)) ((-)) ((-)) ((-))"<<G4endl;


    logicBoxShield1_R->SetVisAttributes(shielding); 
    logicBoxShield1_L->SetVisAttributes(shielding);

    logicBoxShield2_R->SetVisAttributes(shielding); 
    logicBoxShield2_L->SetVisAttributes(shielding);

    logicBoxShield3_R->SetVisAttributes(shielding); 
    logicBoxShield3_L->SetVisAttributes(shielding);

    logicBoxShield4_R->SetVisAttributes(shielding); 
    logicBoxShield4_L->SetVisAttributes(shielding);



    //photon det
    //logicPbBoxForPhot_R->SetVisAttributes(shielding);
    logicPbBoxBackPhot_R->SetVisAttributes(shielding);
    logicPbBoxCenPhot_R->SetVisAttributes(shielding);
    //logicPbBoxForPhot_L->SetVisAttributes(shielding);
    logicPbBoxForPhot->SetVisAttributes(shielding);
    logicPbBoxBackPhot_L->SetVisAttributes(shielding);
    logicPbBoxCenPhot_L->SetVisAttributes(shielding);
    G4VisAttributes* visAtrPlast = new G4VisAttributes(G4Colour(1.0,1.0,0.0));   
    logicPlasticBox_R->SetVisAttributes(visAtrPlast);
    logicPlasticBox_L->SetVisAttributes(visAtrPlast);
    G4VisAttributes* visAtrScin = new G4VisAttributes(G4Colour(1.0,0.0784,0.576));   
    logicPbWO1Box_R->SetVisAttributes(visAtrScin);
    logicPbWO2Box_R->SetVisAttributes(visAtrScin);
    logicPbWO3Box_R->SetVisAttributes(visAtrScin); 
    logicPbWO4Box_R->SetVisAttributes(visAtrScin);

    logicPbWO1Box_L->SetVisAttributes(visAtrScin);
    logicPbWO2Box_L->SetVisAttributes(visAtrScin);
    logicPbWO3Box_L->SetVisAttributes(visAtrScin);
    logicPbWO4Box_L->SetVisAttributes(visAtrScin);
    //logicWinPhot_R->SetVisAttributes(TubsVisAtt_v);
    //logicWinPhot_L->SetVisAttributes(TubsVisAtt_v);



    //Sp17-...
    //G4VisAttributes* SpVisAttributes =   new G4VisAttributes(G4Colour(0.5,0.2,0.2));
    //logicSp17->SetVisAttributes(SpVisAttributes);
    //logicSp18->SetVisAttributes(SpVisAttributes);

    }

    //--------- example of User Limits -------------------------------
    
    // below is an example of how to set tracking constraints in a given
    // logical volume(see also in N02PhysicsList how to setup the processes
    // G4StepLimiter or G4UserSpecialCuts).
    
    // Sets a max Step length in the tracker region, with G4StepLimiter
    //

    G4double maxStep = 0.01*mm;
    G4double maxLength = 5*m; 
    G4double maxTime = 100.*ns;
    G4double minEkin = 100*eV; 
    stepLimit = new G4UserLimits(maxStep,maxLength,maxTime,minEkin);
    logicTube4_R_U_v->SetUserLimits(stepLimit);
    logicTube4_R_D_v->SetUserLimits(stepLimit);
    logicTube4_L_U_v->SetUserLimits(stepLimit);
    logicTube4_L_D_v->SetUserLimits(stepLimit);
    logicTube2_C_R->SetUserLimits(stepLimit);
    logicTube2_C_L->SetUserLimits(stepLimit);
    logicTube2_E_CRU_v->SetUserLimits(stepLimit);
    logicTube2_E_CRD_v->SetUserLimits(stepLimit);
    logicTube2_E_CLU_v->SetUserLimits(stepLimit);
    logicTube2_E_CLD_v->SetUserLimits(stepLimit);
    

    // logicPbWO1Box_R->SetUserLimits(stepLimit);
    // logicPbWO2Box_R->SetUserLimits(stepLimit);
    // logicPbWO3Box_R->SetUserLimits(stepLimit);
    // logicPbWO4Box_R->SetUserLimits(stepLimit);

    // logicTracker->SetUserLimits(stepLimit);
    // Set additional contraints on the track, with G4UserSpecialCuts
    //
    // G4double maxLength = 2*fTrackerLength, maxTime = 0.1*ns, minEkin = 10*MeV;
    // logicTracker->SetUserLimits(new G4UserLimits(maxStep,maxLength,maxTime,
    //                                               minEkin));


    G4cout << " ExN02DetectorConstruction::Construct() : end" << G4endl<<G4endl;  
    G4cout << " ---------------------------------------------------------- " << G4endl;  
    //return (world->GetPhysicalVol());
    

    return physiWorld;
}

void ExN02DetectorConstruction::PrintToFile(FILE *stream,G4ThreeVector &v, G4int j){
    fprintf( stream, "         xSp(%2d) = %10.5f \n", j, v.getX());
    fprintf( stream, "         ySp(%2d) = %10.5f \n", j, v.getY());
    fprintf( stream, "         zSp(%2d) = %10.5f \n", j, v.getZ());
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
