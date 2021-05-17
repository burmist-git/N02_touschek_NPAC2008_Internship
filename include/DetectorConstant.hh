#ifndef DetectorConstant_h
#define DetectorConstant_h

#include <math.h>

#define RotZm(z,x) (z*cos4_07+x*sin4_07)  // rotation anti clock
#define RotXm(z,x) (-z*sin4_07+x*cos4_07) // rotation anti clock

#define RotZp(z,x) (z*cos4_07-x*sin4_07)  // rotation clock
#define RotXp(z,x) (z*sin4_07+x*cos4_07)  // rotation clock

#define RotZTube2m(z,x) (z*cos2_87+x*sin2_87)  // rotation anti clock
#define RotXTube2m(z,x) (-z*sin2_87+x*cos2_87) // rotation anti clock

#define RotZTube2p(z,x) (z*cos2_87-x*sin2_87)  // rotation clock
#define RotXTube2p(z,x) (z*sin2_87+x*cos2_87)  // rotation clock

#define RotZTube3m(z,x) (z*cosAngleT3+x*sinAngleT3)  // rotation anti clock
#define RotXTube3m(z,x) (-z*sinAngleT3+x*cosAngleT3) // rotation anti clock

#define RotZTube3p(z,x) (z*cosAngleT3-x*sinAngleT3)  // rotation clock
#define RotXTube3p(z,x) (z*sinAngleT3+x*cosAngleT3)  // rotation clock

#define RotZoldP(z0,x0,dz,dx) ( (RotZm(z0,x0) + dz)*cos4_07 - (RotXm(z0,x0) + dx)*sin4_07)
#define RotXoldP(z0,x0,dz,dx) ( (RotZm(z0,x0) + dz)*sin4_07 + (RotXm(z0,x0) + dx)*cos4_07)

#define RotZoldM(z0,x0,dz,dx) ( (RotZp(z0,x0) + dz)*cos4_07 + (RotXp(z0,x0) + dx)*sin4_07)
#define RotXoldM(z0,x0,dz,dx) (-(RotZp(z0,x0) + dz)*sin4_07 + (RotXp(z0,x0) + dx)*cos4_07)

#define RotZoldTube2P(z0,x0,dz,dx) ( (RotZTube2m(z0,x0) + dz)*cos2_87 - (RotXTube2m(z0,x0) + dx)*sin2_87)
#define RotXoldTube2P(z0,x0,dz,dx) ( (RotZTube2m(z0,x0) + dz)*sin2_87 + (RotXTube2m(z0,x0) + dx)*cos2_87)

#define RotZoldTube2M(z0,x0,dz,dx) ( (RotZTube2p(z0,x0) + dz)*cos2_87 + (RotXTube2p(z0,x0) + dx)*sin2_87)
#define RotXoldTube2M(z0,x0,dz,dx) (-(RotZTube2p(z0,x0) + dz)*sin2_87 + (RotXTube2p(z0,x0) + dx)*cos2_87)

#define RotZoldTube3P(z0,x0,dz,dx) ( (RotZTube3m(z0,x0) + dz)*cosAngleT3 - (RotXTube3m(z0,x0) + dx)*sinAngleT3)
#define RotXoldTube3P(z0,x0,dz,dx) ( (RotZTube3m(z0,x0) + dz)*sinAngleT3 + (RotXTube3m(z0,x0) + dx)*cosAngleT3)

#define RotZoldTube3M(z0,x0,dz,dx) ( (RotZTube3p(z0,x0) + dz)*cosAngleT3 + (RotXTube3p(z0,x0) + dx)*sinAngleT3)
#define RotXoldTube3M(z0,x0,dz,dx) (-(RotZTube3p(z0,x0) + dz)*sinAngleT3 + (RotXTube3p(z0,x0) + dx)*cosAngleT3)

namespace DetConst{

    static const G4double Pi = 3.14159265358979312;
    static const G4double D_2_R = Pi/180.;

    static const G4double cos4_07 = 0.997478082176520564;
    static const G4double sin4_07 = 0.0709751757831599134;
    static const G4double tan4_07 = sin4_07/cos4_07;
    static const G4double alpha = 4.07;               //beg angle between Z-axis and e-(e+)beampipe
    static const G4double corEndVlikeTube = 0.237767;

    //-----Ellipticalpart-of-the-tube2------//
    static const G4double alpha2_87 = 1.435;              // deg
    static const G4double sin2_87 = 0.0250428564448442748;//
    static const G4double cos2_87 = 0.9996863784913161410;//
    //---------------------------------------//

    //-----V-like-tube----------------------//
    static const G4double sin7_45 = 0.129660943770031734;//    
    static const G4double cos7_45 = 0.991558389435874155;//    
    static const G4double tan7_45 = sin7_45/cos7_45;     //
    static const G4double alpha7_104 = 7.104;            // deg
    static const G4double sin7_9  = 0.137444546037146648;//    
    static const G4double cos7_9  = 0.990509463238308796;//    
    static const G4double tan7_9  = sin7_9/cos7_9;       //
    //--------------------------------------//

    //Central tube of the beampipe (BP) (see DAFNEUP-003-000.pdf or 01_DAFNEUP-003-000.pdf)
    static const G4double length_Tube1 = 48.5;         //cm +/-0.02 cm
    static const G4double innerRadius_Tube1 = 5.5/2;   //cm +/-0.01 cm
    static const G4double outerRadius_Tube1 = 5.9/2;   //cm +/-0.01 cm

    //Conecter between central tube of the beampipe and V-like tube
    //(see DAFNEUP-001-001.pdf or 02_DAFNEUP-001-001.pdf) 
    static const G4double length_Tube2 = 30.13;        // cm
    static const G4double length_Tube2_C = 14.15;      // cm circular part (in section) of the Tube2
    static const G4double zlength_Tube2_E = length_Tube2 - length_Tube2_C;  //cm elliptical part 
                                                               //(in section) of the Tube2
    static const G4double length_Tube2_E = zlength_Tube2_E/cos2_87+0.2;
    static const G4double innerRadiusTube2_E = 5.5/2.;  //+/- 0.1 cm
    static const G4double outerRadiusTube2_E = 5.9/2.;  //+/- 0.1 cm

    //V-like tube (see DAFNEUP-001-005.pdf or  03_DAFNEUP-001-005.pdf)  
    static const G4double length_Tube3 = 28.272; // cm
    static const G4double dist_Tube3   = 3.894;  // cm distans detween center of the end of the
                                    // v-like tube and z-axis

    //Tube conect to the V-like tube (see DAFNEUP-001-003.pdf or 04_DAFNEUP-001-003.pdf) 
    static const G4double length_Tube4 = 58.07;      //cm +/- 0.02
    
    //End of the BP (see DAFNEUP-001-003.pdf or 05_DAFNEUP-001-003.pdf) 
    //All right-hand part of the BP you can see in DAFNEUP-001-000.pdf or 06_DAFNEUP-001-000.pdf
    static const G4double length_Tube5 = 86.9;      //cm +/- 0.02
    static const G4double length_Tube5_C  = 56.0;   // cm circular part (in section) of the Tube5
    static const G4double length_Tube5_Co = length_Tube5 - length_Tube5_C;  //cm cone part (in section)
 
//---------------------------------------------------------------------------

    //---------------------------------
    //Central tube of the beampipe
    //---------------------------------
    static const G4double x_Tube1 = 0.;
    static const G4double y_Tube1 = 0.;
    static const G4double z_Tube1 = 0.;

    //--------------------------------------------
    // connecting rings around the BP1
    //--------------------------------------------
    static const G4double length_Tube1Con = 1.74;
    static const G4double innerRadius_Tube1Con = innerRadius_Tube1 + (outerRadius_Tube1 - innerRadius_Tube1);  
    static const G4double outerRadius_Tube1Con = 5.5;   //cm

    static const G4double x_Tube1Con_R = 0.;
    static const G4double y_Tube1Con_R = 0.;
    static const G4double z_Tube1Con_R = length_Tube1/2 - length_Tube1Con/2;

    static const G4double x_Tube1Con_L = 0.;
    static const G4double y_Tube1Con_L = 0.;
    static const G4double z_Tube1Con_L = -z_Tube1Con_R;

    
    //-------------------------------------------------------------
    //Conecter between central tube of the beampipe and V-like tube
    //-------------------------------------------------------------
    static const G4double x_Tube2_C_R = 0;
    static const G4double y_Tube2_C_R = 0;
    static const G4double z_Tube2_C_R = length_Tube1/2+length_Tube2_C/2;
    static const G4double x_Tube2_C_L = 0;
    static const G4double y_Tube2_C_L = 0;
    static const G4double z_Tube2_C_L = -z_Tube2_C_R;

    //-------------------------------------------------------------
    // rings around the Tube2 circular part which conected to the BP1
    //-------------------------------------------------------------
    static const G4double length_Tube2Con = 1.15;
    static const G4double innerRadius_Tube2Con = innerRadius_Tube1Con;
    static const G4double outerRadius_Tube2Con = 4.12;   //cm

    static const G4double x_Tube2Con_R = 0.;
    static const G4double y_Tube2Con_R = 0.;
    static const G4double z_Tube2Con_R = length_Tube1/2 + length_Tube2Con/2;

    static const G4double x_Tube2Con_L = 0.;
    static const G4double y_Tube2Con_L = 0.;
    static const G4double z_Tube2Con_L = -z_Tube2Con_R;

    //----------------------------------------------------------------
    //"ellictical" part consist of two half circles(left and right) 
    //and two trapezoid up and down
    //-----------------------------------------------------------------
    static const G4double x_Tube2_E_CRU = length_Tube2_E*sin2_87/2.;
    static const G4double y_Tube2_E_CRU = 0;
    static const G4double z_Tube2_E_CRU = length_Tube1/2 + length_Tube2_C + zlength_Tube2_E/2;
    static const G4double x_Tube2_E_CRD = -x_Tube2_E_CRU;
    static const G4double y_Tube2_E_CRD = 0;
    static const G4double z_Tube2_E_CRD = z_Tube2_E_CRU;
    
    static const G4double x_Tube2_E_CLU = x_Tube2_E_CRU;
    static const G4double y_Tube2_E_CLU = 0;
    static const G4double z_Tube2_E_CLU = -z_Tube2_E_CRU;
    static const G4double x_Tube2_E_CLD = -x_Tube2_E_CLU;
    static const G4double y_Tube2_E_CLD = 0;
    static const G4double z_Tube2_E_CLD = z_Tube2_E_CLU;

    static const G4double x_Tube2_E_TRRU = 0;
    static const G4double y_Tube2_E_TRRU = outerRadiusTube2_E - (outerRadiusTube2_E - innerRadiusTube2_E)/2.;
    static const G4double z_Tube2_E_TRRU = length_Tube1/2 + length_Tube2_C + zlength_Tube2_E/2;

    static const G4double x_Tube2_E_TRRD = 0;
    static const G4double y_Tube2_E_TRRD = -y_Tube2_E_TRRU;
    static const G4double z_Tube2_E_TRRD = z_Tube2_E_TRRU;

    static const G4double x_Tube2_E_TRR_v = 0.;
    static const G4double y_Tube2_E_TRR_v = 0.;
    static const G4double z_Tube2_E_TRR_v = length_Tube1/2 + length_Tube2_C + zlength_Tube2_E/2;

    static const G4double x_Tube2_E_TRLU = 0;
    static const G4double y_Tube2_E_TRLU = y_Tube2_E_TRRU;
    static const G4double z_Tube2_E_TRLU = -z_Tube2_E_TRRU;
    
    static const G4double x_Tube2_E_TRLD = 0;
    static const G4double y_Tube2_E_TRLD = -y_Tube2_E_TRLU;
    static const G4double z_Tube2_E_TRLD = z_Tube2_E_TRLU;

    static const G4double x_Tube2_E_TRL_v = 0.;
    static const G4double y_Tube2_E_TRL_v = 0.;
    static const G4double z_Tube2_E_TRL_v = -z_Tube2_E_TRR_v;
    
    static const G4double dx1_Tube2_E_TR = 0;
    static const G4double dx2_Tube2_E_TR = 0.8;   //cm
    static const G4double dy1_Tube2_E_TR = outerRadiusTube2_E - innerRadiusTube2_E;
    static const G4double dy2_Tube2_E_TR = dy1_Tube2_E_TR;
    static const G4double dz_Tube2_E_TR = zlength_Tube2_E;
   
    static const G4double dx1_Tube2_E_TR_v = 0;
    static const G4double dx2_Tube2_E_TR_v = 0.8;   //cm
    static const G4double dy1_Tube2_E_TR_v = 2.*innerRadiusTube2_E;
    static const G4double dy2_Tube2_E_TR_v = dy1_Tube2_E_TR_v;
    static const G4double dz_Tube2_E_TR_v = zlength_Tube2_E;

    //----Case-of-just-circle-------------------------------------------
    static const G4double x_Tube2_E_CR = 0;
    static const G4double y_Tube2_E_CR = 0;
    static const G4double z_Tube2_E_CR = length_Tube1/2 + length_Tube2_C + length_Tube2_E/2;
    static const G4double x_Tube2_E_CL = 0;
    static const G4double y_Tube2_E_CL = 0;
    static const G4double z_Tube2_E_CL = -z_Tube2_E_CR;
    //-----------------------------------------------------------------

    //--------------------------------------
    // V-like tube  
    //--------------------------------------

    //-----------------------
    // new V-like tube consiste of 4 main part
    // part 1:
    //        two boxes made of aluminium
    //        two half cilinder made of aluminium
    //        two half cilinder full of vacuum
    //        one boxe full of vacuum
    // part 2:
    //        one big trapezoid made of aluminium
    //        two tubes full of vacuum
    // part 3:
    //        one litle trapezoid made of aluminium
    // part 4:
    //        two tubes made of aluminium
    //        two tubes full of vacuum
    //-----------------------

    //part 1:
       //two litlle boxes from the top and bottom made of aluminium
       static const G4double x_length_Tube3_par1_B = 0.8;  //cm
       static const G4double y_length_Tube3_par1_B = 0.3;  //cm
       static const G4double z_length_Tube3_par1_B = 1.25;  //cm
       static const G4double x_Tube3_par1_B = 0.0;
       static const G4double y_Tube3_par1_B = innerRadius_Tube1 + y_length_Tube3_par1_B/2;
       static const G4double z_Tube3_par1_B = length_Tube1/2. + length_Tube2 + z_length_Tube3_par1_B/2;
 
       //two tubes from the left and right made of aluminium
       static const G4double r_min_Tube3_par1_T = 2.75;                  //cm
       static const G4double r_max_Tube3_par1_T = 6.1/2;                 //cm
       static const G4double length_Tube3_par1_T= z_length_Tube3_par1_B; 
       static const G4double x_Tube3_par1_T = x_length_Tube3_par1_B/2;
       static const G4double y_Tube3_par1_T = 0.0;
       static const G4double z_Tube3_par1_T = z_Tube3_par1_B;

       //one box full of vacuum
       static const G4double x_length_Tube3_par1_B_v = x_length_Tube3_par1_B; //cm
       static const G4double y_length_Tube3_par1_B_v = r_min_Tube3_par1_T*2;  //cm
       static const G4double z_length_Tube3_par1_B_v = 1.7;                   //cm
       static const G4double x_Tube3_par1_B_v = 0.0;
       static const G4double y_Tube3_par1_B_v = 0.0;
       static const G4double z_Tube3_par1_B_v = z_Tube3_par1_B;

