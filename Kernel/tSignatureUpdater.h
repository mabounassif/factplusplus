/* This file is part of the FaCT++ DL reasoner
Copyright (C) 2011-2015 Dmitry Tsarkov and The University of Manchester
Copyright (C) 2015-2017 Dmitry Tsarkov

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

#ifndef TSIGNATUREUPDATER_H
#define TSIGNATUREUPDATER_H

#include "tDLExpression.h"
#include "tSignature.h"

/// update the signature by adding all signature elements from the expression
class TExpressionSignatureUpdater: public DLExpressionVisitor
{
protected:	// members
		/// Signature to be filled
	TSignature& sig;

protected:	// methods
		/// helper for concept arguments
	void vC ( const TConceptArg& expr ) { expr.getC()->accept(*this); }
		/// helper for individual arguments
	void vI ( const TIndividualArg& expr ) { expr.getI()->accept(*this); }
		/// helper for object role arguments
	void vOR ( const TObjectRoleArg& expr ) { expr.getOR()->accept(*this); }
		/// helper for object role arguments
	void vDR ( const TDataRoleArg& expr ) { expr.getDR()->accept(*this); }
		/// helper for the named entity
	void vE ( const TNamedEntity& e ) { sig.add(e.getEntity()); }
		/// array helper
	template <class Argument>
	void processArray ( const TDLNAryExpression<Argument>& expr )
	{
		for ( typename TDLNAryExpression<Argument>::iterator p = expr.begin(), p_end = expr.end(); p != p_end; ++p )
			(*p)->accept(*this);
	}

public:		// interface
		/// init c'tor
	TExpressionSignatureUpdater ( TSignature& s ) : sig(s) {}
		/// empty d'tor
	virtual ~TExpressionSignatureUpdater ( void ) {}

public:		// visitor interface
	// concept expressions
	virtual void visit ( const TDLConceptTop& ) override {}
	virtual void visit ( const TDLConceptBottom& ) override {}
	virtual void visit ( const TDLConceptName& expr ) override { vE(expr); }
	virtual void visit ( const TDLConceptNot& expr ) override { vC(expr); }
	virtual void visit ( const TDLConceptAnd& expr ) override { processArray(expr); }
	virtual void visit ( const TDLConceptOr& expr ) override { processArray(expr); }
	virtual void visit ( const TDLConceptOneOf& expr ) override { processArray(expr); }
	virtual void visit ( const TDLConceptObjectSelf& expr ) override { vOR(expr); }
	virtual void visit ( const TDLConceptObjectValue& expr ) override { vOR(expr); vI(expr); }
	virtual void visit ( const TDLConceptObjectExists& expr ) override { vOR(expr); vC(expr); }
	virtual void visit ( const TDLConceptObjectForall& expr ) override { vOR(expr); vC(expr); }
	virtual void visit ( const TDLConceptObjectMinCardinality& expr ) override { vOR(expr); vC(expr); }
	virtual void visit ( const TDLConceptObjectMaxCardinality& expr ) override { vOR(expr); vC(expr); }
	virtual void visit ( const TDLConceptObjectExactCardinality& expr ) override { vOR(expr); vC(expr); }
	virtual void visit ( const TDLConceptDataValue& expr ) override { vDR(expr); }
	virtual void visit ( const TDLConceptDataExists& expr ) override { vDR(expr); }
	virtual void visit ( const TDLConceptDataForall& expr ) override { vDR(expr); }
	virtual void visit ( const TDLConceptDataMinCardinality& expr ) override { vDR(expr); }
	virtual void visit ( const TDLConceptDataMaxCardinality& expr ) override { vDR(expr); }
	virtual void visit ( const TDLConceptDataExactCardinality& expr ) override { vDR(expr); }

	// individual expressions
	virtual void visit ( const TDLIndividualName& expr ) override { vE(expr); }

	// object role expressions
	virtual void visit ( const TDLObjectRoleTop& ) override {}
	virtual void visit ( const TDLObjectRoleBottom& ) override {}
	virtual void visit ( const TDLObjectRoleName& expr ) override { vE(expr); }
	virtual void visit ( const TDLObjectRoleInverse& expr ) override { vOR(expr); }
	virtual void visit ( const TDLObjectRoleChain& expr ) override { processArray(expr); }
	virtual void visit ( const TDLObjectRoleProjectionFrom& expr ) override { vOR(expr); vC(expr); }
	virtual void visit ( const TDLObjectRoleProjectionInto& expr ) override { vOR(expr); vC(expr); }

	// data role expressions
	virtual void visit ( const TDLDataRoleTop& ) override {}
	virtual void visit ( const TDLDataRoleBottom& ) override {}
	virtual void visit ( const TDLDataRoleName& expr ) override { vE(expr); }

	// data expressions
	virtual void visit ( const TDLDataTop& ) override {}
	virtual void visit ( const TDLDataBottom& ) override {}
	virtual void visit ( const TDLDataTypeName& ) override {}
	virtual void visit ( const TDLDataTypeRestriction& ) override {}
	virtual void visit ( const TDLDataValue& ) override {}
	virtual void visit ( const TDLDataNot& ) override {}
	virtual void visit ( const TDLDataAnd& ) override {}
	virtual void visit ( const TDLDataOr& ) override {}
	virtual void visit ( const TDLDataOneOf& ) override {}

	// facets
	virtual void visit ( const TDLFacetMinInclusive& ) override {}
	virtual void visit ( const TDLFacetMinExclusive& ) override {}
	virtual void visit ( const TDLFacetMaxInclusive& ) override {}
	virtual void visit ( const TDLFacetMaxExclusive& ) override {}
}; // TExpressionSignatureUpdater

/// update signature by adding the signature of a given axiom to it
class TSignatureUpdater: public DLAxiomVisitor
{
protected:	// members
		/// helper with expressions
	TExpressionSignatureUpdater Updater;

protected:	// methods
		/// helper for the expression processing
	void v ( const TDLExpression* E ) { E->accept(Updater); }
		/// helper for the [begin,end) interval
	template<class Iterator>
	void v ( Iterator begin, Iterator end )
	{
		for ( ; begin != end; ++begin )
			v(*begin);
	}

public:		// visitor interface
	virtual void visit ( const TDLAxiomDeclaration& axiom ) override { v(axiom.getDeclaration()); }

	virtual void visit ( const TDLAxiomEquivalentConcepts& axiom ) override { v ( axiom.begin(), axiom.end() ); }
	virtual void visit ( const TDLAxiomDisjointConcepts& axiom ) override { v ( axiom.begin(), axiom.end() ); }
	virtual void visit ( const TDLAxiomDisjointUnion& axiom ) override { v(axiom.getC()); v ( axiom.begin(), axiom.end() ); }
	virtual void visit ( const TDLAxiomEquivalentORoles& axiom ) override { v ( axiom.begin(), axiom.end() ); }
	virtual void visit ( const TDLAxiomEquivalentDRoles& axiom ) override { v ( axiom.begin(), axiom.end() ); }
	virtual void visit ( const TDLAxiomDisjointORoles& axiom ) override { v ( axiom.begin(), axiom.end() ); }
	virtual void visit ( const TDLAxiomDisjointDRoles& axiom ) override { v ( axiom.begin(), axiom.end() ); }
	virtual void visit ( const TDLAxiomSameIndividuals& axiom ) override { v ( axiom.begin(), axiom.end() ); }
	virtual void visit ( const TDLAxiomDifferentIndividuals& axiom ) override { v ( axiom.begin(), axiom.end() ); }
	virtual void visit ( const TDLAxiomFairnessConstraint& axiom ) override { v ( axiom.begin(), axiom.end() ); }

	virtual void visit ( const TDLAxiomRoleInverse& axiom ) override { v(axiom.getRole()); v(axiom.getInvRole()); }
	virtual void visit ( const TDLAxiomORoleSubsumption& axiom ) override { v(axiom.getRole()); v(axiom.getSubRole()); }
	virtual void visit ( const TDLAxiomDRoleSubsumption& axiom ) override { v(axiom.getRole()); v(axiom.getSubRole()); }
	virtual void visit ( const TDLAxiomORoleDomain& axiom ) override { v(axiom.getRole()); v(axiom.getDomain()); }
	virtual void visit ( const TDLAxiomDRoleDomain& axiom ) override { v(axiom.getRole()); v(axiom.getDomain()); }
	virtual void visit ( const TDLAxiomORoleRange& axiom ) override { v(axiom.getRole()); v(axiom.getRange()); }
	virtual void visit ( const TDLAxiomDRoleRange& axiom ) override { v(axiom.getRole()); v(axiom.getRange()); }
	virtual void visit ( const TDLAxiomRoleTransitive& axiom ) override { v(axiom.getRole()); }
	virtual void visit ( const TDLAxiomRoleReflexive& axiom ) override { v(axiom.getRole()); }
	virtual void visit ( const TDLAxiomRoleIrreflexive& axiom ) override { v(axiom.getRole()); }
	virtual void visit ( const TDLAxiomRoleSymmetric& axiom ) override { v(axiom.getRole()); }
	virtual void visit ( const TDLAxiomRoleAsymmetric& axiom ) override { v(axiom.getRole()); }
	virtual void visit ( const TDLAxiomORoleFunctional& axiom ) override { v(axiom.getRole()); }
	virtual void visit ( const TDLAxiomDRoleFunctional& axiom ) override { v(axiom.getRole()); }
	virtual void visit ( const TDLAxiomRoleInverseFunctional& axiom ) override { v(axiom.getRole()); }

	virtual void visit ( const TDLAxiomConceptInclusion& axiom ) override { v(axiom.getSubC()); v(axiom.getSupC()); }
	virtual void visit ( const TDLAxiomInstanceOf& axiom ) override { v(axiom.getIndividual()); v(axiom.getC()); }
	virtual void visit ( const TDLAxiomRelatedTo& axiom ) override { v(axiom.getIndividual()); v(axiom.getRelation()); v(axiom.getRelatedIndividual()); }
	virtual void visit ( const TDLAxiomRelatedToNot& axiom ) override { v(axiom.getIndividual()); v(axiom.getRelation()); v(axiom.getRelatedIndividual()); }
	virtual void visit ( const TDLAxiomValueOf& axiom ) override { v(axiom.getIndividual()); v(axiom.getAttribute()); }
	virtual void visit ( const TDLAxiomValueOfNot& axiom ) override { v(axiom.getIndividual()); v(axiom.getAttribute()); }

public:		// interface
		/// init c'tor
	TSignatureUpdater ( TSignature& sig ) : Updater(sig) {}
		/// empty d'tor
	virtual ~TSignatureUpdater ( void ) {}
}; // TSignatureUpdater

#endif
