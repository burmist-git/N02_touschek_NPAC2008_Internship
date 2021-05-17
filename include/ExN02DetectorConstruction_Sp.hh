#ifndef ExN02DetectorConstruction_Sp_h
#define ExN02DetectorConstruction_Sp_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"

class G4Orb;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02DetectorConstruction_Sp : public G4VUserDetectorConstruction
{
public:
    
    ExN02DetectorConstruction_Sp(G4LogicalVolume* logic,G4ThreeVector &v1, G4String &name1, G4double rSp);	 
    ~ExN02DetectorConstruction_Sp();

private:

    G4Orb* solid;
    G4LogicalVolume* logic;
    G4PVPlacement* physi;
				
    G4LogicalVolume* logicWorld;
    G4ThreeVector v;  //center of the cilinder part
    G4String name;
    G4double R;
    
public:

    G4VPhysicalVolume* Construct();
    G4LogicalVolume* GetlogicVol(){ return logic;}
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
