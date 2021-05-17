{
    //TFile f ("SteppingAction.root");
    TFile f ("p4Sp_g4_511MeV_E_10e5_geom2_fieldOff.root");

   f.ls();

   TTree *MyTree = t1;
   
   //TCanvas *myCanvas01 = new TCanvas("myCanvas01","canvas",10,10,500,500);
   //TH1F  *hzOld = new TH1F("hzOld","histo",100,80,110);
   //MyTree->Draw("zOld>>hzOld");
   
   //TCanvas *myCanvas02 = new TCanvas("myCanvas02","canvas",20,20,500,500);
   //TH1F  *hz = new TH1F("hz","histo",100,70,120);
   //MyTree->Draw("z>>hz");

/*   
   TCanvas *myCanvas03 = new TCanvas("myCanvas03","canvas",30,30,500,500);
   TH1F  *hx = new TH1F("hx","histo",100,-1,1);
   MyTree->Draw("x>>hx");

   TCanvas *myCanvas04 = new TCanvas("myCanvas04","canvas",40,40,500,500);
   TH1F  *hxOld = new TH1F("hxOld","histo",100,3,6.5);
   MyTree->Draw("xOld>>hxOld");
*/

   std::string name;
   std::string nameForEPS;
   std::string nameForJPG;

   std::string flag_Print;
   std::string flag_Logy;
   std::string flag_Logx;

   TCanvas *myCanvas = new TCanvas("myCanvas01","canvas",0,0,1000,1200);
   myCanvas->SetFillColor(0);

   TH1F  *hEkin = new TH1F("hEkin","histo",100,0,511);
   TH1F  *hEkin02 = new TH1F("hEkin02","histo",100,0,1);

   TH1F  *hx = new TH1F("hx","histo",100,-55,55);
   TH1F  *hy = new TH1F("hy","histo",100,-55,55);
   TH1I  *hcharge = new TH1I("hcharge","histo",100,-2,2);

   //-------------------------------
   flag_Print = "flag_PrintON";
   //flag_Print = "flag_PrintOFF";

   //flag_Logy = "flag_LogyON";
   flag_Logy = "flag_LogyOFF";

   //flag_Logx = "flag_LogxON";
   flag_Logx = "flag_LogxOFF";

   name = "charge";
   //-------------------------------   


   //std::string sWhat = "t1.Ekin>>hEkin";
   //std::string sWhat = "t1.Ekin>>hEkin02";

   //std::string sWhat = "t1.y:t1.x";
   //std::string sWhat = "t1.x>>hx";
   //std::string sWhat = "t1.y>>y";
   //std::string sWhat = "t1.z";

   std::string sWhat = "t1.charge>>hcharge";

   
   
   std::string sCut;
   sCut  = "t1.pz>0";
   //sCut += "&& t1.charge==0";//gamma
   //sCut += "&& t1.charge<0"; //e-
   //sCut += "&& t1.charge>0"; //e+



   //sCut = "";

   

   nameForEPS = name + ".eps";
   nameForJPG = name + ".jpg";

   f->cd();
   MyTree->Draw(sWhat.c_str(), sCut.c_str());
   if (flag_Logy == "flag_LogyON"){
       gPad->SetLogy(1);  
   }
   if (flag_Logx == "flag_LogxON"){
       gPad->SetLogx(1);  
   }
   
   if (flag_Print == "flag_PrintON"){
       myCanvas->Print(nameForEPS.c_str());
       myCanvas->Print(nameForJPG.c_str());
   }

/*
   myCanvas05->Print("yBxQD1RU.ps");
   myCanvas05->Print("yBxQD1RU.eps");
   myCanvas05->Print("yBxQD1RU.pdf");
   myCanvas05->Print("yBxQD1RU.png");
   myCanvas05->Print("yBxQD1RU.jpg");


   TF1 * fit = new TF1("fit","[0]*x + [1]",-1,1);
   TGraph *gr = new TGraph(MyTree->GetSelectedRows(), MyTree->GetV2(), MyTree->GetV1());
   gr->Fit("fit","R+");

   TCanvas *myCanvas06 = new TCanvas("myCanvas06","canvas",60,60,500,500);
   TH2F  *h2xvsz = new TH2F("h2xvsz","histo",1000,80,110,1000,-1.5,1.5);
   MyTree->Draw("x:z>>hxvsz");
   myCanvas06->Print("yzQD1RU.ps");
   myCanvas06->Print("yzQD1RU.eps");
   myCanvas06->Print("yzQD1RU.pdf");
   myCanvas06->Print("yzQD1RU.png");
   myCanvas06->Print("yzQD1RU.jpg");
*/

}
