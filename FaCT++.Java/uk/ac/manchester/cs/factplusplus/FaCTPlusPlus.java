package uk.ac.manchester.cs.factplusplus;


/**
 * Author: Matthew Horridge<br>
 * The University Of Manchester<br>
 * Medical Informatics Group<br>
 * Date: 10-Jul-2006<br><br>
 * <p/>
 * matthew.horridge@cs.man.ac.uk<br>
 * www.cs.man.ac.uk/~horridgm<br><br>
 *
 * An interface to the native FaCT++ reasoner.  Use of this
 * class requires the FaCT++ JNI library for the appropriate
 * platform.
 */
public class FaCTPlusPlus {

    static {
        // Load the FaCT++ JNI library
        System.loadLibrary("FaCTPlusPlusJNI");
    }

    /**
     * Set internally on the native side - DO NOT ALTER!
     */
    private long KernelId;

    public FaCTPlusPlus() throws FaCTPlusPlusException {
        try{
            initKernel();
        }
        catch(Exception e){
            throw new FaCTPlusPlusException(e);
        }
    }

    /**
     * Use this method to dispose of native resources.  This method
     * MUST be called when the reasoner is no longer required.  Failure
     * to call dispose, may result in memory leaks!
     */
    public void dispose() throws Exception {
        deleteKernel();
    }

    private native void initKernel() throws Exception;

    private native void deleteKernel() throws FaCTPlusPlusException;

    /**
     * Clears told and any cached information from the kernel.
     * @throws FaCTPlusPlusException
     */
    public native void clearKernel() throws FaCTPlusPlusException;

    /**
     * Causes the whole taxonomy to be computed.
     * @throws FaCTPlusPlusException
     */
    public native void classify() throws FaCTPlusPlusException;

    /**
     * Causes all individual types to be computed
     * @throws FaCTPlusPlusException
     */
    public native void realise() throws FaCTPlusPlusException;


    /**
     * Gets the class corresponding to TOP
     * @throws FaCTPlusPlusException
     */
    public native ClassPointer getThing() throws FaCTPlusPlusException;

    /**
     * Gets the class corresponding to BOTTOM
     * @throws FaCTPlusPlusException
     */
    public native ClassPointer getNothing() throws FaCTPlusPlusException;

    /**
     * Gets a pointer to a named class.
     * @param name The name of the class.
     * @return A <code>ClassPointer</code>
     * @throws FaCTPlusPlusException
     */
    public native ClassPointer getNamedClass(String name) throws FaCTPlusPlusException;

    /**
     * Gets a pointer to an object property.
     * @param name The name of the property.
     * @return A pointer to the object property that has the specified name.
     * @throws FaCTPlusPlusException
     */
    public native ObjectPropertyPointer getObjectProperty(String name) throws FaCTPlusPlusException;

    public native DataPropertyPointer getDataProperty(String name) throws FaCTPlusPlusException;

    public native IndividualPointer getIndividual(String name) throws FaCTPlusPlusException;


    ///////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Datatype stuff


    /**
     * Gets the top data type.
     */
    public native DataTypePointer getDataTop() throws FaCTPlusPlusException;

    /**
     * Gets a pointer to a built in data type
     * @param name The name of the datatype. e.g. string, int, float etc.
     */
    public native DataTypePointer getBuiltInDataType(String name) throws FaCTPlusPlusException;

    /**
     * Assigns a name to a datatype expression
     * @param name The name to assign to the datatype
     * @param datatypeExpression
     */
    public native DataTypeExpressionPointer getDataSubType(String name, DataTypeExpressionPointer datatypeExpression) throws FaCTPlusPlusException;

    /**
     * Gets a data enumeration using previously added arguments
     * (initArgList, addArg, closeArgList)
     */
    public native DataTypeExpressionPointer getDataEnumeration() throws FaCTPlusPlusException;

