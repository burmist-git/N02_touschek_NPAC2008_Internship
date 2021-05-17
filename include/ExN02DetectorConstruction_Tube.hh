#ifndef ExN02DetectorConstruction_Tube_h
#define ExN02DetectorConstruction_Tube_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"

class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02DetectorConstruction_Tube : public G4VUserDetectorConstruction
{
public:
    
    ExN02DetectorConstruction_Tube(G4LogicalVolume* logic,
				  G4ThreeVector &v1, //center of the cone part
				  G4double angl,     //angle of rotation in zx plain 
				  G4double inR,
				  G4double ouR,
				  G4double leng,
				  G4Material* mat,
				  G4double anglS,
				  G4double anglE,
				  G4String &name1);
    ~ExN02DetectorConstruction_Tube();
   
private:

    G4Tubs* solid;
    G4LogicalVolume* logic;
    G4PVPlacement* physi;
 
    G4LogicalVolume* logicWorld;
    G4ThreeVector v;  //center of the cilinder part
    G4double angle;
    G4double inRad;
    G4double ouRad;
    G4double length;
    G4Material* material;
    G4double angleS;
    G4double angleE;
    G4String name;

public:
 
				
    G4VPhysicalVolume* Construct();
    G4LogicalVolume* GetlogicVol(){ return logic;}
    void PrintInfo();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
