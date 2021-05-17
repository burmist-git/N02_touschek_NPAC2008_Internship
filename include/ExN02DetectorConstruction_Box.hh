#ifndef ExN02DetectorConstruction_Box_h
#define ExN02DetectorConstruction_Box_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02DetectorConstruction_Box : public G4VUserDetectorConstruction
{
public:
    
    ExN02DetectorConstruction_Box(G4LogicalVolume* logic,
				  G4ThreeVector &v1, //center of the cone part
				  G4double angl,     //angle of rotation in zx plain 
				  G4double lx,
				  G4double ly,
				  G4double lz,
				  G4Material* mat,
				  G4String &name1);
    ~ExN02DetectorConstruction_Box();
   
private:
    G4Box* solid;
    G4LogicalVolume* logic;
    G4PVPlacement* physi; 

    G4LogicalVolume* logicWorld;
    G4ThreeVector v;  //center of the cilinder part
    G4double angle;
    G4double lengthX;
    G4double lengthY;
    G4double lengthZ;
    G4Material* material;
    G4String name;

public:
 				
    G4VPhysicalVolume* Construct();
    G4LogicalVolume* GetlogicVol(){ return logic;}
    void PrintInfo();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
