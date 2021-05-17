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
// $Id: ExN02DetectorConstruction.hh,v 1.9 2007/10/17 08:50:35 gcosmo Exp $
// GEANT4 tag $Name: geant4-09-01-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef ExN02DetectorConstruction_h
#define ExN02DetectorConstruction_h 1


#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "ExN02MagneticField.hh"

#include "G4RunManager.hh"

//Field
#include "G4MagneticField.hh"
#include "G4EqMagElectricField.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4ChordFinder.hh"

#include "G4UniformElectricField.hh"
//--------------------------------

class G4Box;
class G4Tubs;
class G4Cons;
class G4Trd;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;
class ExN02DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    
    ExN02DetectorConstruction();
    ~ExN02DetectorConstruction();
    
public:
    
    G4VPhysicalVolume* Construct();

    void PrintToFile(FILE *stream,G4ThreeVector &v, G4int j);
    
    const 
    //G4VPhysicalVolume* GetTracker() {return physiTracker;};
    //G4double GetTrackerFullLength() {return fTrackerLength;};
    //G4double GetTargetFullLength()  {return fTargetLength;};
   
    G4double GetWorldFullLength()   {return fWorldLength;}; 
    
    //void setTargetMaterial (G4String);
    //void setChamberMaterial(G4String);


    //void SetMagField(G4double);
    
    void SetRunManager(G4RunManager *runMan) {runManager = runMan;};
    G4RunManager *GetRunManager() {return runManager;};

