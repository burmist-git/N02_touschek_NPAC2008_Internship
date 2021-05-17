#include "ExN02DetectorConstruction_World.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
 
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "ExN02MaterialConstruction.hh"

#include "DetectorConstant.hh" 
using namespace DetConst;

ExN02DetectorConstruction_World::ExN02DetectorConstruction_World(G4Material* mat){
    material = mat;
}

ExN02DetectorConstruction_World::~ExN02DetectorConstruction_World(){

}


G4VPhysicalVolume* ExN02DetectorConstruction_World::Construct()
{
    //------------------------------ 
    // World
    //------------------------------ 
    G4cout<<" ExN02DetectorConstruction_World.cc "<<G4endl;
    G4cout<<" ExN02DetectorConstruction_World::Construct() begin"<<G4endl;

    //ExN02MaterialConstruction* materialConst = new ExN02MaterialConstruction();
    //G4Material* Air = materialConst->ConstructAir();

    //G4Material* vacuum = materialConst->ConstructBeamVacuum();

 
    fWorldLength= 2.2*(length_Tube1/2+length_Tube2+length_Tube3+length_Tube4+length_Tube5)*cm;
    fWorldDX    = 6*(x_Tube5_Co_R_U + length_Tube5_Co/2*sin4_07)*cm;  
    fWorldDY    = 0.8*m;

    G4double HalfWorldLength = 0.5*fWorldLength;  
    G4double HalfWorldDX = 0.5*fWorldDX;
    G4double HalfWorldDY = 0.5*fWorldDY;

    solidWorld= new G4Box("world",HalfWorldDX,HalfWorldDY,HalfWorldLength);
    logicWorld= new G4LogicalVolume( solidWorld, material, "World", 0, 0, 0);
    // 
    physiWorld = new G4PVPlacement(0,               // no rotation
				   G4ThreeVector(), // at (0,0,0)
				   logicWorld,      // its logical volume
				   "World",         // its name
				   0,               // its mother  volume
				   false,           // no boolean operations
				   0);              // copy number    

    G4cout<<" ExN02DetectorConstruction_World::Construct() end"<<G4endl;
    return physiWorld;
}