    //part 2:
       //one big trapezoid made of aluminium
       static const G4double dx1_Tube3_par2_TR = 7.872;  //cm
       static const G4double dx2_Tube3_par2_TR = 14.439; //cm
       static const G4double dy1_Tube3_par2_TR = 8.0;    //cm
       static const G4double dy2_Tube3_par2_TR = 8.0;    //cm
       static const G4double dz_Tube3_par2_TR = sqrt(sqr(25.509) - 
       sqr(dx2_Tube3_par2_TR/2-dx1_Tube3_par2_TR/2));    //cm
       static const G4double x_Tube3_par2_TR = 0.0;
       static const G4double y_Tube3_par2_TR = 0.0;
       static const G4double z_Tube3_par2_TR = length_Tube1/2. + length_Tube2 + 
       z_length_Tube3_par1_B + dz_Tube3_par2_TR/2;       //cm
       //two tubes full of vacuum
       static const G4double x1_Tube3_par2_T = 0.4;
       static const G4double z1_Tube3_par2_T = length_Tube1/2. + length_Tube2;
       static const G4double x2_Tube3_par2_T = 3.894;
       static const G4double z2_Tube3_par2_T = length_Tube1/2. + length_Tube2 + 
       z_length_Tube3_par1_B + dz_Tube3_par2_TR + 14.439*tan4_07/2 + 
       1.25/cos4_07;
       static const G4double length_Tube3_par2_T_v = sqrt(sqr(x2_Tube3_par2_T-x1_Tube3_par2_T)
       +sqr(z2_Tube3_par2_T - z1_Tube3_par2_T));         //cm
       static const G4double x_Tube3_par2_T_v = (x2_Tube3_par2_T + x1_Tube3_par2_T)/2;
       static const G4double y_Tube3_par2_T_v = 0.0;
       static const G4double z_Tube3_par2_T_v = (z2_Tube3_par2_T + z1_Tube3_par2_T)/2;
       static const G4double tan_Tube3_par2  = (x2_Tube3_par2_T - x1_Tube3_par2_T)/
       (z2_Tube3_par2_T - z1_Tube3_par2_T) ;             //cm
       static const G4double angle_Tube3_par2 = atan(tan_Tube3_par2)*180/Pi;
       static const G4double r_max_Tube3_par2_T = r_min_Tube3_par1_T*cos(angle_Tube3_par2*Pi/180);
       static const G4double sinAngleT3 = sin(angle_Tube3_par2*Pi/180.);
       static const G4double cosAngleT3 = cos(angle_Tube3_par2*Pi/180.);
       static const G4double tagAngleT3 = sinAngleT3/cosAngleT3;

    // part 3:
       //one litle trapezoid made of aluminium
       static const G4double dx1_Tube3_par3_TR = 14.439;  //cm
       static const G4double dx2_Tube3_par3_TR = 0.0;     //cm
       static const G4double dy1_Tube3_par3_TR = 8.0;     //cm
       static const G4double dy2_Tube3_par3_TR = 8.0;     //cm
       //static const G4double dz_Tube3_par3_TR = 28.272-dz_Tube3_par2_TR-1.7-1.25*cos4_07;//cm
       static const G4double dz_Tube3_par3_TR = 14.439*tan4_07/2;//cm
       static const G4double x_Tube3_par3_TR = 0.0;
       static const G4double y_Tube3_par3_TR = 0.0;
       static const G4double z_Tube3_par3_TR = length_Tube1/2. + length_Tube2 + 
       z_length_Tube3_par1_B + dz_Tube3_par2_TR + dz_Tube3_par3_TR/2;//cm
      
    //part 4;
       //two tubes made of aluminium
       static const G4double r_min_Tube3_par4  = 5.511/2;               //cm
       static const G4double r_max_Tube3_par4  = (5.511 + 6.7)/4;       //cm
       static const G4double length_Tube3_par4 = 1.25;                  //cm 
       static const G4double x_Tube3_par4 = 3.894 - length_Tube3_par4*sin4_07/2;
       static const G4double y_Tube3_par4 = 0.0;
       static const G4double tmo1_Tube3_par4 = z2_Tube3_par2_T;
       static const G4double z_Tube3_par4 = tmo1_Tube3_par4 - 3.894*tan4_07 - 
       length_Tube3_par4*cos4_07/2;
       //two tubes full of vacuum
       static const G4double r_min_Tube3_par4_v  = 0.0;              //cm
       static const G4double r_max_Tube3_par4_v  = r_min_Tube3_par4; //cm
       static const G4double length_Tube3_par4_v = 1.25;             //cm



/*
       static const G4double r_min_Tube3_par4_T = 5.511/2;  //cm
       static const G4double r_max_Tube3_par4_T = 6.7/2; //cm
       static const G4double length_Tube3_par4_T = 1.25;  //cm
       static const G4double x_Tube3_par4_T_U = (2*3.894 - length_Tube3_par4_T*tan4_07)/2;
       static const G4double y_Tube3_par4_T_U = 0.0;
       static const G4double z_Tube3_par4_T_U = length_Tube1/2. + length_Tube2 + 
       z_length_Tube3_par1_B + dz_Tube3_par2_TR + dz_Tube3_par3_TR/2;//cm
*/

/*
    static const G4double x_Tube3_par1_R_B_D = x_Tube3_par2_R_B_U;
    static const G4double y_Tube3_par1_R_B_D = -y_Tube3_par2_R_B_U;
    static const G4double z_Tube3_par1_R_B_D = z_Tube3_par2_R_B_U;

    //two boxes from the left
    static const G4double x_Tube3_par1_L_B_U = x_Tube3_par2_R_B_U;
    static const G4double y_Tube3_par1_L_B_U = y_Tube3_par2_R_B_U;
    static const G4double z_Tube3_par1_L_B_U = -z_Tube3_par2_R_B_U;

    static const G4double x_Tube3_par1_L_B_D = x_Tube3_par2_R_B_D;
    static const G4double y_Tube3_par1_L_B_D = y_Tube3_par2_R_B_D;
    static const G4double z_Tube3_par1_L_B_D = -z_Tube3_par2_R_B_D;
*/
    //part 2 
    /*

      static const G4double x_length_Tube3_par2_Tr = 0.0;
      static const G4double y_length_Tube3_par2_Tr = innerRadius_Tube1 + (outerRadius_Tube1 - innerRadius_Tube1)/2;
      static const G4double z_length_Tube3_par2_Tr = length_Tube1/2. + length_Tube1;

      //one big trapezoid right
      static const G4double x_Tube3_par2_R_Tr = 0.0;
      static const G4double y_Tube3_par2_R_Tr = innerRadius_Tube1 + (outerRadius_Tube1 - innerRadius_Tube1)/2;
      static const G4double z_Tube3_par2_R_Tr = length_Tube1/2. + length_Tube1;
      
      //left
      static const G4double x_Tube3_par2_L_Tr = x_Tube3_par2_R_B_U;
      static const G4double y_Tube3_par2_L_Tr = -y_Tube3_par2_R_B_U;
      static const G4double z_Tube3_par2_L_Tr = z_Tube3_par2_R_B_U;

    */
    
/*
    //two half  from the right
    static const G4double x_Tube3_par2_R_B_U = 0.0;
    static const G4double y_Tube3_par2_R_B_U = innerRadius_Tube1 + (outerRadius_Tube1 - innerRadius_Tube1)/2;
    static const G4double z_Tube3_par2_R_B_U = length_Tube1/2. + length_Tube1;

    static const G4double x_Tube3_par2_R_B_D = x_Tube3_par2_B_U;
    static const G4double y_Tube3_par2_R_B_D = -y_Tube3_par2_B_U;
    static const G4double z_Tube3_par2_R_B_D = z_Tube3_par2_B_U;
*/





    //-----------------------

    static const G4double x_Tube3_R_U = dist_Tube3;
    static const G4double y_Tube3_R_U = 0;
    static const G4double z_Tube3_R_U = length_Tube1/2 + length_Tube2 + length_Tube3 - corEndVlikeTube;
    static const G4double x_Tube3_R_D = -x_Tube3_R_U;
    static const G4double y_Tube3_R_D = 0;
    static const G4double z_Tube3_R_D = z_Tube3_R_U;  

/*
    static const G4double x_Tube3_R_U = dist_Tube3;
    static const G4double y_Tube3_R_U = 0;
    static const G4double z_Tube3_R_U = length_Tube1/2 + length_Tube2 + length_Tube3 - corEndVlikeTube;
    static const G4double x_Tube3_R_D = -x_Tube3_R_U;
    static const G4double y_Tube3_R_D = 0;
    static const G4double z_Tube3_R_D = z_Tube3_R_U;  
*/
    static const G4double x_Tube3_L_U = x_Tube3_R_U;
    static const G4double y_Tube3_L_U = 0;
    static const G4double z_Tube3_L_U = -z_Tube3_R_U;
    static const G4double x_Tube3_L_D = -x_Tube3_L_U;
    static const G4double y_Tube3_L_D = 0;
    static const G4double z_Tube3_L_D = z_Tube3_L_U;

    static const G4double x_Tube3_Center_TR1_R = 0.;
    static const G4double y_Tube3_Center_TR1_R = 0.;
    static const G4double z_Tube3_Center_TR1_R = length_Tube1/2 + length_Tube2 + (length_Tube3 - 6.7*sin4_07)/2;
    
    static const G4double x_Tube3_Center_TR1_L = 0.;
    static const G4double y_Tube3_Center_TR1_L = 0.;
    static const G4double z_Tube3_Center_TR1_L = -z_Tube3_Center_TR1_R;
 
    //G4double dx1_Tube3_TR1 = 7.827;                        //cm
    static const G4double dx1_Tube3_TR1 = 7.5;                            //cm (see 0303)
    static const G4double dy1_Tube3_TR1 = 8.;                             //cm    
    static const G4double dx2_Tube3_TR1 = 14.439;                         //cm
    static const G4double dy2_Tube3_TR1 = 8.;                             //cm 
    static const G4double dz_Tube3_TR1  = 28.272 - 6.7*sin4_07;           //cm 

    static const G4double x_Tube3_Center_TR2_R = 0.;
    static const G4double y_Tube3_Center_TR2_R = 0.;
    static const G4double z_Tube3_Center_TR2_R = length_Tube1/2 + length_Tube2 + length_Tube3 - 6.7*sin4_07/2;
    
    static const G4double x_Tube3_Center_TR2_L = 0.;
    static const G4double y_Tube3_Center_TR2_L = 0.;
    static const G4double z_Tube3_Center_TR2_L = -z_Tube3_Center_TR2_R;
    
    static const G4double dx1_Tube3_TR2 = 14.439;                       //cm
    static const G4double dy1_Tube3_TR2 = 8.;                           //cm    
    static const G4double dx2_Tube3_TR2 = 0.;                           //cm
    static const G4double dy2_Tube3_TR2 = 8.;                           //cm 
    static const G4double dz_Tube3_TR2  = 6.7*sin4_07;                  //cm 
 
    //G4double length_Tube3_TU = sqrt(3.894*3.894+(28.272-6.7/2*sin4_07)*(28.272-6.7/2*sin4_07));
    static const G4double length_Tube3_TU_cor = 0.32;
    static const G4double length_Tube3_TU = sqrt((3.894-0.4)*(3.894-0.4)+(28.272-6.7/2*sin4_07)*(28.272-6.7/2*sin4_07)) + length_Tube3_TU_cor;
    static const G4double z_length_Tube3_TU = (28.272-6.7/2*sin4_07);
    static const G4double x_length_Tube3_TU = (3.894-0.4);
    
    static const G4double innerradius_Tube3_TU = 0.;
    static const G4double outerradius_Tube3_TU = 5.513/2.;

    //G4double x_Tube3_Center_TU_R_U = length_Tube3_TU/2*sin7_9;
    //G4double y_Tube3_Center_TU_R_U = 0.;
    //G4double z_Tube3_Center_TU_R_U = length_Tube1/2 + length_Tube2 + length_Tube3_TU/2*cos7_9;
    
    //G4double x_Tube3_Center_TU_R_D = -length_Tube3_TU/2*sin7_9;
    //G4double y_Tube3_Center_TU_R_D = 0.;
    //G4double z_Tube3_Center_TU_R_D = length_Tube1/2 + length_Tube2 + length_Tube3_TU/2*cos7_9;

    static const G4double cos7_104 = z_length_Tube3_TU/length_Tube3_TU;
    static const G4double sin7_104 = x_length_Tube3_TU/length_Tube3_TU;

    static const G4double x_Tube3_Center_TU_R_U = length_Tube3_TU/2*sin7_104+0.4;
    static const G4double y_Tube3_Center_TU_R_U = 0.;
    static const G4double z_Tube3_Center_TU_R_U = length_Tube1/2 + length_Tube2 + length_Tube3_TU/2*cos7_104;
    
    static const G4double x_Tube3_Center_TU_R_D = -x_Tube3_Center_TU_R_U; 
    static const G4double y_Tube3_Center_TU_R_D = y_Tube3_Center_TU_R_U;
    static const G4double z_Tube3_Center_TU_R_D = z_Tube3_Center_TU_R_U;

    static const G4double x_Tube3_Center_TU_L_U = x_Tube3_Center_TU_R_U;
    static const G4double y_Tube3_Center_TU_L_U = 0.;
    static const G4double z_Tube3_Center_TU_L_U = -z_Tube3_Center_TU_R_U;
    
    static const G4double x_Tube3_Center_TU_L_D = -x_Tube3_Center_TU_L_U; 
    static const G4double y_Tube3_Center_TU_L_D = y_Tube3_Center_TU_L_U;
    static const G4double z_Tube3_Center_TU_L_D = z_Tube3_Center_TU_L_U;
  
    //-----------------------------------------------------------------
    
    //--------------------------------
    //Tube conect to the V-like tube 
    //--------------------------------
    static const G4double x_Tube4_R_U = dist_Tube3 + length_Tube4/2*sin4_07;
    static const G4double y_Tube4_R_U = 0;
    static const G4double z_Tube4_R_U = z_Tube3_R_U + length_Tube4/2*cos4_07;
    static const G4double x_Tube4_R_D = -x_Tube4_R_U;
    static const G4double y_Tube4_R_D = 0;
    static const G4double z_Tube4_R_D = z_Tube4_R_U;
 
    static const G4double x_Tube4_L_U = x_Tube4_R_U;
    static const G4double y_Tube4_L_U = 0;
    static const G4double z_Tube4_L_U = -z_Tube4_R_U;
    static const G4double x_Tube4_L_D = -x_Tube4_L_U;
    static const G4double y_Tube4_L_D = 0;
    static const G4double z_Tube4_L_D = z_Tube4_L_U;

    static const G4double x_maxAxisTube4_R_U = x_Tube4_R_U + length_Tube4/2*sin4_07;
    static const G4double y_maxAxisTube4_R_U = 0;
    static const G4double z_maxAxisTube4_R_U = z_Tube4_R_U + length_Tube4/2*cos4_07;

    static const G4double x_minAxisTube4_R_U = x_Tube4_R_U - length_Tube4/2*sin4_07;
    static const G4double y_minAxisTube4_R_U = 0;
    static const G4double z_minAxisTube4_R_U = z_Tube4_R_U - length_Tube4/2*cos4_07;


    //-------------------------------------------
    //End of the BP
    // cm circular part (in section) of the Tube5
    //-------------------------------------------
    static const G4double x_Tube5_C_R_U = dist_Tube3 + length_Tube4*sin4_07 + length_Tube5_C/2*sin4_07;
    static const G4double y_Tube5_C_R_U = 0;
    static const G4double z_Tube5_C_R_U = z_Tube3_R_U + length_Tube4*cos4_07 + length_Tube5_C/2*cos4_07;
    static const G4double x_Tube5_C_R_D = -x_Tube5_C_R_U;
    static const G4double y_Tube5_C_R_D = 0;
    static const G4double z_Tube5_C_R_D = z_Tube5_C_R_U;

    static const G4double x_Tube5_C_L_U = x_Tube5_C_R_U;
    static const G4double y_Tube5_C_L_U = 0;
    static const G4double z_Tube5_C_L_U = -z_Tube5_C_R_U;
    static const G4double x_Tube5_C_L_D = -x_Tube5_C_L_U;
    static const G4double y_Tube5_C_L_D = 0;
    static const G4double z_Tube5_C_L_D = z_Tube5_C_L_U;

    // cm cone part (in section) of the Tube5
    static const G4double r1min_Tube5_Co = innerRadius_Tube1;  //cm +/-01
    static const G4double r2min_Tube5_Co = 8.8/2;              //cm +/-01
    static const G4double r1max_Tube5_Co = outerRadius_Tube1;  //cm 
    static const G4double r2max_Tube5_Co = r2min_Tube5_Co + (outerRadius_Tube1 - innerRadius_Tube1); //cm

