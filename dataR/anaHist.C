{
   TFile f ("MagneticInfo.root");
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
   TCanvas *myCanvas05 = new TCanvas("myCanvas05","canvas",50,50,500,500);
   TH2F  *h2xvsBx = new TH2F("hxvsBy","histo",1000,-1,1,1000,-1.5,1.5);
   MyTree->Draw("By:x>>hxvsBy");

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
}
