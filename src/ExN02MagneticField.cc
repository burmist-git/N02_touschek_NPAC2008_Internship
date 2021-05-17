//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: A01MagneticField.cc,v 1.6 2006/06/29 16:32:57 gunter Exp $
// --------------------------------------------------------------
//

#include "ExN02MagneticField.hh"

#include "math.h"
#include "DetectorConstant.hh" 


//write to file
//#include "iostream.h"
//#include "fstream.h"

using namespace std;
using namespace DetConst;

//#include "DetectorConstant.hh" 
//using namespace DetConst;

ExN02MagneticField::ExN02MagneticField()
{
    //streamQD0_R = fopen("MagneticInfoQD0_R.txt","w");   
    //streamQD0_L = fopen("MagneticInfoQD0_L.txt","w");
 
    //streamQD1_R_U = fopen("MagneticInfoQD1_R_U.txt","w");
    //streamQD1_R_D = fopen("MagneticInfoQD1_R_D.txt","w");
    //streamQD1_L_U = fopen("MagneticInfoQD1_L_U.txt","w");
    //streamQD1_L_D = fopen("MagneticInfoQD1_L_D.txt","w");

    // myfile.open ("example.txt");

    //Bx = 0.;
    //By = 0.;
    //Bz = 0.;

    gQD0 = -2.923;  //k*Gauss/cm
    gQD1 = 1.25;    //k*Gauss/cm
    //messenger = new A01MagneticFieldMessenger(this);
    G4cout << "ExN02MagneticField::ExN02MagneticField()" << G4endl;
}

ExN02MagneticField::~ExN02MagneticField()
{
    //fclose(streamQD0_R);
    //fclose(streamQD0_L);

    //fclose(streamQD1_R_U);
    //fclose(streamQD1_R_D);
    //fclose(streamQD1_L_U);
    //fclose(streamQD1_L_D);

    //myfile.close();
    //delete messenger; 
}

void ExN02MagneticField::GetFieldValue(const double Point[4],double *Bfield) const
{
    SetField(Point, Bfield[0],Bfield[1],Bfield[2]); //you can use this


}