    static const G4double x_Tube5_Co_R_U = dist_Tube3 + length_Tube4*sin4_07 + length_Tube5_C*sin4_07 + length_Tube5_Co/2*sin4_07;
    static const G4double y_Tube5_Co_R_U = 0;
    static const G4double z_Tube5_Co_R_U =  z_Tube3_R_U + length_Tube4*cos4_07 + length_Tube5_C*cos4_07 + length_Tube5_Co/2*cos4_07;
    static const G4double x_Tube5_Co_R_D = -x_Tube5_Co_R_U;
    static const G4double y_Tube5_Co_R_D = 0;
    static const G4double z_Tube5_Co_R_D = z_Tube5_Co_R_U;

    static const G4double x_Tube5_Co_L_U = x_Tube5_Co_R_U;
    static const G4double y_Tube5_Co_L_U = 0;
    static const G4double z_Tube5_Co_L_U = -z_Tube5_Co_R_U;
    static const G4double x_Tube5_Co_L_D = -x_Tube5_Co_L_U;
    static const G4double y_Tube5_Co_L_D = 0;
    static const G4double z_Tube5_Co_L_D = z_Tube5_Co_L_U;

    //-------------------------------------------------------------------
    // !!!!!!Magnetic field!!!!!!!
    //-------------------------------------------------------------------

    //-QD0--------------------------------
    static const G4double length_QD0_T = 21.0;     //cm   
    static const G4double innerRadius_QD0_T = 3.3; //cm
    static const G4double outerRadius_QD0_T = 10.; //cm
    static const G4double x_QD0_T_R = 0.;  
    static const G4double y_QD0_T_R = 0.;    
    static const G4double z_QD0_T_R = 42.5;        //cm
    static const G4double x_QD0_T_L = x_QD0_T_R;  
    static const G4double y_QD0_T_L = y_QD0_T_R;    
    static const G4double z_QD0_T_L = -z_QD0_T_R;
     
    static const G4double length_QD0_Co = 2.0;     //cm   
    static const G4double innerRadius1_QD0_Co = 3.3;
    static const G4double outerRadius1_QD0_Co = 9.45;
    static const G4double innerRadius2_QD0_Co = 3.3;
    static const G4double outerRadius2_QD0_Co = 10.;
    static const G4double x_QD0_Co_R = 0.;  
    static const G4double y_QD0_Co_R = 0.;    
    static const G4double z_QD0_Co_R = z_QD0_T_R - length_QD0_T/2. - length_QD0_Co/2.; //cm
    static const G4double x_QD0_Co_L = x_QD0_Co_R;  
    static const G4double y_QD0_Co_L = y_QD0_Co_R;    
    static const G4double z_QD0_Co_L = -z_QD0_Co_R;

    static const G4double z_max_QD0_R = z_QD0_T_R + length_QD0_T/2;
    static const G4double z_min_QD0_R =  z_QD0_T_R - length_QD0_T/2 - length_QD0_Co;
    static const G4double z_max_QD0_L = -z_max_QD0_R;
    static const G4double z_min_QD0_L = -z_min_QD0_R;

    static const G4double x_max_QD0_R = innerRadius_QD0_T;
    static const G4double x_min_QD0_R = -innerRadius_QD0_T;
    static const G4double x_max_QD0_L = innerRadius_QD0_T;
    static const G4double x_min_QD0_L = -innerRadius_QD0_T;

    static const G4double y_max_QD0_R = innerRadius_QD0_T;
    static const G4double y_min_QD0_R = -innerRadius_QD0_T;
    static const G4double y_max_QD0_L = innerRadius_QD0_T;
    static const G4double y_min_QD0_L = -innerRadius_QD0_T;


    //------------------------------------

    //QD1--QF1-----------------------------
    static const G4double length_QD1_Al = 1.0;    //cm
    static const G4double length_QD1_SRCO = 24.0; //cm
    static const G4double length_QD1 = length_QD1_SRCO  + length_QD1_Al;
    static const G4double innerRadius_QD1 = 3.;   //cm
    static const G4double outerRadius_QD1 = 4.5;  //cm

    static const G4double D = RotXm(z_Tube4_R_U, x_Tube4_R_U); 

    //e-
    static const G4double z_QD1_R_Umy = 95.394989 + 0.5;
    static const G4double x_QD1_R_Umy = (z_QD1_R_Umy*sin4_07 + D)/cos4_07;

    static const G4double xmax_QD1_R_Umy = x_QD1_R_Umy + length_QD1_SRCO/2*sin4_07;
    static const G4double ymax_QD1_R_Umy = innerRadius_QD1;
    static const G4double zmax_QD1_R_Umy = z_QD1_R_Umy + length_QD1_SRCO/2*cos4_07;

    static const G4double xmin_QD1_R_Umy = x_QD1_R_Umy - length_QD1_SRCO/2*sin4_07;
    static const G4double ymin_QD1_R_Umy = -innerRadius_QD1;
    static const G4double zmin_QD1_R_Umy = z_QD1_R_Umy - length_QD1_SRCO/2*cos4_07;

    static const G4double xmax_QD1_L_Dmy = -xmax_QD1_R_Umy;
    static const G4double ymax_QD1_L_Dmy = ymax_QD1_R_Umy;
    static const G4double zmax_QD1_L_Dmy = -zmax_QD1_R_Umy;

    static const G4double xmin_QD1_L_Dmy = -xmin_QD1_R_Umy;
    static const G4double ymin_QD1_L_Dmy = ymin_QD1_R_Umy;
    static const G4double zmin_QD1_L_Dmy = -zmin_QD1_R_Umy;
    //---    

    //e+
    static const G4double z_QD1_L_Umy = -z_QD1_R_Umy;
    static const G4double x_QD1_L_Umy =  x_QD1_R_Umy;

    static const G4double xmax_QD1_L_Umy = xmax_QD1_R_Umy;
    static const G4double ymax_QD1_L_Umy = ymax_QD1_R_Umy;
    static const G4double zmax_QD1_L_Umy = -zmax_QD1_R_Umy;

    static const G4double xmin_QD1_L_Umy = xmin_QD1_R_Umy;
    static const G4double ymin_QD1_L_Umy = ymin_QD1_R_Umy;
    static const G4double zmin_QD1_L_Umy = -zmin_QD1_R_Umy;

    static const G4double xmax_QD1_R_Dmy = -xmax_QD1_R_Umy;
    static const G4double ymax_QD1_R_Dmy = ymax_QD1_R_Umy;
    static const G4double zmax_QD1_R_Dmy = zmax_QD1_R_Umy;

    static const G4double xmin_QD1_R_Dmy = -xmin_QD1_R_Umy;
    static const G4double ymin_QD1_R_Dmy = ymin_QD1_R_Umy;
    static const G4double zmin_QD1_R_Dmy = zmin_QD1_R_Umy;
    //----------------------------------------------------

    static const G4double z_QD1_SRCO_R_U = 95.394989 + 0.5; //cm
    static const G4double x_QD1_SRCO_R_U = x_Tube4_R_U - (z_Tube4_R_U - z_QD1_SRCO_R_U)*tan4_07;
    static const G4double y_QD1_SRCO_R_U = 0;
    static const G4double z_QD1_Al_R_U = z_QD1_SRCO_R_U - (length_QD1_Al + length_QD1_SRCO)/2*cos4_07;
    static const G4double x_QD1_Al_R_U = x_QD1_SRCO_R_U - (length_QD1_Al + length_QD1_SRCO)/2*tan4_07;
    static const G4double y_QD1_Al_R_U = 0;

    static const G4double z_QD1_SRCO_R_D = z_QD1_SRCO_R_U;
    static const G4double x_QD1_SRCO_R_D = -x_QD1_SRCO_R_U;
    static const G4double y_QD1_SRCO_R_D = y_QD1_SRCO_R_U;
    static const G4double z_QD1_Al_R_D = z_QD1_Al_R_U;
    static const G4double x_QD1_Al_R_D = -x_QD1_Al_R_U;
    static const G4double y_QD1_Al_R_D = y_QD1_Al_R_U;

    static const G4double z_QD1_SRCO_L_U = -z_QD1_SRCO_R_U;
    static const G4double x_QD1_SRCO_L_U = x_QD1_SRCO_R_U;
    static const G4double y_QD1_SRCO_L_U = y_QD1_SRCO_R_U;
    static const G4double z_QD1_Al_L_U = -z_QD1_Al_R_U;
    static const G4double x_QD1_Al_L_U = x_QD1_Al_R_U;
    static const G4double y_QD1_Al_L_U = y_QD1_Al_R_U;

    static const G4double z_QD1_SRCO_L_D = z_QD1_SRCO_L_U;
    static const G4double x_QD1_SRCO_L_D = -x_QD1_SRCO_L_U;
    static const G4double y_QD1_SRCO_L_D = y_QD1_SRCO_L_U;
    static const G4double z_QD1_Al_L_D = z_QD1_Al_L_U;
    static const G4double x_QD1_Al_L_D = -x_QD1_Al_L_U;
    static const G4double y_QD1_Al_L_D = y_QD1_Al_L_U;

       //QD1--QF1--NEW---------------------------
       static const G4double length_QD1_new_Al = 0.5;    //cm
       static const G4double x_QD1_new_Al_R = RotXoldP(z_QD1_SRCO_R_U,x_QD1_SRCO_R_U,-(length_QD1_SRCO/2 + length_QD1_new_Al/2),0.0);
       static const G4double y_QD1_new_Al_R = 0.0;       //cm
       static const G4double z_QD1_new_Al_R = RotZoldP(z_QD1_SRCO_R_U,x_QD1_SRCO_R_U,-(length_QD1_SRCO/2 + length_QD1_new_Al/2),0.0);

       static const G4double x_QD1_new_Al_L = RotXoldP(z_QD1_SRCO_R_U,x_QD1_SRCO_R_U,(length_QD1_SRCO/2 + length_QD1_new_Al/2),0.0);
       static const G4double y_QD1_new_Al_L = 0.0;       //cm
       static const G4double z_QD1_new_Al_L = RotZoldP(z_QD1_SRCO_R_U,x_QD1_SRCO_R_U,(length_QD1_SRCO/2 + length_QD1_new_Al/2),0.0);

    //---max
    static const G4double z_maxAxis_QD1_SRCO_R_U = z_QD1_SRCO_R_U + length_QD1_SRCO/2*cos4_07;
    static const G4double x_maxAxis_QD1_SRCO_R_U = x_QD1_SRCO_R_U + length_QD1_SRCO/2*sin4_07;
    static const G4double y_maxAxis_QD1_SRCO_R_U = 0.0;
    static const G4double z_maxAxis_QD1_Al_R_U = z_QD1_Al_R_U + length_QD1_Al/2*cos4_07;
    static const G4double x_maxAxis_QD1_Al_R_U = x_QD1_Al_R_U + length_QD1_Al/2*sin4_07;
    static const G4double y_maxAxis_QD1_Al_R_U = 0.0;  

    static const G4double z_maxAxis_QD1_SRCO_R_D = z_maxAxis_QD1_SRCO_R_U;
    static const G4double x_maxAxis_QD1_SRCO_R_D = -x_maxAxis_QD1_SRCO_R_U;
    static const G4double y_maxAxis_QD1_SRCO_R_D = y_maxAxis_QD1_SRCO_R_U;
    static const G4double z_maxAxis_QD1_Al_R_D = z_maxAxis_QD1_Al_R_U;
    static const G4double x_maxAxis_QD1_Al_R_D = -x_maxAxis_QD1_Al_R_U;
    static const G4double y_maxAxis_QD1_Al_R_D = y_maxAxis_QD1_Al_R_U;

    static const G4double z_maxAxis_QD1_SRCO_L_U = -z_maxAxis_QD1_SRCO_R_U;
    static const G4double x_maxAxis_QD1_SRCO_L_U = x_maxAxis_QD1_SRCO_R_U;
    static const G4double y_maxAxis_QD1_SRCO_L_U = y_maxAxis_QD1_SRCO_R_U;
    static const G4double z_maxAxis_QD1_Al_L_U = -z_maxAxis_QD1_Al_R_U;
    static const G4double x_maxAxis_QD1_Al_L_U = x_maxAxis_QD1_Al_R_U;
    static const G4double y_maxAxis_QD1_Al_L_U = y_maxAxis_QD1_Al_R_U;

    static const G4double z_maxAxis_QD1_SRCO_L_D = z_maxAxis_QD1_SRCO_L_U;
    static const G4double x_maxAxis_QD1_SRCO_L_D = -x_maxAxis_QD1_SRCO_L_U;
    static const G4double y_maxAxis_QD1_SRCO_L_D = y_maxAxis_QD1_SRCO_L_U;
    static const G4double z_maxAxis_QD1_Al_L_D = z_maxAxis_QD1_Al_L_U;
    static const G4double x_maxAxis_QD1_Al_L_D = -x_maxAxis_QD1_Al_L_U;
    static const G4double y_maxAxis_QD1_Al_L_D = y_maxAxis_QD1_Al_L_U;

    //---min
    static const G4double z_minAxis_QD1_SRCO_R_U = z_QD1_SRCO_R_U - length_QD1_SRCO/2*cos4_07;
    static const G4double x_minAxis_QD1_SRCO_R_U = x_QD1_SRCO_R_U - length_QD1_SRCO/2*sin4_07;
    static const G4double y_minAxis_QD1_SRCO_R_U = 0.0;
    static const G4double z_minAxis_QD1_Al_R_U = z_QD1_Al_R_U - length_QD1_Al/2*cos4_07;
    static const G4double x_minAxis_QD1_Al_R_U = x_QD1_Al_R_U - length_QD1_Al/2*sin4_07;
    static const G4double y_minAxis_QD1_Al_R_U = 0.0;  

    static const G4double z_minAxis_QD1_SRCO_R_D = z_minAxis_QD1_SRCO_R_U;
    static const G4double x_minAxis_QD1_SRCO_R_D = -x_minAxis_QD1_SRCO_R_U;
    static const G4double y_minAxis_QD1_SRCO_R_D = y_minAxis_QD1_SRCO_R_U;
    static const G4double z_minAxis_QD1_Al_R_D = z_minAxis_QD1_Al_R_U;
    static const G4double x_minAxis_QD1_Al_R_D = -x_minAxis_QD1_Al_R_U;
    static const G4double y_minAxis_QD1_Al_R_D = y_minAxis_QD1_Al_R_U;

    static const G4double z_minAxis_QD1_SRCO_L_U = -z_minAxis_QD1_SRCO_R_U;
    static const G4double x_minAxis_QD1_SRCO_L_U = x_minAxis_QD1_SRCO_R_U;
    static const G4double y_minAxis_QD1_SRCO_L_U = y_minAxis_QD1_SRCO_R_U;
    static const G4double z_minAxis_QD1_Al_L_U = -z_minAxis_QD1_Al_R_U;
    static const G4double x_minAxis_QD1_Al_L_U = x_minAxis_QD1_Al_R_U;
    static const G4double y_minAxis_QD1_Al_L_U = y_minAxis_QD1_Al_R_U;

    static const G4double z_minAxis_QD1_SRCO_L_D = z_minAxis_QD1_SRCO_L_U;
    static const G4double x_minAxis_QD1_SRCO_L_D = -x_minAxis_QD1_SRCO_L_U;
    static const G4double y_minAxis_QD1_SRCO_L_D = y_minAxis_QD1_SRCO_L_U;
    static const G4double z_minAxis_QD1_Al_L_D = z_minAxis_QD1_Al_L_U;
    static const G4double x_minAxis_QD1_Al_L_D = -x_minAxis_QD1_Al_L_U;
    static const G4double y_minAxis_QD1_Al_L_D = y_minAxis_QD1_Al_L_U;

    //---max and min of the corners
    //R U
    static const G4double z_max_QD1_SRCO_R_U = z_maxAxis_QD1_SRCO_R_U + innerRadius_QD1*sin4_07;
    static const G4double z_max_QD1_Al_R_U = z_maxAxis_QD1_Al_R_U + innerRadius_QD1*sin4_07;
    static const G4double z_min_QD1_SRCO_R_U = z_minAxis_QD1_SRCO_R_U - innerRadius_QD1*sin4_07;
    static const G4double z_min_QD1_Al_R_U = z_minAxis_QD1_Al_R_U - innerRadius_QD1*sin4_07;

