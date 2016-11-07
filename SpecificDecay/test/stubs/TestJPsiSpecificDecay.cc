#include "BPHAnalysis/SpecificDecay/test/stubs/TestJPsiSpecificDecay.h"

#include "FWCore/Framework/interface/MakerMacros.h"

#include "BPHAnalysis/RecoDecay/interface/BPHRecoBuilder.h"
#include "BPHAnalysis/RecoDecay/interface/BPHRecoSelect.h"
#include "BPHAnalysis/RecoDecay/interface/BPHRecoCandidate.h"
#include "BPHAnalysis/RecoDecay/interface/BPHPlusMinusCandidate.h"
#include "BPHAnalysis/RecoDecay/interface/BPHMomentumSelect.h"
#include "BPHAnalysis/RecoDecay/interface/BPHVertexSelect.h"
#include "BPHAnalysis/RecoDecay/interface/BPHTrackReference.h"

#include "BPHAnalysis/SpecificDecay/interface/BPHMuonPtSelect.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHMuonEtaSelect.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHParticlePtSelect.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHParticleNeutralVeto.h"
#include "BPHAnalysis/RecoDecay/interface/BPHMultiSelect.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHMassSelect.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHChi2Select.h"

#include "BPHAnalysis/SpecificDecay/interface/BPHOniaToMuMuBuilder.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHKx0ToKPiBuilder.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHPhiToKKBuilder.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHBuToJPsiKBuilder.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHBsToJPsiPhiBuilder.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHBdToJPsiKxBuilder.h"
#include "BPHAnalysis/SpecificDecay/interface/BPHParticleMasses.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/TrackReco/interface/Track.h"

#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"

#include <TH1.h>
#include <TFile.h>

#include <set>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#define SET_LABEL(NAME,PSET) ( NAME = PSET.getParameter<string>( #NAME ) )
// SET_LABEL(xyz,ps);
// is equivalent to
// xyz = ps.getParameter<string>( "xyx" )

TestJPsiSpecificDecay::TestJPsiSpecificDecay( const edm::ParameterSet& ps ) {

  SET_LABEL( pcCandsLabel, ps );
  SET_LABEL( patMuonLabel, ps );

  //consume< vector<pat::PackedCandidateCollection> >( pcCandsToken, pcCandsLabel );
  consume< vector<BPHTrackReference::candidate> >( pcCandsToken, pcCandsLabel );
  consume< pat::MuonCollection>( patMuonToken, patMuonLabel );

  SET_LABEL( outDump, ps );
  if ( outDump == "" ) fPtr = &cout;
  else                 fPtr = new ofstream( outDump.c_str() );

}

TestJPsiSpecificDecay::~TestJPsiSpecificDecay() {
}

void TestJPsiSpecificDecay::fillDescriptions(
                           edm::ConfigurationDescriptions& descriptions ) {
   edm::ParameterSetDescription desc;
   desc.add<string>( "patMuonLabel", "" );
   desc.add<string>( "pcCandsLabel", "" );
   desc.add<string>( "outDump", "dump.txt" );
   descriptions.add( "testJPsiSpecificDecay", desc );
   return;
}

void TestJPsiSpecificDecay::beginJob() {
  *fPtr << "TestBPHSpecificDecay::beginJob" << endl;
  return;
}

void TestJPsiSpecificDecay::analyze( const edm::Event& ev, const edm::EventSetup& es ) {

  ostream& outF = *fPtr;
  outF << "--------- event "
       << ev.id().run() << " / "
       << ev.id().event() << " ---------" << endl;

  int nrc = 0;

  //PF candidates
  //edm::Handle<pat::PackedCandidateCollection> pcCands;
  edm::Handle< vector<BPHTrackReference::candidate> > pcCands;
  pcCandsToken.get( ev, pcCands );
  nrc = pcCands->size();
  edm::Handle<pat::MuonCollection> patMuon;
  patMuonToken.get( ev, patMuon );

  // get muons from pat::CompositeCandidate objects describing onia;
  // muons from all composite objects are copied to an unique std::vector
  // usePC
  vector<const reco::Candidate*> muDaugs;
  set<const pat::Muon*> muonSet;

  BPHOniaToMuMuBuilder* onia = 0;

  onia = new BPHOniaToMuMuBuilder( es,
                      BPHRecoBuilder::createCollection( pcCands, "cfmig" ),
                      BPHRecoBuilder::createCollection( pcCands, "cfmig" ) );

  vector<BPHPlusMinusConstCandPtr> lFull = onia->build();
  //int iFull;
  //int nFull = lFull.size();

  BPHMuonPtSelect   ptSel1( 3.0 );
  BPHMuonPtSelect   ptSel2( 3.5 );
  BPHMuonPtSelect   ptSel3( 4.5 );
  BPHMuonEtaSelect etaSel1( 1.6 );
  BPHMuonEtaSelect etaSel2( 1.4 );
  BPHMuonEtaSelect etaSel3( 1.2 );

  BPHMultiSelect<BPHRecoSelect> select1( BPHSelectOperation::and_mode );
  select1.include(  ptSel1 );
  select1.include( etaSel1 );
  select1.include( etaSel2, false );
  BPHMultiSelect<BPHRecoSelect> select2( BPHSelectOperation::and_mode );
  select2.include(  ptSel2 );
  select2.include( etaSel2 );
  select2.include( etaSel3, false );
  BPHMultiSelect<BPHRecoSelect> select3( BPHSelectOperation::and_mode );
  select3.include(  ptSel3 );
  select3.include( etaSel3 );
  BPHMultiSelect<BPHRecoSelect> muoSel( BPHSelectOperation::or_mode );
  muoSel.include( select1 );
  muoSel.include( select2 );
  muoSel.include( select3 );

  BPHMassSelect massJPsi(  2.95,  3.25  );

  vector<BPHPlusMinusConstCandPtr> lJPsi = onia->getList(
                                           BPHOniaToMuMuBuilder::Psi1,
                                           &muoSel, &massJPsi );

  int iJPsi;
  int nJPsi = lJPsi.size();
  outF << nJPsi << " JPsi cand found" << endl;
  for ( iJPsi = 0; iJPsi < nJPsi; ++iJPsi ) dumpRecoCand( "JPsi",
                                                          lJPsi[iJPsi].get() );
  if ( !nJPsi ) return;
  if ( !nrc   ) return;

}

