#ifndef __TIDYPLOT__
#define __TIDYPLOT__

#include "TColor.h"
#include "TCanvas.h"
#include "TAttMarker.h"

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
void PlotWorkspaceVars(RooWorkspace* ws_,std::vector<TString> vars,std::vector<RooDataSet*> data_list,std::vector<Double_t> weights_={0},TString output_name="RooVars.pdf")
        {
                TCanvas * canvas = new TCanvas("canvas","canvas",800,800);

                canvas->DivideSquare(vars.size());

                std::vector<EColor> colors;
		colors = (std::vector<EColor>){kRed,kBlue,kBlack,kGreen,kYellow,kPink,kAzure,kOrange,kTeal,kCyan,kViolet,kSpring,kMagenta};

                std::vector<Double_t> weights = {1};

                for(int k=0;k<weights_.size();++k){weights.push_back(weights_[k]);}

                for(int i=0;i<vars.size(); ++i)
                {
                        canvas->cd(i+1);
                        RooRealVar * x = (RooRealVar*)ws_->var(vars[i]);
                        RooPlot * frame = x->frame();
                        for(int j=0;j<data_list.size();++j)
                        {
                                data_list[j]->plotOn(frame,XErrorSize(0),DataError(RooAbsData::None),MarkerStyle(7),
                                                        MarkerSize(1),MarkerColor(colors[j]),Rescale(weights[j]));
                        }
                        frame->SetTitle(Form("A Rooplot of %s",vars[i].Data()));
			frame->Draw();
                }
                canvas->SaveAs(output_name);
        }
#endif
