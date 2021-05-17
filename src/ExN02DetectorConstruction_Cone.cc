#include "ExN02DetectorConstruction_Cone.hh"
#include "G4Material.hh"
#include "ExN02MaterialConstruction.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "DetectorConstant.hh" 

using namespace DetConst;

ExN02DetectorConstruction_Cone::ExN02DetectorConstruction_Cone(G4LogicalVolume* logic,
				  G4ThreeVector &v1, //center of the part
				  G4double angl,     //angle of rotation in zx plain 
				  G4double inRa,
				  G4double ouRa,
				  G4double inRb,
				  G4double ouRb,
				  G4double leng,
				  G4Material* mat,
				  G4double anglS,
				  G4double anglE,
				  G4String &name1)
    : solid(0), logic(0), physi(0) 
{
    logicWorld = logic;
    v = v1;
    angle = angl;
    inR1 = inRa;
    ouR1 = ouRa;
    inR2 = inRb;
    ouR2 = ouRb;
    length = leng;
    material = mat;
    angleS = anglS;
    angleE = anglE;
    name = name1;
}

ExN02DetectorConstruction_Cone::~ExN02DetectorConstruction_Cone(){

}

G4VPhysicalVolume* ExN02DetectorConstruction_Cone::Construct(){
    solid = new G4Cons(name,
		       inR1,
		       ouR1,
		       inR2,
		       ouR2,
		       length/2,
		       angleS,
		       angleE);    
    G4RotationMatrix *pRot = new G4RotationMatrix();// Rotates X and Z axes only
    pRot->rotateY(angle);                           // Rotates 4.07 degrees
    logic = new G4LogicalVolume(solid, material,name,0,0,0);
    physi = new G4PVPlacement(pRot,        // rotation
			      v,           // at (x,y,z)
			      logic,       // its logical volume
			      name,        // its name
			      logicWorld,  // its mother  volume
			      false,       // no boolean operations
			      0);          // copy number 
    
    return physi;
}
