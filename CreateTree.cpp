#include "ClassEvento.h"
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iterator>
//#include"DataStructureClass.h"
/*
class Evento
{
public:
    int NEventi;
    int NHit;
    std::vector<int> Strip;
    std::vector<int> Layer;

};

*/

void CreateTree(const std::string &fileinput, const std::string &fileoutput){


int NEventi = 0;
int NHit= 0;
TString nomefile = fileoutput; //necessario renderlo come TString sennò si lamenta...
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
cout<< "Debugging:"<<mapping["X0"]<<'\n'; // unit testing della mappa (fatto dentro il codice stesso ma vabbè...)
//std::map<std::string, std::vector<int>> mymap;
std::string line;
std::ifstream myfile_in(fileinput);



int ciclo = 0;


if (myfile_in.is_open())
{
while(getline(myfile_in, line))
{

//if(ciclo == 3){break;}
if(ciclo>0){


std::istringstream iss{line};
std::vector<std::string> words{
std::istream_iterator<std::string>(iss),
std::istream_iterator<std::string>()
};
// words è il vettore delle parole

//resetto i vettori dell'oggetto...
eventoprova.Layer.clear();
eventoprova.Strip.clear();


NEventi = ciclo;
NHit = stoi(words[1]);

eventoprova.NHit =NHit;
eventoprova.NEventi = NEventi;
/*
cout<<"Il numero di hit è "<<eventoprova.NHit<<'\n';
cout<<"Il numero di evento è "<<eventoprova.NEventi<<'\n';
*/
int Strip[NHit];
int Layer[NHit];
for(int i = 0; i<NHit; i++)
{
   Layer[i] = mapping[words[i+2+4*i]];
   Strip[i] = stoi(words[i+4+4*i]);
   //cout<< "The Layer hitten is "<< (mapping[words[i+2+4*i]]) << " and its strip is " << stoi(words[i+4+4*i])<< '\n';
   //cout<< "The Layer hitten is "<< words[i+2+4*i] << " and its strip is " << stoi(words[i+4+4*i])<< '\n';
   //cout<<i<<'\n';
   eventoprova.Layer.push_back(Layer[i]);
   eventoprova.Strip.push_back(Strip[i]);
}
/*
for (auto x :eventoprova.Layer){
   std::cout << x << '\n';
}




cout<<"Il layer è: "<<eventoprova.Layer[1]<<'\n';
cout<< "Lo strip è: "<<eventoprova.Strip[1]<<'\n';

cout<< NHit<<'\n';
*/
//cout << "Numero Evento:" << eventoprova.NEventi<<'\n';
VettoreEventi.push_back(eventoprova);
tree->Fill();
}
//cout<<"Il numero di Hit è"<<NHit<<'\n';

ciclo++;

}
	output-> Write();
	output->Close();
    myfile_in.close();
}
/*
for (auto x: VettoreEventi){
std::cout<<x.NHit<<'\n';
}
*/







}
