#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
Int_t culc(){
    string flag, flag2;
    flag = "check off";
    flag2 = "my calculation on";
    if(flag2 == "my calculation on"){
	Double_t cos = (TMath::Cos(TMath::Pi()*4.07/180));
	Double_t sin = (TMath::Sin(TMath::Pi()*4.07/180));
	cout<<cos<<endl;
	cout<<sin<<endl;
	cout<< corEndVlikeTube()<<endl;
	//return 0;
    }
    //Central tube of the beampipe (BP) (see DAFNEUP-003-000.pdf or 01_DAFNEUP-003-000.pdf)
    Double_t length_Tube1 = 48.5;         //cm +/-0.02 cm
    Double_t innerRadius_Tube1 = 5.5/2;   //cm +/-0.01 cm
    Double_t outerRadius_Tube1 = 5.9/2;   //cm +/-0.01 cm

    //Conecter between central tube of the beampipe and V-like tube
    //(see DAFNEUP-001-001.pdf or 02_DAFNEUP-001-001.pdf) 
    Double_t length_Tube2 = 30.13;        // cm
    Double_t length_Tube2_C = 14.15;      // cm circular part (in section) of the Tube2
    Double_t length_Tube2_E = length_Tube2 - length_Tube2_C;  //cm ellipsoidal part 
                                                              //(in section) of the Tube2

    //V-like tube (see DAFNEUP-001-005.pdf or  03_DAFNEUP-001-005.pdf)  
    Double_t length_Tube3 = 28.272; // cm
    Double_t dist_Tube3   = 3.894;  // cm distans detween center of the end of the
                                    // v-like tube and z-axis

    //Tube conect to the V-like tube (see DAFNEUP-001-003.pdf or 04_DAFNEUP-001-003.pdf) 
    Double_t length_Tube4 = 58.07;      //cm +/- 0.02
    
    //End of the BP (see DAFNEUP-001-003.pdf or 05_DAFNEUP-001-003.pdf) 
    //All right-hand part of the BP you can see in DAFNEUP-001-000.pdf or 06_DAFNEUP-001-000.pdf
    Double_t length_Tube5 = 86.9;      //cm +/- 0.02
    Double_t length_Tube5_C  = 56.0;      // cm circular part (in section) of the Tube5
    Double_t length_Tube5_Co = length_Tube5 - length_Tube5_C;  //cm cone part (in section)
 
//---------------------------------------------------------------------------
//  Coordinates of the centres of the tubs
    Double_t cos4_07 = (TMath::Cos(TMath::Pi()*4.07/180));
    Double_t sin4_07 = (TMath::Sin(TMath::Pi()*4.07/180));
    Double_t tan4_07 = sin4_07/cos4_07;

    if(flag2 == "my calculation on"){
	Double_t L = length_Tube1/2.+ length_Tube2;
	Double_t length_Tube3_TU = TMath::Sqrt((3.894-0.4)*(3.894-0.4)+(28.272-6.7/2*sin4_07)*(28.272-6.7/2*sin4_07));
	Double_t zlength_Tube3_TU = (28.272-6.7/2*sin4_07);
	cout<< " length_Tube3_TU : "<< length_Tube3_TU<<endl;
	cout<< " zlength_Tube3_TU : "<< zlength_Tube3_TU<<endl;
	Double_t angle_r = TMath::ACos(zlength_Tube3_TU/length_Tube3_TU);
	Double_t angle_d = angle_r * 180/(TMath::Pi());
	cout<< "angle_r : "<< angle_r<< " angle_d : "<< angle_d <<endl;
	cout<<" L = "<< L <<endl;
	cout<<14.439/2.*tan4_07<<endl;
	cout<<28.272 - 6.7/2*sin4_07 <<endl;

	Double_t tan1_435 = TMath::Tan(TMath::Pi()*1.435/180.);
        
	cout<< " 6.3 = "<<2*(30.13 - 14.15)*tan1_435+5.5<<endl;
	Double_t sin2_87 = TMath::Sin(TMath::Pi()*2.87/2/180.);
	Double_t cos2_87 = TMath::Cos(TMath::Pi()*2.87/2/180.);
	cout<< " sin2.87 = "<< sin2_87<<endl;
	cout<< " cos2.87 = "<< cos2_87<<endl;
	printf("sin2.87 = %20.19f \n",sin2_87);
	printf("cos2.87 = %20.19f \n",cos2_87);


	Double_t sin7_104 = TMath::Sin(TMath::Pi()*7.104/180.);
	Double_t cos7_104 = TMath::Cos(TMath::Pi()*7.104/180.);
	cout<< " sin7_104 = "<< sin7_104<<endl;
	cout<< " cos7_104 = "<< cos7_104<<endl;
	printf("sin7_104 = %20.19f \n",sin7_104);
	printf("cos7_104 = %20.19f \n",cos7_104);
	return 0;
    }

    //Central tube of the beampipe
    Double_t x_Tube1 = 0;
    Double_t y_Tube1 = 0;
    Double_t z_Tube1 = 0;
    cout<<"--Central tube of the beampipe--"<<endl;
    cout<< setw(6)<< " x :"<< setw(10)<< x_Tube1<< setw(6)<< " z :"<<setw(10)<< z_Tube1<<endl<<endl;
    
    //Conecter between central tube of the beampipe and V-like tube
    Double_t x_Tube2_C_R = 0;
    Double_t y_Tube2_C_R = 0;
    Double_t z_Tube2_C_R = length_Tube1/2+length_Tube2_C/2;
    Double_t x_Tube2_E_R = 0;
    Double_t y_Tube2_E_R = 0;
    Double_t z_Tube2_E_R = length_Tube1/2 + length_Tube2_C + length_Tube2_E/2;
    cout<<"--Conecter between central tube of the beampipe and V-like tube--"<<endl;
    cout<<" circular part (in section) of the Tube2 "<<endl;
    cout<< setw(6)<< " x :"<< setw(10)<< x_Tube2_C_R<< setw(6)<< " z :"<<setw(10)<< z_Tube2_C_R<<endl;
    cout<<" ellipsoidal part (in section) of the Tube2 "<<endl;
    cout<< setw(6)<< " x :"<< setw(10)<< x_Tube2_E_R<< setw(6)<< " z :"<<setw(10)<< z_Tube2_E_R<<endl<<endl;
 
    Double_t x_Tube2_C_L = 0;
    Double_t y_Tube2_C_L = 0;
    Double_t z_Tube2_C_L = -z_Tube2_C_R;
    Double_t x_Tube2_E_L = 0;
    Double_t y_Tube2_E_L = 0;
    Double_t z_Tube2_E_L = -z_Tube2_E_R ;

    //Coordinates of the ends of V-like tube
    Double_t x_Tube3_R_U = dist_Tube3;
    Double_t y_Tube3_R_U = 0;
    Double_t z_Tube3_R_U = length_Tube1/2 + length_Tube2 + length_Tube3 - corEndVlikeTube();
    Double_t x_Tube3_R_D = -x_Tube3_R_U;
    Double_t y_Tube3_R_D = 0;
    Double_t z_Tube3_R_D = z_Tube3_R_U;  
    cout<<"--Coordinates of the ends of V-like tube--"<<endl;
    cout<< setw(6)<< " x :"<< setw(10)<< x_Tube3_R_U<< setw(6)<< " z :"<<setw(10)<< z_Tube3_R_U<<endl<<endl;
    cout<< " corEndVlikeTube()  "<< corEndVlikeTube() <<endl;
    Double_t x_Tube3_L_U = x_Tube3_R_U;
    Double_t y_Tube3_L_U = 0;
    Double_t z_Tube3_L_U = -z_Tube3_R_U;
    Double_t x_Tube3_L_D = -x_Tube3_L_U;
    Double_t y_Tube3_L_D = 0;
    Double_t z_Tube3_L_D = z_Tube3_L_U;

    //Tube conect to the V-like tube 
    Double_t x_Tube4_R_U = dist_Tube3 + length_Tube4/2*sin4_07;
    Double_t y_Tube4_R_U = 0;
    Double_t z_Tube4_R_U = z_Tube3_R_U + length_Tube4/2*cos4_07;
    Double_t x_Tube4_R_D = -x_Tube4_R_U;
    Double_t y_Tube4_R_D = 0;
    Double_t z_Tube4_R_D = z_Tube4_R_U;
    cout<<"--Tube conect to the V-like tube--"<<endl;
    cout<< setw(6)<< " x :"<< setw(10)<< x_Tube4_R_U<< setw(6)<< " z :"<<setw(10)<< z_Tube4_R_U<<endl<<endl;

    Double_t x_Tube4_L_U = x_Tube4_R_U;
    Double_t y_Tube4_L_U = 0;
    Double_t z_Tube4_L_U = -z_Tube4_R_U;
    Double_t x_Tube4_L_D = -x_Tube4_L_U;
    Double_t y_Tube4_L_D = 0;
    Double_t z_Tube4_L_D = z_Tube4_L_U;

    //End of the BP
    // cm circular part (in section) of the Tube5
    Double_t x_Tube5_C_R_U = dist_Tube3 + length_Tube4*sin4_07 + length_Tube5_C/2*sin4_07;
    Double_t y_Tube5_C_R_U = 0;
    Double_t z_Tube5_C_R_U = z_Tube3_R_U + length_Tube4*cos4_07 + length_Tube5_C/2*cos4_07;
    Double_t x_Tube5_C_R_D = -x_Tube5_C_R_U;
    Double_t y_Tube5_C_R_D = 0;
    Double_t z_Tube5_C_R_D = z_Tube5_C_R_U;
    cout<<"--End of the BP--"<<endl;
    cout<< " circular part (in section) of the Tube5"<<endl;
    cout<< setw(6)<< " x :"<< setw(10)<< x_Tube5_C_R_U<< setw(6)<< " z :"<<setw(10)<< z_Tube5_C_R_U<<endl;

    Double_t x_Tube5_C_L_U = x_Tube5_C_R_U;
    Double_t y_Tube5_C_L_U = 0;
    Double_t z_Tube5_C_L_U = -z_Tube5_C_R_U;
    Double_t x_Tube5_C_L_D = -x_Tube5_C_L_U;
    Double_t y_Tube5_C_L_D = 0;
    Double_t z_Tube5_C_L_D = z_Tube5_C_L_U;
    // cm cone part (in section) of the Tube5
    Double_t x_Tube5_Co_R_U = dist_Tube3 + length_Tube4*sin4_07 + length_Tube5_C*sin4_07 
                                                                + length_Tube5_Co/2*sin4_07;
    Double_t y_Tube5_Co_R_U = 0;
    Double_t z_Tube5_Co_R_U =  z_Tube3_R_U + length_Tube4*cos4_07 + length_Tube5_C*cos4_07
                                                                  + length_Tube5_Co/2*cos4_07;
    Double_t x_Tube5_Co_R_D = -x_Tube5_Co_R_U;
    Double_t y_Tube5_Co_R_D = 0;
    Double_t z_Tube5_Co_R_D = z_Tube5_Co_R_U;
    cout<< " cone part (in section) of the Tube5"<<endl;
    cout<< setw(6)<< " x :"<< setw(10)<< x_Tube5_Co_R_U<< setw(6)<< " z :"<<setw(10)<< z_Tube5_Co_R_U<<endl<<endl;

    Double_t x_Tube5_Co_L_U = x_Tube5_Co_R_U;
    Double_t y_Tube5_Co_L_U = 0;
    Double_t z_Tube5_Co_L_U = -z_Tube5_Co_R_U;
    Double_t x_Tube5_Co_L_D = -x_Tube5_Co_L_U;
    Double_t y_Tube5_Co_L_D = 0;
    Double_t z_Tube5_Co_L_D = z_Tube5_Co_L_U;

    if(flag == "check on"){
	TCanvas *c1 = new TCanvas("c1","BP geometry",10,10,500,500);
	Double_t x[20];
	Double_t y[20];
//----------------------------
	y[0] = x_Tube2_C_R;
	x[0] = z_Tube2_C_R;
	y[1] = x_Tube2_E_R;
	x[1] = z_Tube2_E_R;
    
	y[2] = x_Tube2_C_L;
	x[2] = z_Tube2_C_L;
	y[3] = x_Tube2_E_L;
	x[3] = z_Tube2_E_L;
//----------------------------
	y[4] = x_Tube3_R_U;
	x[4] = z_Tube3_R_U;
	y[5] = x_Tube3_R_D;
	x[5] = z_Tube3_R_D;
    
	y[6] = x_Tube3_L_U;
	x[6] = z_Tube3_L_U;
	y[7] = x_Tube3_L_D;
	x[7] = z_Tube3_L_D;
//----------------------------
	y[8] = x_Tube4_R_U;
	x[8] = z_Tube4_R_U;
	y[9] = x_Tube4_R_D;
	x[9] = z_Tube4_R_D;

	y[10] = x_Tube4_L_U;
	x[10] = z_Tube4_L_U;
	y[11] = x_Tube4_L_D;
	x[11] = z_Tube4_L_D;
//----------------------------	
	y[12] = x_Tube5_C_R_U;
	x[12] = z_Tube5_C_R_U;
	y[13] = x_Tube5_C_R_D;
	x[13] = z_Tube5_C_R_D;
	
	y[14] = x_Tube5_C_L_U;
	x[14] = z_Tube5_C_L_U;
	y[15] = x_Tube5_C_L_D;
	x[15] = z_Tube5_C_L_D;
	
	y[16] = x_Tube5_Co_R_U;
	x[16] = z_Tube5_Co_R_U; 
	y[17] = x_Tube5_Co_R_D;
	x[17] = z_Tube5_Co_R_D;
	
	y[18] = x_Tube5_Co_L_U;
	x[18] = z_Tube5_Co_L_U;
	y[19] = x_Tube5_Co_L_D;
	x[19] = z_Tube5_Co_L_D;
//----------------------------	
	for( Int_t i = 0; i<20;i++){
	    cout<< setw(4)<< i<< setw(9)<< x[i]<< setw(9)<< y[i]<<endl;
	}

	TGraph *g1 = new TGraph(20,x,y);
	g1->Draw("A*");
    }

    return 0;
}

Double_t corEndVlikeTube(){
    Double_t sin4_07 = (TMath::Sin(TMath::Pi()*4.07/180));
    Double_t Diam = 6.7;       //cm (see DAFNEUP-001-005.pdf or  03_DAFNEUP-001-005.pdf)  
    return  Diam/2*sin4_07;
}
