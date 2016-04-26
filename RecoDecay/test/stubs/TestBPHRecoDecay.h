#ifndef TestBaseNtuple_h
#define TestBaseNtuple_h

#include "BPHAnalysis/RecoDecay/test/stubs/AnalyzerTokenWrapper.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "BPHAnalysis/RecoDecay/interface/BPHTrackReference.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"

#include <string>
#include <iostream>
#include <fstream>

class TH1F;
class BPHRecoCandidate;

class TestBPHRecoDecay: public AnalyzerWrapper {

 public:

  explicit TestBPHRecoDecay( const edm::ParameterSet& ps );
  virtual ~TestBPHRecoDecay();

  virtual void beginJob();
  virtual void analyze( const edm::Event& ev, const edm::EventSetup& es );
  virtual void endJob();

 private:

  std::string patMuonLabel;
  std::string ccCandsLabel;
  std::string pfCandsLabel;
  std::string pcCandsLabel;
  std::string gpCandsLabel;

  // token wrappers to allow running both on "old" and "new" CMSSW versions
  TokenWrapper< pat::MuonCollection                       > patMuonToken;
  TokenWrapper< std::vector<pat::CompositeCandidate>      > ccCandsToken;
  TokenWrapper< std::vector<reco::PFCandidate>            > pfCandsToken;
  TokenWrapper< std::vector<BPHTrackReference::candidate> > pcCandsToken;
  TokenWrapper< std::vector<pat::GenericParticle>         > gpCandsToken;

  bool usePM;
  bool useCC;
  bool usePF;
  bool usePC;
  bool useGP;

  std::string outDump;
  std::string outHist;

  std::ofstream* fPtr;

  std::map<std::string,TH1F*> histoMap;

  static std::string getParameter( const edm::ParameterSet& ps,
                                   const std::string& name );

  void dumpRecoCand( const std::string& name,
                     const BPHRecoCandidate* cand );
  void fillHisto   ( const std::string& name,
                     const BPHRecoCandidate* cand );
  void fillHisto( const std::string& name, float x );

  void createHisto( const std::string& name,
                    int nbin, float hmin, float hmax );

};

#endif