    static const G4double x_max_QD1_SRCO_R_U = x_maxAxis_QD1_SRCO_R_U + innerRadius_QD1*cos4_07;
    static const G4double x_max_QD1_Al_R_U = x_maxAxis_QD1_Al_R_U + innerRadius_QD1*cos4_07;
    static const G4double x_min_QD1_SRCO_R_U = x_minAxis_QD1_SRCO_R_U - innerRadius_QD1*cos4_07;
    static const G4double x_min_QD1_Al_R_U = x_minAxis_QD1_Al_R_U - innerRadius_QD1*cos4_07;

    static const G4double y_max_QD1_SRCO_R_U = innerRadius_QD1;
    static const G4double y_max_QD1_Al_R_U = innerRadius_QD1;
    static const G4double y_min_QD1_SRCO_R_U = -innerRadius_QD1;
    static const G4double y_min_QD1_Al_R_U =-innerRadius_QD1;
    
    //R D
    static const G4double z_max_QD1_SRCO_R_D = z_max_QD1_SRCO_R_U;
    static const G4double z_max_QD1_Al_R_D = z_max_QD1_Al_R_U;
    static const G4double z_min_QD1_SRCO_R_D = z_min_QD1_SRCO_R_U;
    static const G4double z_min_QD1_Al_R_D = z_min_QD1_Al_R_U;
 
    static const G4double x_max_QD1_SRCO_R_D = -x_max_QD1_SRCO_R_U;
    static const G4double x_max_QD1_Al_R_D = -x_max_QD1_Al_R_U;
    static const G4double x_min_QD1_SRCO_R_D = -x_min_QD1_SRCO_R_U;
    static const G4double x_min_QD1_Al_R_D = -x_min_QD1_Al_R_U;

    static const G4double y_max_QD1_SRCO_R_D = y_max_QD1_SRCO_R_U;
    static const G4double y_max_QD1_Al_R_D = y_max_QD1_Al_R_U;
    static const G4double y_min_QD1_SRCO_R_D = y_min_QD1_SRCO_R_U;
    static const G4double y_min_QD1_Al_R_D = y_min_QD1_Al_R_U;

    //L U
    static const G4double z_max_QD1_SRCO_L_U = -z_max_QD1_SRCO_R_U;
    static const G4double z_max_QD1_Al_L_U = -z_max_QD1_Al_R_U;
    static const G4double z_min_QD1_SRCO_L_U = -z_min_QD1_SRCO_R_U;
    static const G4double z_min_QD1_Al_L_U = -z_min_QD1_Al_R_U;
 
    static const G4double x_max_QD1_SRCO_L_U = x_max_QD1_SRCO_R_U;
    static const G4double x_max_QD1_Al_L_U = x_max_QD1_Al_R_U;
    static const G4double x_min_QD1_SRCO_L_U = x_min_QD1_SRCO_R_U;
    static const G4double x_min_QD1_Al_L_U = x_min_QD1_Al_R_U;

    static const G4double y_max_QD1_SRCO_L_U = y_max_QD1_SRCO_R_U;
    static const G4double y_max_QD1_Al_L_U = y_max_QD1_Al_R_U;
    static const G4double y_min_QD1_SRCO_L_U = y_min_QD1_SRCO_R_U;
    static const G4double y_min_QD1_Al_L_U = y_min_QD1_Al_R_U;

    //L D
    static const G4double z_max_QD1_SRCO_L_D = -z_max_QD1_SRCO_R_U;
    static const G4double z_max_QD1_Al_L_D = -z_max_QD1_Al_R_U;
    static const G4double z_min_QD1_SRCO_L_D = -z_min_QD1_SRCO_R_U;
    static const G4double z_min_QD1_Al_L_D = -z_min_QD1_Al_R_U;
 
    static const G4double x_max_QD1_SRCO_L_D = -x_max_QD1_SRCO_R_U;
    static const G4double x_max_QD1_Al_L_D = -x_max_QD1_Al_R_U;
    static const G4double x_min_QD1_SRCO_L_D = -x_min_QD1_SRCO_R_U;
    static const G4double x_min_QD1_Al_L_D = -x_min_QD1_Al_R_U;

    static const G4double y_max_QD1_SRCO_L_D = y_max_QD1_SRCO_R_U;
    static const G4double y_max_QD1_Al_L_D = y_max_QD1_Al_R_U;
    static const G4double y_min_QD1_SRCO_L_D = y_min_QD1_SRCO_R_U;
    static const G4double y_min_QD1_Al_L_D = y_min_QD1_Al_R_U;

    //min and max for (Al+SmCo) along Axis 
    //R U 
    static const G4double z_maxAxis_QD1_R_U = z_maxAxis_QD1_SRCO_R_U;
    static const G4double z_minAxis_QD1_R_U = z_minAxis_QD1_Al_R_U;

    static const G4double x_maxAxis_QD1_R_U = x_maxAxis_QD1_SRCO_R_U;
    static const G4double x_minAxis_QD1_R_U = x_minAxis_QD1_Al_R_U;

    static const G4double y_maxAxis_QD1_R_U = innerRadius_QD1;
    static const G4double y_minAxis_QD1_R_U =-innerRadius_QD1;

    //R D
    static const G4double z_maxAxis_QD1_R_D = z_maxAxis_QD1_SRCO_R_U;
    static const G4double z_minAxis_QD1_R_D = z_minAxis_QD1_Al_R_U;

    static const G4double x_maxAxis_QD1_R_D = -x_maxAxis_QD1_SRCO_R_U;
    static const G4double x_minAxis_QD1_R_D = -x_minAxis_QD1_Al_R_U;

    static const G4double y_maxAxis_QD1_R_D = innerRadius_QD1;
    static const G4double y_minAxis_QD1_R_D =-innerRadius_QD1;

    //L U
    static const G4double z_maxAxis_QD1_L_U = -z_maxAxis_QD1_SRCO_R_U;
    static const G4double z_minAxis_QD1_L_U = -z_minAxis_QD1_Al_R_U;

    static const G4double x_maxAxis_QD1_L_U = x_maxAxis_QD1_SRCO_R_U;
    static const G4double x_minAxis_QD1_L_U = x_minAxis_QD1_Al_R_U;

    static const G4double y_maxAxis_QD1_L_U = innerRadius_QD1;
    static const G4double y_minAxis_QD1_L_U =-innerRadius_QD1;

    //L D
    static const G4double z_maxAxis_QD1_L_D = -z_maxAxis_QD1_SRCO_R_U;
    static const G4double z_minAxis_QD1_L_D = -z_minAxis_QD1_Al_R_U;

    static const G4double x_maxAxis_QD1_L_D = -x_maxAxis_QD1_SRCO_R_U;
    static const G4double x_minAxis_QD1_L_D = -x_minAxis_QD1_Al_R_U;

    static const G4double y_maxAxis_QD1_L_D = innerRadius_QD1;
    static const G4double y_minAxis_QD1_L_D =-innerRadius_QD1;

    //(Al+SmCo)
    //R U 
    static const G4double z_max_QD1_R_U = z_max_QD1_SRCO_R_U;
    static const G4double z_min_QD1_R_U = z_min_QD1_Al_R_U;

    static const G4double x_max_QD1_R_U = x_max_QD1_SRCO_R_U;
    static const G4double x_min_QD1_R_U = x_min_QD1_Al_R_U;

    static const G4double y_max_QD1_R_U = innerRadius_QD1;
    static const G4double y_min_QD1_R_U =-innerRadius_QD1;

    //R D
    static const G4double z_max_QD1_R_D = z_max_QD1_SRCO_R_U;
    static const G4double z_min_QD1_R_D = z_min_QD1_Al_R_U;

    static const G4double x_max_QD1_R_D = -x_max_QD1_SRCO_R_U;
    static const G4double x_min_QD1_R_D = -x_min_QD1_Al_R_U;

    static const G4double y_max_QD1_R_D = innerRadius_QD1;
    static const G4double y_min_QD1_R_D =-innerRadius_QD1;

    //L U
    static const G4double z_max_QD1_L_U = -z_max_QD1_SRCO_R_U;
    static const G4double z_min_QD1_L_U = -z_min_QD1_Al_R_U;

    static const G4double x_max_QD1_L_U = x_max_QD1_SRCO_R_U;
    static const G4double x_min_QD1_L_U = x_min_QD1_Al_R_U;

    static const G4double y_max_QD1_L_U = innerRadius_QD1;
    static const G4double y_min_QD1_L_U =-innerRadius_QD1;

    //L D
    static const G4double z_max_QD1_L_D = -z_max_QD1_SRCO_R_U;
    static const G4double z_min_QD1_L_D = -z_min_QD1_Al_R_U;

    static const G4double x_max_QD1_L_D = -x_max_QD1_SRCO_R_U;
    static const G4double x_min_QD1_L_D = -x_min_QD1_Al_R_U;

    static const G4double y_max_QD1_L_D = innerRadius_QD1;
    static const G4double y_min_QD1_L_D =-innerRadius_QD1;  

   //-----------------------------------------------------------------

    //-----------------------------------------------------------------
    // SOYUZ shielding
    //-----------------------------------------------------------------

    //Tube part 1
    static const G4double length_SOY_T1 = 0.5;        //cm       
    static const G4double innerRadius_SOY_T1 = 2.95;  //cm
    static const G4double outerRadius_SOY_T1 = 3.975; //cm

    static const G4double x_SOY_T1_R = 0.;          //cm       
    static const G4double y_SOY_T1_R = 0.;          //cm       
    static const G4double z_SOY_T1_R = 28.3;        //cm       

    static const G4double x_SOY_T1_L = 0.;          //cm       
    static const G4double y_SOY_T1_L = 0.;          //cm       
    static const G4double z_SOY_T1_L = -z_SOY_T1_R; //cm       

    //Tube part 2
    static const G4double length_SOY_T2 = 1.1;       //cm       
    static const G4double innerRadius_SOY_T2 = 2.95; //cm
    static const G4double outerRadius_SOY_T2 = 4.5;  //cm

    static const G4double x_SOY_T2_R = 0.;          //cm       
    static const G4double y_SOY_T2_R = 0.;          //cm       
    static const G4double z_SOY_T2_R = 27.5;        //cm       

    static const G4double x_SOY_T2_L = 0.;          //cm       
    static const G4double y_SOY_T2_L = 0.;          //cm       
    static const G4double z_SOY_T2_L = -z_SOY_T2_R; //cm       

    //Cone part 3
    static const G4double length_SOY_Co3 = 1.1;              //cm       
    static const G4double innerRadius1_SOY_Co3 = 6.52;       //cm
    static const G4double outerRadius1_SOY_Co3 = 8.56718682; //cm
    static const G4double innerRadius2_SOY_Co3 = 6.52;       //cm
    static const G4double outerRadius2_SOY_Co3 = 8.93;       //cm

    static const G4double x_SOY_Co3_R = 0.;            //cm       
    static const G4double y_SOY_Co3_R = 0.;            //cm       
    static const G4double z_SOY_Co3_R = 24.95 + 3.9/2 + length_SOY_Co3/2; //cm

    static const G4double x_SOY_Co3_L = 0.;           //cm       
    static const G4double y_SOY_Co3_L = 0.;           //cm       
    static const G4double z_SOY_Co3_L = -z_SOY_Co3_R; //cm       

    //Cone part 4
    static const G4double length_SOY_Co4 = 3.9;              //cm       
    static const G4double innerRadius1_SOY_Co4 = 5.675;      //cm
    static const G4double outerRadius1_SOY_Co4 = 7.3;        //cm
    static const G4double innerRadius2_SOY_Co4 = 5.675;      //cm
    static const G4double outerRadius2_SOY_Co4 = 8.56718682; //cm

    static const G4double x_SOY_Co4_R = 0.;            //cm       
    static const G4double y_SOY_Co4_R = 0.;            //cm       
    static const G4double z_SOY_Co4_R = 24.95;         //cm       

    static const G4double x_SOY_Co4_L = 0.;            //cm       
    static const G4double y_SOY_Co4_L = 0.;            //cm       
    static const G4double z_SOY_Co4_L = -z_SOY_Co4_R;  //cm       

    //Tube part 5
    static const G4double length_SOY_T5 = 1.1;       //cm       
    static const G4double innerRadius_SOY_T5 = 2.95; //cm
    static const G4double outerRadius_SOY_T5 = 3.6;  //cm

    static const G4double x_SOY_T5_R = 0.;          //cm       
    static const G4double y_SOY_T5_R = 0.;          //cm       
    static const G4double z_SOY_T5_R = 21.85;       //cm       

    static const G4double x_SOY_T5_L = 0.;          //cm       
    static const G4double y_SOY_T5_L = 0.;          //cm       
    static const G4double z_SOY_T5_L = -z_SOY_T5_R; //cm       

    //Tube part 6
    static const G4double length_SOY_T6 = 6.27570634;//cm       
    static const G4double innerRadius_SOY_T6 = 2.95; //cm
    static const G4double outerRadius_SOY_T6 = 4.9;  //cm

    static const G4double x_SOY_T6_R = 0.;          //cm       
    static const G4double y_SOY_T6_R = 0.;          //cm       
    static const G4double z_SOY_T6_R = 18.16214668; //cm       

    static const G4double x_SOY_T6_L = 0.;          //cm       
    static const G4double y_SOY_T6_L = 0.;          //cm       
    static const G4double z_SOY_T6_L = -z_SOY_T6_R; //cm       

    //Cone part 7
    static const G4double length_SOY_Co7 = 4.92429366; //cm       
    static const G4double innerRadius1_SOY_Co7 = 2.95; //cm
    static const G4double outerRadius1_SOY_Co7 = 3.3;  //cm
    static const G4double innerRadius2_SOY_Co7 = 2.95; //cm
    static const G4double outerRadius2_SOY_Co7 = 4.9;  //cm

    static const G4double x_SOY_Co7_R = 0.;         //cm       
    static const G4double y_SOY_Co7_R = 0.;         //cm       
    static const G4double z_SOY_Co7_R = 12.5621468; //cm       

    static const G4double x_SOY_Co7_L = 0.;           //cm       
    static const G4double y_SOY_Co7_L = 0.;           //cm       
    static const G4double z_SOY_Co7_L = -z_SOY_Co7_R; //cm       

    //---------------------------------------------------------------
    // Shielding in the back of the calo module 
    //---------------------------------------------------------------

    static const G4double ZBEAM = -32.5 - 0.5;

    //box 1
    static const G4double lengthBoxShield1X = 29.;
    static const G4double lengthBoxShield1Y = 70.;
    static const G4double lengthBoxShield1Z = 5.;

    static const G4double x_BoxShield1_R = 20.1;
    static const G4double y_BoxShield1_R = 0.;
    static const G4double z_BoxShield1_R = 25.2 - ZBEAM;

    static const G4double x_BoxShield1_L = x_BoxShield1_R;
    static const G4double y_BoxShield1_L = y_BoxShield1_R;
    static const G4double z_BoxShield1_L = -z_BoxShield1_R;

    //box 2
    static const G4double lengthBoxShield2X = 29.;
    static const G4double lengthBoxShield2Y = 70.;
    static const G4double lengthBoxShield2Z = 5.;

    static const G4double x_BoxShield2_R = -22.4;
    static const G4double y_BoxShield2_R = 0.;
    static const G4double z_BoxShield2_R = 25.2 - ZBEAM;

    static const G4double x_BoxShield2_L = x_BoxShield2_R;
    static const G4double y_BoxShield2_L = y_BoxShield2_R;
    static const G4double z_BoxShield2_L = -z_BoxShield2_R;

    //box 3
    static const G4double lengthBoxShield3X = 13.5;
    static const G4double lengthBoxShield3Y = 27.6;
    static const G4double lengthBoxShield3Z = 5.;

    static const G4double x_BoxShield3_R = -1.15;
    static const G4double y_BoxShield3_R = 21.2;
    static const G4double z_BoxShield3_R = 25.2 - ZBEAM;

    static const G4double x_BoxShield3_L = x_BoxShield3_R;
    static const G4double y_BoxShield3_L = y_BoxShield3_R;
    static const G4double z_BoxShield3_L = -z_BoxShield3_R;

