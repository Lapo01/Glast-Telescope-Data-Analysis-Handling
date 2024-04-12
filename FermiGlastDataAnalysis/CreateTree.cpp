/**
CreateTree.cpp
*/

#include "ClassEvento.h"
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iterator>

void CreateTree(const std::string &fileinput, const std::string &fileoutput){


int NEventi = 0;
int NHit= 0;
TString nomefile = fileoutput;
Evento eventoprova;
TFile *output = new TFile(nomefile, "recreate");
TTree *tree = new TTree("tree", "tree");
tree->Branch("eventoprova",&eventoprova);

std::vector<Evento> VettoreEventi;


std::map<std::string, int> mapping;
mapping.insert(std::make_pair("X0",10));
mapping.insert(std::make_pair("X1",11));
mapping.insert(std::make_pair("X2",12));
mapping.insert(std::make_pair("X3",13));
mapping.insert(std::make_pair("X4",14));
mapping.insert(std::make_pair("Y0",20));
mapping.insert(std::make_pair("Y1",21));
mapping.insert(std::make_pair("Y2",22));
mapping.insert(std::make_pair("Y3",23));
mapping.insert(std::make_pair("Y4",24));
cout<< "Debugging:"<<mapping["X0"]<<'\n';
std::string line;
std::ifstream myfile_in(fileinput);



int ciclo = 0;


if (myfile_in.is_open())
{
while(getline(myfile_in, line))
{


if(ciclo>0){


std::istringstream iss{line};
std::vector<std::string> words{
std::istream_iterator<std::string>(iss),
std::istream_iterator<std::string>()
};



eventoprova.Layer.clear();
eventoprova.Strip.clear();


NEventi = ciclo;
NHit = stoi(words[1]);

eventoprova.NHit =NHit;
eventoprova.NEventi = NEventi;

int Strip[NHit];
int Layer[NHit];
for(int i = 0; i<NHit; i++)
{
   Layer[i] = mapping[words[i+2+4*i]];
   Strip[i] = stoi(words[i+4+4*i]);

   eventoprova.Layer.push_back(Layer[i]);
   eventoprova.Strip.push_back(Strip[i]);
}

VettoreEventi.push_back(eventoprova);
tree->Fill();
}


ciclo++;

}
	output-> Write();
	output->Close();
    myfile_in.close();
}








}
