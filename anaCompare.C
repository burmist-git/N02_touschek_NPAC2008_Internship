#include <iostream>
#include <fstream>
using namespace std;

Int_t anaCompare(){
    
    ifstream stream;
    ifstream stream1;

    Float_t eDet1,eDet2,eDet3,eDet4, eTot;


    Int_t Nev = 0;        //number of the events with Etot > 0.
    Int_t Nthreshold = 0; //number of the events with E < E of the threshold
    Int_t NtotEv = 10000;  //total number of events

    const Int_t Nth = 120;  //number of the different thresholds
    Double_t Emin = 0.;    //MeV for efficiently
    Double_t Emax = 2400;    //MeV for efficiently

    Double_t ESmin = 0.;   //MeV for energy in crislals
    Double_t ESmax = 520;  //MeV for energy in crislals
    Int_t NbinS = 500;      //MeV for energy in crislals

    Int_t index;
    Double_t array[Nth];
    Double_t array2[Nth];
    Double_t bin_width = (Emax - Emin)/Nth;
    for(i = 0;i<Nth;i++){
	array[i] = 0.;
	//array2[i] = 0.;
    }

    TCanvas *c1 = new TCanvas("c1","spectrum",10,10,1000,1000);
    
    c1->Divide(3,2);
   
    TH1F *h1 = new TH1F("h1","spectrum1",NbinS,ESmin,ESmax);
    TH1F *h2 = new TH1F("h2","spectrum2",NbinS,ESmin,ESmax);
    TH1F *h3 = new TH1F("h3","spectrum3",NbinS,ESmin,ESmax);
    TH1F *h4 = new TH1F("h4","spectrum4",NbinS,ESmin,ESmax);
    TH1F *h5 = new TH1F("h5","spectrum5",NbinS,ESmin,ESmax);
    TH1F *h6 = new TH1F("h6","spectrum6",Nth,Emin,Emax);
    TH1F *h62 = new TH1F("h6","spectrum6",Nth,Emin,Emax);

    //stream.open("20MeV_E_leonid_Data_10e4.txt");
    //stream.open("5MeV_E_leonid_Data_10e4.txt");
    //stream.open("1MeV_E_leonid_Data_10e4.txt");
    stream.open("spectrum.txt");

    //stream.open("p4SpPhot_g4_511MeV_E_13450_geom23_fieldON_cutsA11.txt");
    //stream.open("./dataALL/Phot/p4Phot_g4_511MeV_E_10e4_geom21_fieldOFF_cuts33.txt");

    //stream.open("50MeV_E_100000.txt");
    //stream.open("100MeV_E_100000.txt");
    //stream.open("200MeV_E_100000.txt");
    //stream.open("300MeV_E_100000.txt");
    //stream.open("400MeV_E_100000.txt");
    //stream.open("510MeV_E_100000.txt");

    //stream.open("50MeV_G_100000.txt");
    //stream.open("100MeV_G_100000.txt");
    //stream.open("200MeV_G_100000.txt");
    //stream.open("300MeV_G_100000.txt");
    //stream.open("400MeV_G_100000.txt");
    //stream.open("510MeV_G_100000.txt");

    //stream.open("p1_100000.txt");
    //stream.open("p2_100000.txt");
    //stream.open("p3_100000.txt");
    //stream.open("p4_100000.txt");
    //stream.open("p5_100000.txt");
    //stream.open("p6_100000.txt");



    if (stream.is_open()){
	while(!stream.eof()){
	    //if(!stream.eof()){
	    stream>>eDet1>>eDet2>>eDet3>>eDet4;
	    //cout<<eDet2<<endl;
	    eTot = eDet1 + eDet2 + eDet3 + eDet4;
	    h1->Fill(eDet1);
	    h2->Fill(eDet2);
	    h3->Fill(eDet3);
	    h4->Fill(eDet4);
	    h5->Fill(eTot);
	    if(eTot!=0){
		index = int(floor((eTot - Emin)/bin_width));
		array[index]++;
		Nev = Nev + 1;
	    }
	    //cout<<eDet1<<endl;
	    //}
	}
    }
    else{
	cout<<"file not open"<<endl;
    }

    //Nev = Nev - 1;

    Float_t eff = 0;
    Float_t effErr = 0;
    Nthreshold = 0;
    for( i = 0; i<Nth; i++){
	eff = (Float_t)(Nev - Nthreshold)/(Float_t)NtotEv;
	effErr = sqrt(eff*(1-eff)/NtotEv);
	h6->SetBinContent(i+1,eff);
	cout<<i<<" "<<eff<<endl;
	h6->SetBinError(i+1,effErr);
	Nthreshold = Nthreshold + array[i];
    }

    //stream1.open("1.txt");
    //stream1.open("1MeV_E_benoit_10000_02.txt");
    //stream1.open("1MeV_E_benoit_10000.txt");
    //stream1.open("10MeV_E_benoit_10000.txt");
    //stream1.open("5MeV_E_benoit_10000.txt");
    //stream1.open("1MeV_G_benoit_10000.txt");
    //stream1.open("10MeV_G_benoit_10000.txt");
    //stream1.open("5MeV_G_benoit_10000.txt");
    //stream1.open("1MeV_E_benoit_10000_05.txt");
    //stream1.open("1MeV_E_new_Benoit.txt");
    //stream1.open("1MeV_E_new_Benoit_02.txt");
    //stream1.open("5MeV_E_new_Benoit.txt");
    //stream1.open("10MeV_E_new_Benoit.txt");

    //stream1.open("effP4_g3_511MeV_4000_Geom1.txt");
    
    //stream1.open("p4Eff_g3_511MeV_E_5000_fieldOff.txt");
    stream1.open("p4Eff_g3_511MeV_E_5000_0_240_12bin_fieldOff.txt");
    //stream1.open("p4Eff_g3_511MeV_E_geom3_fieldOn.txt");
    Float_t x,y;
    Int_t counter = 0;

    if (stream1.is_open()){
	while(!stream1.eof()){
	    stream1>>x>>y;
	    if(x==1){
		counter++;
		i = 0;
		cout<<" counter = "<<counter<<endl;
	    }
	    if(counter == 1){
		//array50Phot[i] = y;
		//cout<<i<<" "<<array50Phot[i]<<endl;
		i++;
		h62->SetBinContent((Int_t)x,y);
	    }
	    if(counter == 2){
		//array50PhotErr[i] = y;
		//cout<<i<<" "<<array50PhotErr[i]<<endl;
		i++;
		h62->SetBinError((Int_t)x,y);
	    }
	}
    }

    h62->SetLineColor(3);

    c1->cd(1);
    h1->Draw();
    gPad->SetLogy(1);
    c1->cd(2);
    h2->Draw();
    gPad->SetLogy(1);
    c1->cd(3);
    h3->Draw();
    gPad->SetLogy(1);
    c1->cd(4);
    h4->Draw();
    gPad->SetLogy(1);
    c1->cd(5);
    h5->Draw();
    gPad->SetLogy(1);
    c1->cd(6);
    h6->Draw();
    h62->Draw("same error");
    //gPad->SetLogy(1);

    stream.close();   
    stream1.close();
    return 0;
}

TH1F *fillHistoB(string file, const Int_t Nth, Double_t Emin,Double_t Emax){

    //const Int_t Nth = 12;  //number of the different thresholds
    //Double_t Emin = 0.;    //MeV for efficiently
    //Double_t Emax = 16;    //MeV for efficiently

    ifstream stream1;

    stream1.open(file.c_str());

    Float_t x,y;
    Int_t counter = 0;

    TH1F *h62 = new TH1F("h6","spectrum6",Nth,Emin,Emax);

    if (stream1.is_open()){
	while(!stream1.eof()){
	    stream1>>x>>y;
	    if(x==1){
		counter++;
		i = 0;
		cout<<" counter = "<<counter<<endl;
	    }
	    if(counter == 1){
		//array50Phot[i] = y;
		//cout<<i<<" "<<array50Phot[i]<<endl;
		i++;
		h62->SetBinContent((Int_t)x,y);
	    }
	    if(counter == 2){
		//array50PhotErr[i] = y;
		//cout<<i<<" "<<array50PhotErr[i]<<endl;
		i++;
		//h62->SetBinError((Int_t)x,y);
	    }
	}
    }

    stream1.close();
    return h62;
}
