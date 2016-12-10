/* This file is part of the FaCT++ DL reasoner
Copyright (C) 2003-2015 Dmitry Tsarkov and The University of Manchester
Copyright (C) 2015-2016 Dmitry Tsarkov

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef DUMPLISP_H
#define DUMPLISP_H

#include "dumpInterface.h"
#include "dlTBox.h"	//TConcept/TRole

/// class for dumping ontology to a lisp format
class dumpLisp : public dumpInterface
{
public:		// interface
		/// the only c'tor -- empty
	dumpLisp ( std::ostream& oo ) : dumpInterface(oo) {}
		/// empty d'tor
	virtual ~dumpLisp ( void ) {}

	// global prologue/epilogue
	virtual void prologue ( void ) override {}
	virtual void epilogue ( void ) override {}

	// general concept expression
	virtual void dumpTop ( void ) override { o << "*TOP*"; }
	virtual void dumpBottom ( void ) override { o << "*BOTTOM*"; }
	virtual void dumpNumber ( unsigned int n ) override { o << n << " "; }

	virtual void startOp ( diOp Op ) override;
		/// start operation >=/<= with number
	virtual void startOp ( diOp Op, unsigned int n ) override { startOp(Op); dumpNumber(n); }
	virtual void contOp ( diOp Op ) override
	{
		if ( Op == diAnd || Op == diOr )
			skipIndent();
		else
			o << " ";
	}
	virtual void finishOp ( diOp Op ) override
	{
		if ( Op == diAnd || Op == diOr )
			decIndent();
		o << ")";
	}

	virtual void startAx ( diAx Ax ) override;
	virtual void contAx ( diAx ) override { o << " "; }
	virtual void finishAx ( diAx ) override { o << ")\n"; }

		/// obtain name by the named entry
	virtual void dumpName ( const TNamedEntry* p ) override { o << "|" << p->getName() << "|"; }
		/// dump concept atom (as used in expression)
	virtual void dumpConcept ( const TConcept* p ) override { dumpName(p); }
		/// dump role atom (as used in expression)
	virtual void dumpRole ( const TRole* p ) override
	{
		if ( p->getId() < 0 )	// inverse
		{
			o << "(inv ";
			dumpName(p->inverse());
			o << ")";
		}
		else
			dumpName(p);
	}
}; // dumpLisp

#endif
