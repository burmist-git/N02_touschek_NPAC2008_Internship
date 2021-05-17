#include "ExN02DetectorConstruction_QD0.hh"
#include "G4Material.hh"
#include "ExN02MaterialConstruction.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "ExN02MaterialConstruction.hh"
#include "DetectorConstant.hh" 
#include "G4VisAttributes.hh"

using namespace DetConst;

ExN02DetectorConstruction_QD0::ExN02DetectorConstruction_QD0(G4LogicalVolume* logic,
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
			      G4String &name2){
    logicWorld = logic;
    vCo = v1;
    vT = v2;
    inR1Co = inR1C;
    ouR1Co = ouR1C;
    inR2Co = inR2C;
    ouR2Co = ouR2C;
    inRT = inR;
    ouRT = ouR;
    material = mat;
    nameCo = name1;
    nameT = name2;
}

ExN02DetectorConstruction_QD0::~ExN02DetectorConstruction_QD0(){

}

G4VPhysicalVolume* ExN02DetectorConstruction_QD0::Construct(){
   
    //QD0_Co
    solidQD0_Co = new G4Cons(nameCo,
			     inR1Co,
			     ouR1Co,
			     inR2Co,
			     ouR2Co,
			     length_QD0_Co/2*cm,
			     0,
			     360*deg);    
    logicQD0_Co = new G4LogicalVolume(solidQD0_Co, material,nameCo,0,0,0);
    physiQD0_Co = new G4PVPlacement(0,                 //no rotation
				    vCo,  // at (x,y,z)
				    logicQD0_Co,     // its logical volume
				    nameCo,        // its name
				    logicWorld,      // its mother  volume
				    false,           // no boolean operations
				    0);              // copy number 

  
    //QD0_T
    solidQD0_T = new G4Tubs(nameT,
			    inRT,
			    ouRT,
			    length_QD0_T/2*cm,
			    0,
			    360*deg);    
    logicQD0_T = new G4LogicalVolume(solidQD0_T, material,nameT,0,0,0);
    physiQD0_T = new G4PVPlacement(0,           //no rotation
				   vT,          // at (x,y,z)
				   logicQD0_T,  // its logical volume
				   nameT,     // its name
				   logicWorld,  // its mother  volume
				   false,       // no boolean operations
				   0);          // copy number 

    G4VisAttributes* VisAttQD0 = new G4VisAttributes(G4Colour(1.0,0.0,0.0));
    logicQD0_T->SetVisAttributes(VisAttQD0);
    logicQD0_Co->SetVisAttributes(VisAttQD0);

    return physiQD0_T;
}

void ExN02DetectorConstruction_QD0::PrintInfo(){
    G4cout<<G4endl;
    G4cout<<"----------ExN02DetectorConstruction_QD0.cc-----------"<<G4endl;
    G4cout<<"------ExN02DetectorConstruction_QD0::PrintInfo()-----"<<G4endl;
    G4cout<<" Cone :"<<G4endl;
    G4cout<<"      Volume name : "<<nameCo<<G4endl;
    G4cout<<"      x = "<<vCo.getX()<<" mm"<<G4endl;
    G4cout<<"      y = "<<vCo.getY()<<" mm"<<G4endl;
    G4cout<<"      z = "<<vCo.getZ()<<" mm"<<G4endl;
    G4cout<<"      inner radius1 = "<<inR1Co<<" mm"<<G4endl;
    G4cout<<"      outer radius1 = "<<ouR1Co<<" mm"<<G4endl;
    G4cout<<"      inner radius2 = "<<inR2Co<<" mm"<<G4endl;
    G4cout<<"      outer radius2 = "<<ouR2Co<<" mm"<<G4endl;
    G4cout<<"      material "<<material<<G4endl;
    G4cout<<" Tube :"<<G4endl;
    G4cout<<"      Volume name : "<<nameT<<G4endl;
    G4cout<<"      x = "<<vT.getX()<<" mm"<<G4endl;
    G4cout<<"      y = "<<vT.getY()<<" mm"<<G4endl;
    G4cout<<"      z = "<<vT.getZ()<<" mm"<<G4endl;
    G4cout<<"      inner radius1 = "<<inRT<<" mm"<<G4endl;
    G4cout<<"      outer radius1 = "<<ouRT<<" mm"<<G4endl;
    G4cout<<"      material "<<material<<G4endl;
    G4cout<<"-----------------------------------------------------"<<G4endl;
    G4cout<<G4endl;
}
