#include <iostream>
#include <fstream>
#include <iomanip>
#include "math.h"
#include "TMath.h"

using namespace std;

Int_t genlabdataTest(){
    ofstream myfile;
    ofstream myfile01;

    Float_t x, y, z, px, py, pz, p;
    Float_t alpha, Ek_min, Ek_max, Ek, Etest;

    Int_t i, N;

    Double_t Pi = TMath::Pi();

    N = 1000;
    Ek_min = 200.;
    Ek_max = 511.;

    myfile.open ("labdataTest.txt");
    myfile01.open ("labdataTest01.txt");

    if(myfile.is_open()){
	for( i = 0; i<N; i++){
	    x = 1.;
	    y = 0.0;
	    z = 0.0;
	    alpha = i*180.0/(N-1);
	    Ek = i*(Ek_max - Ek_min)/(N - 1) + Ek_min;
	    p = Ek*sqrt(1+2.*0.511/Ek);
	    px = -p*sin(alpha/180*Pi);
	    py = 0.0;
	    pz = p*cos(alpha*Pi/180);
	    Etest = sqrt(px*px + py*py + pz*pz + 0.511*0.511) - 0.511; 
	    myfile<<setw(10)<<x<<setw(10)<<y<<setw(10)<<z<<setw(15)<<px<<setw(15)<<py<<setw(15)<<pz<<endl;
	    myfile01<<setw(10)<<x<<setw(10)<<y<<setw(10)<<z<<setw(15)<<px<<setw(15)<<py<<setw(15)<<pz<<setw(15)<<Etest<<endl;
	    cout<<setw(10)<<x<<setw(10)<<y<<setw(10)<<z<<setw(15)<<px<<setw(15)<<py<<setw(15)<<pz<<endl;
	    //cout<<setw(10)<<alpha<<endl;
            //printf("%20.18f\n",pz);
	}
    }
    else{
	cout<<"ERROR : labdataTest.txt is not opened"<<endl;
    }
    myfile.close();
    return 0;
}