    //box 4
    static const G4double lengthBoxShield4X = 13.5;
    static const G4double lengthBoxShield4Y = 27.6;
    static const G4double lengthBoxShield4Z = 5.;

    static const G4double x_BoxShield4_R = -1.15;
    static const G4double y_BoxShield4_R = -21.2;
    static const G4double z_BoxShield4_R = 25.2 - ZBEAM;

    static const G4double x_BoxShield4_L = x_BoxShield4_R;
    static const G4double y_BoxShield4_L = y_BoxShield4_R;
    static const G4double z_BoxShield4_L = -z_BoxShield4_R;

    //-------------------------------------------------------------------
    // photon detector
    //-------------------------------------------------------------------


    //-------------------------------------------------------------------
    //Photon Detector with Benoit corection 
    // Photon detector placed on the left of the IP.
    // * Plastic box containing the crystals:
    //   Plastic box  -3.20000005   0.  -190.

    //  Coordinates (in cm) in the calo frame. To go to the
    //  frame centered at the IP, subtract 33 cm to the Z coordinate
    // * The 4 iron boxes containing in which the crystals are wrapped
    //  Iron box 1 -0.200000003 0.  -4.52999973
    //  Iron box 2 -0.200000003 0.  -1.50999999
    //  Iron  box 3 -0.200000003 0.   1.50999999
    //  Iron box 4  -0.200000003 0.   4.52999973

    static const G4double x_PlasticBox_R =-3.20000005;
    static const G4double y_PlasticBox_R = 0.0;
    static const G4double z_PlasticBox_R = 190 + ZBEAM;

    static const G4double x_PlasticBox_L = x_PlasticBox_R;
    static const G4double y_PlasticBox_L = y_PlasticBox_R;
    static const G4double z_PlasticBox_L = -z_PlasticBox_R;

    //  Coordinates in the frame attached to the plastic box
    static const G4double x_Box1Pl = -0.200000003;
    static const G4double y_Box1Pl = 0.0;
    static const G4double z_Box1Pl = -4.52999973;
    //2
    static const G4double x_Box2Pl = x_Box1Pl;
    static const G4double y_Box2Pl = 0.0;
    static const G4double z_Box2Pl = -1.50999999;
    //3
    static const G4double x_Box3Pl = x_Box1Pl;
    static const G4double y_Box3Pl = 0.0;
    static const G4double z_Box3Pl = 1.50999999; 
    //4
    static const G4double x_Box4Pl = x_Box1Pl;
    static const G4double y_Box4Pl = 0.0;
    static const G4double z_Box4Pl = 4.52999973;


    // * Lead bricks (in the same frame as the plastic box, ie the
    //    calo frame explained above)

    //  Brick 1  -0.352614641   0.  -180.838989 //forward
    //  Brick 2  -1.678431150   0.  -199.471878 //Backward
    //  Brick 3   1.597869630   0.  -190.341385 //central
    //  Brick 4  -5.603922370   0.  -189.828949 //litle

    // Forward brick
    static const G4double x_PbBoxForPhot = -0.352614641;
    static const G4double y_PbBoxForPhot = 0.0;
    static const G4double z_PbBoxForPhot = 180.838989 + ZBEAM;

    // Backward brick
    static const G4double x_PbBoxBackPhot = -1.678431150;
    static const G4double y_PbBoxBackPhot = 0.0;
    static const G4double z_PbBoxBackPhot = 199.471878 + ZBEAM;
    
    // Central brick    
    static const G4double x_PbBoxCenPhot = 1.597869630;
    static const G4double y_PbBoxCenPhot = 0.0;
    static const G4double z_PbBoxCenPhot = 190.341385 + ZBEAM;

    // * Window
    //  Window  -3.59441853   0.  -180.608322
    
    //small cylindrical window in frame of IP
    static const G4double x_WinPhot = -3.59441853;
    static const G4double y_WinPhot = 0.0;
    static const G4double z_WinPhot = 180.608322 + ZBEAM;

    //small cylindrical window in frame of Forward brick
    static const G4double x_WinPhotN = -RotXp(z_PbBoxForPhot,x_PbBoxForPhot) + RotXp(z_WinPhot,x_WinPhot);
    static const G4double y_WinPhotN = 0.0;
    static const G4double z_WinPhotN = 0.0;    


    //-------------------------------------------------------------------

    //my photon detector
    static const G4double thicknessSkinIron = 0.01;   //cm
    static const G4double thicknessSkinPlastic = 0.5; //cm

    static const G4double lengthX_PbWOBox = 3.;
    static const G4double lengthY_PbWOBox = 11.;
    static const G4double lengthZ_PbWOBox = 3.;

    static const G4double lengthX_IronBox = thicknessSkinIron*2 + lengthX_PbWOBox;
    static const G4double lengthY_IronBox = thicknessSkinIron*2 + lengthY_PbWOBox;
    static const G4double lengthZ_IronBox = thicknessSkinIron*2 + lengthZ_PbWOBox;

    static const G4double lengthX_PlasticBox = thicknessSkinPlastic*2 + thicknessSkinIron*2 + lengthX_PbWOBox;
    static const G4double lengthY_PlasticBox = thicknessSkinPlastic*2 + thicknessSkinIron*2 + lengthY_PbWOBox;
    static const G4double lengthZ_PlasticBox = thicknessSkinPlastic*2 + thicknessSkinIron*8 + lengthZ_PbWOBox*4;


    /* have to be comented if Benoit corection is applied 
    static const G4double x_PlasticBox_R =-3.2;
    static const G4double y_PlasticBox_R = 0.0;
    static const G4double z_PlasticBox_R = 190 + ZBEAM;

    static const G4double x_PlasticBox_L = x_PlasticBox_R;
    static const G4double y_PlasticBox_L = y_PlasticBox_R;
    static const G4double z_PlasticBox_L = -z_PlasticBox_R;
    */

    //distance between beampipe and plastic box center 
    static const G4double ptmp1 = outerRadius_Tube1/sin(D_2_R*(90-4.07));
    static const G4double ptmp2 = (z_Tube5_C_R_D - z_PlasticBox_R)*sin4_07;
    static const G4double dlength_PlasticBox = x_PlasticBox_R - ( x_Tube5_C_R_D + ptmp1 + ptmp2)*cos4_07;
   

    //Boxs in world frame
    //1
    static const G4double x_Box1_R = x_PlasticBox_R + lengthZ_IronBox*3./2.*sin4_07;
    static const G4double y_Box1_R = 0.0;
    static const G4double z_Box1_R = z_PlasticBox_R - lengthZ_IronBox*3./2.*cos4_07;
    //2
    static const G4double x_Box2_R = x_PlasticBox_R + lengthZ_IronBox/2.*sin4_07;
    static const G4double y_Box2_R = 0.0;
    static const G4double z_Box2_R = z_PlasticBox_R - lengthZ_IronBox/2.*cos4_07;
    //3
    static const G4double x_Box3_R = x_PlasticBox_R - lengthZ_IronBox/2.*sin4_07;
    static const G4double y_Box3_R = 0.0;
    static const G4double z_Box3_R = z_PlasticBox_R + lengthZ_IronBox/2.*cos4_07; 
    //4
    static const G4double x_Box4_R = x_PlasticBox_R - lengthZ_IronBox*3./2.*sin4_07;
    static const G4double y_Box4_R = 0.0;
    static const G4double z_Box4_R = z_PlasticBox_R + lengthZ_IronBox*3./2.*cos4_07;

    //1 in world frame
    static const G4double x_Box1_L = x_Box1_R;
    static const G4double y_Box1_L = 0.0;
    static const G4double z_Box1_L = -z_Box1_R;
    //2
    static const G4double x_Box2_L = x_Box2_R;
    static const G4double y_Box2_L = 0.0;
    static const G4double z_Box2_L = -z_Box2_R; 
    //3
    static const G4double x_Box3_L = x_Box3_R;
    static const G4double y_Box3_L = 0.0;
    static const G4double z_Box3_L =-z_Box3_R; 
    //4
    static const G4double x_Box4_L = x_Box4_R;
    static const G4double y_Box4_L = 0.0;
    static const G4double z_Box4_L =-z_Box4_R;

    /*  have to be comented if Benoit corection is applied
    //Boxs in plastic box frame
    //1
    static const G4double x_Box1Pl = 0.0;
    static const G4double y_Box1Pl = 0.0;
    static const G4double z_Box1Pl = -(lengthZ_PlasticBox - 2*thicknessSkinPlastic)/8*3;
    //2
    static const G4double x_Box2Pl = 0.0;
    static const G4double y_Box2Pl = 0.0;
    static const G4double z_Box2Pl = -(lengthZ_PlasticBox - 2*thicknessSkinPlastic)/8;
    //3
    static const G4double x_Box3Pl = 0.0;
    static const G4double y_Box3Pl = 0.0;
    static const G4double z_Box3Pl = (lengthZ_PlasticBox - 2*thicknessSkinPlastic)/8; 
    //4
    static const G4double x_Box4Pl = 0.0;
    static const G4double y_Box4Pl = 0.0;
    static const G4double z_Box4Pl = (lengthZ_PlasticBox - 2*thicknessSkinPlastic)/8*3;
    //-------------------------------------------------------------------
    */

    //-------------------------------------------------------------------
    // Shielding of the photon detector
    // 3 lead brick
    // 1 small cylindrical window
    //-------------------------------------------------------------------

    // Forward and backward bricks    
    static const G4double lengthX_PbBoxPhot = 10.;
    static const G4double lengthY_PbBoxPhot = 20.;
    static const G4double lengthZ_PbBoxPhot = 5.;

    static const G4double zN_PlasticBox = cos4_07*z_PlasticBox_R - sin4_07*x_PlasticBox_R;
    static const G4double xN_PlasticBox = sin4_07*z_PlasticBox_R + cos4_07*x_PlasticBox_R;

    static const G4double zNFor_PlasticBox = zN_PlasticBox - lengthZ_PlasticBox/2 - lengthZ_PbBoxPhot/2;
    static const G4double xNFor_PlasticBox = xN_PlasticBox + (lengthX_PbBoxPhot/2-dlength_PlasticBox);

    static const G4double zNBack_PlasticBox = zN_PlasticBox + lengthZ_PlasticBox/2 + lengthZ_PbBoxPhot/2;
    static const G4double xNBack_PlasticBox = xN_PlasticBox + (lengthX_PbBoxPhot/2-dlength_PlasticBox);

    /*  have to be comented if Benoit corection is applied
    // Forward brick
    static const G4double x_PbBoxForPhot = -sin4_07*zNFor_PlasticBox + cos4_07*xNFor_PlasticBox;
    static const G4double y_PbBoxForPhot = 0.;
    static const G4double z_PbBoxForPhot = cos4_07*zNFor_PlasticBox + sin4_07*xNFor_PlasticBox;
   
    // Backward brick
    static const G4double x_PbBoxBackPhot = -sin4_07*zNBack_PlasticBox + cos4_07*xNBack_PlasticBox;
    static const G4double y_PbBoxBackPhot = 0.;
    static const G4double z_PbBoxBackPhot = cos4_07*zNBack_PlasticBox + sin4_07*xNBack_PlasticBox;
    */

    // Central brick    
    static const G4double lengthX_PbBoxCenPhot = lengthX_PbBoxPhot - dlength_PlasticBox - lengthX_PlasticBox/2 ;
    static const G4double lengthY_PbBoxCenPhot = 20.;
    static const G4double lengthZ_PbBoxCenPhot = lengthZ_PlasticBox;

    /*  have to be comented if Benoit corection is applied
    static const G4double x_PbBoxCenPhot = x_PlasticBox_R + (lengthX_PlasticBox/2 + lengthX_PbBoxCenPhot/2)*cos4_07;
    static const G4double y_PbBoxCenPhot = 0.0;
    static const G4double z_PbBoxCenPhot = z_PlasticBox_R + (lengthX_PlasticBox/2 + lengthX_PbBoxCenPhot/2)*sin4_07;
    */

    //small cylindrical window
    static const G4double innerRadiusWinPhot = 0.0;
    static const G4double outerRadiusWinPhot = 1.5/2;
    static const G4double length_WinPhot = 5.0;

    static const G4double zNn_WinPhot = zN_PlasticBox - lengthZ_PlasticBox/2 - lengthZ_PbBoxPhot/2;
    static const G4double xNn_WinPhot = xN_PlasticBox + (lengthX_PbBoxPhot/2 -lengthX_PlasticBox/2-0.8- 0.0*3.25 -dlength_PlasticBox);

    /*  have to be comented if Benoit corection is applied
    static const G4double x_WinPhot = -sin4_07*zNn_WinPhot + cos4_07*xNn_WinPhot;
    static const G4double y_WinPhot = 0.;
    static const G4double z_WinPhot = cos4_07*zNn_WinPhot + sin4_07*xNn_WinPhot;
    */

    //-------------------------------------------------------------------

    //-------------------------------------------
    //Sensitive detectors with class SD!!! more precise
    //-------------------------------------------

    static const G4double z_SD1_L = RotZoldP(-z_WinPhot,x_WinPhot,-lengthZ_PbBoxPhot/2,0.);
    static const G4double x_SD1_L = RotXoldP(-z_WinPhot,x_WinPhot,-lengthZ_PbBoxPhot/2,0.);
    //-------------------------------------------



    //-------------------------------------------------------------------
    //Checking of the geometry !!!!!!!!!!!!!!!
    //-------------------------------------------------------------------

    static const G4double x_Sp1 = x_Tube4_L_U + length_Tube4/2*sin4_07 + (outerRadius_Tube1+innerRadius_Tube1)/2*cos4_07;  
    static const G4double y_Sp1 = 0.;
    static const G4double z_Sp1 = z_Tube4_L_U - length_Tube4/2*cos4_07 + (outerRadius_Tube1+innerRadius_Tube1)/2*sin4_07;

    static const G4double x_Sp2 = x_Tube4_L_U + length_Tube4/2*sin4_07 - (outerRadius_Tube1+innerRadius_Tube1)/2*cos4_07;  
    static const G4double y_Sp2 = 0.;
    static const G4double z_Sp2 = z_Tube4_L_U - length_Tube4/2*cos4_07 - (outerRadius_Tube1+innerRadius_Tube1)/2*sin4_07;

    static const G4double x_Sp3 = -x_Sp1; 
    static const G4double y_Sp3 = 0.;
    static const G4double z_Sp3 = z_Sp1; 

    static const G4double x_Sp4 = -x_Sp2;
    static const G4double y_Sp4 = 0.;
    static const G4double z_Sp4 = z_Sp2; 

    static const G4double x_Sp5 = x_Tube4_L_U - length_Tube4/2*sin4_07 + (outerRadius_Tube1+innerRadius_Tube1)/2*cos4_07;
    static const G4double y_Sp5 = 0.;
    static const G4double z_Sp5 = z_Tube4_L_U + length_Tube4/2*cos4_07 + (outerRadius_Tube1+innerRadius_Tube1)/2*sin4_07;

    static const G4double x_Sp6 = 0.;
    static const G4double y_Sp6 = 0.;
    static const G4double z_Sp6 = z_Tube3_Center_TR1_L -  dz_Tube3_TR1/2.;

    static const G4double x_Sp7 = x_Tube4_L_D + length_Tube4/2*sin4_07 - (outerRadius_Tube1+innerRadius_Tube1)/2*cos4_07;
    static const G4double y_Sp7 = 0.;
    static const G4double z_Sp7 = z_Tube4_L_U + length_Tube4/2*cos4_07 - (outerRadius_Tube1+innerRadius_Tube1)/2*sin4_07;

    //-----Sp8------
    static const G4double xtmp = x_Tube3_Center_TU_L_U + length_Tube3_TU/2.*sin7_9 - outerradius_Tube3_TU*cos7_9; 
    static const G4double ztmp = z_Tube3_Center_TU_L_U - length_Tube3_TU/2.*cos7_9 - outerradius_Tube3_TU*sin7_9;
    static const G4double x_Sp8 = 0.;
    static const G4double y_Sp8 = 0.;
    static const G4double z_Sp8 = ztmp + xtmp/tan7_9;