bool ExN02MagneticField::SetField( const double *Point,  G4double & Bx, G4double & By, G4double & Bz) const {

    G4String flag_SetZeroField;
    //flag_SetZeroField = "SetZeroFieldOn";
    flag_SetZeroField = "SetZeroFieldOff";

    G4String flag_TurnOFFBottomField;
    //flag_TurnOFFBottomField = "TurnOFFBottomFieldON";
    flag_TurnOFFBottomField = "TurnOFFBottomFieldOFF";

    if(flag_SetZeroField == "SetZeroFieldOn"){
        Bx = 0.;
	By = 0.;
	Bz = 0.;
	return false;
    }
    
    
    G4double x_QD1_R_U_ = 0.;
    G4double y_QD1_R_U_ = 0.;
    G4double z_QD1_R_U_ = 0.;

    G4double x_QD1_R_D_ = 0.;
    G4double y_QD1_R_D_ = 0.;
    G4double z_QD1_R_D_ = 0.;

    G4double x_QD1_L_U_ = 0.;
    G4double y_QD1_L_U_ = 0.;
    G4double z_QD1_L_U_ = 0.;

    G4double x_QD1_L_D_ = 0.;
    G4double y_QD1_L_D_ = 0.;
    G4double z_QD1_L_D_ = 0.;
    //---
    G4double z_max_QD1_R_U_;
    G4double x_max_QD1_R_U_;
    G4double z_min_QD1_R_U_;
    G4double x_min_QD1_R_U_;
    
    G4double z_max_QD1_R_D_;
    G4double x_max_QD1_R_D_;
    G4double z_min_QD1_R_D_;
    G4double x_min_QD1_R_D_;
    
    G4double z_max_QD1_L_U_;
    G4double x_max_QD1_L_U_;
    G4double z_min_QD1_L_U_;
    G4double x_min_QD1_L_U_;
    
    G4double z_max_QD1_L_D_;
    G4double x_max_QD1_L_D_;
    G4double z_min_QD1_L_D_;
    G4double x_min_QD1_L_D_;
    //--

    x_QD1_R_U_ = RotationX(Point[2],Point[0],-1); //mm
    y_QD1_R_U_ = Point[1];                        //mm
    z_QD1_R_U_ = RotationZ(Point[2],Point[0],-1); //mm

    x_QD1_R_D_ = RotationX(Point[2],Point[0],1);  //mm
    y_QD1_R_D_ = Point[1];                        //mm
    z_QD1_R_D_ = RotationZ(Point[2],Point[0],1);  //mm

    x_QD1_L_U_ = RotationX(Point[2],Point[0],1);  //mm
    y_QD1_L_U_ = Point[1];                        //mm
    z_QD1_L_U_ = RotationZ(Point[2],Point[0],1);  //mm

    x_QD1_L_D_ = RotationX(Point[2],Point[0],-1); //mm
    y_QD1_L_D_ = Point[1];                        //mm
    z_QD1_L_D_ = RotationZ(Point[2],Point[0],-1); //mm
    
    //--
    G4double x_tmp_R_U_ = RotationX( z_QD1_SRCO_R_U, x_QD1_SRCO_R_U,-1); //cm
    G4double x_tmp_L_D_ = RotationX( z_QD1_SRCO_L_D, x_QD1_SRCO_L_D,-1); //cm


    z_max_QD1_R_U_ = RotationZ(zmax_QD1_R_Umy,xmax_QD1_R_Umy,-1); //cm
    x_max_QD1_R_U_ = RotationX(zmax_QD1_R_Umy,xmax_QD1_R_Umy,-1); //cm
    z_min_QD1_R_U_ = RotationZ(zmin_QD1_R_Umy,xmin_QD1_R_Umy,-1); //cm
    x_min_QD1_R_U_ = RotationX(zmin_QD1_R_Umy,xmin_QD1_R_Umy,-1); //cm

    z_max_QD1_L_D_ = RotationZ(zmax_QD1_L_Dmy,xmax_QD1_L_Dmy,-1); //cm
    x_max_QD1_L_D_ = RotationX(zmax_QD1_L_Dmy,xmax_QD1_L_Dmy,-1); //cm
    z_min_QD1_L_D_ = RotationZ(zmin_QD1_L_Dmy,xmin_QD1_L_Dmy,-1); //cm
    x_min_QD1_L_D_ = RotationX(zmin_QD1_L_Dmy,xmin_QD1_L_Dmy,-1); //cm

    z_max_QD1_L_U_ = RotationZ(zmax_QD1_L_Umy,xmax_QD1_L_Umy,1); //cm
    x_max_QD1_L_U_ = RotationX(zmax_QD1_L_Umy,xmax_QD1_L_Umy,1); //cm
    z_min_QD1_L_U_ = RotationZ(zmin_QD1_L_Umy,xmin_QD1_L_Umy,1); //cm
    x_min_QD1_L_U_ = RotationX(zmin_QD1_L_Umy,xmin_QD1_L_Umy,1); //cm

    z_max_QD1_R_D_ = RotationZ(zmax_QD1_R_Dmy,xmax_QD1_R_Dmy,1); //cm
    x_max_QD1_R_D_ = RotationX(zmax_QD1_R_Dmy,xmax_QD1_R_Dmy,1); //cm
    z_min_QD1_R_D_ = RotationZ(zmin_QD1_R_Dmy,xmin_QD1_R_Dmy,1); //cm
    x_min_QD1_R_D_ = RotationX(zmin_QD1_R_Dmy,xmin_QD1_R_Dmy,1); //cm

        
   // z_max_QD1_R_U_ = RotationZ(z_maxAxis_QD1_R_U,x_maxAxis_QD1_R_U,-1); //cm
   // x_max_QD1_R_U_ = RotationX(z_maxAxis_QD1_R_U,x_maxAxis_QD1_R_U,-1); //cm
   // z_min_QD1_R_U_ = RotationZ(z_minAxis_QD1_R_U,x_minAxis_QD1_R_U,-1); //cm
   // x_min_QD1_R_U_ = RotationX(z_minAxis_QD1_R_U,x_minAxis_QD1_R_U,-1); //cm
	  
   // z_max_QD1_L_D_ = RotationZ(z_maxAxis_QD1_L_D,x_maxAxis_QD1_L_D,-1); //cm
   // x_max_QD1_L_D_ = RotationX(z_maxAxis_QD1_L_D,x_maxAxis_QD1_L_D,-1); //cm
   // z_min_QD1_L_D_ = RotationZ(z_minAxis_QD1_L_D,x_minAxis_QD1_L_D,-1); //cm
   // x_min_QD1_L_D_ = RotationX(z_minAxis_QD1_L_D,x_minAxis_QD1_L_D,-1); //cm
	    
   // z_max_QD1_R_D_ = RotationZ(z_maxAxis_QD1_R_D,x_maxAxis_QD1_R_D,1);  //cm
   // x_max_QD1_R_D_ = RotationX(z_maxAxis_QD1_R_D,x_maxAxis_QD1_R_D,1);  //cm
   // z_min_QD1_R_D_ = RotationZ(z_minAxis_QD1_R_D,x_minAxis_QD1_R_D,1);  //cm
   // x_min_QD1_R_D_ = RotationX(z_minAxis_QD1_R_D,x_minAxis_QD1_R_D,1);  //cm
	 
   // z_max_QD1_L_U_ = RotationZ(z_maxAxis_QD1_L_U,x_maxAxis_QD1_L_U,1);  //cm
   // x_max_QD1_L_U_ = RotationX(z_maxAxis_QD1_L_U,x_maxAxis_QD1_L_U,1);  //cm
   // z_min_QD1_L_U_ = RotationZ(z_minAxis_QD1_L_U,x_minAxis_QD1_L_U,1);  //cm
   // x_min_QD1_L_U_ = RotationX(z_minAxis_QD1_L_U,x_minAxis_QD1_L_U,1);  //cm
          
    //--
 
    Bz = 0.;
 
    //G4cout << " Point[0] = "<<Point[0]*mm << " Point[1] = "<<Point[1]*mm << " Point[2] = "<<Point[2]*mm<<G4endl;
    //G4cout << " z_max_QD0_R = "<<z_max_QD0_R*cm << " z_min_QD0_R = "<< z_min_QD0_R*cm << " innerRadius_QD0_T = "<<innerRadius_QD0_T*cm<<G4endl;

    if (flag_TurnOFFBottomField == "TurnOFFBottomFieldON"){
	if( (z_QD1_R_U_*mm < z_max_QD1_R_U_*cm) && (z_QD1_R_U_*mm > z_min_QD1_R_U_*cm) && 
	    ((sqr(x_QD1_R_U_*mm-x_max_QD1_R_U_*cm)+sqr(y_QD1_R_U_*mm))<sqr(innerRadius_QD1*cm)) ){
	    //QD1 right upper
		Bx = y_QD1_R_U_*gQD1/100.0*tesla;
		By = (x_QD1_R_U_ - x_max_QD1_R_U_*cm)*gQD1/100.0*tesla;
		
		
		//fprintf(streamQD1_R_U," x = %10.5f, y = %10.5f, z = %10.5f, Bx = %10.5f, By = %10.5f, Bz = %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx*100, By*100, Bz*100 );
		//fprintf(streamQD1_R_U," x_QD1_R_U_        = %10.5f \n",x_QD1_R_U_ );
		//fprintf(streamQD1_R_U," x_max_QD1_R_U_*cm = %10.5f \n",x_max_QD1_R_U_*cm );
		//fprintf(streamQD1_R_U," x_tmp_R_U_*cm     = %10.5f \n",x_tmp_R_U_*cm );
		
		//fprintf(streamQD1_R_U," %10.5f %10.5f %10.5f %10.5f %10.5f %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx/tesla*10, By/tesla*10, Bz/tesla*10 );
		
		return true;
	}
	else if( (z_QD1_L_U_*mm > z_max_QD1_L_U_*cm) && (z_QD1_L_U_*mm < z_min_QD1_L_U_*cm) && 
		 ((sqr(x_QD1_L_U_*mm-x_max_QD1_L_U_*cm)+sqr(y_QD1_L_U_*mm))<sqr(innerRadius_QD1*cm)) ){
	    //QD1 left upper	
	    Bx = y_QD1_L_U_*gQD1/100.0*tesla;
	    By = (x_QD1_L_U_ - x_max_QD1_L_U_*cm)*gQD1/100.0*tesla;
	    
	    //fprintf(streamQD1_L_U," x = %10.5f, y = %10.5f, z = %10.5f, Bx = %10.5f, By = %10.5f, Bz = %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx*100, By*100, Bz*100 );
	    
	    //fprintf(streamQD1_L_U," %10.5f %10.5f %10.5f %10.5f %10.5f %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx/tesla*10, By/tesla*10, Bz/tesla*10 );
	    
	    return true;
	}
	else{
	    Bx = 0.;
	    By = 0.;
	    return false;
	}
    }

    if (flag_TurnOFFBottomField == "TurnOFFBottomFieldOFF"){
	if( (Point[2] < z_max_QD0_R*cm) && (Point[2] > z_min_QD0_R*cm) && 
	    ((sqr(Point[0])+sqr(Point[1]))<sqr(innerRadius_QD0_T*cm)) ){

	    //QD0 right	

	    Bx = Point[1]*gQD0/100.0*tesla;
	    By = Point[0]*gQD0/100.0*tesla;	
	    //fprintf(streamQD0_R," x = %10.5f, y = %10.5f, z = %10.5f, Bx = %10.5f, By = %10.5f, Bz = %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx*100, By*100, Bz*100 );
	    //fprintf(streamQD0_R," %10.5f %10.5f %10.5f %10.5f %10.5f %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx/tesla*10, By/tesla*10, Bz/tesla*10 );	    
	    return true; 
	}
	else if( (Point[2] > z_max_QD0_L*cm) && (Point[2] < z_min_QD0_L*cm) && 
		 ((sqr(Point[0])+sqr(Point[1]))<sqr(innerRadius_QD0_T*cm)) ){
	    //QD0 left

	    Bx = Point[1]*gQD0/100.0*tesla;
	    By = Point[0]*gQD0/100.0*tesla;	    
	    //fprintf(streamQD0_L," x = %10.5f, y = %10.5f, z = %10.5f, Bx = %10.5f, By = %10.5f, Bz = %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx*100, By*100, Bz*100 );
	    //fprintf(streamQD0_L," %10.5f %10.5f %10.5f %10.5f %10.5f %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx/tesla*10, By/tesla*10, Bz/tesla*10 );
	    return true;
	}
	else if( (z_QD1_R_U_*mm < z_max_QD1_R_U_*cm) && (z_QD1_R_U_*mm > z_min_QD1_R_U_*cm) && 
		 ((sqr(x_QD1_R_U_*mm-x_max_QD1_R_U_*cm)+sqr(y_QD1_R_U_*mm))<sqr(innerRadius_QD1*cm)) ){
	    //QD1 right upper	  
	    if(((x_max_QD1_R_U_-x_min_QD1_R_U_)*(x_max_QD1_R_U_-x_min_QD1_R_U_)) < 0.00000000000001){
		Bx = y_QD1_R_U_*gQD1/100.0*tesla;
		By = (x_QD1_R_U_ - x_max_QD1_R_U_*cm)*gQD1/100.0*tesla;
		
		// fprintf(streamQD1_R_U," x = %10.5f, y = %10.5f, z = %10.5f, Bx = %10.5f, By = %10.5f, Bz = %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx*100, By*100, Bz*100 );
                // fprintf(streamQD1_R_U," x_QD1_R_U_        = %10.5f \n",x_QD1_R_U_ );
                // fprintf(streamQD1_R_U," x_max_QD1_R_U_*cm = %10.5f \n",x_max_QD1_R_U_*cm );
                // fprintf(streamQD1_R_U," x_tmp_R_U_*cm     = %10.5f \n",x_tmp_R_U_*cm );
		
    
		//fprintf(streamQD1_R_U," %10.5f %10.5f %10.5f %10.5f %10.5f %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx/tesla*10, By/tesla*10, Bz/tesla*10 );
		return true;
	    }
 	    else{
 		G4cout<<"!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!"<<G4endl;
 		G4cout<<"  ExN02MagneticField.cc"<<G4endl;
 		G4cout<<"  ExN02MagneticField::SetField"<<G4endl;
 		G4cout<<"  QD1 right upper"<<G4endl;
 		G4cout<<"  x_max_QD1_R_U_-x_min_QD1_R_U_"<<(x_max_QD1_R_U_-x_min_QD1_R_U_)<<G4endl;
 		G4cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<G4endl;
 		return false;
 	    }
	}
	else if( (z_QD1_L_D_*mm > z_max_QD1_L_D_*cm) && (z_QD1_L_D_*mm < z_min_QD1_L_D_*cm) && 
		 ((sqr(x_QD1_L_D_*mm-x_max_QD1_L_D_*cm)+sqr(y_QD1_L_D_*mm))<sqr(innerRadius_QD1*cm)) ){
	    //QD1 left bottom	
	    if(((x_max_QD1_L_D_-x_min_QD1_L_D_)*(x_max_QD1_L_D_-x_min_QD1_L_D_)) < 0.000000000001){
		Bx = y_QD1_L_D_*gQD1/100.0*tesla;
		By = (x_QD1_L_D_ - x_max_QD1_L_D_*cm)*gQD1/100.0*tesla;
		
		
		// fprintf(streamQD1_L_D," x = %10.5f, y = %10.5f, z = %10.5f, Bx = %10.5f, By = %10.5f, Bz = %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx*100, By*100, Bz*100 );
                // fprintf(streamQD1_L_D," x_QD1_L_D_        = %10.5f \n",x_QD1_L_D_ );
                // fprintf(streamQD1_L_D," x_max_QD1_L_D_*cm = %10.5f \n",x_max_QD1_L_D_*cm ); 
                // fprintf(streamQD1_L_D," x_tmp_R_U_*cm     = %10.5f \n",x_tmp_L_D_*cm );
		
	    
		//fprintf(streamQD1_L_D," %10.5f %10.5f %10.5f %10.5f %10.5f %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx/tesla*10, By/tesla*10, Bz/tesla*10 );
	    
		return true;
	    }
 	    else{
 		G4cout<<"!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!"<<G4endl;
 		G4cout<<"  ExN02MagneticField.cc"<<G4endl;
 		G4cout<<"  ExN02MagneticField::SetField"<<G4endl;
 		G4cout<<"  QD1 left bottom"<<G4endl;
 		G4cout<<"  x_max_QD1_L_D_-x_min_QD1_L_D_"<<(x_max_QD1_L_D_-x_min_QD1_L_D_)<<G4endl;
 		G4cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<G4endl;
 		Bx = 0.;
 		By = 0.;
 		return false;
 	    }
	}
	else if( (z_QD1_R_D_*mm < z_max_QD1_R_D_*cm) && (z_QD1_R_D_*mm > z_min_QD1_R_D_*cm) && 
		 ((sqr(x_QD1_R_D_*mm-x_max_QD1_R_D_*cm)+sqr(y_QD1_R_D_*mm))<sqr(innerRadius_QD1*cm)) ){
	    //QD1 right bottom	  
	    if(((x_max_QD1_R_D_-x_min_QD1_R_D_)*(x_max_QD1_R_D_-x_min_QD1_R_D_)) < 0.000000000001){
		Bx = y_QD1_R_D_*gQD1/100.0*tesla;
		By = (x_QD1_R_D_ - x_max_QD1_R_D_*cm)*gQD1/100.0*tesla;
		//fprintf(streamQD1_R_D," x = %10.5f, y = %10.5f, z = %10.5f, Bx = %10.5f, By = %10.5f, Bz = %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx*100, By*100, Bz*100 );
		//fprintf(streamQD1_R_D," %10.5f %10.5f %10.5f %10.5f %10.5f %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx/tesla*10, By/tesla*10, Bz/tesla*10 );		
		return true;
	    }
	    else{
 		G4cout<<"!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!"<<G4endl;
 		G4cout<<"  ExN02MagneticField.cc"<<G4endl;
 		G4cout<<"  ExN02MagneticField::SetField"<<G4endl;
 		G4cout<<"  QD1 right bottom"<<G4endl;
 		G4cout<<"  x_max_QD1_R_D_-x_min_QD1_R_D_"<<(x_max_QD1_R_D_-x_min_QD1_R_D_)<<G4endl;
 		G4cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<G4endl;
 		Bx = 0.;
 		By = 0.;
 		return false;
	    }
	}
	else if( (z_QD1_L_U_*mm > z_max_QD1_L_U_*cm) && (z_QD1_L_U_*mm < z_min_QD1_L_U_*cm) && 
		 ((sqr(x_QD1_L_U_*mm-x_max_QD1_L_U_*cm)+sqr(y_QD1_L_U_*mm))<sqr(innerRadius_QD1*cm)) ){
	    //QD1 left upper
	    if(((x_max_QD1_L_U_-x_min_QD1_L_U_)*(x_max_QD1_L_U_-x_min_QD1_L_U_)) < 0.000000000001){
		Bx = y_QD1_L_U_*gQD1/100.0*tesla;
		By = (x_QD1_L_U_ - x_max_QD1_L_U_*cm)*gQD1/100.0*tesla;
		//fprintf(streamQD1_L_U," x = %10.5f, y = %10.5f, z = %10.5f, Bx = %10.5f, By = %10.5f, Bz = %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx*100, By*100, Bz*100 );	    
		//fprintf(streamQD1_L_U," %10.5f %10.5f %10.5f %10.5f %10.5f %10.5f \n", Point[0]/10, Point[1]/10, Point[2]/10, Bx/tesla*10, By/tesla*10, Bz/tesla*10 );
		return true;
	    }
	    else{
		G4cout<<"!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!"<<G4endl;
 		G4cout<<"  ExN02MagneticField.cc"<<G4endl;
 		G4cout<<"  ExN02MagneticField::SetField"<<G4endl;
 		G4cout<<"  QD1 left upper"<<G4endl;
 		G4cout<<"  x_max_QD1_L_U_-x_min_QD1_L_U_"<<(x_max_QD1_L_U_-x_min_QD1_L_U_)<<G4endl;
 		G4cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<G4endl;
 		Bx = 0.;
 		By = 0.;
 		return false;
	    }
	}
	else{
	    Bx = 0.;
	    By = 0.;
	    return false;
	}
    }
    

    return false;
}

G4double ExN02MagneticField::RotationZ(G4double z, G4double x, G4int Ind){

     if(Ind == 1){
	 return z*cos4_07-x*sin4_07;
     }

     if(Ind == -1){
	 return z*cos4_07+x*sin4_07;
     }

     return 0;
}

G4double ExN02MagneticField::RotationX(G4double z, G4double x, G4int Ind){

     if(Ind ==1){
	 return z*sin4_07+x*cos4_07;
     }

     if(Ind ==-1){
	 return -z*sin4_07+x*cos4_07;
     }

     return 0;
}