private:
    
    G4RunManager *runManager;

    //-----------------------------------------------------------------------
    // Materials
    //-----------------------------------------------------------------------
    G4Material* BP1Mater;     
    G4Material* BP1Mater_v;
    G4Material* QDMater;
    G4Material* Air;
    G4Material* ShieldsMater;
    G4Material* PVCMater;
    G4Material* IronMater;
    G4Material* PbWOMater;

    G4Material* PbWOMater1;
    G4Material* PbWOMater2;
    //-----------------------------------------------------------------------

    //----------------------------------------------------------------------- 
    //field 
    //-----------------------------------------------------------------------
    ExN02MagneticField*     fpMagField;   // pointer to the magnetic field 
    G4EqMagElectricField*   fEquation;
    G4MagIntegratorStepper* fStepper;
    G4MagInt_Driver*        fIntgrDriver;
    G4ChordFinder*          fChordFinder; 
    //G4UniformElectricField* fpMagField; 
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //limits
    //-----------------------------------------------------------------------
    G4UserLimits* stepLimit;             // pointer to user step limits
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //world volume
    //-----------------------------------------------------------------------
    G4double fWorldLength;            // Full length of the world volume     
    G4double fWorldDX;            // Extension in x of the world volume
    G4double fWorldDY;            // Extension in Y of the world volume
    
    G4Box*             solidWorld;    // pointer to the solid envelope 
    G4LogicalVolume*   logicWorld;    // pointer to the logical envelope
    G4VPhysicalVolume* physiWorld;    // pointer to the physical envelope
    //----------------------------------------------------------------------- 

    //-----------------------------------------------------------------------
    //magnets
    //QD0 consist of two part: conical and cylindrical sections
    //-----------------------------------------------------------------------
    G4Cons*             solidQD0_Co_R;  
    G4LogicalVolume*    logicQD0_Co_R;    
    G4VPhysicalVolume*  physiQD0_Co_R;   

    G4Tubs*             solidQD0_T_R;  
    G4LogicalVolume*    logicQD0_T_R;    
    G4VPhysicalVolume*  physiQD0_T_R;   

    G4Cons*             solidQD0_Co_L;  
    G4LogicalVolume*    logicQD0_Co_L;    
    G4VPhysicalVolume*  physiQD0_Co_L;   

    G4Tubs*             solidQD0_T_L;  
    G4LogicalVolume*    logicQD0_T_L;    
    G4VPhysicalVolume*  physiQD0_T_L;   
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //QD1 consist of two different materials aluminium and SRCO
    //-----------------------------------------------------------------------
    G4Tubs*             solidQD1_Al_R_U;  
    G4LogicalVolume*    logicQD1_Al_R_U;    
    G4VPhysicalVolume*  physiQD1_Al_R_U;   
    G4Tubs*             solidQD1_SRCO_R_U;  
    G4LogicalVolume*    logicQD1_SRCO_R_U;    
    G4VPhysicalVolume*  physiQD1_SRCO_R_U;   
    G4Tubs*             solidQD1_Al_R_D;  
    G4LogicalVolume*    logicQD1_Al_R_D;    
    G4VPhysicalVolume*  physiQD1_Al_R_D;   
    G4Tubs*             solidQD1_SRCO_R_D;  
    G4LogicalVolume*    logicQD1_SRCO_R_D;    
    G4VPhysicalVolume*  physiQD1_SRCO_R_D;   

    G4Tubs*             solidQD1_Al_L_U;  
    G4LogicalVolume*    logicQD1_Al_L_U;    
    G4VPhysicalVolume*  physiQD1_Al_L_U;   
    G4Tubs*             solidQD1_SRCO_L_U;  
    G4LogicalVolume*    logicQD1_SRCO_L_U;    
    G4VPhysicalVolume*  physiQD1_SRCO_L_U;   
    G4Tubs*             solidQD1_Al_L_D;  
    G4LogicalVolume*    logicQD1_Al_L_D;    
    G4VPhysicalVolume*  physiQD1_Al_L_D;   
    G4Tubs*             solidQD1_SRCO_L_D;  
    G4LogicalVolume*    logicQD1_SRCO_L_D;    
    G4VPhysicalVolume*  physiQD1_SRCO_L_D;
    //----------------------------------------------------------------------- 

    //-----------------------------------------------------------------------
    //Tubes1
    //-----------------------------------------------------------------------
    G4Tubs*            solidBP1;    // pointer to the solid Beampipe section 1
    G4LogicalVolume*   logicBP1;    // pointer to the logical Beampipe section 1
    G4VPhysicalVolume* physiBP1;    // pointer to the physical Beampipe section 1
    
    G4Tubs*            solidBP1_v;  // pointer to the vacuum Beampipe section 1
    G4LogicalVolume*   logicBP1_v;  // pointer to the logical Beampipe section 1
    G4VPhysicalVolume* physiBP1_v;  // pointer to the physical Beampipe section 1
    //----------------------------------------------------------------------- 

    //----------------------------------------------------------------------- 
    // connecting rings around the BP1
    //----------------------------------------------------------------------- 
    G4Tubs*            solidBP1Con_R;    // pointer to the solid Beampipe section 1
    G4LogicalVolume*   logicBP1Con_R;    // pointer to the logical Beampipe section 1
    G4VPhysicalVolume* physiBP1Con_R;    // pointer to the physical Beampipe section 1
    
    G4Tubs*            solidBP1Con_L;  // pointer to the vacuum Beampipe section 1
    G4LogicalVolume*   logicBP1Con_L;  // pointer to the logical Beampipe section 1
    G4VPhysicalVolume* physiBP1Con_L;  // pointer to the physical Beampipe section 1

    //----------------------------------------------------------------------- 

    //-----------------------------------------------------------------------
    //Tubes2 circle part
    //-----------------------------------------------------------------------
    G4Tubs*            solidTube2_C_R; // pointer to the solid Tube2_C_R
    G4LogicalVolume*   logicTube2_C_R; // pointer to the logical Tube2_C_R
    G4VPhysicalVolume* physiTube2_C_R; // pointer to the physical Tube2_C_R
    
    G4Tubs*            solidTube2_C_R_v;  // pointer to the vacuum Tube2_C_R
    G4LogicalVolume*   logicTube2_C_R_v; 
    G4VPhysicalVolume* physiTube2_C_R_v; 

    G4Tubs*            solidTube2_C_L; // pointer to the solid Tube2_C_R
    G4LogicalVolume*   logicTube2_C_L; // pointer to the logical Tube2_C_R
    G4VPhysicalVolume* physiTube2_C_L; // pointer to the physical Tube2_C_R
    
    G4Tubs*            solidTube2_C_L_v;  // pointer to the vacuum Tube2_C_R
    G4LogicalVolume*   logicTube2_C_L_v; 
    G4VPhysicalVolume* physiTube2_C_L_v; 
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    // rings around the Tube2 circular part which conected to the BP1
    //-----------------------------------------------------------------------
    G4Tubs*            solidTube2Con_R; 
    G4LogicalVolume*   logicTube2Con_R; 
    G4VPhysicalVolume* physiTube2Con_R; 

    G4Tubs*            solidTube2Con_L; 
    G4LogicalVolume*   logicTube2Con_L; 
    G4VPhysicalVolume* physiTube2Con_L; 
    //-----------------------------------------------------------------------


    //-----------------------------------------------------------------------
    //Tubes2 elliptical part
    //-----------------------------------------------------------------------
    //----Case-of-just-circle-----------------------------------------------
    G4Tubs*            solidTube2_E_CR; // pointer to the solid Tube2_E_R
    G4LogicalVolume*   logicTube2_E_CR; // pointer to the logical Tube2_E_R
    G4VPhysicalVolume* physiTube2_E_CR; // pointer to the physical Tube2_E_R
    
    G4Tubs*            solidTube2_E_CR_v; // pointer to the vacuum Tube2_E_R
    G4LogicalVolume*   logicTube2_E_CR_v; 
    G4VPhysicalVolume* physiTube2_E_CR_v; 

    G4Tubs*            solidTube2_E_CL; // pointer to the solid Tube2_E_R
    G4LogicalVolume*   logicTube2_E_CL; // pointer to the logical Tube2_E_R
    G4VPhysicalVolume* physiTube2_E_CL; // pointer to the physical Tube2_E_R
    
    G4Tubs*            solidTube2_E_CL_v; // pointer to the vacuum Tube2_E_R
    G4LogicalVolume*   logicTube2_E_CL_v; 
    G4VPhysicalVolume* physiTube2_E_CL_v; 
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //"ellictical" part consist of two half circles(left and right) 
    //and two trapezoid up and down
    //-----------------------------------------------------------------------
    G4Tubs*            solidTube2_E_CRU; // pointer to the solid Tube2_E_R
    G4LogicalVolume*   logicTube2_E_CRU; // pointer to the logical Tube2_E_R
    G4VPhysicalVolume* physiTube2_E_CRU; // pointer to the physical Tube2_E_R

    G4Tubs*            solidTube2_E_CRD; // pointer to the solid Tube2_E_R
    G4LogicalVolume*   logicTube2_E_CRD; // pointer to the logical Tube2_E_R
    G4VPhysicalVolume* physiTube2_E_CRD; // pointer to the physical Tube2_E_R
    
    G4Tubs*            solidTube2_E_CRU_v;  // pointer to the vacuum Tube2_E_R
    G4LogicalVolume*   logicTube2_E_CRU_v; 
    G4VPhysicalVolume* physiTube2_E_CRU_v; 

    G4Tubs*            solidTube2_E_CRD_v;  // pointer to the vacuum Tube2_E_R
    G4LogicalVolume*   logicTube2_E_CRD_v; 
    G4VPhysicalVolume* physiTube2_E_CRD_v;
 
    G4Tubs*            solidTube2_E_CLU; // pointer to the solid Tube2_E_R
    G4LogicalVolume*   logicTube2_E_CLU; // pointer to the logical Tube2_E_R
    G4VPhysicalVolume* physiTube2_E_CLU; // pointer to the physical Tube2_E_R

    G4Tubs*            solidTube2_E_CLD; // pointer to the solid Tube2_E_R
    G4LogicalVolume*   logicTube2_E_CLD; // pointer to the logical Tube2_E_R
    G4VPhysicalVolume* physiTube2_E_CLD; // pointer to the physical Tube2_E_R
    
    G4Tubs*            solidTube2_E_CLU_v;  // pointer to the vacuum Tube2_E_R
    G4LogicalVolume*   logicTube2_E_CLU_v; 
    G4VPhysicalVolume* physiTube2_E_CLU_v; 

    G4Tubs*            solidTube2_E_CLD_v;  // pointer to the vacuum Tube2_E_R
    G4LogicalVolume*   logicTube2_E_CLD_v; 
    G4VPhysicalVolume* physiTube2_E_CLD_v;
    //trapezoid
    G4Trd*             solidTube2_E_TRRU; // pointer to the solid Tube5_Co_R_U
    G4LogicalVolume*   logicTube2_E_TRRU; // pointer to the logical Tube5_Co_R_U
    G4VPhysicalVolume* physiTube2_E_TRRU; // pointer to the physical Tube5_Co_R_U

    G4Trd*             solidTube2_E_TRRD; // pointer to the solid Tube5_Co_R_U
    G4LogicalVolume*   logicTube2_E_TRRD; // pointer to the logical Tube5_Co_R_U
    G4VPhysicalVolume* physiTube2_E_TRRD; // pointer to the physical Tube5_Co_R_U
    
    G4Trd*             solidTube2_E_TRR_v; // pointer to the solid Tube5_Co_R_U
    G4LogicalVolume*   logicTube2_E_TRR_v; // pointer to the logical Tube5_Co_R_U
    G4VPhysicalVolume* physiTube2_E_TRR_v; // pointer to the physical Tube5_Co_R_U

    G4Trd*             solidTube2_E_TRLU; // pointer to the solid Tube5_Co_R_U
    G4LogicalVolume*   logicTube2_E_TRLU; // pointer to the logical Tube5_Co_R_U
    G4VPhysicalVolume* physiTube2_E_TRLU; // pointer to the physical Tube5_Co_R_U

    G4Trd*             solidTube2_E_TRLD; // pointer to the solid Tube5_Co_R_U
    G4LogicalVolume*   logicTube2_E_TRLD; // pointer to the logical Tube5_Co_R_U
    G4VPhysicalVolume* physiTube2_E_TRLD; // pointer to the physical Tube5_Co_R_U
    
    G4Trd*             solidTube2_E_TRL_v; // pointer to the solid Tube5_Co_R_U
    G4LogicalVolume*   logicTube2_E_TRL_v; // pointer to the logical Tube5_Co_R_U
    G4VPhysicalVolume* physiTube2_E_TRL_v; // pointer to the physical Tube5_Co_R_U
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //V-like tube
    //-----------------------------------------------------------------------
    G4Trd*             solidTube3_TR1_R; // pointer to the solid Tube5_Co_R_U
    G4LogicalVolume*   logicTube3_TR1_R; // pointer to the logical Tube5_Co_R_U
    G4VPhysicalVolume* physiTube3_TR1_R; // pointer to the physical Tube5_Co_R_U

    G4Trd*             solidTube3_TR2_R; // pointer to the solid Tube5_Co_R_U
    G4LogicalVolume*   logicTube3_TR2_R; // pointer to the logical Tube5_Co_R_U
    G4VPhysicalVolume* physiTube3_TR2_R; // pointer to the physical Tube5_Co_R_U

    G4Trd*             solidTube3_TR1_L; // pointer to the solid Tube5_Co_R_U
    G4LogicalVolume*   logicTube3_TR1_L; // pointer to the logical Tube5_Co_R_U
    G4VPhysicalVolume* physiTube3_TR1_L; // pointer to the physical Tube5_Co_R_U
    
    G4Trd*             solidTube3_TR2_L; // pointer to the solid Tube5_Co_R_U
    G4LogicalVolume*   logicTube3_TR2_L; // pointer to the logical Tube5_Co_R_U
    G4VPhysicalVolume* physiTube3_TR2_L; // pointer to the physical Tube5_Co_R_U

    G4Tubs*            solidTube3_TU_R_U;
    G4LogicalVolume*   logicTube3_TU_R_U;
    G4VPhysicalVolume* physiTube3_TU_R_U; 

    G4Tubs*            solidTube3_TU_R_D;
    G4LogicalVolume*   logicTube3_TU_R_D;
    G4VPhysicalVolume* physiTube3_TU_R_D; 

    G4Tubs*            solidTube3_TU_L_U;
    G4LogicalVolume*   logicTube3_TU_L_U;
    G4VPhysicalVolume* physiTube3_TU_L_U; 

    G4Tubs*            solidTube3_TU_L_D;
    G4LogicalVolume*   logicTube3_TU_L_D;
    G4VPhysicalVolume* physiTube3_TU_L_D; 
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //Tubes4
    //-----------------------------------------------------------------------
    G4Tubs*            solidTube4_R_U; // pointer to the solid Tube4_R_U
    G4LogicalVolume*   logicTube4_R_U; // pointer to the logical Tube4_R_U
    G4VPhysicalVolume* physiTube4_R_U; // pointer to the physical Tube4_R_U
    
    G4Tubs*            solidTube4_R_U_v;  // pointer to the vacuum Tube4_R_U
    G4LogicalVolume*   logicTube4_R_U_v; 
    G4VPhysicalVolume* physiTube4_R_U_v; 

    G4Tubs*            solidTube4_R_D; // pointer to the solid Tube4_R_U
    G4LogicalVolume*   logicTube4_R_D; // pointer to the logical Tube4_R_U
    G4VPhysicalVolume* physiTube4_R_D; // pointer to the physical Tube4_R_U
    
    G4Tubs*            solidTube4_R_D_v;  // pointer to the vacuum Tube4_R_U
    G4LogicalVolume*   logicTube4_R_D_v; 
    G4VPhysicalVolume* physiTube4_R_D_v; 

    G4Tubs*            solidTube4_L_U; // pointer to the solid Tube4_R_U
    G4LogicalVolume*   logicTube4_L_U; // pointer to the logical Tube4_R_U
    G4VPhysicalVolume* physiTube4_L_U; // pointer to the physical Tube4_R_U
    
    G4Tubs*            solidTube4_L_U_v;  // pointer to the vacuum Tube4_R_U
    G4LogicalVolume*   logicTube4_L_U_v; 
    G4VPhysicalVolume* physiTube4_L_U_v; 

    G4Tubs*            solidTube4_L_D; // pointer to the solid Tube4_R_U
    G4LogicalVolume*   logicTube4_L_D; // pointer to the logical Tube4_R_U
    G4VPhysicalVolume* physiTube4_L_D; // pointer to the physical Tube4_R_U
    
    G4Tubs*            solidTube4_L_D_v;  // pointer to the vacuum Tube4_R_U
    G4LogicalVolume*   logicTube4_L_D_v; 
    G4VPhysicalVolume* physiTube4_L_D_v; 
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //Tubes5 (circle part)
    //-----------------------------------------------------------------------
    G4Tubs*            solidTube5_C_R_U; // pointer to the solid Tube5_C_R_U
    G4LogicalVolume*   logicTube5_C_R_U; // pointer to the logical Tube5_C_R_U
    G4VPhysicalVolume* physiTube5_C_R_U; // pointer to the physical Tube5_C_R_U
    
    G4Tubs*            solidTube5_C_R_U_v;  // pointer to the vacuum Tube5_C_R_U
    G4LogicalVolume*   logicTube5_C_R_U_v; 
    G4VPhysicalVolume* physiTube5_C_R_U_v; 

    G4Tubs*            solidTube5_C_R_D; // pointer to the solid Tube5_C_R_U
    G4LogicalVolume*   logicTube5_C_R_D; // pointer to the logical Tube5_C_R_U
    G4VPhysicalVolume* physiTube5_C_R_D; // pointer to the physical Tube5_C_R_U
    
    G4Tubs*            solidTube5_C_R_D_v;  // pointer to the vacuum Tube5_C_R_U
    G4LogicalVolume*   logicTube5_C_R_D_v; 
    G4VPhysicalVolume* physiTube5_C_R_D_v; 
    
    G4Tubs*            solidTube5_C_L_U; // pointer to the solid Tube5_C_R_U
    G4LogicalVolume*   logicTube5_C_L_U; // pointer to the logical Tube5_C_R_U
    G4VPhysicalVolume* physiTube5_C_L_U; // pointer to the physical Tube5_C_R_U
    
    G4Tubs*            solidTube5_C_L_U_v;  // pointer to the vacuum Tube5_C_R_U
    G4LogicalVolume*   logicTube5_C_L_U_v; 
    G4VPhysicalVolume* physiTube5_C_L_U_v; 

    G4Tubs*            solidTube5_C_L_D; // pointer to the solid Tube5_C_R_U
    G4LogicalVolume*   logicTube5_C_L_D; // pointer to the logical Tube5_C_R_U
    G4VPhysicalVolume* physiTube5_C_L_D; // pointer to the physical Tube5_C_R_U
    
    G4Tubs*            solidTube5_C_L_D_v;  // pointer to the vacuum Tube5_C_R_U
    G4LogicalVolume*   logicTube5_C_L_D_v; 
    G4VPhysicalVolume* physiTube5_C_L_D_v; 
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //Tubes5 (cone part)
    //-----------------------------------------------------------------------
    G4Cons*            solidTube5_Co_R_U; // pointer to the solid Tube5_Co_R_U
    G4LogicalVolume*   logicTube5_Co_R_U; // pointer to the logical Tube5_Co_R_U
    G4VPhysicalVolume* physiTube5_Co_R_U; // pointer to the physical Tube5_Co_R_U

    G4Cons*            solidTube5_Co_R_U_v;  // pointer to the vacuum Tube5_Co_R_U
    G4LogicalVolume*   logicTube5_Co_R_U_v; 
    G4VPhysicalVolume* physiTube5_Co_R_U_v; 

    G4Cons*            solidTube5_Co_R_D; // pointer to the solid Tube5_Co_R_U
    G4LogicalVolume*   logicTube5_Co_R_D; // pointer to the logical Tube5_Co_R_U
    G4VPhysicalVolume* physiTube5_Co_R_D; // pointer to the physical Tube5_Co_R_U

    G4Cons*            solidTube5_Co_R_D_v;  // pointer to the vacuum Tube5_Co_R_U
    G4LogicalVolume*   logicTube5_Co_R_D_v; 
    G4VPhysicalVolume* physiTube5_Co_R_D_v; 
    G4Cons*            solidTube5_Co_L_U; // pointer to the solid Tube5_Co_R_U
    G4LogicalVolume*   logicTube5_Co_L_U; // pointer to the logical Tube5_Co_R_U
    G4VPhysicalVolume* physiTube5_Co_L_U; // pointer to the physical Tube5_Co_R_U

    G4Cons*            solidTube5_Co_L_U_v;  // pointer to the vacuum Tube5_Co_R_U
    G4LogicalVolume*   logicTube5_Co_L_U_v; 
    G4VPhysicalVolume* physiTube5_Co_L_U_v; 

    G4Cons*            solidTube5_Co_L_D; // pointer to the solid Tube5_Co_R_U
    G4LogicalVolume*   logicTube5_Co_L_D; // pointer to the logical Tube5_Co_R_U
    G4VPhysicalVolume* physiTube5_Co_L_D; // pointer to the physical Tube5_Co_R_U

    G4Cons*            solidTube5_Co_L_D_v;  // pointer to the vacuum Tube5_Co_R_U
    G4LogicalVolume*   logicTube5_Co_L_D_v; 
    G4VPhysicalVolume* physiTube5_Co_L_D_v; 
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    // SOYUZ shielding
    //-----------------------------------------------------------------------

    //Tube part 1
    G4Tubs*            solidSOY_T1_R;
    G4LogicalVolume*   logicSOY_T1_R;
    G4VPhysicalVolume* physiSOY_T1_R;

    G4Tubs*            solidSOY_T1_L;
    G4LogicalVolume*   logicSOY_T1_L;
    G4VPhysicalVolume* physiSOY_T1_L;

    //Tube part 2 
    G4Tubs*            solidSOY_T2_R;
    G4LogicalVolume*   logicSOY_T2_R;
    G4VPhysicalVolume* physiSOY_T2_R;

    G4Tubs*            solidSOY_T2_L;
    G4LogicalVolume*   logicSOY_T2_L;
    G4VPhysicalVolume* physiSOY_T2_L;
 
    //Cone part 3
    G4Cons*            solidSOY_Co3_R;
    G4LogicalVolume*   logicSOY_Co3_R; 
    G4VPhysicalVolume* physiSOY_Co3_R; 

    G4Cons*            solidSOY_Co3_L;
    G4LogicalVolume*   logicSOY_Co3_L; 
    G4VPhysicalVolume* physiSOY_Co3_L; 

    //Cone part 4
    G4Cons*            solidSOY_Co4_R;
    G4LogicalVolume*   logicSOY_Co4_R; 
    G4VPhysicalVolume* physiSOY_Co4_R; 

    G4Cons*            solidSOY_Co4_L;
    G4LogicalVolume*   logicSOY_Co4_L; 
    G4VPhysicalVolume* physiSOY_Co4_L; 

    //Tube part 5 
    G4Tubs*            solidSOY_T5_R;
    G4LogicalVolume*   logicSOY_T5_R;
    G4VPhysicalVolume* physiSOY_T5_R;

    G4Tubs*            solidSOY_T5_L;
    G4LogicalVolume*   logicSOY_T5_L;
    G4VPhysicalVolume* physiSOY_T5_L;

    //Tube part 6 
    G4Tubs*            solidSOY_T6_R;
    G4LogicalVolume*   logicSOY_T6_R;
    G4VPhysicalVolume* physiSOY_T6_R;

    G4Tubs*            solidSOY_T6_L;
    G4LogicalVolume*   logicSOY_T6_L;
    G4VPhysicalVolume* physiSOY_T6_L;


    //Cone part 7
    G4Cons*            solidSOY_Co7_R;
    G4LogicalVolume*   logicSOY_Co7_R; 
    G4VPhysicalVolume* physiSOY_Co7_R; 

    G4Cons*            solidSOY_Co7_L;
    G4LogicalVolume*   logicSOY_Co7_L; 
    G4VPhysicalVolume* physiSOY_Co7_L; 
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    // Shielding in the back of the calo module 
    //-----------------------------------------------------------------------

    //Box 1
    G4Box*             solidBoxShield1_R;
    G4LogicalVolume*   logicBoxShield1_R; 
    G4VPhysicalVolume* physiBoxShield1_R; 

    G4Box*             solidBoxShield1_L;
    G4LogicalVolume*   logicBoxShield1_L; 
    G4VPhysicalVolume* physiBoxShield1_L;

    //Box 2
    G4Box*             solidBoxShield2_R;
    G4LogicalVolume*   logicBoxShield2_R; 
    G4VPhysicalVolume* physiBoxShield2_R; 

    G4Box*             solidBoxShield2_L;
    G4LogicalVolume*   logicBoxShield2_L; 
    G4VPhysicalVolume* physiBoxShield2_L;

    //Box 3
    G4Box*             solidBoxShield3_R;
    G4LogicalVolume*   logicBoxShield3_R; 
    G4VPhysicalVolume* physiBoxShield3_R; 

    G4Box*             solidBoxShield3_L;
    G4LogicalVolume*   logicBoxShield3_L; 
    G4VPhysicalVolume* physiBoxShield3_L;

    //Box 4
    G4Box*             solidBoxShield4_R;
    G4LogicalVolume*   logicBoxShield4_R; 
    G4VPhysicalVolume* physiBoxShield4_R; 

    G4Box*             solidBoxShield4_L;
    G4LogicalVolume*   logicBoxShield4_L; 
    G4VPhysicalVolume* physiBoxShield4_L;
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    // photon detector
    //-----------------------------------------------------------------------

    //Plastic box
    G4Box*             solidPlasticBox_R;
    G4LogicalVolume*   logicPlasticBox_R; 
    G4VPhysicalVolume* physiPlasticBox_R;

    G4Box*             solidPlasticBox_L;
    G4LogicalVolume*   logicPlasticBox_L; 
    G4VPhysicalVolume* physiPlasticBox_L;

    //Iron boxs 
    // 1 R
    G4Box*             solidIron1Box_R;
    G4LogicalVolume*   logicIron1Box_R; 
    G4VPhysicalVolume* physiIron1Box_R;
    // 2 R
    G4Box*             solidIron2Box_R;
    G4LogicalVolume*   logicIron2Box_R; 
    G4VPhysicalVolume* physiIron2Box_R;
    // 3 R
    G4Box*             solidIron3Box_R;
    G4LogicalVolume*   logicIron3Box_R; 
    G4VPhysicalVolume* physiIron3Box_R;
    // 4 R
    G4Box*             solidIron4Box_R;
    G4LogicalVolume*   logicIron4Box_R; 
    G4VPhysicalVolume* physiIron4Box_R;
    // 1 L
    G4Box*             solidIron1Box_L;
    G4LogicalVolume*   logicIron1Box_L; 
    G4VPhysicalVolume* physiIron1Box_L;
    // 2 L
    G4Box*             solidIron2Box_L;
    G4LogicalVolume*   logicIron2Box_L; 
    G4VPhysicalVolume* physiIron2Box_L;
    // 3 L
    G4Box*             solidIron3Box_L;
    G4LogicalVolume*   logicIron3Box_L; 
    G4VPhysicalVolume* physiIron3Box_L;
    // 4 L
    G4Box*             solidIron4Box_L;
    G4LogicalVolume*   logicIron4Box_L; 
    G4VPhysicalVolume* physiIron4Box_L;

    //PbWO boxs 
    // 1 R
    G4Box*             solidPbWO1Box_R;
    G4LogicalVolume*   logicPbWO1Box_R; 
    G4VPhysicalVolume* physiPbWO1Box_R;
    // 2 R
    G4Box*             solidPbWO2Box_R;
    G4LogicalVolume*   logicPbWO2Box_R; 
    G4VPhysicalVolume* physiPbWO2Box_R;
    // 3 R
    G4Box*             solidPbWO3Box_R;
    G4LogicalVolume*   logicPbWO3Box_R; 
    G4VPhysicalVolume* physiPbWO3Box_R;
    // 4 R
    G4Box*             solidPbWO4Box_R;
    G4LogicalVolume*   logicPbWO4Box_R; 
    G4VPhysicalVolume* physiPbWO4Box_R;
    // 1 L
    G4Box*             solidPbWO1Box_L;
    G4LogicalVolume*   logicPbWO1Box_L; 
    G4VPhysicalVolume* physiPbWO1Box_L;
    // 2 L
    G4Box*             solidPbWO2Box_L;
    G4LogicalVolume*   logicPbWO2Box_L; 
    G4VPhysicalVolume* physiPbWO2Box_L;
    // 3 L
    G4Box*             solidPbWO3Box_L;
    G4LogicalVolume*   logicPbWO3Box_L; 
    G4VPhysicalVolume* physiPbWO3Box_L;
    // 4 L
    G4Box*             solidPbWO4Box_L;
    G4LogicalVolume*   logicPbWO4Box_L; 
    G4VPhysicalVolume* physiPbWO4Box_L;

    //Shielding material
    //---
    G4LogicalVolume* logicPbBoxForPhot_R;
    G4LogicalVolume* logicPbBoxBackPhot_R;
    G4LogicalVolume* logicPbBoxCenPhot_R;

    G4LogicalVolume* logicPbBoxForPhot_L;
    G4LogicalVolume* logicPbBoxBackPhot_L;
    G4LogicalVolume* logicPbBoxCenPhot_L;
    //-----------------------------------------------------------------------


    G4LogicalVolume* logicSp17;
    G4LogicalVolume* logicSp18;
    G4LogicalVolume* logicSp19;


    //-----------------------------------------------------------------------
    //!!!!!!!!!!create SensitiveDetector !!!!!!!!
    // for checking energy and momenru of the output electron
    //-----------------------------------------------------------------------

    G4Tubs*            solidSenDetElectMom_L_U; 
    G4LogicalVolume*   logicSenDetElectMom_L_U; 
    G4VPhysicalVolume* physiSenDetElectMom_L_U; 

    G4Tubs*            solidSenDetElectMom_R_U; 
    G4LogicalVolume*   logicSenDetElectMom_R_U; 
    G4VPhysicalVolume* physiSenDetElectMom_R_U; 

    G4Tubs*            solidSenDetElectMom_Centre; 
    G4LogicalVolume*   logicSenDetElectMom_Centre; 
    G4VPhysicalVolume* physiSenDetElectMom_Centre;


    G4LogicalVolume* logicSenDetShower_R;
    G4VPhysicalVolume* physiSenDetShower_R;

    G4LogicalVolume* logicSenDetShower_L;
    G4VPhysicalVolume* physiSenDetShower_L;

    G4LogicalVolume* logicSenDetShower1_L;
    G4VPhysicalVolume* physiSenDetShower1_L;


    //-----------------------------------------------------------------------

    ExN02DetectorMessenger* detectorMessenger;  // pointer to the Messenger

public:
    G4VPhysicalVolume* GetPbWO1Box_R(){return physiPbWO1Box_R;};
    G4VPhysicalVolume* GetPbWO2Box_R(){return physiPbWO2Box_R;};
    G4VPhysicalVolume* GetPbWO3Box_R(){return physiPbWO3Box_R;};
    G4VPhysicalVolume* GetPbWO4Box_R(){return physiPbWO4Box_R;};

    G4VPhysicalVolume* GetPbWO1Box_L(){return physiPbWO1Box_L;};
    G4VPhysicalVolume* GetPbWO2Box_L(){return physiPbWO2Box_L;};
    G4VPhysicalVolume* GetPbWO3Box_L(){return physiPbWO3Box_L;};
    G4VPhysicalVolume* GetPbWO4Box_L(){return physiPbWO4Box_L;};

    G4VPhysicalVolume* GetSenDetShower_R(){return physiSenDetShower_R;};
    G4VPhysicalVolume* GetSenDetShower_L(){return physiSenDetShower_L;};
    G4VPhysicalVolume* GetSenDetShower1_L(){return physiSenDetShower1_L;};

    G4VPhysicalVolume* GetSenDetTube4_R_U_v(){return physiTube4_R_U_v;};
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
