#ifndef BPHAnalysis_SpecificDecay_TestJPsiSpecificDecay_h
#define BPHAnalysis_SpecificDecay_TestJPsiSpecificDecay_h

#include "BPHAnalysis/RecoDecay/interface/BPHAnalyzerTokenWrapper.h"

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

class TestJPsiSpecificDecay:
      public BPHAnalyzerWrapper<BPHModuleWrapper::one_analyzer> {

 public:

  explicit TestJPsiSpecificDecay( const edm::ParameterSet& ps );
  virtual ~TestJPsiSpecificDecay();

  static void fillDescriptions( edm::ConfigurationDescriptions& descriptions );

  virtual void beginJob();
  virtual void analyze( const edm::Event& ev, const edm::EventSetup& es );
  virtual void endJob();

 private:

  std::string pcCandsLabel;

  // token wrappers to allow running both on "old" and "new" CMSSW versions
  //BPHTokenWrapper< std::vector<pat::PackedCandidateCollection> > pcCandsToken;
  BPHTokenWrapper< std::vector<BPHTrackReference::candidate> > pcCandsToken;

  std::string outDump;
  std::ostream* fPtr;

  void dumpRecoCand( const std::string& name,
                     const BPHRecoCandidate* cand );

};

#endif
