/*===========================================================================*
 * This file is part of the BiCePS Linear Integer Solver (BLIS).             *
 *                                                                           *
 * ALPS is distributed under the Eclipse Public License as part of the       *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors:                                                                  *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *                                                                           *
 * Conceptual Design:                                                        *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *          Laszlo Ladanyi, IBM T.J. Watson Research Center                  *
 *          Matthew Saltzman, Clemson University                             *
 *                                                                           * 
 *                                                                           *
 * Copyright (C) 2001-2015, Lehigh University, Yan Xu, and Ted Ralphs.       *
 * All Rights Reserved.                                                      *
 *===========================================================================*/

#ifndef BlisSolution_h_
#define BlisSolution_h_

#include "Alps.h"
#include "BcpsSolution.h"

//#############################################################################
/** This class contains the solutions generated by the LP solver (either
    primal or dual. The class exists primarily to pass solutions to the
    object generator(s). */ 
//#############################################################################

class BlisSolution : public BcpsSolution {

 protected:

 public:
    
    /** Default constructor. */
    BlisSolution() 
	: 
	BcpsSolution()
	{}

    /** Useful constructor. */
    BlisSolution(int s, const double *values, double objValue)
	:
	BcpsSolution(s, values, objValue)
	{}

    /** Destructor. */
    virtual ~BlisSolution() { }

    /** Print out the solution.*/
    /** Print the solution.*/
    virtual void print(std::ostream& os) const {
        double nearInt = 0.0;
	for (int j = 0; j < size_; ++j) {
	    if (values_[j] > 1.0e-15 || values_[j] < -1.0e-15) {
                nearInt = floor(values_[j] + 0.5);
                if (ALPS_FABS(nearInt - values_[j]) < 1.0e-6) {
                    os << "x[" << j << "] = " << nearInt << std::endl;
                }
                else {
                    os << "x[" << j << "] = " << values_[j] << std::endl;
                }   
	    }
	}
    }
    
    /** Check if IP feasible. If yes, return a IP solution; othersize, 
	return NULL. */
    // BlisIpSolution* testIntegrality(const double etol = 1e-5) const; 
    
    using AlpsKnowledge::encode ;
    /** The method that encodes the solution into a encoded object. */
    virtual AlpsEncoded* encode() const {
	AlpsEncoded* encoded = new AlpsEncoded(AlpsKnowledgeTypeSolution);
	encodeBcps(encoded);
	// Nothing to do for Blis part.
	return encoded;
    }
  
    /** The method that decodes the solution from a encoded object. */
    virtual AlpsKnowledge* decode(AlpsEncoded& encoded) const {
	BlisSolution * sol = new BlisSolution();
	sol->decodeBcps(encoded);
	return sol;
    }
    
};

//#############################################################################
//#############################################################################

#endif
