#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Int_t anaSpectrum(){
    // reading a text file

    //-----------FLAGS!!!!!!!!!!!!-------------
    string flag_morrePlotON;
    flag_morrePlot = "morrePlotON";
    //flag_morrePlot = "morrePlotOFF";
        string flag_integralPlotON;
        flag_integralPlotON = "integralPlotON";
        //flag_integralPlotON = "integralPlotOFF";
    //-----------------------------------------

    if(flag_morrePlot == "morrePlotOFF"){ 

	Double_t x,y;
	Int_t i;

	i = 0;
	
	TCanvas *c1 = new TCanvas("c1","spectrum",10,10,800,400);
	c1->SetFillColor(10);
	TH1F *h1 = new TH1F("h1","compton",5000,0,0.60);
	
	//ifstream myfile("spectrum100000PdWO4.dat");
	ifstream myfile("spectrumPhotRight.dat");
   
	if (myfile.is_open()){
	    while (!myfile.eof() ){
		//while (i<100){
		myfile >>x >>y;
		h1->SetBinContent(i,y);
		//cout<<i<<"  " << x<<" "<< y << endl;
		i++;
	    }
	    myfile.close();
	}
	else cout << "Unable to open file"; 
	
	h1->Draw();
    }

    if(flag_morrePlot == "morrePlotON"){ 

	Double_t x,y, yint1, yint2, yint3;
	//Double_t x2,y2,i;
	Int_t i = 0;
	yint = 0;

	TCanvas *c1 = new TCanvas("c1","spectrum",10,10,800,400);
	c1->SetFillColor(10);

	TH1F *h1 = new TH1F("h1","With whole shielding",5000,0,0.60);
	TH1F *h2 = new TH1F("h2","No front lead brick",5000,0,0.60);
	TH1F *h3 = new TH1F("h3","Without shielding",5000,0,0.60);	
	TH1F *hint1 = new TH1F("hint1","integral spectrum",5000,0,0.60);
	TH1F *hint2 = new TH1F("hint2","integral spectrum",5000,0,0.60);
	TH1F *hint3 = new TH1F("hint3","integral spectrum",5000,0,0.60);

	ifstream myfile1("spectrumPhotRight01.dat"); //with whole shielding 
	ifstream myfile2("spectrumPhotRight03.dat"); //no front lead brick
   	ifstream myfile3("spectrumPhotRight04.dat"); //without shielding

	if (myfile1.is_open() && myfile2.is_open()){
	    //while(!myfile1.eof()||!myfile2.eof() ){
	    while(!myfile1.eof()){
		//while (i<100){
		myfile1 >>x >>y;
		h1->SetBinContent(i,y);
		yint1 = yint1 + y;
		myfile2 >>x >>y;
		h2->SetBinContent(i,y);
		yint2 = yint2 + y;
		myfile3 >>x >>y;
		h3->SetBinContent(i,y);
		yint3 = yint3 + y;
		if (flag_integralPlotON == "integralPlotON"){
                    hint1->SetBinContent(i,(31045 - yint1)); //19676
                    hint2->SetBinContent(i,(32581 - yint2));
                    hint3->SetBinContent(i,(31938 - yint3));
		}
		cout<<i<<"  " << x<<" "<< yint1<< endl;
		i++;
	    }
	    myfile1.close();
	    myfile2.close();
	    myfile3.close();
	}
	else cout << "Unable to open file";

	h1->SetLineColor(1);
	h2->SetLineColor(2);
	h3->SetLineColor(3);

	h1->Draw();
	h2->Draw("same");
	h3->Draw("same");

	if (flag_integralPlotON == "integralPlotON"){
	    TCanvas *c2 = new TCanvas("c2","integral spectrum",10,10,800,400);
	    c2->SetFillColor(10);
	    hint1->SetLineColor(1);
	    hint2->SetLineColor(2);
	    hint3->SetLineColor(3);
	    hint1->Draw();
	    hint3->Draw("same");
	    hint2->Draw("same");
	}

    }

    return 0;
}