    public native DataTypeExpressionPointer getRestrictedDataType(DataTypeExpressionPointer d, DataTypeFacet facet) throws FaCTPlusPlusException;

    public native DataTypeFacet getLength(DataValuePointer dv) throws FaCTPlusPlusException;

    public native DataTypeFacet getMinLength(DataValuePointer dv) throws FaCTPlusPlusException;

    public native DataTypeFacet getMaxLength(DataValuePointer dv) throws FaCTPlusPlusException;

    public native DataTypeFacet getPattern(DataValuePointer dv) throws FaCTPlusPlusException;

    public native DataTypeFacet getMinExclusiveFacet(DataValuePointer dv) throws FaCTPlusPlusException;

    public native DataTypeFacet getMaxExclusiveFacet(DataValuePointer dv) throws FaCTPlusPlusException;

    public native DataTypeFacet getMinInclusiveFacet(DataValuePointer dv) throws FaCTPlusPlusException;

    public native DataTypeFacet getMaxInclusiveFacet(DataValuePointer dv) throws FaCTPlusPlusException;

    public native DataTypeFacet getTotalDigitsFacet(DataValuePointer dv) throws FaCTPlusPlusException;

    public native DataTypeFacet getFractionDigitsFacet(DataValuePointer dv) throws FaCTPlusPlusException;




    public native DataTypeExpressionPointer getNot(DataTypeExpressionPointer d) throws FaCTPlusPlusException;

    public native DataValuePointer getDataValue(String literal, DataTypePointer type) throws FaCTPlusPlusException;



    ////////////////////////////////////////////////////////////////////////////////////////////////////



    /**
     * Gets an intersection whose operands are in the last
     * closed arg list.
     */
    public native ClassPointer getConceptAnd() throws FaCTPlusPlusException;

    /**
     * Gets a union whose operands are in the last
     * closed arg list.
     */
    public native ClassPointer getConceptOr() throws FaCTPlusPlusException;

    public native ClassPointer getConceptNot(ClassPointer c) throws FaCTPlusPlusException;

    public native ClassPointer getObjectSome(ObjectPropertyPointer r, ClassPointer c) throws FaCTPlusPlusException;

    public native ClassPointer getObjectAll(ObjectPropertyPointer r, ClassPointer c) throws FaCTPlusPlusException;

    public native ClassPointer getObjectValue(ObjectPropertyPointer r, IndividualPointer i) throws FaCTPlusPlusException;

    public native ClassPointer getDataSome(DataPropertyPointer r, DataTypeExpressionPointer d) throws FaCTPlusPlusException;

    public native ClassPointer getDataAll(DataPropertyPointer r, DataTypeExpressionPointer d) throws FaCTPlusPlusException;

    public native ClassPointer getDataValue(DataPropertyPointer r, DataValuePointer d) throws FaCTPlusPlusException;

    public native ClassPointer getObjectAtLeast(int num, ObjectPropertyPointer r, ClassPointer c) throws FaCTPlusPlusException;

    public native ClassPointer getObjectExact(int num, ObjectPropertyPointer r, ClassPointer c) throws FaCTPlusPlusException;

    public native ClassPointer getObjectAtMost(int num, ObjectPropertyPointer r, ClassPointer c) throws FaCTPlusPlusException;

    public native ClassPointer getDataAtLeast(int num, DataPropertyPointer r, DataTypeExpressionPointer d) throws FaCTPlusPlusException;

    public native ClassPointer getDataExact(int num, DataPropertyPointer r, DataTypeExpressionPointer d) throws FaCTPlusPlusException;

    public native ClassPointer getDataAtMost(int num, DataPropertyPointer r, DataTypeExpressionPointer d) throws FaCTPlusPlusException;

    public native ObjectPropertyPointer getInverseProperty(ObjectPropertyPointer r) throws FaCTPlusPlusException;

