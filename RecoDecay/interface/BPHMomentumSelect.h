#ifndef BPHMomentumSelect_H
#define BPHMomentumSelect_H
/** \class BPHMomentumSelect
 *
 *  Description: 
 *     Base class for candidate selection at momentum sum level
 *
 *  $Date: 2015-07-06 18:32:01 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------


//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
class BPHDecayMomentum;

//---------------
// C++ Headers --
//---------------


//              ---------------------
//              -- Class Interface --
//              ---------------------

class BPHMomentumSelect {

 public:

  /** Constructor
   */
  BPHMomentumSelect();

  /** Destructor
   */
  virtual ~BPHMomentumSelect();

  /** Operations
   */
  /// accept function
  virtual bool accept( const BPHDecayMomentum& cand ) const = 0;

 private:

  // private copy and assigment constructors
  BPHMomentumSelect           ( const BPHMomentumSelect& x );
  BPHMomentumSelect& operator=( const BPHMomentumSelect& x );

};


#endif // BPHMomentumSelect_H

