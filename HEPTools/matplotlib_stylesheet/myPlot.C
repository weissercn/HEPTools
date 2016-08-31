// all users - please change the name of this file to myPlot.C
// Commits to lhcbdocs svn of .C files are not allowed

//===================================
void Example1DPlot(Int_t colored = 1, Int_t stacked = 0)
{
  ///////////////////////
  // 1D Histogram Example using LHCb style File
  // Chris Parkes 7/1/2011
  // Niels Tuning 2/2/2012
  ///////////////////////
  
  ///////
  // Call LHCb style file
  ///////
  gROOT->ProcessLine(".x lhcbStyle.C");

  ////////////
  // Make some example histograms to use for plot
  ///////////
  
  // define a function 
  myFunc1 = new TF1("myFunc1","gaus(0)",0,10);
  
  // fill three 1D histograms
  myFunc1->SetParameters(10,4,1);
  h1fa = new TH1F("h1fa","Example Plot A",20,0,10);
  h1fa->FillRandom("myFunc1",1050);

  myFunc1->SetParameters(9,3.9,0.9);
  h1fb = new TH1F("h1fb","Example Plot B",20,0,10);
  h1fb->FillRandom("myFunc1",900);

  myFunc1->SetParameters(2,2,2);
  h1fc = new TH1F("h1fc","Example Plot C",20,0,10);
  h1fc->FillRandom("myFunc1",1000);
   
  myFunc1->SetParameters(3,3,0.5);
  h1fd= new TH1F("h1fd","Example Plot D",20,0,10);
  h1fd->FillRandom("myFunc1",100);
   
  /////////////////
  // The example plot
  /////////////////

  // Root fill colours and hatch styles at 
  // http://root.cern.ch/root/html/TAttFill.html#F1
  if (colored == 0) {    
    // black and white
    h1fb->SetFillColor(kGray+0);
    h1fc->SetFillColor(kGray+1);
    h1fd->SetFillColor(kGray+3);
  } else if (colored == 1) {
    // 'Primary' colors:
    h1fb->SetFillColor(kYellow-7);
    h1fc->SetFillColor(kGreen-7);
    h1fd->SetFillColor(kBlue-7);    
  } else if (colored == 2) {
    // Old LHCb Style:
    h1fb->SetFillColor(1);
    h1fc->SetFillColor(1);
    h1fd->SetFillColor(1);
    h1fb->SetFillStyle(3004);
    h1fc->SetFillStyle(3005);
    h1fd->SetFillStyle(3006);
  }

  // Eample of adding stat box - turned off by default in plots
  // gStyle->SetOptStat("emr");  // show only nent - e , mean - m , rms - r

  // create canvas
  Int_t canvasWidth  = 400;
  Int_t canvasHeight = 300;
  TCanvas *c1 = new TCanvas("c1","Canvas",canvasWidth,canvasHeight);

  // Stacked:
  if (stacked == 1){    
    h1fa->Add(h1fc);
    h1fa->Add(h1fd);
    h1fb->Add(h1fc);
    h1fb->Add(h1fd);
    h1fc->Add(h1fd);
    h1fb->SetMaximum(350.); // set y maximum
  } else {    
    h1fb->SetMaximum(250.); // set y maximum
  }
  
  // Set Axis Titles:
  h1fb->GetXaxis()->SetTitle("#font[12]{m}(#font[12]{D}^{+}#pi^{#font[122]{-}}) [GeV/#font[12]{c}^{2}]");
  h1fb->GetYaxis()->SetTitle("Entries / (0.5 GeV/#font[12]{c}^{2})");

  // Draw plots 
  // options described at http://root.cern.ch/root/html/THistPainter.html#HP01b
  h1fb->DrawCopy("");
  h1fc->DrawCopy("SAME");
  h1fd->DrawCopy("SAME");
  // P0: draw bin also for empty bins.
  // E1: Draw error bars with perpendicular lines at the edges.
  // X0: suppress the error bar along X.
  h1fa->DrawCopy("P0E1same"); 
  h1fa->DrawCopy("P0Esame"); // error bar through marker 
  h1fa->DrawCopy("sameaxis");  // sameaxis: redraw axis hidden by the fill area  

  // Don't hide the components:
  h1fb->SetFillStyle(0);
  h1fc->SetFillStyle(0);
  h1fd->SetFillStyle(0);
  h1fb->DrawCopy("SAME");
  h1fc->DrawCopy("SAME");
  h1fd->DrawCopy("SAME");

  // Put fill style back for the legend:
  h1fb->SetFillStyle(1001);
  h1fc->SetFillStyle(1001);
  h1fd->SetFillStyle(1001);

  // Write 'LHCb' label:
  lhcbName->Draw();

  // Example of adding a legend to plot
  // http://root.cern.ch/root/html528/TLegend.html#TLegend
  legend = new TLegend(0.65,0.65,0.92,0.92);
  legend->SetFillColor(0);   
  legend->SetTextSize(0.055);   
  legend->AddEntry(h1fa,"Data","P"); 
  legend->AddEntry(h1fb,"#font[12]{B^{0}_{s}#rightarrow D_{s}^{#font[122]{-}}K^{+}}","F");
  legend->AddEntry(h1fc,"Background 1","F");
  legend->AddEntry(h1fd,"Background 2","F");
  legend->Draw();
  
  // update canvas
  c1->Update();
  
  // write out .png (for pdflatex) or .eps (for compiled latex) files
  char filename[64];
  sprintf(filename,"Example1DPlot-root-%1d.pdf",colored);
  c1->SaveAs(filename);
}


