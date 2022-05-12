#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include "TLorentzVector.h"
#include <cmath>
#include <functional>

using std::cin;
using std::cout;
using std::endl;

void CreateTreeForPileupJetIdTraining()
{
  //TFile *inf = TFile::Open("/eos/user/d/deroy/btagvar_nojettimePU200_Pt30to50_11cmssw.root");
  //TFile *inf = TFile::Open("/eos/user/d/deroy/btagvar_2021nojettimev3_30to50Pt.root");
  //TFile *inf = TFile::Open("/eos/user/d/deroy/btagvar_2021nojettimev3_15to30Pt.root");
  //TFile *inf = TFile::Open("/eos/user/d/deroy/btagvar_2021nojettimev3_50to80Pt.root");
  //TFile *inf = TFile::Open("/eos/user/d/deroy/btagvar_2021nojettimev3_80to120Pt.root");
  //TFile *inf = TFile::Open("/eos/user/d/deroy/btagvar_2021nojettimev3_120to170Pt.root");

  TFile *inf = TFile::Open("/eos/user/d/deroy/btagvar_2021nojettimev3_2016FlatFinal.root");

  TTree *trIN_puppi   = (TTree*)inf->Get("jmepuppi/events");
  TTree *trIN_chs   = (TTree*)inf->Get("jmechs/events");

  //TFile *outf   = TFile::Open("pileupJetId_timeTrain_3EtaSplit_11cmssw11samp_Pt30to50bin.root","RECREATE");
  //TFile *outf   = TFile::Open("pileupJetId_timeTrain_4EtaSplit_2021nojettimev3_2016Flat15to50GVPtchs.root","RECREATE");

  TFile *outf   = TFile::Open("Background_Tr2016_forCHS1Set.root","RECREATE");

  //TTree *trOUT1 = new TTree("jetsMatchedEta0to2p5","jetsMatchedEta0to2p5");                         
  TTree *trOUT2 = new TTree("jetsUnMatchedEta0to2p5","jetsUnMatchedEta0to2p5");
  //TTree *trOUT1_p = new TTree("jetsMatchedEta0to2p5_p","jetsMatchedEta0to2p5_p");
  //TTree *trOUT2_p = new TTree("jetsUnMatchedEta0to2p5_p","jetsUnMatchedEta0to2p5_p");
  //TTree *trOUT3 = new TTree("jetsMatchedEta2p5to2p75","jetsMatchedEta2p5to2p75");
  TTree *trOUT4 = new TTree("jetsUnMatchedEta2p5to2p75","jetsUnMatchedEta2p5to2p75");
  //TTree *trOUT5 = new TTree("jetsMatchedEta2p75to3","jetsMatchedEta2p75to3");                        
  TTree *trOUT6 = new TTree("jetsUnMatchedEta2p75to3","jetsUnMatchedEta2p75to3");
  //TTree *trOUT7 = new TTree("jetsMatchedEta3to5","jetsMatchedEta3to5");
  TTree *trOUT8 = new TTree("jetsUnMatchedEta3to5","jetsUnMatchedEta3to5");
  
  float genevtwt;
  int runNum,evtNum,nVtx,npu; //nLeptons;
  float rho; //llMass;
  vector<int>   *flavorParton(0),*nParticles(0),*nCharged(0);
  vector<float> *pt(0),*eta(0),*aziphi(0),*jetmass(0),*genDR(0),*genPt(0);
  vector<float> *dR2Mean(0),*majW(0),*minW(0),*frac01(0),*frac02(0),*frac03(0),*frac04(0),*ptD(0),
    *beta(0),*betaStar(0),*pull(0),*jetR(0),*jetRchg(0);

  //for puppi input tree//
  float genevtwt_p;
  int runNum_p,evtNum_p,nVtx_p,npu_p; //nLeptons;                                                      
  float rho_p; //llMass;                                                                               
           
  vector<int>   *flavorParton_p(0),*nParticles_p(0),*nCharged_p(0);
  vector<float> *pt_p(0),*eta_p(0),*aziphi_p(0),*jetmass_p(0),*genDR_p(0),*genPt_p(0);
  vector<float> *dR2Mean_p(0),*majW_p(0),*minW_p(0),*frac01_p(0),*frac02_p(0),*frac03_p(0),*frac04_p(0),*ptD_p(0), *beta_p(0),*betaStar_p(0),*pull_p(0),*jetR_p(0),*jetRchg_p(0);
  
  int runNum_,evtNum_,nVtx_,npu_,flavorParton_,nParticles_,nCharged_;
  float rho_,pt_,eta_,phi_,mass_,genDR_,genPt_,beta_,betaStar_,pull_,jetR_,jetRchg_,genevtwt_;
  float dR2Mean_,majW_,minW_,frac01_,frac02_,frac03_,frac04_,ptD_;

  //int runNum_pout,evtNum_pout,nVtx_pout,npu_pout,flavorParton_pout,nParticles_pout,nCharged_pout;
  //float rho_pout,pt_pout,eta_pout,phi_pout,mass_pout,genDR_pout,genPt_pout,beta_pout,betaStar_pout,pull_pout,jetR_pout,jetRchg_pout,genevtwt_pout;
  //float dR2Mean_pout,majW_pout,minW_pout,frac01_pout,frac02_pout,frac03_pout,frac04_pout,ptD_pout;
                
  //------- input tree --------------
  
  trIN_chs->SetBranchAddress("genEvtWeight"   ,&genevtwt);
  trIN_chs->SetBranchAddress("runNo"          ,&runNum);  
  trIN_chs->SetBranchAddress("evtNo"          ,&evtNum);
  trIN_chs->SetBranchAddress("npv"            ,&nVtx);
  trIN_chs->SetBranchAddress("rho"            ,&rho);
  trIN_chs->SetBranchAddress("jetPt"          ,&pt);
  trIN_chs->SetBranchAddress("jetEta"         ,&eta);
  trIN_chs->SetBranchAddress("phi"            ,&aziphi);
  trIN_chs->SetBranchAddress("mass"           ,&jetmass);
  trIN_chs->SetBranchAddress("dR2Mean"        ,&dR2Mean);
  trIN_chs->SetBranchAddress("majW"           ,&majW);
  trIN_chs->SetBranchAddress("minW"           ,&minW);
  trIN_chs->SetBranchAddress("frac01"         ,&frac01);
  trIN_chs->SetBranchAddress("frac02"         ,&frac02);
  trIN_chs->SetBranchAddress("frac03"         ,&frac03);
  trIN_chs->SetBranchAddress("frac04"         ,&frac04);
  trIN_chs->SetBranchAddress("ptD"            ,&ptD);
  trIN_chs->SetBranchAddress("beta"           ,&beta);
  trIN_chs->SetBranchAddress("betaStar"       ,&betaStar);
  trIN_chs->SetBranchAddress("pull"           ,&pull);
  trIN_chs->SetBranchAddress("jetR"           ,&jetR);
  trIN_chs->SetBranchAddress("jetRchg"        ,&jetRchg);
  trIN_chs->SetBranchAddress("nParticles"     ,&nParticles);
  trIN_chs->SetBranchAddress("nCharged"       ,&nCharged);
  trIN_chs->SetBranchAddress("dRMatch"        ,&genDR);
  trIN_chs->SetBranchAddress("jetGenPt"       ,&genPt);
  trIN_chs->SetBranchAddress("jetFlavorParton",&flavorParton);
  trIN_chs->SetBranchAddress("nTrueInt"       ,&npu);  
  
  //trIN->SetBranchAddress("nLeptons"       ,&nLeptons);
  //trIN->SetBranchAddress("llMass"         ,&llMass);
  //trIN->SetBranchAddress("PFcandtime"     ,&PFcandtime);
  //trIN->SetBranchAddress("PFcandtimerr_"  ,&PFcandtimerr_);
  //trIN->SetBranchAddress("PFcand_"        ,&PFcand_);
  //trIN->SetBranchAddress("Vtxtime_"       ,&Vtxtime_);
  //trIN->SetBranchAddress("Vtxtimerr_"     ,&Vtxtimerr_);

  trIN_puppi->SetBranchAddress("genEvtWeight"   ,&genevtwt_p);
  trIN_puppi->SetBranchAddress("runNo"          ,&runNum_p);
  trIN_puppi->SetBranchAddress("evtNo"          ,&evtNum_p);
  trIN_puppi->SetBranchAddress("npv"            ,&nVtx_p);
  trIN_puppi->SetBranchAddress("rho"            ,&rho_p);
  trIN_puppi->SetBranchAddress("jetPt"          ,&pt_p);
  trIN_puppi->SetBranchAddress("jetEta"         ,&eta_p);
  trIN_puppi->SetBranchAddress("phi"            ,&aziphi_p);
  trIN_puppi->SetBranchAddress("mass"           ,&jetmass_p);
  trIN_puppi->SetBranchAddress("dR2Mean"        ,&dR2Mean_p);
  trIN_puppi->SetBranchAddress("majW"           ,&majW_p);
  trIN_puppi->SetBranchAddress("minW"           ,&minW_p);
  trIN_puppi->SetBranchAddress("frac01"         ,&frac01_p);
  trIN_puppi->SetBranchAddress("frac02"         ,&frac02_p);
  trIN_puppi->SetBranchAddress("frac03"         ,&frac03_p);
  trIN_puppi->SetBranchAddress("frac04"         ,&frac04_p);
  trIN_puppi->SetBranchAddress("ptD"            ,&ptD_p);
  trIN_puppi->SetBranchAddress("beta"           ,&beta_p);
  trIN_puppi->SetBranchAddress("betaStar"       ,&betaStar_p);
  trIN_puppi->SetBranchAddress("pull"           ,&pull_p);
  trIN_puppi->SetBranchAddress("jetR"           ,&jetR_p);
  trIN_puppi->SetBranchAddress("jetRchg"        ,&jetRchg_p);
  trIN_puppi->SetBranchAddress("nParticles"     ,&nParticles_p);
  trIN_puppi->SetBranchAddress("nCharged"       ,&nCharged_p);
  trIN_puppi->SetBranchAddress("dRMatch"        ,&genDR_p);
  trIN_puppi->SetBranchAddress("jetGenPt"       ,&genPt_p);
  trIN_puppi->SetBranchAddress("jetFlavorParton",&flavorParton_p);
  trIN_puppi->SetBranchAddress("nTrueInt"       ,&npu_p);

  //------- output trees --------------
  /*
    trOUT1->Branch("runNum"            ,&runNum_      ,"runNum_/I");
    trOUT1->Branch("evtNum"            ,&evtNum_      ,"evtNum_/I");
    trOUT1->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
    trOUT1->Branch("rho"               ,&rho_         ,"rho_/F");
    trOUT1->Branch("jetPt"             ,&pt_          ,"pt_/F");
    trOUT1->Branch("jetEta"            ,&eta_         ,"eta_/F");
    trOUT1->Branch("phi"               ,&phi_         ,"phi_/F");
    trOUT1->Branch("mass"              ,&mass_        ,"mass_/F");
    trOUT1->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
    trOUT1->Branch("majW"              ,&majW_        ,"majW_/F");
    trOUT1->Branch("minW"              ,&minW_        ,"minW_/F");
    trOUT1->Branch("frac01"            ,&frac01_      ,"frac01_/F");
    trOUT1->Branch("frac02"            ,&frac02_      ,"frac01_/F");
    trOUT1->Branch("frac03"            ,&frac03_      ,"frac01_/F");
    trOUT1->Branch("frac04"            ,&frac04_      ,"frac01_/F");
    trOUT1->Branch("ptD"               ,&ptD_         ,"ptD_/F");
    trOUT1->Branch("beta"              ,&beta_        ,"beta_/F");
    trOUT1->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
    trOUT1->Branch("pull"              ,&pull_        ,"pull_/F");
    trOUT1->Branch("jetR"              ,&jetR_        ,"jetR_/F");
    trOUT1->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
    trOUT1->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
    trOUT1->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
    trOUT1->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
    trOUT1->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
    trOUT1->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
    trOUT1->Branch("nTrueInt"          ,&npu_         ,"npu_/I");
    trOUT1->Branch("genevtwt_"           ,&genevtwt_    ,"genevtwt_/F");      
  */
  trOUT2->Branch("runNum"            ,&runNum_      ,"runNum_/I");
  trOUT2->Branch("evtNum"            ,&evtNum_      ,"evtNum_/I");
  trOUT2->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
  trOUT2->Branch("rho"               ,&rho_         ,"rho_/F");
  trOUT2->Branch("jetPt"             ,&pt_          ,"pt_/F");
  trOUT2->Branch("jetEta"            ,&eta_         ,"eta_/F");
  trOUT2->Branch("phi"               ,&phi_         ,"phi_/F");
  trOUT2->Branch("mass"              ,&mass_        ,"mass_/F");
  trOUT2->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
  trOUT2->Branch("majW"              ,&majW_        ,"majW_/F");
  trOUT2->Branch("minW"              ,&minW_        ,"minW_/F");
  trOUT2->Branch("frac01"            ,&frac01_      ,"frac01_/F");
  trOUT2->Branch("frac02"            ,&frac02_      ,"frac01_/F");
  trOUT2->Branch("frac03"            ,&frac03_      ,"frac01_/F");
  trOUT2->Branch("frac04"            ,&frac04_      ,"frac01_/F");
  trOUT2->Branch("ptD"               ,&ptD_         ,"ptD_/F");
  trOUT2->Branch("beta"              ,&beta_        ,"beta_/F");
  trOUT2->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
  trOUT2->Branch("pull"              ,&pull_        ,"pull_/F");
  trOUT2->Branch("jetR"              ,&jetR_        ,"jetR_/F");
  trOUT2->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
  trOUT2->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
  trOUT2->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
  trOUT2->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
  trOUT2->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
  trOUT2->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
  trOUT2->Branch("nTrueInt"          ,&npu_         ,"npu_/I");
  trOUT2->Branch("genevtwt_"         ,&genevtwt_    ,"genevtwt_/F");
  /*
    trOUT3->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
    trOUT3->Branch("rho"               ,&rho_         ,"rho_/F");
    trOUT3->Branch("jetPt"             ,&pt_          ,"pt_/F");
    trOUT3->Branch("jetEta"            ,&eta_         ,"eta_/F");
    trOUT3->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
    trOUT3->Branch("majW"              ,&majW_        ,"majW_/F");
    trOUT3->Branch("minW"              ,&minW_        ,"minW_/F");
    trOUT3->Branch("frac01"            ,&frac01_      ,"frac01_/F");
    trOUT3->Branch("frac02"            ,&frac02_      ,"frac01_/F");
    trOUT3->Branch("frac03"            ,&frac03_      ,"frac01_/F");
    trOUT3->Branch("frac04"            ,&frac04_      ,"frac01_/F");
    trOUT3->Branch("ptD"               ,&ptD_         ,"ptD_/F");
    trOUT3->Branch("beta"              ,&beta_        ,"beta_/F");
    trOUT3->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
    trOUT3->Branch("pull"              ,&pull_        ,"pull_/F");
    trOUT3->Branch("jetR"              ,&jetR_        ,"jetR_/F");
    trOUT3->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
    trOUT3->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
    trOUT3->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
    trOUT3->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
    trOUT3->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
    trOUT3->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
    trOUT3->Branch("nTrueInt"          ,&npu_         ,"npu_/I");
    trOUT3->Branch("genevtwt_"           ,&genevtwt_    ,"genevtwt_/F");
  */
    trOUT4->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
    trOUT4->Branch("rho"               ,&rho_         ,"rho_/F");
    trOUT4->Branch("jetPt"             ,&pt_          ,"pt_/F");
    trOUT4->Branch("jetEta"            ,&eta_         ,"eta_/F");
    trOUT4->Branch("phi"               ,&phi_         ,"phi_/F");
    trOUT4->Branch("mass"              ,&mass_        ,"mass_/F");
    trOUT4->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
    trOUT4->Branch("majW"              ,&majW_        ,"majW_/F");
    trOUT4->Branch("minW"              ,&minW_        ,"minW_/F");
    trOUT4->Branch("frac01"            ,&frac01_      ,"frac01_/F");
    trOUT4->Branch("frac02"            ,&frac02_      ,"frac01_/F");
    trOUT4->Branch("frac03"            ,&frac03_      ,"frac01_/F");
    trOUT4->Branch("frac04"            ,&frac04_      ,"frac01_/F");
    trOUT4->Branch("ptD"               ,&ptD_         ,"ptD_/F");
    trOUT4->Branch("beta"              ,&beta_        ,"beta_/F");
    trOUT4->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
    trOUT4->Branch("pull"              ,&pull_        ,"pull_/F");
    trOUT4->Branch("jetR"              ,&jetR_        ,"jetR_/F");
    trOUT4->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
    trOUT4->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
    trOUT4->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
    trOUT4->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
    trOUT4->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
    trOUT4->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
    trOUT4->Branch("nTrueInt"          ,&npu_         ,"npu_/I"); 
    trOUT4->Branch("genevtwt_"           ,&genevtwt_    ,"genevtwt_/F");
  /*
    trOUT5->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
    trOUT5->Branch("rho"               ,&rho_         ,"rho_/F");
    trOUT5->Branch("jetPt"             ,&pt_          ,"pt_/F");
    trOUT5->Branch("jetEta"            ,&eta_         ,"eta_/F");
    trOUT5->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
    trOUT5->Branch("majW"              ,&majW_        ,"majW_/F");
    trOUT5->Branch("minW"              ,&minW_        ,"minW_/F");
    trOUT5->Branch("frac01"            ,&frac01_      ,"frac01_/F");
    trOUT5->Branch("frac02"            ,&frac02_      ,"frac01_/F");
    trOUT5->Branch("frac03"            ,&frac03_      ,"frac01_/F");
    trOUT5->Branch("frac04"            ,&frac04_      ,"frac01_/F");
    trOUT5->Branch("ptD"               ,&ptD_         ,"ptD_/F");
    trOUT5->Branch("beta"              ,&beta_        ,"beta_/F");
    trOUT5->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
    trOUT5->Branch("pull"              ,&pull_        ,"pull_/F");
    trOUT5->Branch("jetR"              ,&jetR_        ,"jetR_/F");
    trOUT5->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
    trOUT5->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
    trOUT5->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
    trOUT5->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
    trOUT5->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
    trOUT5->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
    trOUT5->Branch("nTrueInt"          ,&npu_         ,"npu_/I");
    trOUT5->Branch("genevtwt_"           ,&genevtwt_    ,"genevtwt_/F");
  */
    trOUT6->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
    trOUT6->Branch("rho"               ,&rho_         ,"rho_/F");
    trOUT6->Branch("jetPt"             ,&pt_          ,"pt_/F");
    trOUT6->Branch("jetEta"            ,&eta_         ,"eta_/F");
    trOUT6->Branch("phi"               ,&phi_         ,"phi_/F");
    trOUT6->Branch("mass"              ,&mass_        ,"mass_/F");
    trOUT6->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
    trOUT6->Branch("majW"              ,&majW_        ,"majW_/F");
    trOUT6->Branch("minW"              ,&minW_        ,"minW_/F");
    trOUT6->Branch("frac01"            ,&frac01_      ,"frac01_/F");
    trOUT6->Branch("frac02"            ,&frac02_      ,"frac01_/F");
    trOUT6->Branch("frac03"            ,&frac03_      ,"frac01_/F");
    trOUT6->Branch("frac04"            ,&frac04_      ,"frac01_/F");
    trOUT6->Branch("ptD"               ,&ptD_         ,"ptD_/F");
    trOUT6->Branch("beta"              ,&beta_        ,"beta_/F");
    trOUT6->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
    trOUT6->Branch("pull"              ,&pull_        ,"pull_/F");
    trOUT6->Branch("jetR"              ,&jetR_        ,"jetR_/F");
    trOUT6->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
    trOUT6->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
    trOUT6->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
    trOUT6->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
    trOUT6->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
    trOUT6->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
    trOUT6->Branch("nTrueInt"          ,&npu_         ,"npu_/I");
    trOUT6->Branch("genevtwt_"           ,&genevtwt_    ,"genevtwt_/F");
  /*
    trOUT7->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
    trOUT7->Branch("rho"               ,&rho_         ,"rho_/F");
    trOUT7->Branch("jetPt"             ,&pt_          ,"pt_/F");
    trOUT7->Branch("jetEta"            ,&eta_         ,"eta_/F");
    trOUT7->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
    trOUT7->Branch("majW"              ,&majW_        ,"majW_/F");
    trOUT7->Branch("minW"              ,&minW_        ,"minW_/F");
    trOUT7->Branch("frac01"            ,&frac01_      ,"frac01_/F");
    trOUT7->Branch("frac02"            ,&frac02_      ,"frac01_/F");
    trOUT7->Branch("frac03"            ,&frac03_      ,"frac01_/F");
    trOUT7->Branch("frac04"            ,&frac04_      ,"frac01_/F");
    trOUT7->Branch("ptD"               ,&ptD_         ,"ptD_/F");
    trOUT7->Branch("beta"              ,&beta_        ,"beta_/F");
    trOUT7->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
    trOUT7->Branch("pull"              ,&pull_        ,"pull_/F");
    trOUT7->Branch("jetR"              ,&jetR_        ,"jetR_/F");
    trOUT7->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
    trOUT7->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
    trOUT7->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
    trOUT7->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
    trOUT7->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
    trOUT7->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
    trOUT7->Branch("nTrueInt"          ,&npu_         ,"npu_/I");
    trOUT7->Branch("genevtwt_"           ,&genevtwt_    ,"genevtwt_/F");
  */
    trOUT8->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
    trOUT8->Branch("rho"               ,&rho_         ,"rho_/F");
    trOUT8->Branch("jetPt"             ,&pt_          ,"pt_/F");
    trOUT8->Branch("jetEta"            ,&eta_         ,"eta_/F");
    trOUT8->Branch("phi"               ,&phi_         ,"phi_/F");
    trOUT8->Branch("mass"              ,&mass_        ,"mass_/F");
    trOUT8->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
    trOUT8->Branch("majW"              ,&majW_        ,"majW_/F");
    trOUT8->Branch("minW"              ,&minW_        ,"minW_/F");
    trOUT8->Branch("frac01"            ,&frac01_      ,"frac01_/F");
    trOUT8->Branch("frac02"            ,&frac02_      ,"frac01_/F");
    trOUT8->Branch("frac03"            ,&frac03_      ,"frac01_/F");
    trOUT8->Branch("frac04"            ,&frac04_      ,"frac01_/F");
    trOUT8->Branch("ptD"               ,&ptD_         ,"ptD_/F");
    trOUT8->Branch("beta"              ,&beta_        ,"beta_/F");
    trOUT8->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
    trOUT8->Branch("pull"              ,&pull_        ,"pull_/F");
    trOUT8->Branch("jetR"              ,&jetR_        ,"jetR_/F");
    trOUT8->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
    trOUT8->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
    trOUT8->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
    trOUT8->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
    trOUT8->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
    trOUT8->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
    trOUT8->Branch("nTrueInt"          ,&npu_         ,"npu_/I");
    trOUT8->Branch("genevtwt_"           ,&genevtwt_    ,"genevtwt_/F");
  
  int decade(0);
  int NN = trIN_chs->GetEntries();
  int NN_pu = trIN_puppi->GetEntries();
  
  cout<<"Reading chs "<<NN<< " entries "<<endl;
  cout<<"Reading puppi "<<NN_pu<< " entries "<<endl;

  for(int iev=0;iev<20000;iev++) {
    double progress = 10.0*iev/(1.0*iev);
    int k = TMath::FloorNint(progress); 
    if (k > decade) 
      cout<<10*k<<" %"<<endl;
    decade = k; 
    
    trIN_chs->GetEntry(iev);
    //std::cout << " inside chs event number " << iev << std::endl;
    
    for(int ievp=0;ievp<20000;ievp++) {
      trIN_puppi->GetEntry(ievp);
      
      // std::cout << " inside puppi event number " << ievp << std::endl;

      if (genevtwt != -999 && genevtwt_p != -999 && evtNum == evtNum_p && runNum == runNum_p) {
	//std::cout << " evtNum " << evtNum << " evtNum_p " << evtNum_p << " runNum " << runNum << " runNum_p " << runNum_p << std::endl;
	for(unsigned j=0;j<pt->size();j++) {

	  if ((*pt)[j] > 50 && (*pt)[j] < 15 && (*genPt)[j] < 10) continue;

	  float dRmin(99);
          
	  for(unsigned k=0;k<pt_p->size();k++) {

	    if ((*pt_p)[k] > 50 && (*pt_p)[k] < 15 && (*genPt_p)[k] < 10) continue;

            if ((*genDR)[j] > 0.4 && (*flavorParton)[j] == 0 /*&& fabs((*eta)[j]) < 2.5 && */ && (*genDR_p)[k] > 0.4 && (*flavorParton_p)[k] == 0 /*&& fabs((*eta_p)[k]) < 2.5*/) {
	
	      float p1 = (*aziphi)[j];
              float p2 = (*aziphi_p)[k];
              float e1 = (*eta)[j];
              float e2 = (*eta_p)[k];
	      auto dp = std::abs(p1 - p2);
	      if (dp > float(M_PI)) dp -= float(2 * M_PI);
              float dR = sqrt((e1 - e2) * (e1 - e2) + dp * dp);
	      //std::cout << " dR " << dR << std::endl;
	      if (dR < dRmin) dRmin = dR;
            }
          }
	
	  if (dRmin < 0.3) {

	    //std::cout << " dRmin " << dRmin << std::endl;

	    genevtwt_ = genevtwt;
	    nVtx_         = nVtx;
	    npu_          = npu;
	    rho_          = rho;
	    flavorParton_ = (*flavorParton)[j];
	    nParticles_   = (*nParticles)[j];
	    nCharged_     = (*nCharged)[j];
	    pt_           = (*pt)[j];
	    eta_          = (*eta)[j];
	    genDR_        = (*genDR)[j];
	    genPt_        = (*genPt)[j];
	    beta_         = (*beta)[j];
	    betaStar_     = (*betaStar)[j];
	    pull_         = (*pull)[j];
	    jetR_         = (*jetR)[j];
	    jetRchg_      = (*jetRchg)[j];
	    dR2Mean_      = (*dR2Mean)[j];
	    majW_         = (*majW)[j];
	    minW_         = (*minW)[j];
	    frac01_       = (*frac01)[j];
	    frac02_       = (*frac02)[j];
	    frac03_       = (*frac03)[j];
	    frac04_       = (*frac04)[j];
	    ptD_          = (*ptD)[j];
	    float abs_eta = fabs(eta_);
	    
	    //if (pt_ > 50 && pt_ < 15 && genPt_ < 10) continue;
	    
	    //if (genDR_ < 0.01 && flavorParton_ != 0) {
	    //	  if (abs_eta < 2.5) { 
	    //	    trOUT1->Fill();
	    //	  }
	    //else if (abs_eta > 2.5 && abs_eta < 2.75) {
	    //trOUT3->Fill();
	    //}
	    //else if (abs_eta > 2.75 && abs_eta < 3.0) {
	    //trOUT5->Fill();
	    //}
	    //else if (abs_eta > 3.0 && abs_eta < 5.0) {
	    //trOUT7->Fill();
	    //}
	    //else {
	    //trOUT7->Fill();
	    //} 
	    //}

	    if ((genDR_ > 0.4) && (flavorParton_ == 0)) {
	      if (abs_eta < 2.5) { 
		trOUT2->Fill();
	      }
	      else if (abs_eta > 2.5 && abs_eta < 2.75) {
		trOUT4->Fill();
	      }
	      else if (abs_eta > 2.75 && abs_eta < 3.0) {
		trOUT6->Fill();
	      }
	      else if (abs_eta > 3.0 && abs_eta < 5.0) {
		trOUT8->Fill();
	      }
	      //else {
	      //trOUT8->Fill();
	      //}*/
	    }
	  }
	  else continue;
	  //} /*commented out if (sigmatMin != 999 && timediffMin != 999) {* as time not stored with Run2/Run3
	}
	break;
      }
      //break;
    }
  }
  //}
  cout<<"==== Number of jets ===="<<endl;
  cout<<"0.0  - 2.5 bkg: "<<trOUT2->GetEntries()<<endl;
  cout<<"2.5  - 2.75 bkg: "<<trOUT4->GetEntries()<<endl;
  cout<<"2.75 - 3.0 bkg: "<< trOUT6->GetEntries()<<endl;
  cout<<"3.0  - 5.0 bkg: "<< trOUT8->GetEntries()<<endl; 

  //cout<<"0.0  - 2.5  sig: "<<trOUT1->GetEntries()<<", bkg: "<<trOUT2->GetEntries()<<endl;
  //cout<<"2.5  - 2.75 sig: "<<trOUT3->GetEntries()<<", bkg: "<<trOUT4->GetEntries()<<endl;
  //cout<<"2.75 - 3.0  sig: "<<trOUT5->GetEntries()<<", bkg: "<<trOUT6->GetEntries()<<endl;
  //cout<<"3.0  - 5.0  sig: "<<trOUT7->GetEntries()<<", bkg: "<<trOUT8->GetEntries()<<endl; 
  outf->cd();
 //trOUT1->Write();
  trOUT2->Write();
  //trOUT3->Write();
  trOUT4->Write();
  //trOUT5->Write();
  trOUT6->Write();
  //trOUT7->Write();
  trOUT8->Write();
  outf->Close();
  inf->Close();
}






