void TestJPsiSpecificDecay::endJob() {
  *fPtr << "TestBPHSpecificDecay::endJob" << endl;
  return;
}

void TestJPsiSpecificDecay::dumpRecoCand( const string& name,
                                         const BPHRecoCandidate* cand ) {

  ostream& outF = *fPtr;

  static string cType = " cowboy";
  static string sType = " sailor";
  static string dType = "";
  string* type;
  const BPHPlusMinusCandidate* pmCand =
        dynamic_cast<const BPHPlusMinusCandidate*>( cand );
  if ( pmCand != 0 ) {
    if ( pmCand->isCowboy() ) type = &cType;
    else                      type = &sType;
  }
  else                        type = &dType;

  outF << "****** " << name << "   cand mass: "
       << cand->composite().mass() << " momentum "
       << cand->composite().px() << " "
       << cand->composite().py() << " "
       << cand->composite().pz() << *type << endl;

  bool validFit = cand->isValidFit();
  const RefCountedKinematicTree     kt = cand->kinematicTree();
  const RefCountedKinematicParticle kp = cand->currentParticle();
  if ( validFit ) {
  outF << "****** " << name << " constr mass: "
       << cand->p4().mass() << " momentum "
       << cand->p4().px() << " "
       << cand->p4().py() << " "
       << cand->p4().pz() << endl;
  }

  const reco::Vertex& vx = cand->vertex();
  const reco::Vertex::Point& vp = vx.position();
  double chi2 = vx.chi2();
  int    ndof = lround( vx.ndof() );
  double prob = TMath::Prob( chi2, ndof );
  string tdca = "";
  if ( pmCand != 0 ) {
    stringstream sstr;
    sstr << " - " << pmCand->cAppInRPhi().distance();
    tdca = sstr.str();
  }
  outF << "****** " << name << " vertex: "
       << vx.isFake() << " " << vx.isValid() << " - "
       << chi2 << " " << ndof << " " << prob << " - "
       << vp.X() << " " << vp.Y() << " " << vp.Z() << tdca << endl;

  const vector<string>& dl = cand->daugNames();
  int i;
  int n = dl.size();
  for ( i = 0; i < n; ++i ) {
    const string& name = dl[i];
    const reco::Candidate* dp = cand->getDaug( name );
    GlobalPoint gp( vp.X(), vp.Y(), vp.Z() ); 
    GlobalVector dm( 0.0, 0.0, 0.0 );
    const reco::TransientTrack* tt = cand->getTransientTrack( dp );
    if ( tt != 0 ) {
      TrajectoryStateClosestToPoint tscp =
                                    tt->trajectoryStateClosestToPoint( gp );
      dm = tscp.momentum();
//      TrajectoryStateOnSurface tsos = tt->stateOnSurface( gp );
//      GlobalVector gv = tsos.globalMomentum();
    }
    outF << "daughter " << i
         << " " << name
         << " " <<  ( dp->charge() > 0 ? '+' : '-' )
         << " momentum: "
         << dp->px() << " "
         << dp->py() << " "
         << dp->pz() << " - at vertex: "
         << dm.x() << " "
         << dm.y() << " "
         << dm.z() << endl;
  }
  const vector<string>& dc = cand->compNames();
  int j;
  int m = dc.size();
  for ( j = 0; j < m; ++j ) {
    const string& name = dc[j];
    const BPHRecoCandidate* dp = cand->getComp( name ).get();
    outF << "composite daughter " << j
         << " " << name
         << " momentum: "
         << dp->composite().px() << " "
         << dp->composite().py() << " "
         << dp->composite().pz() << endl;
  }

  if ( validFit ) {
  const RefCountedKinematicVertex kv = cand->currentDecayVertex();
  GlobalPoint gp = kv->position(); 
  outF << "   kin fit vertex: "
       << gp.x() << " "
       << gp.y() << " "
       << gp.z() << endl;
  vector<RefCountedKinematicParticle> dk = kt->finalStateParticles();
  int k;
  int l = dk.size();
  for ( k = 0; k < l; ++k ) {
    const reco::TransientTrack& tt = dk[k]->refittedTransientTrack();
    TrajectoryStateClosestToPoint tscp =
                                  tt.trajectoryStateClosestToPoint( gp );
    GlobalVector dm = tscp.momentum();
//    TrajectoryStateOnSurface tsos = tt.stateOnSurface( gp );
//    GlobalVector dm = tsos.globalMomentum();
    outF << "daughter " << k << " refitted: "
         << dm.x() << " "
         << dm.y() << " "
         << dm.z() << endl;
  }
  }

  return;

}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE( TestJPsiSpecificDecay );
