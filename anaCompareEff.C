#include <iostream>
#include <fstream>
using namespace std;

//TH1F *fillHistoB(string , const Int_t , Double_t ,Double_t );
//Th1F *fillHistoL(string , const Int_t , Double_t ,Double_t, Int_t );

Int_t anaCompareEff(){
    
    Int_t NtotEv = 10000;  //total number of events

    const Int_t Nth = 12;  //number of the different thresholds
    Double_t Emin = 0.;    //MeV for efficiently
    Double_t Emax = 1.6;   //MeV for efficiently

    TCanvas *c1 = new TCanvas("c1","spectrum",10,10,1000,1000);
    
    c1->Divide(2,1);
   
    TH1F *h1L = new TH1F("h1L","eff1L",Nth,Emin,Emax);
    TH1F *h2L = new TH1F("h2L","eff2L",Nth,Emin,Emax);
    TH1F *h3L = new TH1F("h3L","eff3L",Nth,Emin,Emax);
    TH1F *h4L = new TH1F("h4L","eff4L",Nth,Emin,Emax);
    TH1F *h5L = new TH1F("h5L","eff5L",Nth,Emin,Emax);

    TH1F *h1B = new TH1F("h1B","eff1B",Nth,Emin,Emax);
    TH1F *h2B = new TH1F("h2B","eff2B",Nth,Emin,Emax);
    TH1F *h3B = new TH1F("h3B","eff3B",Nth,Emin,Emax);
    TH1F *h4B = new TH1F("h4B","eff4B",Nth,Emin,Emax);
    TH1F *h5B = new TH1F("h5B","eff5B",Nth,Emin,Emax);
 
    h1L = fillHistoL( "1MeV_E_leonid_Data_10e4.txt", Nth, Emin, 1.6, NtotEv);
    h1B = fillHistoB("1MeV_E_new_Benoit.txt", Nth, Emin, 1.6);

    h2L = fillHistoL( "5MeV_E_leonid_Data_10e4.txt", Nth, Emin, 8., NtotEv);
    h2B = fillHistoB("5MeV_E_new_Benoit.txt", Nth, Emin, 1.6);

    h3L = fillHistoL( "10MeV_E_leonid_Data_10e4.txt", Nth, Emin, 16, NtotEv);
    h3B = fillHistoB("10MeV_E_new_Benoit.txt", Nth, Emin, 1.6);

    h4L = fillHistoL( "20MeV_E_leonid_Data_10e4.txt", Nth, Emin, 32, NtotEv);
    h4B = fillHistoB("20MeV_E_new_Benoit.txt", Nth, Emin, 1.6);

    h5L = fillHistoL( "100MeV_E_leonid_Data_10e4.txt", Nth, Emin, 160, NtotEv);
    h5B = fillHistoB("100MeV_E_new_Benoit.txt", Nth, Emin, 1.6);
 
    h1L->SetLineColor(1);
    h1B->SetLineColor(1);

    h2L->SetLineColor(2);
    h2B->SetLineColor(2);

    h3L->SetLineColor(3);
    h3B->SetLineColor(3);

    h4L->SetLineColor(4);
    h4B->SetLineColor(4);

    h5L->SetLineColor(6);
    h5B->SetLineColor(6);

    c1->cd(1);
    h1L->Draw();
    h2L->Draw("same");
    h3L->Draw("same");
    h4L->Draw("same");
    h5L->Draw("same");
    gPad->SetLogy(1);
    c1->cd(2);
    h1B->Draw();
    h2B->Draw("same");
    h3B->Draw("same");
    h4B->Draw("same");
    h5B->Draw("same");
    gPad->SetLogy(1);

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

TH1F *fillHistoL(string file, const Int_t Nth, Double_t Emin,Double_t Emax, Int_t NtotEv){

    ifstream stream;

    Float_t eDet1,eDet2,eDet3,eDet4, eTot;

    Int_t Nev = 0;        //number of the events with Etot > 0.
    Int_t Nthreshold = 0; //number of the events with E < E of the threshold

    Int_t i = 0;

    Int_t index;
    Double_t array[Nth];
    Double_t bin_width = (Emax - Emin)/Nth;
    for(i = 0;i<Nth;i++){
	array[i] = 0.;
    }

    TH1F *h6 = new TH1F("h6","spectrum6",Nth,0.,1.6);

    stream.open(file.c_str());

    if (stream.is_open()){
	while(!stream.eof()){
	    stream>>eDet1>>eDet2>>eDet3>>eDet4;
	    //cout<<eDet2<<endl;
	    eTot = eDet1 + eDet2 + eDet3 + eDet4;
	    //h1->Fill(eDet1);
	    //h2->Fill(eDet2);
	    //h3->Fill(eDet3);
	    //h4->Fill(eDet4);
	    //h5->Fill(eTot);
	    if(eTot!=0){
		index = int(floor((eTot - Emin)/bin_width));
		array[index]++;
		Nev = Nev + 1;
	    }
	    //cout<<eDet1<<endl;
	}
    }
    else{
	cout<<"file not open"<<endl;
    }

    Nthreshold = 0;
    for( i = 0; i<Nth; i++){
	h6->SetBinContent(i+1,(Float_t)(Nev - 1 - Nthreshold)/(Float_t)NtotEv);
	Nthreshold = Nthreshold + array[i];
    }

    stream.close();   

    return h6;
}
