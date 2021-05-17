#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

Int_t anaConvStTou(){
   
    ifstream myfileLab("labdata.txt");
    ifstream myfileStep("SteppingActionTou01.txt");
    ofstream myfileTouDat("inputDataTou.txt");

    //labdata.dat cm , GeV
    Double_t x1,y1,z1, px1,py1,pz1,w;

    //labdata.dat mm , MeV
    Double_t x2,y2,z2, px2,py2,pz2;

    Int_t n;
    Int_t i;
    Int_t j = 0;
 
    if (myfileLab.is_open()){
	if (myfileStep.is_open()){
	    if (myfileTouDat.is_open()){
		while(!myfileLab.eof() ){
		    //while(j<100 ){
		    myfileLab >>x1 >>y1>>z1 >>px1>>py1 >>pz1>>w;
		    n = w;
		    myfileStep >>x2 >>y2 >>z2 >>px2 >>py2 >>pz2;
		    for(i = 0;i<n;i++){
			myfileTouDat<<setw(15)<<x2<<setw(15)<<y2<<setw(15)<<z2<<setw(15)<<px2<<setw(15)<<py2<<setw(15)<<pz2<<endl;
		    }
		    if(j%100 == 0){
			cout<<j<< endl;
		    }
		    j++;
		    //cout<<"  " << x<<" "<< y << endl;
		}
	    }
	    else cout << "ERROR : inputDataTou.txt"; 
	}
	else cout << "ERROR : SteppingActionTou01.txt"; 
    }
    else cout << "ERROR : labdata.dat"; 
   
    myfileLab.close();
    myfileStep.close();
    myfileTouDat.close();

    return 0;
}