    /**
     * Gets a property chain whose properties are in the last
     * closed arg list.
     */
    public native ObjectPropertyPointer getPropertyComposition() throws FaCTPlusPlusException;

    /**
     * Gets an enumeration whose individuals are in the last
     * closed arg list.
     */
    public native ClassPointer getOneOf() throws FaCTPlusPlusException;

    public native ClassPointer getSelf(ObjectPropertyPointer r) throws FaCTPlusPlusException;

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Axioms

    public native AxiomPointer tellClassDeclaration(ClassPointer c) throws FaCTPlusPlusException;

    public native AxiomPointer tellObjectPropertyDeclaration(ObjectPropertyPointer op) throws FaCTPlusPlusException;

    public native AxiomPointer tellDataPropertyDeclaration(DataPropertyPointer dp) throws FaCTPlusPlusException;

    public native AxiomPointer tellIndividualDeclaration(IndividualPointer ip) throws FaCTPlusPlusException;


    public native AxiomPointer tellSubClassOf(ClassPointer c, ClassPointer d) throws FaCTPlusPlusException;

    /**
     * Tells an equivalent classes axiom, whose classes are
     * in the last closed arg list.
     */
    public native AxiomPointer tellEquivalentClass() throws FaCTPlusPlusException;

    /**
     * Tells a disjoint classes axiom, whose classes are
     * in the last closed arg list.
     */
    public native AxiomPointer tellDisjointClasses() throws FaCTPlusPlusException;


    public native AxiomPointer tellSubObjectProperties(ObjectPropertyPointer s, ObjectPropertyPointer r) throws FaCTPlusPlusException;

    /**
     * Tells an equivalent object properties axiom, whose properties are
     * in the last closed arg list.
     */
    public native AxiomPointer tellEquivalentObjectProperties() throws FaCTPlusPlusException;

    public native AxiomPointer tellInverseProperties(ObjectPropertyPointer s, ObjectPropertyPointer r) throws FaCTPlusPlusException;

    public native AxiomPointer tellObjectPropertyRange(ObjectPropertyPointer s, ClassPointer c) throws FaCTPlusPlusException;

    public native AxiomPointer tellDataPropertyRange(DataPropertyPointer s, DataTypeExpressionPointer d) throws FaCTPlusPlusException;

    public native AxiomPointer tellObjectPropertyDomain(ObjectPropertyPointer s, ClassPointer c) throws FaCTPlusPlusException;

    public native AxiomPointer tellDataPropertyDomain(DataPropertyPointer s, ClassPointer c) throws FaCTPlusPlusException;

    /**
     * Tells a disjoint object properties axiom, whose properties are
     * in the last closed arg list.
     */
    public native AxiomPointer tellDisjointObjectProperties() throws FaCTPlusPlusException;

    public native AxiomPointer tellFunctionalObjectProperty(ObjectPropertyPointer s) throws FaCTPlusPlusException;

    public native AxiomPointer tellInverseFunctionalObjectProperty(ObjectPropertyPointer s) throws FaCTPlusPlusException;

    public native AxiomPointer tellSymmetricObjectProperty(ObjectPropertyPointer s) throws FaCTPlusPlusException;

    public native AxiomPointer tellAntiSymmetricObjectProperty(ObjectPropertyPointer s) throws FaCTPlusPlusException;

    public native AxiomPointer tellReflexiveObjectProperty(ObjectPropertyPointer s) throws FaCTPlusPlusException;

    public native AxiomPointer tellIrreflexiveObjectProperty(ObjectPropertyPointer s) throws FaCTPlusPlusException;

    public native AxiomPointer tellTransitiveObjectProperty(ObjectPropertyPointer s) throws FaCTPlusPlusException;



    public native AxiomPointer tellSubDataProperties(DataPropertyPointer s, DataPropertyPointer r) throws FaCTPlusPlusException;

