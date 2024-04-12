//#ifndef "ClassEvento.h"
#include"ClassEvento.h"
#include <TMath.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iterator>

/*
class Evento
{
public:
    int NEventi;
    int NHit;
    std::vector<int> Strip;
    std::vector<int> Layer;
//Se vuoi aggiungere altri metodi fa pure.



};
*/


void LetturaTree(const std::string file)
{
 int X0 = 10;
 int X1 = 11;   
 int X2 = 12;   
 int X3 = 13;   
 int X4 = 14;   
 int Y0 = 20;
 int Y1 = 21;   
 int Y2 = 22;   
 int Y3 = 23;   
 int Y4 = 24;  


std::map<int, std::string> mapping;
mapping.insert(std::make_pair(10,"X0"));
mapping.insert(std::make_pair(11,"X1"));
mapping.insert(std::make_pair(12,"X2"));
mapping.insert(std::make_pair(13,"X3"));
mapping.insert(std::make_pair(14,"X4"));
mapping.insert(std::make_pair(20,"Y0"));
mapping.insert(std::make_pair(21,"Y1"));
mapping.insert(std::make_pair(22,"Y2"));
mapping.insert(std::make_pair(23,"Y3"));
mapping.insert(std::make_pair(24,"Y4"));









 int stringa[10]  = {X0, X1, X2, X3, X4, Y0, Y1, Y2, Y3, Y4};
 TString FileName= file;
 TString SaveDist = file+"HitDistribution" + "pdf";
	TFile *input = new TFile(FileName,"read");
    
	TTree *tree = (TTree*)input->Get("tree");
	
    
    TString Title1;
    TString Title2;
    TString SaveFileOcc;
    TString SaveFileHit;
	Evento evento;
    Evento *p = &evento;
    cout<<&evento<<'\n';
	tree->SetBranchAddress("eventoprova", &p); 
    int NHit;
    int NEventi;	
    int NHitPerLayer = 0;
    std::vector<int> Strip;
    std::vector<int> Layer;
	
	int entries = tree->GetEntries();
	cout << entries << endl;
for (auto x:stringa){
    //int x = stringa[1];
    Title1 ="Strip Occupancy Layer" + mapping[x];
    Title2 ="Hit Distribution for Layer" + mapping[x];
    TH1F *hist = new TH1F("hist", "Hit Distribution", 100, 0, 100);
    TH1F *hist2 = new TH1F("hist", Title1, 1536, 0, 1536);
    TH1F *hist3 = new TH1F("hist", Title2, 10, 0, 10);
    for(int i= 0; i< entries; i++){
    tree->GetEntry(i);
    NHit = evento.NHit;
    hist->Fill(NHit);
    NEventi = evento.NEventi;
    for (int i = 0; i<NHit; i++){
    if (evento.Layer[i] == x){   // guarda qui
    
    hist2->Fill(evento.Strip[i]);
    NHitPerLayer++;
     
    }
    hist3->Fill(NHitPerLayer); 
    NHitPerLayer = 0;
    }
    
    }
    
    
    cout<<evento.NHit<<'\n';
    TCanvas *c1 = new TCanvas();

    hist->Draw();

    TCanvas *c2 = new TCanvas();
    c2->SetLogy();    
    hist2->Draw();

    TCanvas *c3 = new TCanvas();
    hist3->Draw();
    
    SaveFileOcc = "StripOccupancyLayer" + mapping[x] + "pdf";
    SaveFileHit= "HitDistribution" +mapping[x] +"pdf";
    
    //c2->SaveAs(SaveFileOcc);
    //c3->SaveAs(SaveFileHit);
    c1->SaveAs(SaveDist);
    delete hist2;
    delete hist3;
    delete hist;
    delete c1;
    delete c2;
    delete c3;

   }
    
}



//#endif