    static const G4double x_Sp9 = dx1_Tube3_TR1/2.;
    static const G4double y_Sp9 = 0.;
    static const G4double z_Sp9 = z_Tube3_Center_TR1_L + dz_Tube3_TR1/2.;

    static const G4double x_Sp10 = -x_Sp9;
    static const G4double y_Sp10 = 0.;
    static const G4double z_Sp10 = z_Sp9;

    static const G4double x_Sp11 = 0.;
    static const G4double y_Sp11 = 0.;
    static const G4double z_Sp11 = z_Tube2_C_L - length_Tube2_C/2 ;

    static const G4double x_Sp12 = (outerRadius_Tube1+innerRadius_Tube1)/2;
    static const G4double y_Sp12 = 0.;
    static const G4double z_Sp12 = 0.;
 
    static const G4double x_Sp13 = -x_Sp12;
    static const G4double y_Sp13 = 0.;
    static const G4double z_Sp13 = 0.;
    
    static const G4double x_Sp14 = 0.;
    static const G4double y_Sp14 = 0.;
    static const G4double z_Sp14 = z_Tube2_C_R + length_Tube2_C/2;

    static const G4double x_Sp15 = 0.;
    static const G4double y_Sp15 = 0.;
    static const G4double z_Sp15 = length_Tube1/2 + length_Tube2_C + zlength_Tube2_E;

    static const G4double x_Sp16 = 0.;
    static const G4double y_Sp16 = 0.;
    static const G4double z_Sp16 = z_Tube3_Center_TR1_R + dz_Tube3_TR1/2.;
    //-------------------

    //left photon monitor
    static const G4double x_Sp17 = x_PbBoxBackPhot;
    static const G4double z_Sp17 = -z_PbBoxBackPhot;

    static const G4double x_Sp18 = RotXoldP(z_Sp17,x_Sp17,-lengthZ_PbBoxPhot/2,lengthX_PbBoxPhot/2);
    static const G4double z_Sp18 = RotZoldP(z_Sp17,x_Sp17,-lengthZ_PbBoxPhot/2,lengthX_PbBoxPhot/2);
    
    static const G4double x_Sp19 = RotXoldP(z_Sp17,x_Sp17,+lengthZ_PbBoxPhot/2,lengthX_PbBoxPhot/2);
    static const G4double z_Sp19 = RotZoldP(z_Sp17,x_Sp17,+lengthZ_PbBoxPhot/2,lengthX_PbBoxPhot/2);

    static const G4double x_Sp20 = RotXoldP(z_Sp17,x_Sp17,-lengthZ_PbBoxPhot/2,-lengthX_PbBoxPhot/2);
    static const G4double z_Sp20 = RotZoldP(z_Sp17,x_Sp17,-lengthZ_PbBoxPhot/2,-lengthX_PbBoxPhot/2);

    static const G4double x_Sp21 = x_PbBoxCenPhot;
    static const G4double z_Sp21 = -z_PbBoxCenPhot;

    static const G4double x_Sp22 = RotXoldP(z_Sp21,x_Sp21,lengthZ_PbBoxCenPhot/2,lengthX_PbBoxCenPhot/2);
    static const G4double z_Sp22 = RotZoldP(z_Sp21,x_Sp21,lengthZ_PbBoxCenPhot/2,lengthX_PbBoxCenPhot/2);
    
    static const G4double x_Sp24 = x_PbBoxForPhot;
    static const G4double z_Sp24 = -z_PbBoxForPhot;

    static const G4double x_Sp23 = RotXoldP(z_Sp24,x_Sp24,lengthZ_PbBoxPhot/2,lengthX_PbBoxPhot/2);
    static const G4double z_Sp23 = RotZoldP(z_Sp24,x_Sp24,lengthZ_PbBoxPhot/2,lengthX_PbBoxPhot/2);

    static const G4double x_Sp25 = RotXoldP(-z_WinPhot,x_WinPhot,length_WinPhot/2,0.0);
    static const G4double z_Sp25 = RotZoldP(-z_WinPhot,x_WinPhot,length_WinPhot/2,0.0);

    static const G4double x_Sp26 = x_Box1_R;
    static const G4double z_Sp26 = -z_Box1_R;

    //left QDF1

    static const G4double x_Sp30 = x_QD1_SRCO_R_U;
    static const G4double z_Sp30 = -z_QD1_SRCO_R_U;

    static const G4double x_Sp31 = x_QD1_Al_R_U;
    static const G4double z_Sp31 = -z_QD1_Al_R_U;

    static const G4double x_Sp27 = RotXoldM(z_Sp30,x_Sp30,-length_QD1_SRCO/2, outerRadius_QD1);
    static const G4double z_Sp27 = RotZoldM(z_Sp30,x_Sp30,-length_QD1_SRCO/2, outerRadius_QD1);

    static const G4double x_Sp28 = RotXoldM(z_Sp30,x_Sp30,length_QD1_SRCO/2, outerRadius_QD1);
    static const G4double z_Sp28 = RotZoldM(z_Sp30,x_Sp30,length_QD1_SRCO/2, outerRadius_QD1);

    static const G4double x_Sp29 = RotXoldM(z_Sp31,x_Sp31,length_QD1_Al/2, outerRadius_QD1);
    static const G4double z_Sp29 = RotZoldM(z_Sp31,x_Sp31,length_QD1_Al/2, outerRadius_QD1);

    static const G4double x_Sp32 = RotXoldM(z_Sp30,x_Sp30,-length_QD1_SRCO/2,-outerRadius_QD1);
    static const G4double z_Sp32 = RotZoldM(z_Sp30,x_Sp30,-length_QD1_SRCO/2,-outerRadius_QD1);

    static const G4double x_Sp34 = -x_Sp30;
    static const G4double z_Sp34 = z_Sp30;

    static const G4double x_Sp33 = 0.0;
    static const G4double z_Sp33 = z_Sp32 + x_Sp32/tan4_07;

    //left lead shielding(1)    
    static const G4double x_Sp35 = x_BoxShield3_R;
    static const G4double y_Sp35 = y_BoxShield3_R;
    static const G4double z_Sp35 = -z_BoxShield3_R;

    static const G4double x_Sp36 = x_Sp35 + lengthBoxShield3X/2;
    static const G4double y_Sp36 = y_Sp35;
    static const G4double z_Sp36 = z_Sp35 - lengthBoxShield3Z/2;

    static const G4double x_Sp37 = x_Sp35 + lengthBoxShield3X/2;
    static const G4double y_Sp37 = y_Sp35;
    static const G4double z_Sp37 = z_Sp35 + lengthBoxShield3Z/2;

    //left lead shielding(2)
    static const G4double x_Sp38 = x_BoxShield1_R;
    static const G4double y_Sp38 = y_BoxShield1_R;
    static const G4double z_Sp38 = -z_BoxShield1_R;

    static const G4double x_Sp39 = x_Sp38 - lengthBoxShield1X/2;
    static const G4double y_Sp39 = y_Sp38;
    static const G4double z_Sp39 = z_Sp38 - lengthBoxShield1Z/2;

    static const G4double x_Sp40 = x_Sp38 - lengthBoxShield1X/2;
    static const G4double y_Sp40 = y_Sp38;
    static const G4double z_Sp40 = z_Sp38 + lengthBoxShield1Z/2;

    static const G4double x_Sp43 = x_BoxShield2_R;
    static const G4double y_Sp43 = y_BoxShield2_R;
    static const G4double z_Sp43 = -z_BoxShield2_R;

    static const G4double x_Sp41 = x_Sp43 + lengthBoxShield2X/2;
    static const G4double y_Sp41 = y_Sp43;
    static const G4double z_Sp41 = z_Sp43 - lengthBoxShield2Z/2;

    static const G4double x_Sp42 = x_Sp43 + lengthBoxShield2X/2;
    static const G4double y_Sp42 = y_Sp43;
    static const G4double z_Sp42 = z_Sp43 + lengthBoxShield2Z/2;

    //left QD0
    static const G4double z_Sp47 = -z_QD0_T_R;

    static const G4double z_Sp48 = -z_QD0_Co_R;

    static const G4double y_Sp44 = outerRadius_QD0_T;
    static const G4double z_Sp44 = z_Sp47 - length_QD0_T/2;

    static const G4double y_Sp45 = outerRadius_QD0_T;
    static const G4double z_Sp45 = z_Sp47 + length_QD0_T/2;

    static const G4double y_Sp46 = outerRadius1_QD0_Co;
    static const G4double z_Sp46 = z_Sp48 + length_QD0_Co/2;

    //left SOYUZ

    //Cone part 7 
    static const G4double x_Sp51 = 0.0;
    static const G4double y_Sp51 = 0.0;
    static const G4double z_Sp51 = -z_SOY_Co7_R;

    static const G4double x_Sp49 = 0.0;
    static const G4double y_Sp49 = 0.0;
    static const G4double z_Sp49 = -z_SOY_Co7_R + length_SOY_Co7/2;

    static const G4double x_Sp50 = 0.0;
    static const G4double y_Sp50 = outerRadius1_SOY_Co7;
    static const G4double z_Sp50 = -z_SOY_Co7_R + length_SOY_Co7/2;

    static const G4double x_Sp52 = 0.0;
    static const G4double y_Sp52 = outerRadius2_SOY_Co7;
    static const G4double z_Sp52 = -z_SOY_Co7_R - length_SOY_Co7/2;
    //--------

    //Tube part 6
    static const G4double x_Sp53 = 0.0;
    static const G4double y_Sp53 = 0.0;
    static const G4double z_Sp53 = -z_SOY_T6_R;

    static const G4double x_Sp54 = 0.0;
    static const G4double y_Sp54 = innerRadius_SOY_T6;
    static const G4double z_Sp54 = -z_SOY_T6_R;
    //---

    //Tube part 5
    static const G4double x_Sp55 = 0.0;
    static const G4double y_Sp55 = 0.0;
    static const G4double z_Sp55 = -z_SOY_T5_R;

    static const G4double x_Sp56 = 0.0;
    static const G4double y_Sp56 = outerRadius_SOY_T5;
    static const G4double z_Sp56 = -z_SOY_T5_R;
    //----

    //ring big
    static const G4double x_Sp57 = 0.0;
    static const G4double y_Sp57 = 0.0;
    static const G4double z_Sp57 = -z_Tube1Con_R;

    //ring small
    static const G4double x_Sp59 = 0.0;
    static const G4double y_Sp59 = 0.0;
    static const G4double z_Sp59 = -z_Tube2Con_R;
    //-----

    //Cone part 4
    static const G4double x_Sp61 = 0.0;
    static const G4double y_Sp61 = 0.0;
    static const G4double z_Sp61 = -z_SOY_Co4_R;
    
    static const G4double x_Sp58 = 0.0;
    static const G4double y_Sp58 = outerRadius1_SOY_Co4;
    static const G4double z_Sp58 = -z_SOY_Co4_R + length_SOY_Co4/2;

    static const G4double x_Sp60 = 0.0;
    static const G4double y_Sp60 = innerRadius1_SOY_Co4;
    static const G4double z_Sp60 = -z_SOY_Co4_R;

    static const G4double x_Sp62 = 0.0;
    static const G4double y_Sp62 = outerRadius2_SOY_Co4;
    static const G4double z_Sp62 = -z_SOY_Co4_R - length_SOY_Co4/2;


    //Tube part 1
    static const G4double x_Sp72 = 0.0;
    static const G4double y_Sp72 = 0.0;
    static const G4double z_Sp72 = -z_SOY_T1_R;
    
    static const G4double x_Sp68 = 0.0;
    static const G4double y_Sp68 = innerRadius_SOY_T1;
    static const G4double z_Sp68 = -z_SOY_T1_R;

    static const G4double x_Sp67 = 0.0;
    static const G4double y_Sp67 = outerRadius_SOY_T1;
    static const G4double z_Sp67 = -z_SOY_T1_R;

    //Tube part 2
    static const G4double x_Sp70 = 0.0;
    static const G4double y_Sp70 = 0.0;
    static const G4double z_Sp70 = -z_SOY_T2_R;
     
    static const G4double x_Sp69 = 0.0;
    static const G4double y_Sp69 = innerRadius_SOY_T2;
    static const G4double z_Sp69 = -z_SOY_T2_R;

    static const G4double x_Sp66 = 0.0;
    static const G4double y_Sp66 = outerRadius_SOY_T2;
    static const G4double z_Sp66 = -z_SOY_T2_R;


    //Cone part 3
    static const G4double x_Sp71 = 0.0;
    static const G4double y_Sp71 = 0.0;
    static const G4double z_Sp71 = -z_SOY_Co3_R;
     
    static const G4double x_Sp65 = 0.0;
    static const G4double y_Sp65 = innerRadius1_SOY_Co3;
    static const G4double z_Sp65 = -z_SOY_Co3_R;

    static const G4double x_Sp63 = 0.0;
    static const G4double y_Sp63 = outerRadius1_SOY_Co3;
    static const G4double z_Sp63 = -z_SOY_Co3_R + length_SOY_Co3/2;

    static const G4double x_Sp64 = 0.0;
    static const G4double y_Sp64 = outerRadius2_SOY_Co3;
    static const G4double z_Sp64 = -z_SOY_Co3_R - length_SOY_Co3/2;

    //Right SOYUZ
   
    //Tube part 1
    static const G4double z_Sp88 = z_SOY_T1_R - length_SOY_T1/2;
    static const G4double z_Sp89 = z_SOY_T1_R + length_SOY_T1/2;

    //Tube part 2
    static const G4double z_Sp86 = z_SOY_T2_R - length_SOY_T2/2;
    static const G4double z_Sp87 = z_SOY_T2_R + length_SOY_T2/2;

    //Cone part 3
    static const G4double z_Sp84 = z_SOY_Co3_R - length_SOY_Co3/2;
    static const G4double z_Sp85 = z_SOY_Co3_R + length_SOY_Co3/2;

    //Cone part 4
    static const G4double z_Sp82 = z_SOY_Co4_R - length_SOY_Co4/2;
    static const G4double z_Sp83 = z_SOY_Co4_R + length_SOY_Co4/2;

    //Tube part 5
    static const G4double z_Sp77 = z_SOY_T5_R + length_SOY_T5/2;

    //Tube part 6
    static const G4double z_Sp76 = z_SOY_T6_R + length_SOY_T6/2;

    //Cone part 7
    static const G4double z_Sp74 = z_SOY_Co7_R - length_SOY_Co7/2;
    static const G4double z_Sp75 = z_SOY_Co7_R + length_SOY_Co7/2;

    // right rings big
    static const G4double z_Sp78 = z_Tube1Con_R - length_Tube1Con/2;
    static const G4double z_Sp79 = z_Tube1Con_R + length_Tube1Con/2;

    // right rings small
    static const G4double z_Sp80 = z_Tube2Con_R - length_Tube2Con/2;
    static const G4double z_Sp81 = z_Tube2Con_R + length_Tube2Con/2;

    //right QD0
    static const G4double z_Sp90 = z_QD0_Co_R;
    static const G4double z_Sp91 = z_QD0_T_R;
    static const G4double z_Sp92 = z_QD0_T_R + length_QD0_T/2;

    //right shielding(1)
    static const G4double x_Sp95 = x_BoxShield3_R;
    static const G4double y_Sp95 = y_BoxShield3_R;
    static const G4double z_Sp95 = z_BoxShield3_R;
        
    static const G4double x_Sp93 = x_Sp95 + lengthBoxShield3X/2;
    static const G4double y_Sp93 = y_Sp95;
    static const G4double z_Sp93 = z_Sp95 - lengthBoxShield3Z/2;
    
    static const G4double x_Sp94 = x_Sp95 + lengthBoxShield3X/2;
    static const G4double y_Sp94 = y_Sp95;
    static const G4double z_Sp94 = z_Sp95 + lengthBoxShield3Z/2;

    static const G4double x_Sp96 = x_Sp95 - lengthBoxShield3X/2;
    static const G4double y_Sp96 = y_Sp95;
    static const G4double z_Sp96 = z_Sp95 - lengthBoxShield3Z/2;
    
    static const G4double x_Sp97 = x_Sp95 - lengthBoxShield3X/2;
    static const G4double y_Sp97 = y_Sp95;
    static const G4double z_Sp97 = z_Sp95 + lengthBoxShield3Z/2;