    /**
     * Tells an equivalent data properties axiom, whose properties are
     * in the last closed arg list.
     */
    public native AxiomPointer tellEquivalentDataProperties() throws FaCTPlusPlusException;

    /**
     * Tells a disjoint data properties axiom, whose properties are
     * in the last closed arg list.
     */
    public native AxiomPointer tellDisjointDataProperties() throws FaCTPlusPlusException;

    public native AxiomPointer tellFunctionalDataProperty(DataPropertyPointer s) throws FaCTPlusPlusException;


    public native AxiomPointer tellIndividualType(IndividualPointer i, ClassPointer c) throws FaCTPlusPlusException;

    public native AxiomPointer tellRelatedIndividuals(IndividualPointer i, ObjectPropertyPointer r, IndividualPointer j) throws FaCTPlusPlusException;

    public native AxiomPointer tellNotRelatedIndividuals(IndividualPointer i, ObjectPropertyPointer r, IndividualPointer j) throws FaCTPlusPlusException;

    public native AxiomPointer tellRelatedIndividualValue(IndividualPointer i, DataPropertyPointer r, DataValuePointer dv) throws FaCTPlusPlusException;

    public native AxiomPointer tellNotRelatedIndividualValue(IndividualPointer i, DataPropertyPointer r, DataValuePointer dv) throws FaCTPlusPlusException;

    /**
     * Tells a same individuals axiom, whose individuals are
     * in the last closed arg list.
     */
    public native AxiomPointer tellSameIndividuals() throws FaCTPlusPlusException;

    /**
     * Tells a different individuals axiom, whose individuals are
     * in the last closed arg list.
     */
    public native AxiomPointer tellDifferentIndividuals() throws FaCTPlusPlusException;


    //////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Retract

    public native void retract(AxiomPointer a) throws FaCTPlusPlusException;


    //////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Asks

    public native boolean isKBConsistent() throws FaCTPlusPlusException;

    public native boolean isClassSatisfiable(ClassPointer c) throws FaCTPlusPlusException;

    public native boolean isClassSubsumedBy(ClassPointer c, ClassPointer d) throws FaCTPlusPlusException;

    public native boolean isClassEquivalentTo(ClassPointer c, ClassPointer d) throws FaCTPlusPlusException;

    public native boolean isClassDisjointWith(ClassPointer c, ClassPointer d) throws FaCTPlusPlusException;

    public native ClassPointer [][] askSubClasses(ClassPointer c, boolean direct) throws FaCTPlusPlusException;

    public native ClassPointer [][] askSuperClasses(ClassPointer c, boolean direct) throws FaCTPlusPlusException;

    public native ClassPointer [] askEquivalentClasses(ClassPointer c) throws FaCTPlusPlusException;



    public native ObjectPropertyPointer [][] askSuperObjectProperties(ObjectPropertyPointer r, boolean direct) throws FaCTPlusPlusException;

    public native ObjectPropertyPointer [][] askSubObjectProperties(ObjectPropertyPointer r, boolean direct) throws FaCTPlusPlusException;

    public native ObjectPropertyPointer [] askEquivalentObjectProperties(ObjectPropertyPointer r) throws FaCTPlusPlusException;

    public native ClassPointer [][] askObjectPropertyDomain(ObjectPropertyPointer r) throws FaCTPlusPlusException;

    public native ClassPointer [][] askObjectPropertyRange(ObjectPropertyPointer r) throws FaCTPlusPlusException;

    public native boolean isObjectPropertyFunctional(ObjectPropertyPointer r) throws FaCTPlusPlusException;

    public native boolean isObjectPropertyInverseFunctional(ObjectPropertyPointer r) throws FaCTPlusPlusException;

    public native boolean isObjectPropertySymmetric(ObjectPropertyPointer r) throws FaCTPlusPlusException;

    public native boolean isObjectPropertyAntiSymmetric(ObjectPropertyPointer r) throws FaCTPlusPlusException;

