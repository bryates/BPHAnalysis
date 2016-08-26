#ifndef BPHMuonPtSelect_H
#define BPHMuonPtSelect_H
/** \class BPHMuonPtSelect
 *
 *  Description: 
 *     Class for muon selection by Pt
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
#include "BPHAnalysis/SpecificDecay/interface/BPHParticlePtSelect.h"

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

class BPHMuonPtSelect: public BPHParticlePtSelect {

 public:

  /** Constructor
   */
  BPHMuonPtSelect( double pt ): BPHParticlePtSelect( pt ) {}

  /** Destructor
   */
  virtual ~BPHMuonPtSelect() {}

  /** Operations
   */
  /// select muon
  virtual bool accept( const reco::Candidate& cand ) const {
    if ( reinterpret_cast<const pat::Muon*>( &cand ) == 0 ) return false;
    return BPHParticlePtSelect::accept( cand );
  }

 private:

  // private copy and assigment constructors
  BPHMuonPtSelect           ( const BPHMuonPtSelect& x );
  BPHMuonPtSelect& operator=( const BPHMuonPtSelect& x );

};


#endif // BPHMuonPtSelect_H

