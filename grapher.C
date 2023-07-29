#include <iostream>
#include <TH1D.h>
#include <vector>
#include <TMath.h>
#include <TH1F.h>
#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <Math/Vector4D.h>
#include <Math/GenVector/PtEtaPhiM4D.h>
#include <TString.h>
#include <Math/VectorUtil.h>
#include <TH2D.h>
#include "TChain.h"
#include <string>
#include "TString.h"



int main(int argc, const char* argv[])
{
	using namespace std;
	std::vector<TString> input_files;
	if (argc<3)
	{
		std::cout << "enter at lease two arguments" <<std::endl;
		std::cout << "help:" << std::endl;
        std::cout << "" << std::endl;
        std::cout << " e.g." << std::endl;
        std::cout << "    $ " << argv[0] << " " << "/user/sote/blahbalh/somedirectory" << std::endl;
		std::cout << "    $ " << argv[0] << " " << "don't put / at the end of the directory path" << std::endl;
        std::cout << "    $ " << argv[1] << " " << "name of first root file" <<  std::endl;
        std::cout << "    $ " << argv[2] << " " << "name of second root file" << std::endl;
        std::cout << "    $ " << argv[3] << " " << "name of third root file" << std::endl;
        return 1;
	}


	int n_jets,n_loose_b_jets, n_medium_b_jets, n_tight_b_jets, n_fatjets, bQuarksInHiggsJet;
	double HT,ld_vbsjet_pt,ld_vbsjet_eta,ld_vbsjet_phi,tr_vbsjet_pt,tr_vbsjet_eta,tr_vbsjet_phi,M_jj,deta_jj,abs_deta_jj;
	double MET,ld_vqqfatjet_pt,ld_vqqfatjet_eta,ld_vqqfatjet_phi,ld_vqqfatjet_mass,ld_vqqfatjet_msoftdrop,tr_vqqfatjet_pt,tr_vqqfatjet_eta;
	double tr_vqqfatjet_phi,tr_vqqfatjet_mass,tr_vqqfatjet_msoftdrop,hbbfatjet_pt,hbbfatjet_eta,hbbfatjet_phi,hbbfatjet_mass,hbbfatjet_msoftdrop,ST;
	double ld_vqqjet_pt,ld_vqqjet_eta,ld_vqqjet_phi,ld_vqqjet_mass,tr_vqqjet_pt,tr_vqqjet_eta,tr_vqqjet_phi,tr_vqqjet_mass,vqqjets_Mjj,vqqjets_dR;
	// for the semi merged channel (the two ak4 jets)

	double vqqjets_pt, vqqjets_phi, vqqjets_mass, vqqjets_eta;




	std::string arg2 = argv[2];
	std::string dir_for_rootfiles = argv[1];
	std::string outputname = argv[argc-1];

	int weight_of_eachevent=1;

	for (int i = 2; i < argc-1; i++)
	{
		std::string name_root_file = argv[i];
		TString file_path = TString::Format("%s/%s", dir_for_rootfiles.c_str(),name_root_file.c_str());
		input_files.push_back(file_path);
	}
	TFile * f_output;
	TString outputname_constchar = TString::Format("%s", outputname.c_str());
	f_output =new TFile (outputname_constchar,"recreate");

	//creat the histograms
	TH1D* hist_HT = new TH1D ("hist_HT", "hist_HT", 80, 0, 1000);
	TH1F* hist_n_jets = new TH1F ("hist_n_jets", "hist_n_jets", 10, 0, 10);
	TH1F* hist_n_loose_b_jets = new TH1F ("hist_n_loose_b_jets", "hist_n_loose_b_jets", 5, 0, 5);
	TH1D* hist_n_medium_b_jets = new TH1D ("hist_n_medium_b_jets", "hist_n_medium_b_jets", 80, 0, 5);
	TH1D* hist_n_tight_b_jets = new TH1D ("hist_n_tight_b_jets", "hist_n_tight_b_jets", 80, 0, 5);
	TH1F* hist_n_fatjets = new TH1F ("hist_n_fatjets", "hist_n_fatjets", 5, 0, 5);
	TH1D* hist_ld_vbsjet_pt = new TH1D ("hist_ld_vbsjet_pt", "hist_ld_vbsjet_pt", 80, 0, 800);
	TH1D* hist_ld_vbsjet_eta = new TH1D ("hist_ld_vbsjet_eta", "hist_ld_vbsjet_eta", 80, -6, 6);
	TH1D* hist_ld_vbsjet_phi = new TH1D ("hist_ld_vbsjet_phi", "hist_ld_vbsjet_phi", 80, -6, 6);
	TH1D* hist_tr_vbsjet_pt = new TH1D ("hist_tr_vbsjet_pt", "hist_tr_vbsjet_pt", 80, 0, 500);
	TH1D* hist_tr_vbsjet_eta = new TH1D ("hist_tr_vbsjet_eta", "hist_tr_vbsjet_eta", 80, -6, 6);
	TH1D* hist_tr_vbsjet_phi = new TH1D ("hist_tr_vbsjet_phi", "hist_tr_vbsjet_phi", 80, -6, 6);
	TH1D* hist_M_jj = new TH1D ("hist_M_jj", "hist_M_jj", 80, 0, 10000);
	TH1D* hist_M_jj_0_250 = new TH1D ("hist_M_jj_0_250", "hist_M_jj_0_250", 80, 0, 250);
	TH1D* hist_deta_jj = new TH1D ("hist_deta_jj", "hist_deta_jj", 80, -10, 10);
	TH1D* hist_abs_deta_jj = new TH1D ("hist_abs_deta_jj", "hist_abs_deta_jj", 80, 0, 10);
	TH1D* hist_MET = new TH1D ("hist_MET", "hist_MET", 80, 0, 800);
	// TH1D* hist_ld_vqqfatjet_score = new TH1D ("hist_ld_vqqfatjet_score", "hist_ld_vqqfatjet_score", 100, 0, 1);
	TH1D* hist_ld_vqqfatjet_pt = new TH1D ("hist_ld_vqqfatjet_pt", "hist_ld_vqqfatjet_pt", 80, 0, 3000);
	TH1D* hist_ld_vqqfatjet_eta = new TH1D ("hist_ld_vqqfatjet_eta", "hist_ld_vqqfatjet_eta", 80, -6, 6);
	TH1D* hist_ld_vqqfatjet_phi = new TH1D ("hist_ld_vqqfatjet_phi", "hist_ld_vqqfatjet_phi", 80, -6, 6);
	TH1D* hist_ld_vqqfatjet_mass = new TH1D ("hist_ld_vqqfatjet_mass", "hist_ld_vqqfatjet_mass", 80, 0, 250);
	TH1D* hist_ld_vqqfatjet_msoftdrop = new TH1D ("hist_ld_vqqfatjet_msoftdrop", "hist_ld_vqqfatjet_msoftdrop", 80, 0, 250);
	// TH1D* hist_tr_vqqfatjet_score = new TH1D ("hist_tr_vqqfatjet_score", "hist_tr_vqqfatjet_score", 100, 0, 1);
	// TH1D* hist_tr_vqqfatjet_pt = new TH1D ("hist_tr_vqqfatjet_pt", "hist_tr_vqqfatjet_pt", 80, 0, 3000);
	// TH1D* hist_tr_vqqfatjet_eta = new TH1D ("hist_tr_vqqfatjet_eta", "hist_tr_vqqfatjet_eta", 80, -6, 6);
	// TH1D* hist_tr_vqqfatjet_phi = new TH1D ("hist_tr_vqqfatjet_phi", "hist_tr_vqqfatjet_phi", 80, -6, 6);
	// TH1D* hist_tr_vqqfatjet_mass = new TH1D ("hist_tr_vqqfatjet_mass", "hist_tr_vqqfatjet_mass", 80, 0, 250);
	// TH1D* hist_tr_vqqfatjet_msoftdrop = new TH1D ("hist_tr_vqqfatjet_msoftdrop", "hist_tr_vqqfatjet_msoftdrop", 80, 0, 250);
	// TH1D* hist_hbbfatjet_score = new TH1D ("hist_hbbfatjet_score", "hist_hbbfatjet_score", 100, 0, 1);
	TH1D* hist_hbbfatjet_pt = new TH1D ("hist_hbbfatjet_pt", "hist_hbbfatjet_pt", 80, 0, 3000);
	TH1D* hist_hbbfatjet_eta = new TH1D ("hist_hbbfatjet_eta", "hist_hbbfatjet_eta", 80, -6, 6);
	TH1D* hist_hbbfatjet_phi = new TH1D ("hist_hbbfatjet_phi", "hist_hbbfatjet_phi", 80, -6, 6);
	TH1D* hist_hbbfatjet_mass = new TH1D ("hist_hbbfatjet_mass", "hist_hbbfatjet_mass", 80, 0, 250);
	TH1D* hist_hbbfatjet_msoftdrop = new TH1D ("hist_hbbfatjet_msoftdrop", "hist_hbbfatjet_msoftdrop", 80, 0, 250);
	TH1D* hist_ST = new TH1D ("hist_ST", "hist_ST", 80, 0, 6000);

	// for the semi merged channel (the two ak4 jets)
	TH1D* hist_ld_vqqjet_pt = new TH1D ("hist_ld_vqqjet_pt", "hist_ld_vqqjet_pt", 80, 0, 2000);
	TH1D* hist_ld_vqqjet_eta = new TH1D ("hist_ld_vqqjet_eta", "hist_ld_vqqjet_eta", 80, -6, 6);
	TH1D* hist_ld_vqqjet_phi = new TH1D ("hist_ld_vqqjet_phi", "hist_ld_vqqjet_phi", 80, -6, 6);
	TH1D* hist_ld_vqqjet_mass = new TH1D ("hist_ld_vqqjet_mass", "hist_ld_vqqjet_mass", 80, 0, 100);
	TH1D* hist_tr_vqqjet_pt = new TH1D ("hist_tr_vqqjet_pt", "hist_tr_vqqjet_pt", 80, 0, 2000);
	TH1D* hist_tr_vqqjet_eta = new TH1D ("hist_tr_vqqjet_eta", "hist_tr_vqqjet_eta", 80, -6, 6);
	TH1D* hist_tr_vqqjet_phi = new TH1D ("hist_tr_vqqjet_phi", "hist_tr_vqqjet_phi", 80, -6, 6);
	TH1D* hist_tr_vqqjet_mass = new TH1D ("hist_tr_vqqjet_mass", "hist_tr_vqqjet_mass", 80, 0, 100);
	// TH1D* hist_vqqjets_Mjj = new TH1D ("hist_vqqjets_Mjj", "hist_vqqjets_Mjj", 80, 0, 250);
	TH1D* hist_vqqjets_dR = new TH1D ("hist_vqqjets_dR", "hist_vqqjets_dR", 80, 0, 10);

//  combining the two vqq ak4 jets four vectors
	TH1D* hist_vqqjets_pt = new TH1D ("hist_vqqjets_pt", "hist_vqqjets_pt", 80, 0, 2000);
	TH1D* hist_vqqjets_eta = new TH1D ("hist_vqqjets_eta", "hist_vqqjets_eta", 80, -6, 6);
	TH1D* hist_vqqjets_phi = new TH1D ("hist_vqqjets_phi", "hist_vqqjets_phi", 80, -6, 6);
	TH1D* hist_vqqjets_mass = new TH1D ("hist_vqqjets_mass", "hist_vqqjets_mass", 80, 0, 250);

	TH1D* hist_bQuarksInHiggsJet = new TH1D ("hist_bQuarksInHiggsJet", "hist_bQuarksInHiggsJet", 80, 0, 6);


	for (int ifile = 0; ifile < input_files.size(); ifile++)
	{
		TFile* f1 = new TFile(input_files[ifile]);
		TTree* t1 = (TTree*) f1->Get("tree");

		t1->SetBranchAddress("HT", &HT);
		t1->SetBranchAddress("n_jets", &n_jets);
		t1->SetBranchAddress("n_loose_b_jets", &n_loose_b_jets);
		t1->SetBranchAddress("n_medium_b_jets", &n_medium_b_jets);
		t1->SetBranchAddress("n_tight_b_jets", &n_tight_b_jets);
		t1->SetBranchAddress("n_fatjets", &n_fatjets);
		t1->SetBranchAddress("ld_vbsjet_pt", &ld_vbsjet_pt);
		t1->SetBranchAddress("ld_vbsjet_eta", &ld_vbsjet_eta);
		t1->SetBranchAddress("ld_vbsjet_phi", &ld_vbsjet_phi);
		t1->SetBranchAddress("tr_vbsjet_pt", &tr_vbsjet_pt);
		t1->SetBranchAddress("tr_vbsjet_eta", &tr_vbsjet_eta);
		t1->SetBranchAddress("tr_vbsjet_phi", &tr_vbsjet_phi);
		t1->SetBranchAddress("M_jj", &M_jj);
		t1->SetBranchAddress("deta_jj", &deta_jj);
		t1->SetBranchAddress("abs_deta_jj", &abs_deta_jj);
		t1->SetBranchAddress("MET", &MET);
		// t1->SetBranchAddress("ld_vqqfatjet_score", &ld_vqqfatjet_score);
		t1->SetBranchAddress("ld_vqqfatjet_pt", &ld_vqqfatjet_pt);
		t1->SetBranchAddress("ld_vqqfatjet_eta", &ld_vqqfatjet_eta);
		t1->SetBranchAddress("ld_vqqfatjet_phi", &ld_vqqfatjet_phi);
		t1->SetBranchAddress("ld_vqqfatjet_mass", &ld_vqqfatjet_mass);
		t1->SetBranchAddress("ld_vqqfatjet_msoftdrop", &ld_vqqfatjet_msoftdrop);
		// t1->SetBranchAddress("tr_vqqfatjet_score", &tr_vqqfatjet_score);
		// t1->SetBranchAddress("tr_vqqfatjet_pt", &tr_vqqfatjet_pt);
		// t1->SetBranchAddress("tr_vqqfatjet_eta", &tr_vqqfatjet_eta);
		// t1->SetBranchAddress("tr_vqqfatjet_phi", &tr_vqqfatjet_phi);
		// t1->SetBranchAddress("tr_vqqfatjet_mass", &tr_vqqfatjet_mass);
		// t1->SetBranchAddress("tr_vqqfatjet_msoftdrop", &tr_vqqfatjet_msoftdrop);
		// t1->SetBranchAddress("hbbfatjet_score", &hbbfatjet_score);
		t1->SetBranchAddress("hbbfatjet_pt", &hbbfatjet_pt);
		t1->SetBranchAddress("hbbfatjet_eta", &hbbfatjet_eta);
		t1->SetBranchAddress("hbbfatjet_phi", &hbbfatjet_phi);
		t1->SetBranchAddress("hbbfatjet_mass", &hbbfatjet_mass);
		t1->SetBranchAddress("hbbfatjet_msoftdrop", &hbbfatjet_msoftdrop);
		t1->SetBranchAddress("ST", &ST);

		// for the semi merged channel (the two ak4 jets)
		t1->SetBranchAddress("ld_vqqjet_pt", &ld_vqqjet_pt);
		t1->SetBranchAddress("ld_vqqjet_eta", &ld_vqqjet_eta);
		t1->SetBranchAddress("ld_vqqjet_phi", &ld_vqqjet_phi);
		t1->SetBranchAddress("ld_vqqjet_mass", &ld_vqqjet_mass);
		t1->SetBranchAddress("tr_vqqjet_pt", &tr_vqqjet_pt);
		t1->SetBranchAddress("tr_vqqjet_eta", &tr_vqqjet_eta);
		t1->SetBranchAddress("tr_vqqjet_phi", &tr_vqqjet_phi);
		t1->SetBranchAddress("tr_vqqjet_mass", &tr_vqqjet_mass);
		t1->SetBranchAddress("vqqjets_Mjj", &vqqjets_Mjj);
		t1->SetBranchAddress("vqqjets_dR", &vqqjets_dR);
		//  combining the two vqq ak4 jets four vectors
		t1->SetBranchAddress("vqqjets_pt", &vqqjets_pt);
		t1->SetBranchAddress("vqqjets_eta", &vqqjets_eta);
		t1->SetBranchAddress("vqqjets_phi", &vqqjets_phi);
		t1->SetBranchAddress("vqqjets_mass", &vqqjets_mass);

		t1->SetBranchAddress("bQuarksInHiggsJet", &bQuarksInHiggsJet);


		for (int i1 = 0; i1 < t1->GetEntries(); i1++)
		{
			t1->GetEntry(i1);
			if(i1% 10000 ==0) std::cout<<i1<<std::endl;

			hist_HT->Fill(HT, weight_of_eachevent);
			hist_n_jets->Fill(n_jets, weight_of_eachevent);
			hist_n_loose_b_jets->Fill(n_loose_b_jets, weight_of_eachevent);
			hist_n_medium_b_jets->Fill(n_medium_b_jets, weight_of_eachevent);
			hist_n_tight_b_jets->Fill(n_tight_b_jets, weight_of_eachevent);
			hist_n_fatjets->Fill(n_fatjets, weight_of_eachevent);
			hist_ld_vbsjet_pt->Fill(ld_vbsjet_pt, weight_of_eachevent);
			hist_ld_vbsjet_eta->Fill(ld_vbsjet_eta, weight_of_eachevent);
			hist_ld_vbsjet_phi->Fill(ld_vbsjet_phi, weight_of_eachevent);
			hist_tr_vbsjet_pt->Fill(tr_vbsjet_pt, weight_of_eachevent);
			hist_tr_vbsjet_eta->Fill(tr_vbsjet_eta, weight_of_eachevent);
			hist_tr_vbsjet_phi->Fill(tr_vbsjet_phi, weight_of_eachevent);
			hist_M_jj->Fill(M_jj, weight_of_eachevent);
			hist_M_jj_0_250->Fill(M_jj, weight_of_eachevent);
			hist_deta_jj->Fill(deta_jj, weight_of_eachevent);
			hist_abs_deta_jj->Fill(abs_deta_jj, weight_of_eachevent);
			hist_MET->Fill(MET, weight_of_eachevent);
			// hist_ld_vqqfatjet_score->Fill(ld_vqqfatjet_score, weight_of_eachevent);
			hist_ld_vqqfatjet_pt->Fill(ld_vqqfatjet_pt, weight_of_eachevent);
			hist_ld_vqqfatjet_eta->Fill(ld_vqqfatjet_eta, weight_of_eachevent);
			hist_ld_vqqfatjet_phi->Fill(ld_vqqfatjet_phi, weight_of_eachevent);
			hist_ld_vqqfatjet_mass->Fill(ld_vqqfatjet_mass, weight_of_eachevent);
			hist_ld_vqqfatjet_msoftdrop->Fill(ld_vqqfatjet_msoftdrop, weight_of_eachevent);
			// hist_tr_vqqfatjet_score->Fill(tr_vqqfatjet_score, weight_of_eachevent);
			// hist_tr_vqqfatjet_pt->Fill(tr_vqqfatjet_pt, weight_of_eachevent);
			// hist_tr_vqqfatjet_eta->Fill(tr_vqqfatjet_eta, weight_of_eachevent);
			// hist_tr_vqqfatjet_phi->Fill(tr_vqqfatjet_phi, weight_of_eachevent);
			// hist_tr_vqqfatjet_mass->Fill(tr_vqqfatjet_mass, weight_of_eachevent);
			// hist_tr_vqqfatjet_msoftdrop->Fill(tr_vqqfatjet_msoftdrop, weight_of_eachevent);
			// hist_hbbfatjet_score->Fill(hbbfatjet_score, weight_of_eachevent);
			hist_hbbfatjet_pt->Fill(hbbfatjet_pt, weight_of_eachevent);
			hist_hbbfatjet_eta->Fill(hbbfatjet_eta, weight_of_eachevent);
			hist_hbbfatjet_phi->Fill(hbbfatjet_phi, weight_of_eachevent);
			hist_hbbfatjet_mass->Fill(hbbfatjet_mass, weight_of_eachevent);
			hist_hbbfatjet_msoftdrop->Fill(hbbfatjet_msoftdrop, weight_of_eachevent);
			hist_ST->Fill(ST, weight_of_eachevent);

			// for the semi merged channel (the two ak4 jets)
			hist_ld_vqqjet_pt->Fill(ld_vqqjet_pt, weight_of_eachevent);
			hist_ld_vqqjet_eta->Fill(ld_vqqjet_eta, weight_of_eachevent);
			hist_ld_vqqjet_phi->Fill(ld_vqqjet_phi, weight_of_eachevent);
			hist_ld_vqqjet_mass->Fill(ld_vqqjet_mass, weight_of_eachevent);
			hist_tr_vqqjet_pt->Fill(tr_vqqjet_pt, weight_of_eachevent);
			hist_tr_vqqjet_eta->Fill(tr_vqqjet_eta, weight_of_eachevent);
			hist_tr_vqqjet_phi->Fill(tr_vqqjet_phi, weight_of_eachevent);
			hist_tr_vqqjet_mass->Fill(tr_vqqjet_mass, weight_of_eachevent);
			// hist_vqqjets_Mjj->Fill(vqqjets_Mjj, weight_of_eachevent);
			hist_vqqjets_dR->Fill(vqqjets_dR, weight_of_eachevent);

			//  combining the two vqq ak4 jets four vectors
			hist_vqqjets_pt->Fill(vqqjets_pt, weight_of_eachevent);
			hist_vqqjets_eta->Fill(vqqjets_eta, weight_of_eachevent);
			hist_vqqjets_phi->Fill(vqqjets_phi, weight_of_eachevent);
			hist_vqqjets_mass->Fill(vqqjets_mass, weight_of_eachevent);

			hist_bQuarksInHiggsJet->Fill(bQuarksInHiggsJet, weight_of_eachevent);


	}
		f1->Close();
	}



	// for (int i1 = 0; i1 < input_files.size(); i1++) {
	// 	cout << input_files[i1] <<endl;
	// }

	f_output->cd();
	hist_HT->Write();
	hist_n_jets->Write();
	hist_n_loose_b_jets->Write();
	hist_n_medium_b_jets->Write();
	hist_n_tight_b_jets->Write();
	hist_n_fatjets->Write();
	hist_ld_vbsjet_pt->Write();
	hist_ld_vbsjet_eta->Write();
	hist_ld_vbsjet_phi->Write();
	hist_tr_vbsjet_pt->Write();
	hist_tr_vbsjet_eta->Write();
	hist_tr_vbsjet_phi->Write();
	hist_M_jj->Write();
	hist_M_jj_0_250->Write();
	hist_deta_jj->Write();
	hist_abs_deta_jj->Write();
	hist_MET->Write();
	// hist_ld_vqqfatjet_score->Write();
	hist_ld_vqqfatjet_pt->Write();
	hist_ld_vqqfatjet_eta->Write();
	hist_ld_vqqfatjet_phi->Write();
	hist_ld_vqqfatjet_mass->Write();
	hist_ld_vqqfatjet_msoftdrop->Write();
	// hist_tr_vqqfatjet_score->Write();
	// hist_tr_vqqfatjet_pt->Write();
	// hist_tr_vqqfatjet_eta->Write();
	// hist_tr_vqqfatjet_phi->Write();
	// hist_tr_vqqfatjet_mass->Write();
	// hist_tr_vqqfatjet_msoftdrop->Write();
	// hist_hbbfatjet_score->Write();
	hist_hbbfatjet_pt->Write();
	hist_hbbfatjet_eta->Write();
	hist_hbbfatjet_phi->Write();
	hist_hbbfatjet_mass->Write();
	hist_hbbfatjet_msoftdrop->Write();
	hist_ST->Write();


	hist_ld_vqqjet_pt->Write();
	hist_ld_vqqjet_eta->Write();
	hist_ld_vqqjet_phi->Write();
	hist_ld_vqqjet_mass->Write();
	hist_tr_vqqjet_pt->Write();
	hist_tr_vqqjet_eta->Write();
	hist_tr_vqqjet_phi->Write();
	hist_tr_vqqjet_mass->Write();
	// hist_vqqjets_Mjj->Write();
	hist_vqqjets_dR->Write();

	//  combining the two vqq ak4 jets four vectors
	hist_vqqjets_pt->Write();
	hist_vqqjets_eta->Write();
	hist_vqqjets_phi->Write();
	hist_vqqjets_mass->Write();

	hist_bQuarksInHiggsJet->Write();

    f_output->Close();



}