    //right shielding(2)

    static const G4double x_Sp99 = x_BoxShield1_R;
    static const G4double y_Sp99 = y_BoxShield1_R;
    static const G4double z_Sp99 = z_BoxShield1_R;

    static const G4double x_Sp98 = x_Sp99 + lengthBoxShield1Z/2;
    static const G4double y_Sp98 = y_Sp99;
    static const G4double z_Sp98 = z_Sp99;

    static const G4double x_Sp102 = x_BoxShield2_R;
    static const G4double y_Sp102 = y_BoxShield2_R;
    static const G4double z_Sp102 = z_BoxShield2_R;

    static const G4double x_Sp100 = x_Sp102 + lengthBoxShield2X/2;
    static const G4double y_Sp100 = y_Sp102;
    static const G4double z_Sp100 = z_Sp102 - lengthBoxShield2Z/2;

    static const G4double x_Sp101 = x_Sp102 + lengthBoxShield2X/2;
    static const G4double y_Sp101 = y_Sp102;
    static const G4double z_Sp101 = z_Sp102 + lengthBoxShield2Z/2;

    static const G4double x_Sp103 = x_Sp102 - lengthBoxShield2X/2;
    static const G4double y_Sp103 = y_Sp102;
    static const G4double z_Sp103 = z_Sp102;

    //right QF1

    static const G4double x_Sp105 = x_QD1_SRCO_R_U;
    static const G4double y_Sp105 = y_QD1_SRCO_R_U;
    static const G4double z_Sp105 = z_QD1_SRCO_R_U;

    static const G4double x_Sp104 = RotXoldP(z_Sp105,x_Sp105,length_QD1_SRCO/2,0.0);
    static const G4double y_Sp104 = y_Sp105;
    static const G4double z_Sp104 = RotZoldP(z_Sp105,x_Sp105,length_QD1_SRCO/2,0.0);

    static const G4double x_Sp106 = RotXoldP(z_Sp105,x_Sp105,-length_QD1_SRCO/2,0.0);
    static const G4double y_Sp106 = y_Sp105;
    static const G4double z_Sp106 = RotZoldP(z_Sp105,x_Sp105,-length_QD1_SRCO/2,0.0);

    static const G4double x_Sp107 = x_QD1_Al_R_U;
    static const G4double y_Sp107 = y_QD1_Al_R_U;
    static const G4double z_Sp107 = z_QD1_Al_R_U;

    static const G4double x_Sp108 = RotXoldP(z_Sp107,x_Sp107,-length_QD1_Al/2,0.0);
    static const G4double y_Sp108 = y_Sp105;
    static const G4double z_Sp108 = RotZoldP(z_Sp107,x_Sp107,-length_QD1_Al/2,0.0);

    static const G4double x_Sp110 = -x_QD1_SRCO_R_U;
    static const G4double y_Sp110 = y_QD1_SRCO_R_U;
    static const G4double z_Sp110 = z_QD1_SRCO_R_U;

    static const G4double x_Sp109 = RotXoldM(z_Sp110,x_Sp110,length_QD1_SRCO/2,0.0);
    static const G4double y_Sp109 = y_Sp110;
    static const G4double z_Sp109 = RotZoldM(z_Sp110,x_Sp110,length_QD1_SRCO/2,0.0);

    static const G4double x_Sp111 = RotXoldM(z_Sp110,x_Sp110,-length_QD1_SRCO/2,0.0);
    static const G4double y_Sp111 = y_Sp110;
    static const G4double z_Sp111 = RotZoldM(z_Sp110,x_Sp110,-length_QD1_SRCO/2,0.0);

    static const G4double x_Sp112 = -x_QD1_Al_R_U;
    static const G4double y_Sp112 = y_QD1_Al_R_U;
    static const G4double z_Sp112 = z_QD1_Al_R_U;

    static const G4double x_Sp113 = RotXoldM(z_Sp112,x_Sp112,-length_QD1_Al/2,0.0);
    static const G4double y_Sp113 = y_Sp112;
    static const G4double z_Sp113 = RotZoldM(z_Sp112,x_Sp112,-length_QD1_Al/2,0.0);

   //right photon monitor    
    static const G4double x_Sp118 = x_Box1_R;
    static const G4double y_Sp118 = y_Box1_R;
    static const G4double z_Sp118 = z_Box1_R; 
    
    static const G4double x_Sp120 = x_Box2_R;
    static const G4double y_Sp120 = y_Box2_R;
    static const G4double z_Sp120 = z_Box2_R; 
    
    static const G4double x_Sp122 = x_Box3_R;
    static const G4double y_Sp122 = y_Box3_R;
    static const G4double z_Sp122 = z_Box3_R; 
    
    static const G4double x_Sp124 = x_Box4_R;
    static const G4double y_Sp124 = y_Box4_R;
    static const G4double z_Sp124 = z_Box4_R; 
    
    static const G4double x_Sp119 = RotXoldM(z_Sp118,x_Sp118, lengthZ_IronBox/2, lengthX_IronBox/2);
    static const G4double y_Sp119 = y_Sp118;
    static const G4double z_Sp119 = RotZoldM(z_Sp118,x_Sp118, lengthZ_IronBox/2, lengthX_IronBox/2);

    static const G4double x_Sp121 = RotXoldM(z_Sp120,x_Sp120, lengthZ_IronBox/2, lengthX_IronBox/2);
    static const G4double y_Sp121 = y_Sp120;
    static const G4double z_Sp121 = RotZoldM(z_Sp120,x_Sp120, lengthZ_IronBox/2, lengthX_IronBox/2);

    static const G4double x_Sp123 = RotXoldM(z_Sp122,x_Sp122, lengthZ_IronBox/2, lengthX_IronBox/2);
    static const G4double y_Sp123 = y_Sp122;
    static const G4double z_Sp123 = RotZoldM(z_Sp122,x_Sp122, lengthZ_IronBox/2, lengthX_IronBox/2);

    //Slielding around of the photon detectors

    static const G4double x_Sp115 = x_PbBoxForPhot;
    static const G4double y_Sp115 = y_PbBoxForPhot;
    static const G4double z_Sp115 = z_PbBoxForPhot;

    static const G4double x_Sp114 = RotXoldM(z_Sp115,x_Sp115,0.0,lengthX_PbBoxPhot/2);
    static const G4double y_Sp114 = y_Sp115;
    static const G4double z_Sp114 = RotZoldM(z_Sp115,x_Sp115,0.0,lengthX_PbBoxPhot/2);

    static const G4double x_Sp117 = RotXoldM(z_Sp115,x_Sp115,0.0,-lengthX_PbBoxPhot/2);
    static const G4double y_Sp117 = y_Sp115;
    static const G4double z_Sp117 = RotZoldM(z_Sp115,x_Sp115,0.0,-lengthX_PbBoxPhot/2);

    static const G4double x_Sp116 = x_WinPhot;
    static const G4double y_Sp116 = y_WinPhot;
    static const G4double z_Sp116 = z_WinPhot;

    static const G4double x_Sp125 = x_PbBoxCenPhot;
    static const G4double y_Sp125 = y_PbBoxCenPhot;
    static const G4double z_Sp125 = z_PbBoxCenPhot;

    //--
    static const G4double x_Sp129 = x_PbBoxBackPhot;
    static const G4double y_Sp129 = y_PbBoxBackPhot;
    static const G4double z_Sp129 = z_PbBoxBackPhot;

    static const G4double x_Sp126 = RotXoldM(z_Sp129,x_Sp129,-lengthZ_PbBoxPhot/2,lengthX_PbBoxPhot/2);
    static const G4double y_Sp126 = y_Sp129;
    static const G4double z_Sp126 = RotZoldM(z_Sp129,x_Sp129,-lengthZ_PbBoxPhot/2,lengthX_PbBoxPhot/2);

    static const G4double x_Sp127 = RotXoldM(z_Sp129,x_Sp129,-lengthZ_PbBoxPhot/2,0.0);
    static const G4double y_Sp127 = y_Sp129;
    static const G4double z_Sp127 = RotZoldM(z_Sp129,x_Sp129,-lengthZ_PbBoxPhot/2,0.0);

    static const G4double x_Sp128 = RotXoldM(z_Sp129,x_Sp129,-lengthZ_PbBoxPhot/2,-lengthX_PbBoxPhot/2);
    static const G4double y_Sp128 = y_Sp129;
    static const G4double z_Sp128 = RotZoldM(z_Sp129,x_Sp129,-lengthZ_PbBoxPhot/2,-lengthX_PbBoxPhot/2);


    //benchmarksGeom04 new banch of 

    //-------------------------------------------
    //End of the BP
    // cm circular part (in section) of the Tube5
    //-------------------------------------------

    static G4double x_S1 = RotXoldM( z_Tube5_Co_L_U, x_Tube5_Co_L_U, -length_Tube5_Co/2, 0);
    static G4double z_S1 = RotZoldM( z_Tube5_Co_L_U, x_Tube5_Co_L_U, -length_Tube5_Co/2, 0);

    static G4double x_S2 = RotXoldM( z_Tube5_Co_L_U, x_Tube5_Co_L_U, length_Tube5_Co/2, 0);
    static G4double z_S2 = RotZoldM( z_Tube5_Co_L_U, x_Tube5_Co_L_U, length_Tube5_Co/2, 0);
    
    static G4double x_S3 = RotXoldM( z_Tube5_Co_L_U, x_Tube5_Co_L_U, length_Tube5_Co/2, r1max_Tube5_Co);
    static G4double z_S3 = RotZoldM( z_Tube5_Co_L_U, x_Tube5_Co_L_U, length_Tube5_Co/2, r1max_Tube5_Co);
    
    static G4double x_S4 = RotXoldM( z_Tube5_Co_L_U, x_Tube5_Co_L_U, length_Tube5_Co/2, -r1max_Tube5_Co);
    static G4double z_S4 = RotZoldM( z_Tube5_Co_L_U, x_Tube5_Co_L_U, length_Tube5_Co/2, -r1max_Tube5_Co);
    
    static G4double x_S5 = x_Tube5_C_L_U;
    static G4double z_S5 = z_Tube5_C_L_U;

    static G4double x_S6 = RotXoldM( z_Tube5_C_L_U, x_Tube5_C_L_U, length_Tube5_C/2, r1max_Tube5_Co);
    static G4double z_S6 = RotZoldM( z_Tube5_C_L_U, x_Tube5_C_L_U, length_Tube5_C/2, r1max_Tube5_Co);
    
    static G4double x_S7 = RotXoldM( z_Tube5_C_L_U, x_Tube5_C_L_U, length_Tube5_C/2, -r1max_Tube5_Co);
    static G4double z_S7 = RotZoldM( z_Tube5_C_L_U, x_Tube5_C_L_U, length_Tube5_C/2, -r1max_Tube5_Co);
    
    static G4double x_S8 = -x_S4;
    static G4double z_S8 =  z_S4; 
    
    static G4double x_S9 = -x_S2;
    static G4double z_S9 =  z_S2; 
    
    static G4double x_S10 = RotXoldP( z_Tube5_C_L_D, x_Tube5_C_L_D, length_Tube5_C/2, 0.0);
    static G4double z_S10 = RotZoldP( z_Tube5_C_L_D, x_Tube5_C_L_D, length_Tube5_C/2, 0.0);

    //photon detector left

    static G4double x_S11 = RotXoldP( -z_PbBoxBackPhot, x_PbBoxBackPhot, -lengthZ_PbBoxPhot/2, lengthX_PbBoxPhot/2);
    static G4double y_S11 = lengthY_PbBoxPhot/2;
    static G4double z_S11 = RotZoldP( -z_PbBoxBackPhot, x_PbBoxBackPhot, -lengthZ_PbBoxPhot/2, lengthX_PbBoxPhot/2);
    
    static G4double x_S12 = RotXoldP( z_PlasticBox_L, x_PlasticBox_L, -lengthZ_PbWOBox/2 + z_Box1Pl, lengthX_PbWOBox/2 + x_Box1Pl);
    static G4double y_S12 = lengthY_PbWOBox/2;
    static G4double z_S12 = RotZoldP( z_PlasticBox_L, x_PlasticBox_L, -lengthZ_PbWOBox/2 + z_Box1Pl, lengthX_PbWOBox/2 + x_Box1Pl);
    
    static G4double x_S13 = RotXoldP( z_PlasticBox_L, x_PlasticBox_L, lengthZ_PbWOBox/2 + z_Box4Pl, -lengthX_PbWOBox/2 + x_Box4Pl);
    static G4double y_S13 = -lengthY_PbWOBox/2;
    static G4double z_S13 = RotZoldP( z_PlasticBox_L, x_PlasticBox_L, lengthZ_PbWOBox/2 + z_Box4Pl, -lengthX_PbWOBox/2 + x_Box4Pl);
    
    static G4double x_S14 = RotXoldP( -z_PbBoxForPhot, x_PbBoxForPhot, lengthZ_PbBoxPhot/2, -lengthX_PbBoxPhot/2);
    static G4double y_S14 = -lengthY_PbBoxPhot/2;
    static G4double z_S14 = RotZoldP( -z_PbBoxForPhot, x_PbBoxForPhot, lengthZ_PbBoxPhot/2, -lengthX_PbBoxPhot/2);

    static G4double x_S15 = RotXoldM( z_QD1_SRCO_L_U, x_QD1_SRCO_L_U, -length_QD1_SRCO/2, outerRadius_QD1);
    static G4double z_S15 = RotZoldM( z_QD1_SRCO_L_U, x_QD1_SRCO_L_U, -length_QD1_SRCO/2, outerRadius_QD1);
    
    static G4double x_S16 = RotXoldM( z_QD1_SRCO_L_U, x_QD1_SRCO_L_U, -length_QD1_SRCO/2, 0.0);
    static G4double z_S16 = RotZoldM( z_QD1_SRCO_L_U, x_QD1_SRCO_L_U, -length_QD1_SRCO/2, 0.0);
    
    static G4double x_S17 = x_QD1_SRCO_L_U;
    static G4double z_S17 = z_QD1_SRCO_L_U;
    
    static G4double x_S18 = RotXoldM( z_QD1_SRCO_L_U, x_QD1_SRCO_L_U, length_QD1_SRCO/2, 0.0);
    static G4double z_S18 = RotZoldM( z_QD1_SRCO_L_U, x_QD1_SRCO_L_U, length_QD1_SRCO/2, 0.0);
    
    static G4double x_S19 = 0.0;
    static G4double z_S19 = (-outerRadius_QD1 + RotXp(z_QD1_SRCO_L_U,x_QD1_SRCO_L_U))/sin4_07;
    
    static G4double x_S20 = -x_S16;
    static G4double z_S20 =  z_S16;

    static G4double x_S21 = RotXoldP( z_QD1_SRCO_L_D, x_QD1_SRCO_L_D, length_QD1_SRCO/2, -outerRadius_QD1);
    static G4double z_S21 = RotZoldP( z_QD1_SRCO_L_D, x_QD1_SRCO_L_D, length_QD1_SRCO/2, -outerRadius_QD1);
    
    static G4double x_S22 = RotXoldM( z_QD1_SRCO_L_U, x_QD1_SRCO_L_U, -length_QD1_SRCO/2-length_QD1_new_Al, outerRadius_QD1);
    static G4double z_S22 = RotZoldM( z_QD1_SRCO_L_U, x_QD1_SRCO_L_U, -length_QD1_SRCO/2-length_QD1_new_Al, outerRadius_QD1);
    
    static G4double x_S23 = RotXoldM( z_QD1_SRCO_L_U, x_QD1_SRCO_L_U, -length_QD1_SRCO/2-length_QD1_new_Al, -outerRadius_QD1);
    static G4double z_S23 = RotZoldM( z_QD1_SRCO_L_U, x_QD1_SRCO_L_U, -length_QD1_SRCO/2-length_QD1_new_Al, -outerRadius_QD1);

    static G4double x_S24 = RotXoldM( z_QD1_SRCO_L_U, x_QD1_SRCO_L_U, length_QD1_SRCO/2, -outerRadius_QD1);
    static G4double z_S24 = RotZoldM( z_QD1_SRCO_L_U, x_QD1_SRCO_L_U, length_QD1_SRCO/2, -outerRadius_QD1);
    
