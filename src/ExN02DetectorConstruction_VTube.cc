#include "ExN02DetectorConstruction_VTube.hh"
#include "G4Material.hh"
#include "ExN02MaterialConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "ExN02MaterialConstruction.hh"
#include "DetectorConstant.hh" 
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include <iostream>
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"

using namespace DetConst;



ExN02DetectorConstruction_VTube::ExN02DetectorConstruction_VTube(G4LogicalVolume* logic, G4Material* mat,G4Material* mat_v)
    :logicWorld(logic), mat(mat), mat_v(mat_v)
{


}


ExN02DetectorConstruction_VTube::~ExN02DetectorConstruction_VTube(){

}


void ExN02DetectorConstruction_VTube::ConstructVlikeTube(const char *flag,G4Material *mat, G4Material *mat_v){

    //part 1:
    G4ThreeVector pos_P1_B_U;
    G4ThreeVector pos_P1_B_D;

    G4ThreeVector pos_P1_T_R;
    G4ThreeVector pos_P1_T_L;

    G4ThreeVector pos_P1_B_R;
    G4ThreeVector pos_P1_B_v;

    G4ThreeVector pos_P2_TR;
    G4ThreeVector pos_P3_TR;

    G4ThreeVector pos_P4_U;
    G4ThreeVector pos_P4_D;

    G4double dx1_par2;
    G4double dx2_par2;

    G4double dx1_par3;
    G4double dx2_par3;

    G4RotationMatrix *pRotU = new G4RotationMatrix();// Rotates X and Z axes
    G4RotationMatrix *pRotD = new G4RotationMatrix();// Rotates X and Z axes
    G4double angle4_07 = 4.07;

    G4ThreeVector pos_P2_T_U; 
    G4RotationMatrix *pRot_P2_U = new G4RotationMatrix();

    G4ThreeVector pos_P2_T_D; 
    G4RotationMatrix *pRot_P2_D = new G4RotationMatrix();

    G4ThreeVector zTrans;

    if (flag == "right"){
	pos_P1_B_U = G4ThreeVector(  x_Tube3_par1_B*cm,   y_Tube3_par1_B*cm,   z_Tube3_par1_B*cm);
	pos_P1_B_D = G4ThreeVector(  x_Tube3_par1_B*cm,  -y_Tube3_par1_B*cm,   z_Tube3_par1_B*cm);
	pos_P1_T_R = G4ThreeVector(  x_Tube3_par1_T*cm,   y_Tube3_par1_T*cm,   z_Tube3_par1_T*cm);
	pos_P1_T_L = G4ThreeVector( -x_Tube3_par1_T*cm,   y_Tube3_par1_T*cm,   z_Tube3_par1_T*cm);
	pos_P1_B_R = G4ThreeVector(x_Tube3_par1_B_v*cm, y_Tube3_par1_B_v*cm, z_Tube3_par1_B_v*cm);
	pos_P1_B_v = G4ThreeVector(x_Tube3_par1_B_v*cm, y_Tube3_par1_B_v*cm, z_Tube3_par1_B_v*cm);
	pos_P2_TR = G4ThreeVector( x_Tube3_par2_TR*cm, y_Tube3_par2_TR*cm, z_Tube3_par2_TR*cm);
	pos_P3_TR = G4ThreeVector( x_Tube3_par3_TR*cm, y_Tube3_par3_TR*cm, z_Tube3_par3_TR*cm);
	pos_P4_U =  G4ThreeVector( x_Tube3_par4*cm, y_Tube3_par4*cm, z_Tube3_par4*cm);
	pos_P4_D =  G4ThreeVector( -x_Tube3_par4*cm, y_Tube3_par4*cm, z_Tube3_par4*cm);
	pos_P2_T_U = G4ThreeVector( x_Tube3_par2_T_v*cm, y_Tube3_par2_T_v*cm, z_Tube3_par2_T_v*cm);
	pos_P2_T_D = G4ThreeVector( -x_Tube3_par2_T_v*cm, y_Tube3_par2_T_v*cm, z_Tube3_par2_T_v*cm);
//	pos_P2_T_U = G4ThreeVector( 0.0*cm, 0.0*cm, 0.0*cm);
//	pos_P2_T_D = G4ThreeVector( -x*cm, y_Tube3_par2_T_v*cm, 0.0*cm);

	pRotU->rotateY(-angle4_07*deg);                          
	pRotD->rotateY(angle4_07*deg);                          

	//normal --- G1
	pRot_P2_U->rotateY(-angle_Tube3_par2*deg);
	pRot_P2_D->rotateY(angle_Tube3_par2*deg);

	//G2
	//pRot_P2_U->rotateY(-(angle_Tube3_par2*0.86)*deg);
	//pRot_P2_D->rotateY((angle_Tube3_par2*0.86)*deg);

	//G3
	//pRot_P2_U->rotateY(-(angle_Tube3_par2*1.14)*deg);
	//pRot_P2_D->rotateY((angle_Tube3_par2*1.14)*deg);

	dx1_par2 = dx1_Tube3_par2_TR/2.*cm;
	dx2_par2 = dx2_Tube3_par2_TR/2.*cm;
	dx1_par3 =  dx1_Tube3_par3_TR/2*cm;
	dx2_par3 =  (dx2_Tube3_par3_TR/2 + 0.01)*cm;

	zTrans = G4ThreeVector(0, 0, dz_Tube3_par2_TR/2.*cm+dz_Tube3_par3_TR/2.*cm);

    }
    else if(flag == "left"){
	pos_P1_B_U = G4ThreeVector( x_Tube3_par1_B*cm, y_Tube3_par1_B*cm, -z_Tube3_par1_B*cm);
	pos_P1_B_D = G4ThreeVector( x_Tube3_par1_B*cm,-y_Tube3_par1_B*cm, -z_Tube3_par1_B*cm);
	pos_P1_T_R = G4ThreeVector( x_Tube3_par1_T*cm, y_Tube3_par1_T*cm, -z_Tube3_par1_T*cm);
	pos_P1_T_L = G4ThreeVector(-x_Tube3_par1_T*cm, y_Tube3_par1_T*cm, -z_Tube3_par1_T*cm);
	pos_P1_B_R = G4ThreeVector(x_Tube3_par1_B_v*cm, y_Tube3_par1_B_v*cm,-z_Tube3_par1_B_v*cm);
	pos_P1_B_v = G4ThreeVector(x_Tube3_par1_B_v*cm, y_Tube3_par1_B_v*cm,-z_Tube3_par1_B_v*cm);
	//pos_P2_TR = G4ThreeVector( x_Tube3_par2_TR*cm, y_Tube3_par2_TR*cm,(-z_Tube3_par2_TR + (-z_S31-54.38-1.25) )*cm);
	pos_P2_TR = G4ThreeVector( x_Tube3_par2_TR*cm, y_Tube3_par2_TR*cm,-z_Tube3_par2_TR*cm);
	pos_P3_TR = G4ThreeVector( x_Tube3_par3_TR*cm, y_Tube3_par3_TR*cm,-z_Tube3_par3_TR*cm);
	pos_P4_U =  G4ThreeVector( x_Tube3_par4*cm, y_Tube3_par4*cm, -z_Tube3_par4*cm);
	pos_P4_D =  G4ThreeVector( -x_Tube3_par4*cm, y_Tube3_par4*cm, -z_Tube3_par4*cm);
	pos_P2_T_U = G4ThreeVector( x_Tube3_par2_T_v*cm, y_Tube3_par2_T_v*cm, -z_Tube3_par2_T_v*cm);
	pos_P2_T_D = G4ThreeVector( -x_Tube3_par2_T_v*cm, y_Tube3_par2_T_v*cm, -z_Tube3_par2_T_v*cm);
//	pos_P2_T_U = G4ThreeVector( 0.0*cm, 0.0*cm, 0.0*cm);
//	pos_P2_T_D = G4ThreeVector( -x_Tube3_par2_T_v*cm, y_Tube3_par2_T_v*cm, 0.0*cm);

	pRotU->rotateY(angle4_07*deg);                          
	pRotD->rotateY(-angle4_07*deg);                          
	pRot_P2_U->rotateY(angle_Tube3_par2*deg);
	pRot_P2_D->rotateY(-angle_Tube3_par2*deg);

	dx2_par2 = dx1_Tube3_par2_TR/2.*cm;
	dx1_par2 = dx2_Tube3_par2_TR/2.*cm;
	dx2_par3 =  dx1_Tube3_par3_TR/2*cm;
	dx1_par3 =  (dx2_Tube3_par3_TR/2 + 0.01)*cm;
	zTrans = G4ThreeVector(0, 0, -dz_Tube3_par2_TR/2.*cm-dz_Tube3_par3_TR/2.*cm);
    }
 
    //part 1 box upper full of aluminium 
    solid_P1_B_U = new G4Box("Tube3_P1_B_U",
			     x_length_Tube3_par1_B/2*cm,
			     y_length_Tube3_par1_B/2*cm,
			     z_length_Tube3_par1_B/2*cm);    
    logic_P1_B_U = new G4LogicalVolume(solid_P1_B_U, mat,"Tube3_P1_B_U",0,0,0);
    physi_P1_B_U = new G4PVPlacement(0,             //no rotation
				    pos_P1_B_U,     // at (x,y,z)
				    logic_P1_B_U,   // its logical volume
				    "Tube3_P1_B_U", // its name
				    logicWorld,     // its mother  volume
				    false,          // no boolean operations
				    0);             // copy number 

    //part 1 box bottom full of aluminium
    solid_P1_B_D = new G4Box("Tube3_P1_B_D",
			     x_length_Tube3_par1_B/2*cm,
			     y_length_Tube3_par1_B/2*cm,
			     z_length_Tube3_par1_B/2*cm);    
    logic_P1_B_D = new G4LogicalVolume(solid_P1_B_D, mat,"Tube3_P1_B_D",0,0,0);
    physi_P1_B_D = new G4PVPlacement(0,             //no rotation
				    pos_P1_B_D,     // at (x,y,z)
				    logic_P1_B_D,   // its logical volume
				    "Tube3_P1_B_D", // its name
				    logicWorld,     // its mother  volume
				    false,          // no boolean operations
				    0);             // copy number 

    //part1 half tube righr full of aluminium
    solid_P1_T_R = new G4Tubs("Tube3_P1_T_R",
			     r_min_Tube3_par1_T*cm,
			     r_max_Tube3_par1_T*cm,
			     length_Tube3_par1_T/2*cm,
	                     270.0*deg,
	                     180.0*deg);    
    logic_P1_T_R = new G4LogicalVolume(solid_P1_T_R, mat,"Tube3_P1_T_R",0,0,0);
    physi_P1_T_R = new G4PVPlacement(0,             //no rotation
				    pos_P1_T_R,     // at (x,y,z)
				    logic_P1_T_R,   // its logical volume
				    "Tube3_P1_T_R", // its name
				    logicWorld,     // its mother  volume
				    false,          // no boolean operations
				    0);             // copy number    

    //part1 half tube left full of aluminium
    solid_P1_T_L = new G4Tubs("Tube3_P1_T_L",
			     r_min_Tube3_par1_T*cm,
			     r_max_Tube3_par1_T*cm,
			     length_Tube3_par1_T/2*cm,
	                     90.0*deg,
	                     180.0*deg);    
    logic_P1_T_L = new G4LogicalVolume(solid_P1_T_L, mat,"Tube3_P1_T_L",0,0,0);
    physi_P1_T_L = new G4PVPlacement(0,             //no rotation
				    pos_P1_T_L,     // at (x,y,z)
				    logic_P1_T_L,   // its logical volume
				    "Tube3_P1_T_L", // its name
				    logicWorld,     // its mother  volume
				    false,          // no boolean operations
				    0);             // copy number    

    //part 1 box full of vacuum
    solid_P1_B_v = new G4Box("Tube3_P1_B_v",
			     x_length_Tube3_par1_B_v/2*cm,
			     y_length_Tube3_par1_B_v/2*cm,
			     z_length_Tube3_par1_B_v/2*cm);    
    logic_P1_B_v = new G4LogicalVolume(solid_P1_B_v, mat_v,"Tube3_P1_B_v",0,0,0);
    physi_P1_B_v = new G4PVPlacement(0,             //no rotation
				    pos_P1_B_v,     // at (x,y,z)
				    logic_P1_B_v,   // its logical volume
				    "Tube3_P1_B_v", // its name
				    logicWorld,     // its mother  volume
				    false,          // no boolean operations
				    0);             // copy number 

    //part1 half tube righr full of vacuum
    solid_P1_T_R_v = new G4Tubs("Tube3_P1_T_R_v",
				0.0*cm,
				r_min_Tube3_par1_T*cm,
				length_Tube3_par1_T/2*cm,
				270.0*deg,
				180.0*deg);    
    logic_P1_T_R_v = new G4LogicalVolume(solid_P1_T_R_v, mat_v,"Tube3_P1_T_R_v",0,0,0);
    physi_P1_T_R_v = new G4PVPlacement(0,             //no rotation
				       pos_P1_T_R,     // at (x,y,z)
				       logic_P1_T_R_v,   // its logical volume
				       "Tube3_P1_T_R_v", // its name
				       logicWorld,     // its mother  volume
				       false,          // no boolean operations
				       0);             // copy number    

    //part1 half tube left full of aluminium
    solid_P1_T_L_v = new G4Tubs("Tube3_P1_T_L_v",
				0.0*cm,
				r_min_Tube3_par1_T*cm,
				length_Tube3_par1_T/2*cm,
				90.0*deg,
				180.0*deg);    
    logic_P1_T_L_v = new G4LogicalVolume(solid_P1_T_L_v, mat_v,"Tube3_P1_T_L_v",0,0,0);
    physi_P1_T_L_v = new G4PVPlacement(0,                //no rotation
				       pos_P1_T_L,       // at (x,y,z)
				       logic_P1_T_L_v,   // its logical volume
				       "Tube3_P1_T_L_v", // its name
				       logicWorld,       // its mother  volume
				       false,            // no boolean operations
				       0);               // copy number


    //part 2 one big trapezoid made of aluminium
    solid_P2_TR  = new G4Trd("Tube3_P2_TR",
			    dx1_par2,
			    dx2_par2,
			    dy1_Tube3_par2_TR/2*cm,
			    dy1_Tube3_par2_TR/2*cm,
			    dz_Tube3_par2_TR/2.*cm);
    // part 3 one litle trapezoid made of aluminium
    solid_P3_TR = new G4Trd("Tube3_P3_TR",
			    dx1_par3,
			    dx2_par3,
			    dy1_Tube3_par3_TR/2*cm,
			    dy1_Tube3_par3_TR/2*cm,
			    dz_Tube3_par3_TR/2.*cm);

    G4UnionSolid* solid_P2_P3_TR  =
	new G4UnionSolid("Tube3_P2_P3_TR", solid_P2_TR, solid_P3_TR,0,zTrans);

    //part 2 tube full of vacuum
    G4Tubs *solid_P2_v = new G4Tubs("Tube3_P2_T_U_v",
				0.0*cm,
				r_max_Tube3_par2_T*cm,
				length_Tube3_par2_T_v/2*cm,
				0.0*deg,
				360.0*deg);    

    G4ThreeVector zTrans2(x_Tube3_par2_T_v*cm, 0, z_Tube3_par2_T_v*cm - z_Tube3_par2_TR*cm);
    G4ThreeVector zTrans3(-x_Tube3_par2_T_v*cm, 0, z_Tube3_par2_T_v*cm - z_Tube3_par2_TR*cm);

    G4SubtractionSolid* subtraction1 =
	new G4SubtractionSolid("Box-Cylinder1", solid_P2_P3_TR, solid_P2_v,pRot_P2_U,zTrans2);

    G4SubtractionSolid* subtraction2 =
	new G4SubtractionSolid("Box-Cylinder2", subtraction1, solid_P2_v,pRot_P2_D,zTrans3);


    logic_P2_TR = new G4LogicalVolume(subtraction2, mat,"Tube3_P2_TR",0,0,0);
    physi_P2_TR = new G4PVPlacement(0,              //no rotation
				    pos_P2_TR,      // at (x,y,z)
				    logic_P2_TR,    // its logical volume
				    "Tube3_P2_TR",  // its name
				    logicWorld,     // its mother  volume
				    true,          // no boolean operations
				    0);             // copy number
    

/*    
    //part 2 one big trapezoid made of aluminium
    solid_P2_TR = new G4Trd("Tube3_P2_TR",
			    dx1_par2,
			    dx2_par2,
			    dy1_Tube3_par2_TR/2*cm,
			    dy1_Tube3_par2_TR/2*cm,
			    dz_Tube3_par2_TR/2.*cm);
    logic_P2_TR = new G4LogicalVolume(solid_P2_TR, mat,"Tube3_P2_TR",0,0,0);
    physi_P2_TR = new G4PVPlacement(0,              //no rotation
				    pos_P2_TR,      // at (x,y,z)
				    logic_P2_TR,    // its logical volume
				    "Tube3_P2_TR",  // its name
				    logicWorld,     // its mother  volume
				    false,          // no boolean operations
				    0);             // copy number

*/
    //part 2 tube full of vacuum
    solid_P2_T_U_v = new G4Tubs("Tube3_P2_T_U_v",
				0.0*cm,
				r_max_Tube3_par2_T*cm,
				length_Tube3_par2_T_v/2*cm,
				0.0*deg,
				360.0*deg);    
    logic_P2_T_U_v = new G4LogicalVolume(solid_P2_T_U_v, mat_v,"Tube3_P2_T_U_v",0,0,0);
    physi_P2_T_U_v = new G4PVPlacement(pRot_P2_U,         //no rotation
				       pos_P2_T_U,        // at (x,y,z)
				       logic_P2_T_U_v,    // its logical volume
				       "Tube3_P2_T_U_v",  // its name
				       logicWorld,        // its mother  volume
				       false,             // no boolean operations
				       0);                // copy number

    //part 2 tube full of vacuum
    solid_P2_T_D_v = new G4Tubs("Tube3_P2_T_D_v",
				0.0*cm,
				r_max_Tube3_par2_T*cm,
				length_Tube3_par2_T_v/2*cm,
				0.0*deg,
				360.0*deg);    
    logic_P2_T_D_v = new G4LogicalVolume(solid_P2_T_D_v, mat_v,"Tube3_P2_T_D_v",0,0,0);
    physi_P2_T_D_v = new G4PVPlacement(pRot_P2_D,         //no rotation
				       pos_P2_T_D,        // at (x,y,z)
				       logic_P2_T_D_v,    // its logical volume
				       "Tube3_P2_T_D_v",  // its name
				       logicWorld,        // its mother  volume
				       false,             // no boolean operations
				       0);                // copy number

/*
    // part 3 one litle trapezoid made of aluminium
    solid_P3_TR = new G4Trd("Tube3_P3_TR",
			    dx1_par3,
			    dx2_par3,
			    dy1_Tube3_par3_TR/2*cm,
			    dy1_Tube3_par3_TR/2*cm,
			    dz_Tube3_par3_TR/2.*cm);
    logic_P3_TR = new G4LogicalVolume(solid_P3_TR, mat,"Tube3_P3_TR",0,0,0);
    physi_P3_TR = new G4PVPlacement(0,               //no rotation
				    pos_P3_TR,       // at (x,y,z)
				    logic_P3_TR,     // its logical volume
				    "Tube3_P3_TR",   // its name
				    logicWorld,      // its mother  volume
				    false,           // no boolean operations
				    0);              // copy number
*/
    // part 4 one upper tube made of aluminium
    solid_P4_U = new G4Tubs("Tube3_P4_U",
			    r_min_Tube3_par4*cm,
			    r_max_Tube3_par4*cm,
			    length_Tube3_par4/2*cm,
			    0.0*deg,
			    360.0*deg);
    logic_P4_U = new G4LogicalVolume(solid_P4_U, mat,"Tube3_P4_U",0,0,0);
    physi_P4_U = new G4PVPlacement(pRotU, 
				   pos_P4_U,        // at (x,y,z)
				   logic_P4_U,      // its logical volume
				   "Tube3_P4_U",    // its name
				   logicWorld,      // its mother  volume
				   false,           // no boolean operations
				   0);              // copy number


   // part 4 one bottom tube made of aluminium
    solid_P4_D = new G4Tubs("Tube3_P4_D",
			    r_min_Tube3_par4*cm,
			    r_max_Tube3_par4*cm,
			    length_Tube3_par4/2*cm,
			    0.0*deg,
			    360.0*deg);
    logic_P4_D = new G4LogicalVolume(solid_P4_D, mat,"Tube3_P4_D",0,0,0);
    physi_P4_D = new G4PVPlacement(pRotD, 
				   pos_P4_D,      // at (x,y,z)
				   logic_P4_D,    // its logical volume
				   "Tube3_P4_D",  // its name
				   logicWorld,    // its mother  volume
				   false,         // no boolean operations
				   0);            // copy number

    // part 4 one upper tube full of vacuum
    solid_P4_U_v = new G4Tubs("Tube3_P4_U_v",
			    r_min_Tube3_par4_v*cm,
			    r_max_Tube3_par4_v*cm,
			    length_Tube3_par4/2*cm,
			    0.0*deg,
			    360.0*deg);
    logic_P4_U_v = new G4LogicalVolume(solid_P4_U_v, mat_v,"Tube3_P4_U_v",0,0,0);
    physi_P4_U_v = new G4PVPlacement(pRotU, 
				     pos_P4_U,        // at (x,y,z)
				     logic_P4_U_v,    // its logical volume
				     "Tube3_P4_U_v",  // its name
				     logicWorld,      // its mother  volume
				     false,           // no boolean operations
				     0);              // copy number


   // part 4 one bottom tube full of vauum
    solid_P4_D_v = new G4Tubs("Tube3_P4_D_v",
			    r_min_Tube3_par4_v*cm,
			    r_max_Tube3_par4_v*cm,
			    length_Tube3_par4/2*cm,
			    0.0*deg,
			    360.0*deg);
    logic_P4_D_v = new G4LogicalVolume(solid_P4_D_v, mat_v,"Tube3_P4_D_v",0,0,0);
    physi_P4_D_v = new G4PVPlacement(pRotD, 
				   pos_P4_D,        // at (x,y,z)
				   logic_P4_D_v,    // its logical volume
				   "Tube3_P4_D_v",  // its name
				   logicWorld,      // its mother  volume
				   false,           // no boolean operations
				   0);              // copy number



    G4VisAttributes* beampipe = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    G4VisAttributes* vacuum = new G4VisAttributes(G4Colour(0.0,1.0,0.0));
    logic_P1_B_U->SetVisAttributes(beampipe);   
    logic_P1_B_D->SetVisAttributes(beampipe);
    logic_P1_T_R->SetVisAttributes(beampipe);
    logic_P1_T_L->SetVisAttributes(beampipe);
    logic_P1_B_v->SetVisAttributes(vacuum);
    logic_P1_T_L_v->SetVisAttributes(vacuum);
    logic_P1_T_R_v->SetVisAttributes(vacuum);
    logic_P2_TR->SetVisAttributes(beampipe);
    logic_P2_T_U_v->SetVisAttributes(vacuum);
    logic_P2_T_D_v->SetVisAttributes(vacuum);

//    logic_P3_TR->SetVisAttributes(beampipe);
    logic_P4_U->SetVisAttributes(beampipe);
    logic_P4_D->SetVisAttributes(beampipe);
    logic_P4_U_v->SetVisAttributes(vacuum);
    logic_P4_D_v->SetVisAttributes(vacuum);

}

G4VPhysicalVolume* ExN02DetectorConstruction_VTube::Construct(){
}

void ExN02DetectorConstruction_VTube::PrintInfo(){
    G4cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<G4endl;
    G4cout<<"----------ExN02DetectorConstruction_VTube.cc-----------"<<G4endl;
    G4cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<G4endl;
    /*
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
    */
}
