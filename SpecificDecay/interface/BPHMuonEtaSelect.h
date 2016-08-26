#ifndef BPHMuonEtaSelect_H
#define BPHMuonEtaSelect_H
/** \class BPHMuonEtaSelect
 *
 *  Descrietaion: 
 *     Class for muon selection by eta
 *
 *
 *  $Date: 2016-05-03 14:57:34 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------
#include "BPHAnalysis/SpecificDecay/interface/BPHParticleEtaSelect.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include "DataFormats/PatCandidates/interface/Muon.h"

//---------------
// C++ Headers --
//---------------


//              ---------------------
//              -- Class Interface --
//              ---------------------

class BPHMuonEtaSelect: public BPHParticleEtaSelect {

 public:

  /** Constructor
   */
  BPHMuonEtaSelect( double eta ): BPHParticleEtaSelect( eta ) {}

  /** Destructor
   */
  virtual ~BPHMuonEtaSelect() {}

  /** Operations
   */
  /// select muon
  virtual bool accept( const reco::Candidate& cand ) const {
    if ( reinterpret_cast<const pat::Muon*>( &cand ) == 0 ) return false;
    return BPHParticleEtaSelect::accept( cand );
  }

 private:

  // private copy and assigment constructors
  BPHMuonEtaSelect           ( const BPHMuonEtaSelect& x );
  BPHMuonEtaSelect& operator=( const BPHMuonEtaSelect& x );

};


#endif // BPHMuonEtaSelect_H

