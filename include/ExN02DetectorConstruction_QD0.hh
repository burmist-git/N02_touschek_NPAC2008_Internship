#ifndef ExN02DetectorConstruction_QD0_h
#define ExN02DetectorConstruction_QD0_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"
//00036 #include "G4AffineTransform.hh"
//00037 #include "G4UnitsTable.hh"
//00038 #include "G4LogicalVolume.hh"
//00039 #include "G4VSolid.hh"

class G4Tubs;
class G4Cons;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02DetectorConstruction_QD0 : public G4VUserDetectorConstruction
{
public:
    
    ExN02DetectorConstruction_QD0(G4LogicalVolume* logic,
				  G4ThreeVector &v1, //center of the cone part 
				  G4ThreeVector &v2,  //center of the cilinder part
				  G4double inR1C,
				  G4double ouR1C,
				  G4double inR2C,
				  G4double ouR2C,
				  G4double inR,
				  G4double ouR,
				  G4Material* mat,
				  G4String &name1,
				  G4String &name2);

    ~ExN02DetectorConstruction_QD0();
    
private:
    //QD0 cone part
    G4Cons* solidQD0_Co;
    G4LogicalVolume* logicQD0_Co;
    G4PVPlacement* physiQD0_Co;
    
    //QD0 tube part

    G4Tubs* solidQD0_T;
    G4LogicalVolume* logicQD0_T;
    G4PVPlacement* physiQD0_T;
				
    G4LogicalVolume* logicWorld;
    G4String nameT;
    G4String nameCo;
    G4ThreeVector vCo; //center of the cone part 
    G4ThreeVector vT;  //center of the cilinder part
    G4double inR1Co;
    G4double ouR1Co;
    G4double inR2Co;
    G4double ouR2Co;
    G4Material* material;
    G4double inRT;
    G4double ouRT;

public:
    G4VPhysicalVolume* Construct();
    G4LogicalVolume* GetLogicQD0_T(){return logicQD0_T;}
    G4LogicalVolume* GetLogicQD0_Co(){return logicQD0_Co;}
    void PrintInfo();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
