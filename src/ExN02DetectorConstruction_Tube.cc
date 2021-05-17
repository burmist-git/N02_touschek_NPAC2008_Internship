#include "ExN02DetectorConstruction_Tube.hh"
#include "G4Material.hh"
#include "ExN02MaterialConstruction.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "DetectorConstant.hh" 
using namespace DetConst;

ExN02DetectorConstruction_Tube::ExN02DetectorConstruction_Tube(G4LogicalVolume* logic,
				  G4ThreeVector &v1, //center of the cone part
				  G4double angl,     //angle of rotation in zx plain 
				  G4double inR,
				  G4double ouR,
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
    inRad = inR;
    ouRad = ouR;
    length = leng;
    material = mat;
    angleS = anglS;
    angleE = anglE;
    name = name1;
}

ExN02DetectorConstruction_Tube::~ExN02DetectorConstruction_Tube(){

}

G4VPhysicalVolume* ExN02DetectorConstruction_Tube::Construct(){

    solid = new G4Tubs(name,
		       inRad,
		       ouRad,
		       length/2,
		       angleS,
		       angleE);    
    G4RotationMatrix *pRot = new G4RotationMatrix();// Rotates X and Z axes only
    pRot->rotateY(angle);                           // Rotates 4.07 degrees
    logic = new G4LogicalVolume(solid,material,name,0,0,0);
    physi = new G4PVPlacement(pRot,             // rotation
			      v,                // at (x,y,z)
			      logic,            // its logical volume
			      name,             // its name
			      logicWorld,       // its mother  volume
			      false,            // no boolean operations
			      0);               // copy number 
  
    return physi;
}

void ExN02DetectorConstruction_Tube::PrintInfo(){
    G4cout<<G4endl;
    G4cout<<"----------ExN02DetectorConstruction_Tube.cc----------"<<G4endl;
    G4cout<<"-----ExN02DetectorConstruction_Tube::PrintInfo()-----"<<G4endl;
    G4cout<<" Tube :"<<G4endl;
    G4cout<<"      Volume name : "<<name<<G4endl;
    G4cout<<"      x = "<<v.getX()<<" mm"<<G4endl;
    G4cout<<"      y = "<<v.getY()<<" mm"<<G4endl;
    G4cout<<"      z = "<<v.getZ()<<" mm"<<G4endl;
    G4cout<<"      inner radius = "<<inRad<<" mm"<<G4endl;
    G4cout<<"      outer radius = "<<ouRad<<" mm"<<G4endl;
    G4cout<<"      material "<<material<<G4endl;
    G4cout<<"-----------------------------------------------------"<<G4endl;
    G4cout<<G4endl;
}
