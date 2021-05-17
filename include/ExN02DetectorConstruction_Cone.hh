#ifndef ExN02DetectorConstruction_Cone_h
#define ExN02DetectorConstruction_Cone_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"

class G4Cons;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02DetectorConstruction_Cone : public G4VUserDetectorConstruction
{
public:
    
    ExN02DetectorConstruction_Cone(G4LogicalVolume* logic,
				  G4ThreeVector &v1, //center of the cone part
				  G4double angl,     //angle of rotation in zx plain 
				  G4double inRa,
				  G4double ouRa,
				  G4double inRb,
				  G4double ouRb,
				  G4double leng,
				  G4Material* mat,
				  G4double anglS,
				  G4double anglE,
				  G4String &name1);
    ~ExN02DetectorConstruction_Cone();
    
public:

    G4VPhysicalVolume* Construct();
    G4LogicalVolume* GetlogicVol(){ return logic;}
 
private:

    G4Cons* solid;
    G4LogicalVolume* logic;
    G4PVPlacement* physi;
				
    G4LogicalVolume* logicWorld;
    G4ThreeVector v;  //center of the cilinder part
    G4double angle;
    G4double inR1;
    G4double ouR1;
    G4double inR2;
    G4double ouR2;
    G4double length;
    G4Material* material;
    G4double angleS;
    G4double angleE;
    G4String name;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
