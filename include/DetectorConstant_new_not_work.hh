#ifndef DetectorConstant_h
#define DetectorConstant_h 1

namespace DetConst{

//************************//
// constants of the setup //
//************************//
    G4double cos4_07 = 0.997478;
    G4double sin4_07 = 0.0709752;
    G4double alpha = 4.07;             //beg angle between Z-axis and e-(e+)beampipe
    G4double corEndVlikeTube = 0.237767;

    //Central tube of the beampipe (BP) (see DAFNEUP-003-000.pdf or 01_DAFNEUP-003-000.pdf)
    G4double length_Tube1 = 48.5;         //cm +/-0.02 cm
    G4double innerRadius_Tube1 = 5.5/2;   //cm +/-0.01 cm
    G4double outerRadius_Tube1 = 5.9/2;   //cm +/-0.01 cm
    //-------------------------------------------------------------------------------------

    //Conecter between central tube of the beampipe and V-like tube
    //(see DAFNEUP-001-001.pdf or 02_DAFNEUP-001-001.pdf) 
    G4double length_Tube2 = 30.13;        // cm
    G4double length_Tube2_C = 14.15;      // cm circular part (in section) of the Tube2
    G4double length_Tube2_E = length_Tube2 - length_Tube2_C;  //cm elliptical part 
                                                              //(in section) of the Tube2
    //-------------------------------------------------------------------------------------

    //V-like tube (see DAFNEUP-001-005.pdf or  03_DAFNEUP-001-005.pdf)  
    G4double length_Tube3 = 28.272; // cm
    G4double dist_Tube3   = 3.894;  // cm distans detween center of the end of the
                                    // v-like tube and z-axis
    //-------------------------------------------------------------------------------------

    //Tube conect to the V-like tube (see DAFNEUP-001-003.pdf or 04_DAFNEUP-001-003.pdf) 
    G4double length_Tube4 = 58.07;      //cm +/- 0.02
    //-------------------------------------------------------------------------------------
    
    //End of the BP (see DAFNEUP-001-003.pdf or 05_DAFNEUP-001-003.pdf) 
    //All right-hand part of the BP you can see in DAFNEUP-001-000.pdf or 06_DAFNEUP-001-000.pdf
    G4double length_Tube5 = 86.9;      //cm +/- 0.02
    G4double length_Tube5_C  = 56.0;   // cm circular part (in section) of the Tube5
    G4double length_Tube5_Co = length_Tube5 - length_Tube5_C;  //cm cone part (in section)
    //-------------------------------------------------------------------------------------

//************************************************//
//  Coordinates of centres of the different parts //
//************************************************//
    //Central tube of the beampipe
    G4double x_Tube1 = 0.;
    G4double y_Tube1 = 0.;
    G4double z_Tube1 = 0.;
    //-------------------------------------

    //Conecter between central tube of the beampipe and V-like tube
    G4double x_Tube2_C_R = 0.;
    G4double y_Tube2_C_R = 0.;
    G4double z_Tube2_C_R = length_Tube1/2+length_Tube2_C/2;
    G4double x_Tube2_E_R = 0.;
    G4double y_Tube2_E_R = 0.;
    G4double z_Tube2_E_R = length_Tube1/2 + length_Tube2_C + length_Tube2_E/2;
 
    G4double x_Tube2_C_L = 0.;
    G4double y_Tube2_C_L = 0.;
    G4double z_Tube2_C_L = -z_Tube2_C_R;
    G4double x_Tube2_E_L = 0.;
    G4double y_Tube2_E_L = 0.;
    G4double z_Tube2_E_L = -z_Tube2_E_R;
    //-------------------------------------

    //Coordinates of the ends of V-like tube

    G4double x_Tube3_TR_R = 0.;
    G4double y_Tube3_TR_R = 0.;
    G4double z_Tube3_TR_R = length_Tube1/2 + length_Tube2 + length_Tube3/2.;

    G4double x_Tube3_R_U = dist_Tube3;
    G4double y_Tube3_R_U = 0.;
    G4double z_Tube3_R_U = length_Tube1/2 + length_Tube2 + length_Tube3 - corEndVlikeTube;
    G4double x_Tube3_R_D = -x_Tube3_R_U;
    G4double y_Tube3_R_D = 0.;
    G4double z_Tube3_R_D = z_Tube3_R_U;  

    G4double x_Tube3_L_U = x_Tube3_R_U;
    G4double y_Tube3_L_U = 0.;
    G4double z_Tube3_L_U = -z_Tube3_R_U;
    G4double x_Tube3_L_D = -x_Tube3_L_U;
    G4double y_Tube3_L_D = 0.;
    G4double z_Tube3_L_D = z_Tube3_L_U;
    //-------------------------------------

    //Tube conect to the V-like tube (see DAFNEUP-001-003.pdf or 04_DAFNEUP-001-003.pdf)  
    Double_t x_Tube4_R_U = dist_Tube3 + length_Tube4/2*sin4_07;
    Double_t y_Tube4_R_U = 0;
    Double_t z_Tube4_R_U = z_Tube3_R_U + length_Tube4/2*cos4_07;
    Double_t x_Tube4_R_D = -x_Tube4_R_U;
    Double_t y_Tube4_R_D = 0.;
    Double_t z_Tube4_R_D = z_Tube4_R_U;

    Double_t x_Tube4_L_U = x_Tube4_R_U;
    Double_t y_Tube4_L_U = 0.;
    Double_t z_Tube4_L_U = -z_Tube4_R_U;
    Double_t x_Tube4_L_D = -x_Tube4_L_U;
    Double_t y_Tube4_L_D = 0.;
    Double_t z_Tube4_L_D = z_Tube4_L_U;
    //-------------------------------------

    //End of the BP (see DAFNEUP-001-003.pdf or 05_DAFNEUP-001-003.pdf) 
    //All right-hand part of the BP you can see in DAFNEUP-001-000.pdf or 06_DAFNEUP-001-000.pdf
    G4double r1min_Tube5_Co_R_U = innerRadius_Tube1;  //cm +/-01
    G4double r2min_Tube5_Co_R_U = 8.8/2;              //cm +/-01
    G4double r1max_Tube5_Co_R_U = outerRadius_Tube1;  //cm 
    G4double r2max_Tube5_Co_R_U = r2min_Tube5_Co_R_U + (outerRadius_Tube1 - innerRadius_Tube1); //cm

    G4double x_Tube5_Co_R_U = dist_Tube3 + length_Tube4*sin4_07 + length_Tube5_C*sin4_07 + length_Tube5_Co/2*sin4_07;
    G4double y_Tube5_Co_R_U = 0.;
    G4double z_Tube5_Co_R_U =  z_Tube3_R_U + length_Tube4*cos4_07 + length_Tube5_C*cos4_07 + length_Tube5_Co/2*cos4_07;
    G4double x_Tube5_Co_R_D = -x_Tube5_Co_R_U;
    G4double y_Tube5_Co_R_D = 0.;
    G4double z_Tube5_Co_R_D = z_Tube5_Co_R_U;

    G4double x_Tube5_Co_L_U = x_Tube5_Co_R_U;
    G4double y_Tube5_Co_L_U = 0.;
    G4double z_Tube5_Co_L_U = -z_Tube5_Co_R_U;
    G4double x_Tube5_Co_L_D = -x_Tube5_Co_L_U;
    G4double y_Tube5_Co_L_D = 0.;
    G4double z_Tube5_Co_L_D = z_Tube5_Co_L_U;
    //-------------------------------------
}

#endif