    public native boolean isObjectPropertyTransitive(ObjectPropertyPointer r) throws FaCTPlusPlusException;

    public native boolean isObjectPropertyReflexive(ObjectPropertyPointer r) throws FaCTPlusPlusException;

    public native boolean isObjectPropertyIrreflexive(ObjectPropertyPointer r) throws FaCTPlusPlusException;


    public native DataPropertyPointer [][] askSuperDataProperties(DataPropertyPointer r, boolean direct) throws FaCTPlusPlusException;

    public native DataPropertyPointer [][] askSubDataProperties(DataPropertyPointer r, boolean direct) throws FaCTPlusPlusException;

    public native DataPropertyPointer [] askEquivalentDataProperties(DataPropertyPointer r) throws FaCTPlusPlusException;

    public native ClassPointer [][] askDataPropertyDomain(DataPropertyPointer r) throws FaCTPlusPlusException;

    public native DataTypeExpressionPointer askDataPropertyRange(DataPropertyPointer r) throws FaCTPlusPlusException;

    public native boolean isDataPropertyFunctional(DataPropertyPointer r) throws FaCTPlusPlusException;


    public native ClassPointer [][] askIndividualTypes(IndividualPointer i, boolean direct) throws FaCTPlusPlusException;

    // helper for the askObjectPropertyRelationships()
    public native ObjectPropertyPointer [] askObjectProperties(IndividualPointer i) throws FaCTPlusPlusException;

    public native IndividualPointer [] askRelatedIndividuals(IndividualPointer individualPointer, ObjectPropertyPointer r) throws FaCTPlusPlusException;

    // helper for the askDataPropertyRelationships()
    public native DataPropertyPointer [] askDataProperties(IndividualPointer i) throws FaCTPlusPlusException;

    public native DataValuePointer [] askRelatedValues(IndividualPointer individualPointer, DataPropertyPointer r) throws FaCTPlusPlusException;

    public native boolean hasDataPropertyRelationship(IndividualPointer i, DataPropertyPointer r, DataValuePointer v) throws FaCTPlusPlusException;

    public native boolean hasObjectPropertyRelationship(IndividualPointer i, ObjectPropertyPointer r, IndividualPointer j) throws FaCTPlusPlusException;

    public native boolean isInstanceOf(IndividualPointer i, ClassPointer c) throws FaCTPlusPlusException;

    public native IndividualPointer [] askInstances(ClassPointer c, boolean direct) throws FaCTPlusPlusException;


    /**
     * This method is deprecated and might be removed in the future releases
     */
    public IndividualPointer [] askInstances(ClassPointer c) throws FaCTPlusPlusException {
        return askInstances(c, false);
    }

    public native IndividualPointer [] askSameAs(IndividualPointer i) throws FaCTPlusPlusException;

    public native boolean isSameAs(IndividualPointer i, IndividualPointer j) throws FaCTPlusPlusException;


    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Options




    ///////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Utilitity stuff

    /**
     * Starts an arg list.  Note that only ONE arg list may be
     * created at any given time.  For example, it is illegal
     * to call initArgList for a second time without closing
     * calling closeArgList first.
     * @throws FaCTPlusPlusException
     */
    public native void initArgList() throws FaCTPlusPlusException;

    /**
     * Adds an argument to the currently open arg list.
     * @param p A pointer to the argument to be added.
     * @throws FaCTPlusPlusException
     */
    public native void addArg(Pointer p) throws FaCTPlusPlusException;

    /**
     * Closes the currently open arg list.  It is illegal to
     * close an empty arg list.  It is also illegal to
     * call this method without calling initArgList first.
     * @throws FaCTPlusPlusException
     */
    public native void closeArgList() throws FaCTPlusPlusException;

    public native void setProgressMonitor(FaCTPlusPlusProgressMonitor progressMonitor) throws FaCTPlusPlusException;

    public native void startChanges();

    public native void endChanges();    

}
