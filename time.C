//*********************************//
// This program calculate          //
// remaining time of simulation    //
//*********************************//

#include <iomanip>

Int_t time(){    
    Float_t Nev = 10000;
    Float_t dN  = 100;
    Float_t dT  = 56.28;

    Float_t Ttot = dT/dN*Nev;
    Float_t Th   = TMath::Floor(Ttot/3600);
    Float_t Tmin = TMath::Floor((Ttot - Th*3600.)/60);
    Float_t Tsec = TMath::Floor( Ttot - Th*3600. - Tmin*60.);
    cout<<setw(5)<<Th<<setw(5)<<Tmin<<setw(5)<<Tsec<<endl;

    return 0;
}
