#ifndef __TIDYPLOT__
#define __TIDYPLOT__

#include "TColor.h"
#include "TCanvas.h"
#include "TAttMarker.h"
#include "TLegend.h"
#include "TGraph.h"

#include "RooPlot.h"

using namespace RooFit;

std::vector<Double_t> GetRange(TTree* tree,TTree* tree2,TString var)
        {
                Double_t min = ((tree->GetMinimum(var) < tree2->GetMinimum(var)) ? tree->GetMinimum(var) : tree2->GetMinimum(var));
                Double_t max = ((tree->GetMaximum(var) > tree2->GetMaximum(var)) ? tree->GetMaximum(var) : tree2->GetMaximum(var));
                std::vector<Double_t> x = {};
                x.push_back(min);
                x.push_back(max);
                std::cout << "Range for " << var << " is: " << min << "-" << max << std::endl;
                return x;
        }
void PlotWorkspaceVars(RooWorkspace* ws_,std::vector<TString> vars,std::vector<RooDataSet*> data_list,std::vector<Double_t> weights_={0},TString output_name="RooVars.pdf",TString args="")
        {
                TCanvas * canvas = new TCanvas("canvas","canvas",800,800);

                canvas->DivideSquare(vars.size());

                std::vector<EColor> colors;
		colors = (std::vector<EColor>){kRed,kBlue,kBlack,kGreen,kYellow,kPink,kAzure,kOrange,kTeal,kCyan,kViolet,kSpring,kMagenta};

                std::vector<Double_t> weights = {1};

                for(int k=0;k<weights_.size();++k){weights.push_back(((weights_.size() > 0) ? weights_[k] : 1));}

                for(int i=0;i<vars.size(); ++i)
                {
                        canvas->cd(i+1);
                        RooRealVar * x = (RooRealVar*)ws_->var(vars[i]);
                        RooPlot * frame = x->frame();
			TLegend *legend = new TLegend(0.65,0.73,0.86,0.87);
			for(int j=0;j<data_list.size();++j)
                        {
				if(args=="V"){std::cout << Form("Printing Variable %s%s on Frame %d: Weight %f",data_list[j]->GetName(),vars[i].Data(),i+1,weights[j]) << std::endl;}
                                data_list[j]->plotOn(frame,XErrorSize(0),DataError(RooAbsData::None),MarkerStyle(7),
                                                        MarkerSize(1),MarkerColor(colors[j]),Rescale(weights[j]),Name(data_list[j]->GetName()));
			TGraph* graph = (TGraph*)frame->getObject(frame->numItems()-1);
			legend->AddEntry(graph,data_list[j]->GetTitle(),"P");
                        }
                        frame->SetTitle(Form("A Rooplot of %s",vars[i].Data()));
			frame->Draw();
			legend->Draw();
                }
                canvas->SaveAs(output_name);
        }
#endif
