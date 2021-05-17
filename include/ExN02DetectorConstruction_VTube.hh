//
// ***********************************
// *  V-like tube consiste of 4 part *
// * part 1:                         *  
// *        two boxes                *
// *        two half cilinder        *
// * part 2:                         *
// *        one big trapezoid        *
// * part 3:                         *
// *        one litle trapezoid      *
// * part 4:                         *
// *        two tubes                *
// ***********************************
//
//....oooOO0OOooo........oooOO0OOooo........
//....oooOO0OOooo........oooOO0OOooo........

#ifndef ExN02DetectorConstruction_VTube_h
#define ExN02DetectorConstruction_VTube_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"
#include <iostream>

class G4Tubs;
class G4Trd;
class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02DetectorConstruction_VTube  : public G4VUserDetectorConstruction
{
public:
    
    ExN02DetectorConstruction_VTube(G4LogicalVolume* logic, G4Material* mat, G4Material* mat_v);
    ~ExN02DetectorConstruction_VTube();
    
private:
   
    G4LogicalVolume*   logicWorld;
    G4Material *mat;
    G4Material *mat_v;

    //part 1 
       //upper box made of aluminium
       G4Box* solid_P1_B_U;
       G4LogicalVolume* logic_P1_B_U;
       G4PVPlacement* physi_P1_B_U;
       //bottom box made of aluminium
       G4Box* solid_P1_B_D;
       G4LogicalVolume* logic_P1_B_D;
       G4PVPlacement* physi_P1_B_D;
       //half tube left made of aluminium
       G4Tubs* solid_P1_T_R;
       G4LogicalVolume* logic_P1_T_R;
       G4PVPlacement* physi_P1_T_R;
       //half tube right made of aluminium
       G4Tubs* solid_P1_T_L;
       G4LogicalVolume* logic_P1_T_L;
       G4PVPlacement* physi_P1_T_L;
       //box full of vacuum
       G4Box* solid_P1_B_v;
       G4LogicalVolume* logic_P1_B_v;
       G4PVPlacement* physi_P1_B_v;
       //half tube left full of vacuum
       G4Tubs* solid_P1_T_R_v;
       G4LogicalVolume* logic_P1_T_R_v;
       G4PVPlacement* physi_P1_T_R_v;
       //half tube right full of vacuum
       G4Tubs* solid_P1_T_L_v;
       G4LogicalVolume* logic_P1_T_L_v;
       G4PVPlacement* physi_P1_T_L_v;

    //part 2
       //one big trapezoid made of aluminium
       G4Trd *solid_P2_TR;
       G4LogicalVolume* logic_P2_TR;
       G4PVPlacement* physi_P2_TR;
       //tube upper full of vacuum
       G4Tubs* solid_P2_T_U_v;
       G4LogicalVolume* logic_P2_T_U_v;
       G4PVPlacement* physi_P2_T_U_v;
       //half tube right full of vacuum
       G4Tubs* solid_P2_T_D_v;
       G4LogicalVolume* logic_P2_T_D_v;
       G4PVPlacement* physi_P2_T_D_v;

    //part 3
       //one litle trapezoid made of aluminium
       G4Trd *solid_P3_TR;
       G4LogicalVolume* logic_P3_TR;
       G4PVPlacement* physi_P3_TR;

    //part 4
       //tube upper made of aluminium
       G4Tubs* solid_P4_U;
       G4LogicalVolume* logic_P4_U;
       G4PVPlacement* physi_P4_U;
       //tube bottom made of aluminium
       G4Tubs* solid_P4_D;
       G4LogicalVolume* logic_P4_D;
       G4PVPlacement* physi_P4_D;
       //tube upper full of vacuum
       G4Tubs* solid_P4_U_v;
       G4LogicalVolume* logic_P4_U_v;
       G4PVPlacement* physi_P4_U_v;
       //tube bottom full of vacuum
       G4Tubs* solid_P4_D_v;
       G4LogicalVolume* logic_P4_D_v;
       G4PVPlacement* physi_P4_D_v;


public:
   
    G4VPhysicalVolume* Construct();
    void ConstructVlikeTube(const char *flag, G4Material *mat, G4Material *mat_v);
    void PrintInfo();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
