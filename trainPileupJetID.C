//#include "TMVA/Factory.h"

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"
#include "TFile.h"
#include "TTree.h"

using namespace TMVA;
using namespace TMath;

void trainPileupJetID(TString ETA);
void trainPileupJetIDAll();

void trainPileupJetIDAll()
{
  //trainPileupJetID("Eta0to2p5");
  //trainPileupJetID("Eta2p5to2p75");
  //trainPileupJetID("Eta2p75to3");
  //trainPileupJetID("Eta3to5");
 
  trainPileupJetID("Eta0to2p5");                                                                       
  trainPileupJetID("Eta2p5to2p75");
  trainPileupJetID("Eta2p75to3");
  trainPileupJetID("Eta3to5");
}

void trainPileupJetID(TString ETA)
{
  /*
    TFile *inf1 = TFile::Open("pileupJetId_timeTrain_3EtaSplit_11cmssw11samp_Pt30to50bin.root");
    TFile *inf2 = TFile::Open("pileupJetId_timeTrain_3EtaSplit_11cmssw11samp_Pt50to80bin.root");
    TFile *inf3 = TFile::Open("pileupJetId_timeTrain_3EtaSplit_11cmssw11samp_Pt80to120bin.root");
    TFile *inf4 = TFile::Open("pileupJetId_timeTrain_3EtaSplit_11cmssw11samp_Pt120to170bin.root");
    TFile *inf5 = TFile::Open("pileupJetId_timeTrain_3EtaSplit_11cmssw11samp_Pt170to300bin.root");
    TFile *inf6 = TFile::Open("pileupJetId_timeTrain_3EtaSplit_11cmssw11samp_Pt300to470bin.root");
    TFile *inf7 = TFile::Open("pileupJetId_timeTrain_3EtaSplit_11cmssw11samp_Pt470to600bin.root");
    TFile *inf8 = TFile::Open("pileupJetId_timeTrain_3EtaSplit_11cmssw11samp_Pt600toInfbin.root");
  */

  //TFile *inf1 = TFile::Open("pileupJetId_timeTrain_3EtaSplit_2021nojettimev3_15to30bin.root");
  //TFile *inf2 = TFile::Open("pileupJetId_timeTrain_3EtaSplit_2021nojettimev3_30to50bin.root");         
  //TFile *inf3 = TFile::Open("pileupJetId_timeTrain_3EtaSplit_2021nojettimev3_50to80bin.root"); 
  //TFile *inf4 = TFile::Open("pileupJetId_timeTrain_3EtaSplit_2021nojettimev3_80to120bin.root"); 
  //TFile *inf5 = TFile::Open("pileupJetId_timeTrain_3EtaSplit_2021nojettimev3_120to170bin.root");
  //TFile *inf6 = TFile::Open("pileupJetId_timeTrain_3EtaSplit_2021nojettimev3_170to300bin.root");

  //TFile *inf = TFile::Open("pileupJetId_timeTrain_4EtaSplit_2021nojettimev3_2018Flat15to50GVPt.root");
  //TFile *inf = TFile::Open("pileupJetId_timeTrain_4EtaSplit_2021nojettimev3_2018Flat15to50GVPtchs.root");
  //TFile *inf = TFile::Open("pileupJetId_timeTrain_4EtaSplit_2021nojettimev3_2017Flat15to50GVPt.root");
  //TFile *inf = TFile::Open("pileupJetId_timeTrain_4EtaSplit_2021nojettimev3_2017Flat15to50GVPtchs.root");
  //TFile *inf = TFile::Open("pileupJetId_timeTrain_4EtaSplit_2021nojettimev3_2016Flat15to50GVPt.root");

  TFile *inf = TFile::Open("pileupJetId_timeTrain_4EtaSplit_2021nojettimev3_2016Flat15to50GVPtchs.root");

  /*
    TTree *sigTree1 = (TTree*)inf1->Get("jetsMatched"+ETA); 
    TTree *bkgTree1 = (TTree*)inf1->Get("jetsUnMatched"+ETA); 
    TTree *sigTree2 = (TTree*)inf2->Get("jetsMatched"+ETA);
    TTree *bkgTree2 = (TTree*)inf2->Get("jetsUnMatched"+ETA);
    TTree *sigTree3 = (TTree*)inf3->Get("jetsMatched"+ETA);
    TTree *bkgTree3 = (TTree*)inf3->Get("jetsUnMatched"+ETA);
    TTree *sigTree4 = (TTree*)inf4->Get("jetsMatched"+ETA);
    TTree *bkgTree4 = (TTree*)inf4->Get("jetsUnMatched"+ETA);
    TTree *sigTree5 = (TTree*)inf5->Get("jetsMatched"+ETA);
    TTree *bkgTree5 = (TTree*)inf5->Get("jetsUnMatched"+ETA);
    TTree *sigTree6 = (TTree*)inf6->Get("jetsMatched"+ETA);
    TTree *bkgTree6 = (TTree*)inf6->Get("jetsUnMatched"+ETA);
    TTree *sigTree7 = (TTree*)inf7->Get("jetsMatched"+ETA);
    TTree *bkgTree7 = (TTree*)inf7->Get("jetsUnMatched"+ETA);
    TTree *sigTree8 = (TTree*)inf8->Get("jetsMatched"+ETA);
    TTree *bkgTree8 = (TTree*)inf8->Get("jetsUnMatched"+ETA);
  */
  
  TTree *sigTree = (TTree*)inf->Get("jetsMatched"+ETA);                                                                    
  TTree *bkgTree = (TTree*)inf->Get("jetsUnMatched"+ETA);
  
  //TFile *outf = new TFile("pileupJetId_DY_mva_"+ETA+"_3EtaSplitN_tdiffMedMin.root","RECREATE");
  //TFile *outf = new TFile("pileupJetId_DY_mva_"+ETA+"_2EtaSplitNsigmatMe.root","RECREATE");
  TFile *outf = new TFile("pileupJetId_DY_mva_"+ETA+"_4EtaSplitN_2016Flat15to50GVPt800Treschs.root","RECREATE"); 

  //TFile *outf = new TFile("pileupJetId_DY_mva_"+ETA+"_3EtaSplitN.root","RECREATE");

  TMVA::Factory* factory = new TMVA::Factory("pileupJetId_QCD_"+ETA,outf,"!V:!Silent:Color:DrawProgressBar:Transformations=I;G:AnalysisType=Classification");

  TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
  /*   
       Double_t Weight1 =  266768.2068;
       Double_t Weight2 =  61524.3951;
       Double_t Weight3 = 27893.7548;
       Double_t Weight4 = 9446.8017;
       Double_t Weight5 = 2426.6795;
       Double_t Weight6 = 164.5633;
       Double_t Weight7 = 13.6803;
       Double_t Weight8 = 4.874;
  */
  
  //Double_t Weight1 =  89317.35;
  //Double_t Weight2 =  5537.224;
  //Double_t Weight3 = 807.39;                                                                    
  //Double_t Weight4 = 78.870;
  //Double_t Weight5 = 13.594;
  //Double_t Weight6 = 3.4911;

  /*
  dataloader->AddSignalTree( sigTree1, Weight1 );
  dataloader->AddBackgroundTree( bkgTree1, Weight1 );
  dataloader->AddSignalTree( sigTree2, Weight2 );
  dataloader->AddBackgroundTree( bkgTree2, Weight2 );
  dataloader->AddSignalTree( sigTree3, Weight3 );
  dataloader->AddBackgroundTree( bkgTree3, Weight3 );
  dataloader->AddSignalTree( sigTree4, Weight4 );
  dataloader->AddBackgroundTree( bkgTree4, Weight4 );
  dataloader->AddSignalTree( sigTree5, Weight5 );
  dataloader->AddBackgroundTree( bkgTree5, Weight5 );
  dataloader->AddSignalTree( sigTree6, Weight6 );
  dataloader->AddBackgroundTree( bkgTree6, Weight6 );
  dataloader->AddSignalTree( sigTree7, Weight7 );
  dataloader->AddBackgroundTree( bkgTree7, Weight7 );
  dataloader->AddSignalTree( sigTree8, Weight8 );
  dataloader->AddBackgroundTree( bkgTree8, Weight8 );
  */

  dataloader->AddSignalTree( sigTree );
  dataloader->AddBackgroundTree( bkgTree );

  dataloader->SetSignalWeightExpression("genevtwt_");
  dataloader->SetBackgroundWeightExpression( "genevtwt_" );

  int N_SIG(sigTree->GetEntries());                                                                                        
  int N_BKG(bkgTree->GetEntries());
  
  int N = TMath::Min(TMath::Min(N_SIG,N_BKG),1000000);
  cout<<N_SIG<<" "<<N_BKG<<endl;

  /*
    int N_SIG1(sigTree1->GetEntries());
    int N_BKG1(bkgTree1->GetEntries());
    int N_SIG2(sigTree2->GetEntries());
    int N_BKG2(bkgTree2->GetEntries());
    int N_SIG3(sigTree3->GetEntries());
    int N_BKG3(bkgTree3->GetEntries());
    int N_SIG4(sigTree4->GetEntries());
    int N_BKG4(bkgTree4->GetEntries());
    int N_SIG5(sigTree5->GetEntries());
    int N_BKG5(bkgTree5->GetEntries());
    int N_SIG6(sigTree6->GetEntries());
    int N_BKG6(bkgTree6->GetEntries());
    
    int N1 = TMath::Min(TMath::Min(N_SIG1,N_BKG1),1000000);
    int N2 = TMath::Min(TMath::Min(N_SIG2,N_BKG2),1000000);
    int N3 = TMath::Min(TMath::Min(N_SIG3,N_BKG3),1000000);
    int N4 = TMath::Min(TMath::Min(N_SIG4,N_BKG4),1000000);
    int N5 = TMath::Min(TMath::Min(N_SIG5,N_BKG5),1000000);
    int N6 = TMath::Min(TMath::Min(N_SIG6,N_BKG6),1000000);
    
    int sm[6] = {N1,N2,N3,N4,N5,N6};
    int sm_num = N1;
    for (int i=1; i<6; i++)
    {
    if (sm[i]<sm_num) sm_num = sm[i];
    }
  */
  //cout<<N_SIG<<" "<<N_BKG<<endl;
  
  const int NVARC = 15;//19; //15;
  TString VARC[NVARC] = {
    "nvtx",
    "dR2Mean",
    "nParticles",
    "nCharged",
    "majW",
    "minW",
    "frac01",
    "frac02",
    "frac03",
    "frac04",
    "ptD",
    "beta",
    "pull",
    "jetR",
    "jetRchg"};
    //"med_tdiff_",
    //"min_tdiff_",
    //"me_tdiff_",
    //"rms_tdiff_"};
  //"rms_sigmat_"};
  /*
    "med_sigmat_",
    "me_sigmat_",
    "rms_tdiff_",
    "med_tdiff_",
    "med_tdiff_"
    };*/
  //char TYPEC[NVARC] = {'I','F','I','I','F','F','F','F','F','F','F','F','F','F','F','F','F','F','F','F','F'};
    char TYPEC[NVARC] = {'I','F','I','I','F','F','F','F','F','F','F','F','F','F','F'};//,'F','F','F','F'};
    
    const int NVARF = 12;//16; //12;
    TString VARF[NVARF] = {
    "nvtx",
    "dR2Mean",
    "nParticles",
    "majW",
    "minW",
    "frac01",
    "frac02",
    "frac03",
    "frac04",
    "ptD",
    "pull",
    "jetR"};
    //"med_tdiff_",
    //"min_tdiff_",
    //"me_tdiff_",
    //"rms_tdiff_"};
  //"rms_sigmat_"};
  /*
    "med_sigmat_",
    "me_sigmat_",
    "rms_tdiff_",
    "med_tdiff_",
    "med_tdiff_"
    };*/
  //char TYPEF[NVARC] = {'I','F','I','F','F','F','F','F','F','F','F','F','F','F','F','F','F','F'};
    char TYPEF[NVARC] = {'I','F','I','F','F','F','F','F','F','F','F','F'};//,'F','F'};
  
  if (ETA == "Eta3to5") {
    for(int i=0;i<NVARF;i++) {
      //factory->AddVariable(VARF[i],TYPEF[i]);
      dataloader->AddVariable(VARF[i],TYPEF[i]);
    }
  }
  else {
    for(int i=0;i<NVARC;i++) {
      //factory->AddVariable(VARC[i],TYPEC[i]);
      dataloader->AddVariable(VARC[i],TYPEC[i]);
    }
  }

  //factory->AddSpectator("jetPt",'F');
  //factory->AddSpectator("jetEta",'F');
  
  dataloader->AddSpectator("jetPt",'F');                                                               
  dataloader->AddSpectator("jetEta",'F');
  
  char name[1000];
  sprintf(name,"nTrain_Signal=%d:nTrain_Background=%d:nTest_Signal=%d:nTest_Background=%d",N/2,N/2,N/2,N/2);
  //sprintf(name,"nTrain_Signal=%d:nTrain_Background=%d:nTest_Signal=%d:nTest_Background=%d",sm_num/2,sm_num/2,sm_num/2,sm_num/2);
  //sprintf(name,"nTrain_Signal=%d:nTrain_Background=%d:nTest_Signal=%d:nTest_Background=%d",500000,500000,500000,1000000);
  dataloader->PrepareTrainingAndTestTree("",name);
  
  //TCut mycuts = "";
  //TCut mycutb = "";

  //dataloader->PrepareTrainingAndTestTree( mycuts, mycutb, "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

  //factory->BookMethod(TMVA::Types::kBDT,"BDT","NTrees=500:BoostType=Grad:Shrinkage=0.1:DoBoostMonitor=True");
  //factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
  //"!H:!V:NTrees=500:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

  factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG","!H:!V:NTrees=800:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods(); 
  
  
  outf->Close();

  delete factory;
  delete dataloader;


}
