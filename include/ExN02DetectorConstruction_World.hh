
#ifndef ExN02DetectorConstruction_World_h
#define ExN02DetectorConstruction_World_h 1


#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"

class G4Box;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02DetectorConstruction_World : public G4VUserDetectorConstruction
{
public:
    
    ExN02DetectorConstruction_World(G4Material* mat);
    ~ExN02DetectorConstruction_World();
    
public:
    
    G4VPhysicalVolume* Construct();
    G4LogicalVolume*   GetlogicVol(){ return logicWorld;}// pointer to the logical envelope
    G4VPhysicalVolume*   GetPhysicalVol(){ return physiWorld;}// pointer to the logical envelope
private:

    G4double fWorldLength;
    G4double fWorldDX;  
    G4double fWorldDY;    

    G4Box*             solidWorld;    // pointer to the solid envelope 
    G4LogicalVolume*   logicWorld;    // pointer to the logical envelope
    G4VPhysicalVolume* physiWorld;    // pointer to the physical envelope

    G4Material* material;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