//=========================
void ExampleMultiplePlots()
{
  ///////
  // Call LHCb style file
  ///////
  gROOT->ProcessLine(".x lhcbStyle.C");

  // Reduce linewidth for multi-figure:
  lhcbStyle->SetLineWidth(1.);


  // define a function 
  myFunc1 = new TF1("myFunc1","gaus(0)",0,10);
  
  // fill three 1D histograms
  myFunc1->SetParameters(10,4,1);
  h1fa = new TH1F("h1fa","Example Plot A",20,0,10);
  h1fa->FillRandom("myFunc1",1100);

  // create canvas
  Int_t canvasWidth  = 600;
  Int_t canvasHeight = 450;

  TCanvas *c2 = new TCanvas("c2","multipads",canvasWidth,canvasHeight);
  Int_t npx   = 3;
  Int_t npy   = 3; 
  Int_t npads = npx*npy;

  // First, make one large pad to allow fpr space for axis titles:
  TPad *pad = new TPad("pad","pad", 0.07, 0.07, 0.95, 0.95);
  // Subdivide the pad, with no space between the pads:
  pad->Divide(npx,npy,0,0);
  pad->Draw();

  // Best is to make titles ourselves:
  TLatex* tyax = new TLatex(0.06, 0.52, "Entries / (0.5 GeV/#font[12]{c}^{2})");
  tyax->SetNDC(kTRUE);    
  tyax->SetTextSize(0.05);      
  tyax->SetTextAngle(90.);
  tyax->Draw();
  TLatex* txax = new TLatex( 0.68, 0.03, "#font[12]{m}(#font[12]{D}^{+}#pi^{#font[122]{-}}) [GeV/#font[12]{c}^{2}]");
  txax->SetNDC(kTRUE);    
  txax->SetTextSize(0.05);      
  txax->Draw();      


  // Prepare the labels (a), (b), etc:
  TCollection* l = new TList();
  l->Add(new TLatex(0.1,0.03,"(a)"));
  l->Add(new TLatex(0.1,0.03,"(b)"));
  l->Add(new TLatex(0.1,0.03,"(c)"));
  l->Add(new TLatex(0.1,0.03,"(d)"));
  l->Add(new TLatex(0.1,0.03,"(e)"));
  l->Add(new TLatex(0.1,0.03,"(f)"));
  l->Add(new TLatex(0.1,0.03,"(g)"));
  l->Add(new TLatex(0.1,0.03,"(h)"));
  l->Add(new TLatex(0.1,0.03,"(i)"));
  TIter myiter(l);

  // Define edges of the histogram:
  Float_t x1=h1fa->GetXaxis()->GetXmin();  
  Float_t x2=h1fa->GetXaxis()->GetXmax();  
  Float_t dx=x2-x1;    
  Float_t y1=h1fa->GetMinimum();    
  Float_t y2=h1fa->GetMaximum();    
  Float_t dy=y2-y1;   

  // Plot the plots:
  for (Int_t ipad = 0; ipad < npads ; ipad++){    
    pad->cd(ipad+1);
    //gPad->SetTickx(0); // omit tick marks on the right
    //gPad->SetTicky(0); // omit tick marks on the top
                Int_t icol = ipad % npx;
                Int_t irow = ipad / npx;

    // We need 'pixel font' to ensure same size of labels/titles in multipad!
    h1fa->SetMaximum(299.);
    h1fa->GetXaxis()->SetLabelFont(133);    
    h1fa->GetXaxis()->SetLabelSize(15);    
    h1fa->GetYaxis()->SetLabelFont(133);    
    h1fa->GetYaxis()->SetLabelSize(15);    
    h1fa->GetYaxis()->SetNdivisions(410); // Reduce the number ot ticks
    h1fa->SetLineWidth(1);  
    h1fa->SetMarkerSize(0.7);  
    h1fa->GetXaxis()->SetTitleSize(0.0); // Don't write automatic axis titles
    h1fa->GetYaxis()->SetTitleSize(0.0); // Don't write automatic axis titles


    // Hack the limits of the axis to avoid 'half-cut-off' labels:
    if (irow == (npx-1)){
      h1fa->SetMinimum(y1);      
    } else {
      h1fa->SetMinimum(y1+1.E-5*dy);      
    }
    if (icol == 0){
      h1fa->GetXaxis()->SetLimits(x1,         x2-1.E-5*dx);
    } else {      
      h1fa->GetXaxis()->SetLimits(x1+1.E-5*dx,x2-1.E-5*dx);
    }

    // Draw your plot:
    h1fa->DrawCopy("P0E1");    

    // Add label (a), (b), etc:
    tekst = (TLatex*)myiter.Next();
    tekst->SetTextFont(133);    
    tekst->SetTextSize(15);    
    tekst->SetX(x1+0.80*dx);
    tekst->SetY(y1+1.10*dy);    
    tekst->Draw();
  }

  c2->SaveAs("ExampleMultipad-root.pdf");
  //c2->SaveAs("ExampleMultipad-root.eps");
  
}
