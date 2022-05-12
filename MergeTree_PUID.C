#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2F.h"
#include <iostream>
#include "TInterpreter.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include <fstream>
#include <sstream>
#include "TROOT.h"

int main (int argc,char *argv[])
{
  
  gROOT->ProcessLine("#include <vector>");
  Int_t Np = -999;
  std::stringstream(argv[1]) >> Np;

  //btagvar_2021nojettimev3_2018FlatFinal.root

  std::string R ( "FlatFinal.root" );
  std::string path ("/eos/user/d/deroy/");
  std::string suffix("btagvar_2021nojettimev3_");
  std::string N = std::string(argv[1]);
  std::string fullpath(path+suffix+N+R);
  
  std::cout << fullpath << std::endl;
  TFile *f = new TFile( fullpath.c_str(), "READ" );

  std::string out = ( "MatchedPUjet_out" );
  std::string fulloutpath(path+N+out+R);

  //std::string fulloutpath(path+out+R);

  //TFile *newfile = new TFile(fulloutpath.c_str(),"recreate");
 
  //TTree *nominal = (TTree*)f->Get("nominal");
  TTree *puppi_tr = (TTree*)f->Get("jmepuppi/events");

  //TTree *nominal_Loose = (TTree*)f->Get("nominal_Loose");
  TTree *chs_tr = (TTree*)f->Get("jmechs/events");
  
  // Create tree reader and its data containers
  //TTreeReader reader1("nominal", f); //first tree
  
  TTreeReader reader1("chs_tr", f); //tree to which pu jet will be matched
  
  //TTreeReaderValue<unsigned long long> eventNumber1(reader1, "eventNumber");
  
  TTreeReaderValue<long> eventNumber1(reader1, "evtNo");
  
  //TTreeReaderValue<int> runNumber1(reader1, "runNo");
  //TTreeReaderArray<float> mu_pt1(reader1, "mu_pt");
  
  //TTreeReaderArray<float> deltaRMatch1(reader1, "dRMatch");

  //TTreeReaderValue<std::vector<float>> deltaRMatch1(reader1, "dRMatch");

  //TTreeReaderArray<int> flavourparton1(reader1, "jetFlavorParton");
  //TTreeReaderArray<float> jetpt1(reader1, "jetPt");
  //TTreeReaderArray<float> jeteta1(reader1, "jetEta");
  //TTreeReaderArray<float> jetphi1(reader1, "phi");
  //TTreeReaderArray<float> jetmass1(reader1, "mass");

  /*
    TTreeReader reader2("nominal_Loose", f); //second tree
    TTreeReaderValue<unsigned long long> eventNumber2(reader2, "eventNumber");
    TTreeReaderValue<Float_t> mcweight(reader2, "weight_mc");
    TTreeReaderValue<Float_t> puweight(reader2, "weight_pileup");
    TTreeReaderValue<Float_t> lsfweight(reader2, "weight_leptonSF");
    TTreeReaderValue<Float_t> met(reader2, "met_met");
    TTreeReaderArray<float> tau32v(reader2, "ljet_tau32_wta");
    TTreeReaderArray<float> tau21v(reader2, "ljet_tau21_wta");
    TTreeReaderArray<float> tau32v2(reader2, "ljet_tau32");
    TTreeReaderArray<float> tau21v2(reader2, "ljet_tau21");
    TTreeReaderArray<float> el_pt2(reader2, "el_pt");
    TTreeReaderArray<float> mu_pt2(reader2, "mu_pt");
    TTreeReaderArray<float> mu_eta2(reader2, "mu_eta");
    TTreeReaderArray<float> mu_phi2(reader2, "mu_phi");
    TTreeReaderArray<float> mu_e2(reader2, "mu_e");
  */

  //TTreeReaderArray<float> jet_pt2(reader2, "jet_pt");
  //TTreeReaderArray<float> jet_eta2(reader2, "jet_eta");
  //TTreeReaderArray<float> jet_phi2(reader2, "jet_phi");
  //TTreeReaderArray<float> jet_e2(reader2, "jet_e");
  
  /*
    TTreeReaderArray<float> ljet_pt2(reader2, "ljet_pt");
    TTreeReaderArray<float> ljet_eta2(reader2, "ljet_eta");
    TTreeReaderArray<float> ljet_phi2(reader2, "ljet_phi");
    TTreeReaderArray<float> ljet_m2(reader2, "ljet_m");
    TTreeReaderArray<float> ljet_e2(reader2, "ljet_e");
  */
  
  //TTree *inputTree1 = (TTree*)f->Get("nominal");   
  //TTree *inputTree2 = (TTree*)f->Get("nominal_Loose");
  
  TTree *inputTree1 = (TTree*)f->Get("jmechs/events");                                                           
  TTree *inputTree2 = (TTree*)f->Get("jmepuppi/events");
  
  
  //TTree *newtree = nominal_Loose->CloneTree(0);
  TTree *newtreeTest = inputTree2->CloneTree(0);
  
  //std::cout << " newtree " << newtree << std::endl;
  std::cout <<" newtreeTest " << newtreeTest << std::endl;
  
   int c2 =0;
   int c2_2 =0;
   int c1= 0;
   int c1_2 =0;
   int cf =0;
 
   int counter = 0;
   
   //while (reader2.Next()) {
   while (reader1.Next()) {

     //std::cout << " Event Number 2: " << (*eventNumber2) << std::endl;  
     std::cout << " Event Number 1: " << (eventNumber1) << std::endl;
     //std::cout << " Run Number 1: " << (*runNumber1) << std::endl; 
     //c2++;
     
     //if(mu_pt2.GetSize() > 1){
       
     //c2_2++;
   } //added now  
     //for (int i=counter; i< inputTree1->GetEntries(); i++){
   //for (int i=counter; i< 100; i++){
   for (int i=0; i< 2000; i++){
     reader1.SetEntry(i);
     //if (deltaRMatch1.size()>1) std::cout << deltaRMatch1.size() << std::endl;
	 std::cout << " Event Number 1: " << (eventNumber1) << std::endl;
	 //std::cout << " Run Number 1: " << (*runNumber1) << std::endl;
	 
	 //if( (*eventNumber2) == (*eventNumber1)) {
	   
	 //std::cout << " Event Number 1: " << (*eventNumber1)  << std::endl; 
	 //std::cout << mu_pt2[0] << std::endl;
	 //std::cout << mu_eta2[0] << std::endl;
	 //std::cout << mu_phi2[0] << std::endl;
	 //std::cout << mu_e2[0] << std::endl;
	  
	   //std::cout << jet_e2[0] << std::endl;
	   //std::cout << jet_pt2[0] << std::endl;
	   //std::cout << jet_eta2[0] << std::endl;
	   //std::cout << jet_phi2[0] << std::endl;
	   
	   //std::cout << el_pt2.GetSize() << std::endl;
	   //std::cout << ljet_pt2[0] << std::endl;
	   //std::cout << ljet_eta2[0] << std::endl;
	   //std::cout << ljet_phi2[0] << std::endl;
	   //std::cout << ljet_m2[0] << std::endl;
	   //std::cout << ljet_e2[0] << std::endl;
	   //std::cout << *met << std::endl;
	   //std::cout << tau32v[0] << std::endl;
	   //std::cout << tau21v[0] << std::endl;
	   //std::cout << tau32v2[0] << std::endl;
	   //std::cout << tau21v2[0] << std::endl;
	   //std::cout << *mcweight << std::endl;
	   //std::cout << *puweight << std::endl;
	   //std::cout << *lsfweight << std::endl;
	   
	 //newtreeTest->Fill();
	 //c1_2++;
	   
	 //counter = i;
	 //break;
	   
	   //}
	 
     }
       
     //}
          
   //}
   
   //newtreeTest->AutoSave();
   
   
   //std::cout << " No of events in tree 2: " << c2 << std::endl;
   //std::cout << " No of events in tree 2 with 2 muons: " << c2_2 << std::endl;
   //std::cout << " No of events in new tree written: " << c1_2 << std::endl;
   
   // newtree->Write("",TObject::kOverwrite); 
   //  newtree->Print();
   
   //newfile->Write();
      
   //return false;
 
   f->Close();
   
}

