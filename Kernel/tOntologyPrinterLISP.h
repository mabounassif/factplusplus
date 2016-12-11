/* This file is part of the FaCT++ DL reasoner
Copyright (C) 2009-2015 Dmitry Tsarkov and The University of Manchester
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

#ifndef TONTOLOGYPRINTERLISP_H
#define TONTOLOGYPRINTERLISP_H

#include "tExpressionPrinterLISP.h"
#include "tDLAxiom.h"
#include "tOntology.h"

class TLISPOntologyPrinter: public DLAxiomVisitor
{
protected:	// members
		/// main stream
	std::ostream& o;
		/// printer for the expressions
	TLISPExpressionPrinter LEP;
		/// if true, print declarations
	bool printDeclarations;
		/// if true, print logical axioms
	bool printAxioms;

protected:	// methods
		/// helper to print several expressions in a row
	template<class Expression>
	TLISPOntologyPrinter& operator << ( const TDLNAryExpression<Expression>& c )
	{
		if (printAxioms)
			for ( const auto& expr: c )
				expr->accept(LEP);
		return *this;
	}
		/// helper to print a string
	TLISPOntologyPrinter& operator << ( const char* str )
	{
		if (printAxioms)
			o << str;
		return *this;
	}
		/// helper to print an expression
	TLISPOntologyPrinter& operator << ( const TDLExpression* expr )
	{
		if (printAxioms)
			expr->accept(LEP);
		return *this;
	}

public:		// visitor interface
	virtual void visit ( const TDLAxiomDeclaration& axiom ) override
	{
		if (!printDeclarations)
			return;
		const TDLExpression* decl = axiom.getDeclaration();
		// print only declarations for non-constant entities, ignore datatypes
		if (const TDLConceptName* concept = dynamic_cast<const TDLConceptName*>(decl))
			o << "(defprimconcept " << concept->getName() << ")\n";
		else if (const TDLIndividualName* individual = dynamic_cast<const TDLIndividualName*>(decl))
			o << "(defindividual " << individual->getName() << ")\n";
		else if (const TDLObjectRoleName* objectRole = dynamic_cast<const TDLObjectRoleName*>(decl))
			o << "(defprimrole " << objectRole->getName() << ")\n";
		else if (const TDLDataRoleName* dataRole = dynamic_cast<const TDLDataRoleName*>(decl))
			o << "(defdatarole " << dataRole ->getName() << ")\n";
	}

	virtual void visit ( const TDLAxiomEquivalentConcepts& axiom ) override { *this << "(equal_c" << axiom << ")\n"; }
	virtual void visit ( const TDLAxiomDisjointConcepts& axiom ) override { *this  << "(disjoint_c" << axiom << ")\n"; }
	virtual void visit ( const TDLAxiomDisjointUnion& axiom ) override
		{ *this << "(disjoint_c" << axiom << ")\n(equal_c" << axiom.getC() << " (or" << axiom << "))\n"; }
	virtual void visit ( const TDLAxiomEquivalentORoles& axiom ) override { *this << "(equal_r" << axiom << ")\n"; }
	virtual void visit ( const TDLAxiomEquivalentDRoles& axiom ) override { *this << "(equal_r" << axiom << ")\n"; }
	virtual void visit ( const TDLAxiomDisjointORoles& axiom ) override { *this << "(disjoint_r" << axiom << ")\n"; }
	virtual void visit ( const TDLAxiomDisjointDRoles& axiom ) override { *this << "(disjoint_r" << axiom << ")\n"; }
	virtual void visit ( const TDLAxiomSameIndividuals& axiom ) override { *this << "(same" << axiom << ")\n"; }
	virtual void visit ( const TDLAxiomDifferentIndividuals& axiom ) override { *this << "(different" << axiom << ")\n"; }
	virtual void visit ( const TDLAxiomFairnessConstraint& axiom ) override { *this << "(fairness" << axiom << ")\n"; }

	virtual void visit ( const TDLAxiomRoleInverse& axiom ) override { *this << "(equal_r" << axiom.getRole() << " (inv" << axiom.getInvRole() << "))\n"; }
	virtual void visit ( const TDLAxiomORoleSubsumption& axiom ) override { *this << "(implies_r" << axiom.getSubRole() << axiom.getRole() << ")\n"; }
	virtual void visit ( const TDLAxiomDRoleSubsumption& axiom ) override { *this << "(implies_r" << axiom.getSubRole() << axiom.getRole() << ")\n"; }
	virtual void visit ( const TDLAxiomORoleDomain& axiom ) override { *this << "(domain" << axiom.getRole() << axiom.getDomain() << ")\n"; }
	virtual void visit ( const TDLAxiomDRoleDomain& axiom ) override { *this << "(domain" << axiom.getRole() << axiom.getDomain() << ")\n"; }
	virtual void visit ( const TDLAxiomORoleRange& axiom ) override { *this << "(range" << axiom.getRole() << axiom.getRange() << ")\n"; }
	virtual void visit ( const TDLAxiomDRoleRange& axiom ) override { *this << "(range" << axiom.getRole() << axiom.getRange() << ")\n"; }
	virtual void visit ( const TDLAxiomRoleTransitive& axiom ) override { *this << "(transitive" << axiom.getRole() << ")\n"; }
	virtual void visit ( const TDLAxiomRoleReflexive& axiom ) override { *this << "(reflexive" << axiom.getRole() << ")\n"; }
	virtual void visit ( const TDLAxiomRoleIrreflexive& axiom ) override { *this << "(irreflexive" << axiom.getRole() << ")\n"; }
	virtual void visit ( const TDLAxiomRoleSymmetric& axiom ) override { *this << "(symmetric" << axiom.getRole() << ")\n"; }
	virtual void visit ( const TDLAxiomRoleAsymmetric& axiom ) override { *this << "(asymmetric" << axiom.getRole() << ")\n"; }
	virtual void visit ( const TDLAxiomORoleFunctional& axiom ) override { *this << "(functional" << axiom.getRole() << ")\n"; }
	virtual void visit ( const TDLAxiomDRoleFunctional& axiom ) override { *this << "(functional" << axiom.getRole() << ")\n"; }
	virtual void visit ( const TDLAxiomRoleInverseFunctional& axiom ) override { *this << "(functional (inv" << axiom.getRole() << "))\n"; }

	virtual void visit ( const TDLAxiomConceptInclusion& axiom ) override { *this << "(implies_c" << axiom.getSubC() << axiom.getSupC() << ")\n"; }
	virtual void visit ( const TDLAxiomInstanceOf& axiom ) override { *this << "(instance" << axiom.getIndividual()  << axiom.getC() << ")\n"; }
	virtual void visit ( const TDLAxiomRelatedTo& axiom ) override
		{ *this << "(related" << axiom.getIndividual() << axiom.getRelation() << axiom.getRelatedIndividual() << ")\n"; }
	virtual void visit ( const TDLAxiomRelatedToNot& axiom ) override
		{ *this<< "(instance" << axiom.getIndividual() << " (all" << axiom.getRelation() << "(not" << axiom.getRelatedIndividual() << ")))\n"; }
	virtual void visit ( const TDLAxiomValueOf& axiom ) override
		{ *this << "(instance" << axiom.getIndividual() << " (some" << axiom.getAttribute() << axiom.getValue() << "))\n"; }
	virtual void visit ( const TDLAxiomValueOfNot& axiom ) override
		{ *this << "(instance" << axiom.getIndividual() << " (all" << axiom.getAttribute() << "(not " << axiom.getValue() << ")))\n"; }

public:		// interface
		/// init c'tor
	TLISPOntologyPrinter ( std::ostream& o_ )
		: o(o_)
		, LEP(o_)
		, printDeclarations(true)
		, printAxioms(true)
		{}
	virtual ~TLISPOntologyPrinter ( void ) {}

		/// instruct printer whether to print/ignore declarations and axioms
	void setPrintFlags(bool declarations, bool axioms)
	{
		printDeclarations = declarations;
		printAxioms = axioms;
	}
}; // TLISPOntologyPrinter

#endif