    static G4double x_S25 = RotXoldM( z_QD1_SRCO_L_U, x_QD1_SRCO_L_U, length_QD1_SRCO/2+length_QD1_new_Al, outerRadius_QD1);
    static G4double z_S25 = RotZoldM( z_QD1_SRCO_L_U, x_QD1_SRCO_L_U, length_QD1_SRCO/2+length_QD1_new_Al, outerRadius_QD1);

    static const G4double x_S26 = -dx2_Tube3_par2_TR/2;
    static const G4double z_S26 = -z_Tube3_par2_TR - dz_Tube3_par2_TR/2;
    
    static const G4double x_S27 = 0.0;
    static const G4double z_S27 = z_S26 - dz_Tube3_par3_TR;
    
    static const G4double x_S28 = -x_S26;
    static const G4double z_S28 = z_S26;

    static const G4double x_S29 = 0.0;
    static const G4double z_S29 = -z_Tube3_par2_T_v - (r_max_Tube3_par2_T/cosAngleT3 - x_Tube3_par2_T_v)/tagAngleT3;
    
    static const G4double x_S30 = -dx1_Tube3_par2_TR/2;
    static const G4double z_S30 = -z_Tube3_par2_TR + dz_Tube3_par2_TR/2;
    
    static const G4double x_S31 = dx1_Tube3_par2_TR/2;
    static const G4double z_S31 = -z_Tube3_par2_TR + dz_Tube3_par2_TR/2;
    
    static const G4double x_S32 = -x_length_Tube3_par1_B/2 - r_max_Tube3_par1_T;
    static const G4double z_S32 = -z_Tube3_par1_T - length_Tube3_par1_T/2;
    
    static const G4double x_S33 = -x_length_Tube3_par1_B/2 - r_max_Tube3_par1_T;
    static const G4double z_S33 = -z_Tube3_par1_T + length_Tube3_par1_T/2;
    
    static const G4double x_S34 = x_length_Tube3_par1_B/2 + r_max_Tube3_par1_T;
    static const G4double z_S34 = -z_Tube3_par1_T - length_Tube3_par1_T/2;
    
    static const G4double x_S35 = x_length_Tube3_par1_B/2 + r_max_Tube3_par1_T;
    static const G4double z_S35 = -z_Tube3_par1_T + length_Tube3_par1_T/2;

    static const G4double x_S36 = RotXoldTube2M( z_Tube2_E_CLU, x_Tube2_E_CLU, -length_Tube2_E/2, outerRadiusTube2_E);
    static const G4double z_S36 = RotZoldTube2M( z_Tube2_E_CLU, x_Tube2_E_CLU, -length_Tube2_E/2, outerRadiusTube2_E);
    
    static const G4double x_S37 = RotXoldTube2P( z_Tube2_E_CLD, x_Tube2_E_CLD, -length_Tube2_E/2, -outerRadiusTube2_E);
    static const G4double z_S37 = RotZoldTube2P( z_Tube2_E_CLD, x_Tube2_E_CLD, -length_Tube2_E/2, -outerRadiusTube2_E);
    
    static const G4double x_S38 = RotXoldTube2M( z_Tube2_E_CLU, x_Tube2_E_CLU, length_Tube2_E/2, outerRadiusTube2_E);
    static const G4double z_S38 = RotZoldTube2M( z_Tube2_E_CLU, x_Tube2_E_CLU, length_Tube2_E/2, outerRadiusTube2_E);
    
    static const G4double x_S39 = RotXoldTube2P( z_Tube2_E_CLD, x_Tube2_E_CLD, length_Tube2_E/2, -outerRadiusTube2_E);
    static const G4double z_S39 = RotZoldTube2P( z_Tube2_E_CLD, x_Tube2_E_CLD, length_Tube2_E/2, -outerRadiusTube2_E);

    static const G4double x_S40 = RotXoldM( -z_Tube3_par4, x_Tube3_par4, -length_Tube3_par4/2, r_max_Tube3_par4);
    static const G4double z_S40 = RotZoldM( -z_Tube3_par4, x_Tube3_par4, -length_Tube3_par4/2, r_max_Tube3_par4);
    
    static const G4double x_S41 = RotXoldM( -z_Tube3_par4, x_Tube3_par4, length_Tube3_par4/2, r_max_Tube3_par4);
    static const G4double z_S41 = RotZoldM( -z_Tube3_par4, x_Tube3_par4, length_Tube3_par4/2, r_max_Tube3_par4);
    
    static const G4double x_S42 = RotXoldP( -z_Tube3_par4, -x_Tube3_par4, -length_Tube3_par4/2, -r_min_Tube3_par4);
    static const G4double z_S42 = RotZoldP( -z_Tube3_par4, -x_Tube3_par4, -length_Tube3_par4/2, -r_min_Tube3_par4);
    
    static const G4double x_S43 = RotXoldP( -z_Tube3_par4, -x_Tube3_par4, length_Tube3_par4/2, -r_min_Tube3_par4);
    static const G4double z_S43 = RotZoldP( -z_Tube3_par4, -x_Tube3_par4, length_Tube3_par4/2, -r_min_Tube3_par4);
    
    static const G4double x_S44 = RotXoldM( -z_Tube3_par4, x_Tube3_par4, -length_Tube3_par4/2, -r_min_Tube3_par4);
    static const G4double z_S44 = RotZoldM( -z_Tube3_par4, x_Tube3_par4, -length_Tube3_par4/2, -r_min_Tube3_par4);
    
    static const G4double x_S45 = RotXoldM( -z_Tube3_par4, x_Tube3_par4, length_Tube3_par4/2, -r_max_Tube3_par4);
    static const G4double z_S45 = RotZoldM( -z_Tube3_par4, x_Tube3_par4, length_Tube3_par4/2, -r_max_Tube3_par4);

    static G4double x_S46 = x_PbBoxBackPhot;
    static G4double z_S46 = -z_PbBoxBackPhot;
    
    static G4double x_S47 =  RotXoldP( -z_PbBoxBackPhot, x_PbBoxBackPhot, -lengthZ_PbBoxPhot/2, -lengthX_PbBoxPhot/2);
    static G4double z_S47 =  RotZoldP( -z_PbBoxBackPhot, x_PbBoxBackPhot, -lengthZ_PbBoxPhot/2, -lengthX_PbBoxPhot/2);

    static G4double x_S48 =  RotXoldP( -z_PbBoxCenPhot, x_PbBoxCenPhot, -lengthZ_PbBoxCenPhot/2, lengthX_PbBoxCenPhot/2);
    static G4double z_S48 =  RotZoldP( -z_PbBoxCenPhot, x_PbBoxCenPhot, -lengthZ_PbBoxCenPhot/2, lengthX_PbBoxCenPhot/2);
    
    static G4double x_S49 = x_PbBoxCenPhot;
    static G4double z_S49 = -z_PbBoxCenPhot;

    static G4double x_S50 =  RotXoldP( -z_PbBoxForPhot, x_PbBoxForPhot, 0.0, lengthX_PbBoxPhot/2);
    static G4double z_S50 =  RotZoldP( -z_PbBoxForPhot, x_PbBoxForPhot, 0.0, lengthX_PbBoxPhot/2);
    
    static G4double x_S51 =  RotXoldP( -z_WinPhot, x_WinPhot, 0.0, outerRadiusWinPhot);
    static G4double z_S51 =  RotZoldP( -z_WinPhot, x_WinPhot, 0.0, outerRadiusWinPhot);
    
    static G4double x_S52 =  x_WinPhot;
    static G4double z_S52 =  -z_WinPhot;
    
    static G4double x_S53 =  RotXoldP( -z_PbBoxForPhot, x_PbBoxForPhot, 0.0,-lengthX_PbBoxPhot/2);
    static G4double z_S53 =  RotZoldP( -z_PbBoxForPhot, x_PbBoxForPhot, 0.0,-lengthX_PbBoxPhot/2);
    
    static G4double x_S54 =  RotXoldP( -z_PbBoxForPhot, x_PbBoxForPhot, lengthZ_PbBoxPhot/2,-lengthX_PbBoxPhot/2);
    static G4double z_S54 =  RotZoldP( -z_PbBoxForPhot, x_PbBoxForPhot, lengthZ_PbBoxPhot/2,-lengthX_PbBoxPhot/2);
    
    static G4double x_S55 =  RotXoldP( -z_PlasticBox_R, x_PlasticBox_R, lengthZ_PlasticBox/2, -lengthX_PlasticBox/2);
    static G4double z_S55 =  RotZoldP( -z_PlasticBox_R, x_PlasticBox_R, lengthZ_PlasticBox/2, -lengthX_PlasticBox/2);
    
    static G4double x_S56 =  RotXoldP( -z_PlasticBox_R, x_PlasticBox_R, lengthZ_PlasticBox/2, lengthX_PlasticBox/2);
    static G4double z_S56 =  RotZoldP( -z_PlasticBox_R, x_PlasticBox_R, lengthZ_PlasticBox/2, lengthX_PlasticBox/2);
    
    static G4double x_S57 =  RotXoldP( -z_PlasticBox_R, x_PlasticBox_R, -lengthZ_PlasticBox/2, lengthX_PlasticBox/2);
    static G4double z_S57 =  RotZoldP( -z_PlasticBox_R, x_PlasticBox_R, -lengthZ_PlasticBox/2, lengthX_PlasticBox/2);
    
    static G4double x_S58 =  RotXoldP( -z_PlasticBox_R, x_PlasticBox_R, z_Box4Pl, x_Box4Pl);
    static G4double z_S58 =  RotZoldP( -z_PlasticBox_R, x_PlasticBox_R, z_Box4Pl, x_Box4Pl);
    
    static G4double x_S59 =  RotXoldP( -z_PlasticBox_R, x_PlasticBox_R, z_Box4Pl - lengthZ_PbWOBox/2, x_Box4Pl + lengthX_PbWOBox/2);
    static G4double z_S59 =  RotZoldP( -z_PlasticBox_R, x_PlasticBox_R, z_Box4Pl - lengthZ_PbWOBox/2, x_Box4Pl + lengthX_PbWOBox/2);
    
    static G4double x_S60 =  RotXoldP( -z_PlasticBox_R, x_PlasticBox_R, z_Box3Pl, x_Box3Pl);
    static G4double z_S60 =  RotZoldP( -z_PlasticBox_R, x_PlasticBox_R, z_Box3Pl, x_Box3Pl);
    
    static G4double x_S61 =  RotXoldP( -z_PlasticBox_R, x_PlasticBox_R, z_Box3Pl - lengthZ_PbWOBox/2, x_Box3Pl + lengthX_PbWOBox/2);
    static G4double z_S61 =  RotZoldP( -z_PlasticBox_R, x_PlasticBox_R, z_Box3Pl - lengthZ_PbWOBox/2, x_Box3Pl + lengthX_PbWOBox/2);
    
    static G4double x_S62 =  RotXoldP( -z_PlasticBox_R, x_PlasticBox_R, z_Box2Pl, x_Box2Pl);
    static G4double z_S62 =  RotZoldP( -z_PlasticBox_R, x_PlasticBox_R, z_Box2Pl, x_Box2Pl);
    
    static G4double x_S63 =  RotXoldP( -z_PlasticBox_R, x_PlasticBox_R, z_Box2Pl - lengthZ_PbWOBox/2, x_Box2Pl + lengthX_PbWOBox/2);
    static G4double z_S63 =  RotZoldP( -z_PlasticBox_R, x_PlasticBox_R, z_Box2Pl - lengthZ_PbWOBox/2, x_Box2Pl + lengthX_PbWOBox/2);
    
    static G4double x_S64 =  RotXoldP( -z_PlasticBox_R, x_PlasticBox_R, z_Box1Pl, x_Box1Pl);
    static G4double z_S64 =  RotZoldP( -z_PlasticBox_R, x_PlasticBox_R, z_Box1Pl, x_Box1Pl);

    static G4double x_S65 =  RotXoldM( z_PbBoxForPhot, x_PbBoxForPhot, -lengthZ_PbBoxPhot/2,lengthX_PbBoxPhot/2);
    static G4double z_S65 =  RotZoldM( z_PbBoxForPhot, x_PbBoxForPhot, -lengthZ_PbBoxPhot/2,lengthX_PbBoxPhot/2);


    //photon detector left




    // control points for shuoting in photon detector
    static const G4double zP1 =  RotZoldM(z_QD1_SRCO_R_D,x_QD1_SRCO_R_D, (length_QD1_SRCO-2)/2,innerRadius_Tube1-0.1);
    static const G4double zP2 =  RotZoldM(z_QD1_SRCO_R_D,x_QD1_SRCO_R_D, 0.,innerRadius_Tube1-0.1);
    static const G4double zP3 =  RotZoldM(z_QD1_SRCO_R_D,x_QD1_SRCO_R_D, -(length_QD1_SRCO-2)/2,innerRadius_Tube1-0.1);
    
    static const G4double xP1 =  RotXoldM(z_QD1_SRCO_R_D,x_QD1_SRCO_R_D, (length_QD1_SRCO-2)/2,innerRadius_Tube1-0.1);
    static const G4double xP2 =  RotXoldM(z_QD1_SRCO_R_D,x_QD1_SRCO_R_D, 0.,innerRadius_Tube1-0.1);
    static const G4double xP3 =  RotXoldM(z_QD1_SRCO_R_D,x_QD1_SRCO_R_D, -(length_QD1_SRCO-2)/2,innerRadius_Tube1-0.1);

    static const G4double zP4 = RotZoldTube3M(z_Tube3_par2_T_v,-x_Tube3_par2_T_v, (length_Tube3_par2_T_v-2)/2,r_max_Tube3_par2_T-0.1);
    static const G4double zP5 = RotZoldTube3M(z_Tube3_par2_T_v,-x_Tube3_par2_T_v, 0.0,r_max_Tube3_par2_T-0.1);
    static const G4double zP6 = RotZoldTube3M(z_Tube3_par2_T_v,-x_Tube3_par2_T_v, -(length_Tube3_par2_T_v-2)/2,r_max_Tube3_par2_T-0.1);

    static const G4double xP4 = RotXoldTube3M(z_Tube3_par2_T_v,-x_Tube3_par2_T_v, (length_Tube3_par2_T_v-2)/2,r_max_Tube3_par2_T-0.1);
    static const G4double xP5 = RotXoldTube3M(z_Tube3_par2_T_v,-x_Tube3_par2_T_v, 0.0,r_max_Tube3_par2_T-0.1);
    static const G4double xP6 = RotXoldTube3M(z_Tube3_par2_T_v,-x_Tube3_par2_T_v, -(length_Tube3_par2_T_v-2)/2,r_max_Tube3_par2_T-0.1);

//r_max_Tube3_par2_T

    //static const G4double x_Tube3_par2_T_v = (x2_Tube3_par2_T + x1_Tube3_par2_T)/2;
    //static const G4double y_Tube3_par2_T_v = 0.0;
    //static const G4double z_Tube3_par2_T_v = (z2_Tube3_par2_T + z1_Tube3_par2_T)/2;
    

    // static const G4double zP1 =  RotZoldM(z_QD1_SRCO_R_D,x_QD1_SRCO_R_D, (length_QD1_SRCO-2)/2,0.);
    // static const G4double zP2 =  RotZoldM(z_QD1_SRCO_R_D,x_QD1_SRCO_R_D, 0.,0.);
    // static const G4double zP3 =  RotZoldM(z_QD1_SRCO_R_D,x_QD1_SRCO_R_D, -(length_QD1_SRCO-2)/2,0.);

    // static const G4double xP1 =  RotXoldM(z_QD1_SRCO_R_D,x_QD1_SRCO_R_D, (length_QD1_SRCO-2)/2,0.);
    // static const G4double xP2 =  RotXoldM(z_QD1_SRCO_R_D,x_QD1_SRCO_R_D, 0.,0.);
    // static const G4double xP3 =  RotXoldM(z_QD1_SRCO_R_D,x_QD1_SRCO_R_D, -(length_QD1_SRCO-2)/2,0.);

}

#endif
