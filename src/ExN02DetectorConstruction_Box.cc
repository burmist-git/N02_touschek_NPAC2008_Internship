#include "ExN02DetectorConstruction_Box.hh"
#include "G4Material.hh"
#include "ExN02MaterialConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "DetectorConstant.hh" 
using namespace DetConst;

ExN02DetectorConstruction_Box::ExN02DetectorConstruction_Box(G4LogicalVolume* logic,
				  G4ThreeVector &v1, //center of the cone part
				  G4double angl,     //angle of rotation in zx plain 
				  G4double lx,
				  G4double ly,
				  G4double lz,
				  G4Material* mat,
 				  G4String &name1)
    : solid(0), logic(0), physi(0) 
{
    logicWorld = logic;
    v = v1;
    angle = angl;
    lengthX = lx;
    lengthY= ly;
    lengthZ = lz;
    material = mat;
    name = name1;
}

ExN02DetectorConstruction_Box::~ExN02DetectorConstruction_Box(){

}

G4VPhysicalVolume* ExN02DetectorConstruction_Box::Construct(){

    solid = new G4Box(name, lengthX/2, lengthY/2, lengthZ/2);
    logic = new G4LogicalVolume( solid, material, name, 0, 0, 0);
    G4RotationMatrix *pRot = new G4RotationMatrix();// Rotates X and Z axes only
    pRot->rotateY(angle);                           // Rotates 4.07 degrees
    physi = new G4PVPlacement(pRot,          // no rotation
			      v,             // at (0,0,0)
			      logic,         // its logical volume
			      name,          // its name
			      logicWorld,    // its mother  volume
			      false,         // no boolean operations
			      0);            // copy number      
    return physi;
}

void ExN02DetectorConstruction_Box::PrintInfo(){
    G4cout<<G4endl;
    G4cout<<"----------ExN02DetectorConstruction_Box.cc-----------"<<G4endl;
    G4cout<<"-----ExN02DetectorConstruction_Tube::PrintInfo()-----"<<G4endl;
    G4cout<<" Box :"<<G4endl;
    G4cout<<"      Volume name : "<<name<<G4endl;
    G4cout<<"      x = "<<v.getX()<<" mm"<<G4endl;
    G4cout<<"      y = "<<v.getY()<<" mm"<<G4endl;
    G4cout<<"      z = "<<v.getZ()<<" mm"<<G4endl;
    G4cout<<"      length X = "<<lengthX<<" mm"<<G4endl;
    G4cout<<"      length Y = "<<lengthY<<" mm"<<G4endl;
    G4cout<<"      length Z = "<<lengthZ<<" mm"<<G4endl;
    G4cout<<"      material "<<material<<G4endl;
    G4cout<<"-----------------------------------------------------"<<G4endl;
    G4cout<<G4endl;
}
