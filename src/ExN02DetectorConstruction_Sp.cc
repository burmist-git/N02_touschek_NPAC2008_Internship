#include "ExN02DetectorConstruction_Sp.hh"
#include "G4Material.hh"
#include "ExN02MaterialConstruction.hh"
#include "G4Orb.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "DetectorConstant.hh" 
using namespace DetConst;



ExN02DetectorConstruction_Sp::ExN02DetectorConstruction_Sp(G4LogicalVolume* logic,
							   G4ThreeVector &v1, G4String &name1, G4double rSp)
{
    logicWorld = logic;
    v = v1;
    name = name1;
    R = rSp;
}

ExN02DetectorConstruction_Sp::~ExN02DetectorConstruction_Sp(){

}

G4VPhysicalVolume* ExN02DetectorConstruction_Sp::Construct(){

    ExN02MaterialConstruction* materialConst = new ExN02MaterialConstruction();
    G4Material* BP1Mater = materialConst->ConstructSmCo();

    solid = new G4Orb( name, R);
    logic = new G4LogicalVolume(solid,BP1Mater,name,0,0,0);
    physi = new G4PVPlacement(0,           // no rotation
			      v, // at (x,y,z)
			      logic,    // its logical volume
			      name,  // its name
			      logicWorld,  // its mother  volume
			      false,       // no boolean operations
			      0);          // copy number 
    return physi;
}
