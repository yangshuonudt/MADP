/* This file is part of the Multiagent Decision Process (MADP) Toolbox. 
 *
 * The majority of MADP is free software released under GNUP GPL v.3. However,
 * some of the included libraries are released under a different license. For 
 * more information, see the included COPYING file. For other information, 
 * please refer to the included README file.
 *
 * This file has been written and/or modified by the following people:
 *
 * Frans Oliehoek 
 * Matthijs Spaan 
 *
 * For contact information please see the included AUTHORS file.
 */

/* Only include this header file once. */
#ifndef _POLICYPOOLPARTIALJPOLVALPAIR_H_
#define _POLICYPOOLPARTIALJPOLVALPAIR_H_ 1

/* the include directives */
#include <iostream>
#include <queue>
#include "Globals.h"
#include "PartialJPDPValuePair.h"
#include "PartialPolicyPoolInterface.h"
#include "boost/shared_ptr.hpp"

class PolicyPoolPartialJPolValPair;
typedef boost::shared_ptr<PolicyPoolPartialJPolValPair> PolicyPoolPartialJPolValPair_sharedPtr;


/**\brief PolicyPoolJPolValPair is a policy pool with partial joint
 * policy - value pairs. */
class PolicyPoolPartialJPolValPair : public PartialPolicyPoolInterface 
{
    private:   
        ///The pointer to the PartialJPDPValuePair queue
        std::priority_queue<PartialJPDPValuePair_sharedPtr> * _m_jpvpQueue_p;
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        PolicyPoolPartialJPolValPair();
        /// Copy constructor.
        //PolicyPoolPartialJPolValPair(const PolicyPoolPartialJPolValPair& a);
        /// Destructor.
        ~PolicyPoolPartialJPolValPair();
        /// Copy assignment operator
        PolicyPoolPartialJPolValPair& operator= (const PolicyPoolPartialJPolValPair& o);
        PartialPolicyPoolInterface& operator= (const PartialPolicyPoolInterface& o);

        //operators:

        //data manipulation (set) functions:
        /**\brief  initializes the policy pool with the empty joint policy
         * and a heuristic value set to infinuty (i.e., DBL_MAX)
         *
         * A pointer to a Interface_ProblemToPolicyDiscretePure is needed to create the
         * joint policy.
         */
        void Init(const Interface_ProblemToPolicyDiscretePure* pu);
        
        /**\brief The 'Select' operator from #refGMAA.
         *
         * This returns a reference to the next PolicyPoolItem (a wrapper for a
         * partial joint policy, together with some properties).
         *
         * The returned PolicyPoolItem is not removed from the PolicyPool.
         */
        PartialPolicyPoolItemInterface_sharedPtr Select() const;   
        /**\brief Removes the item returned by 'Select'.
         *
         * This removes the next PolicyPoolItem (a wrapper for a
         * partial joint policy, together with some properties), as would
         * be returned by 'Select'.
         *
         * If ppiToBeRemoved is specified, it actually checks that the
         * desired PPI is removed.
         */
        void Pop(PartialPolicyPoolItemInterface_sharedPtr ppiToBeRemoved = 
                 PartialPolicyPoolItemInterface_sharedPtr());
        /**\brief returns the contained item with the highest value.
         *
         * This function returns a pointer to the PartialPolicyPoolItemInterface
         * contained in this Policy pool with the highest (heuristic) value.
         *
         * Heuristic is between brackets, because this function is typically
         * used when we found lower bounds (i.e. full policies) and then select
         * the maximum lowerbound.
         *
         * Because this class always 'select's the best ranked policy, this
         * function does the same as 'Select()'.
         */
        PartialPolicyPoolItemInterface_sharedPtr GetBestRanked() const
        {return(Select());};
        /**\brief remove the GetBestRanked() item
         *
         * Removes the PartialPolicyPoolItemInterface contained
         * in this Policy pool with the highest (heuristic) value.
         * (as is returned by GetBestRanked() )
         *
         * Because this class always 'select's the best ranked policy, this
         * function does the same as 'Pop()'.
         */
        void PopBestRanked()
        {Pop();};
        /**\brief Add a PolicyPoolItem to the Pool.
         *
         * ...
         */
        void Insert(PartialPolicyPoolItemInterface_sharedPtr  ppi); 
        
        /**\brief add all elements of pp to 'this'.
         *
         * Note, that the pool pp is emptied in this process.
         */
        void Union(PartialPolicyPoolInterface_sharedPtr  pp);
        void Prune(double v);       
        //get (data) functions:
        
        /**\brief return the number of items in the policy pool
         *
         * ...
         */
        size_t Size() const
        {
            return(_m_jpvpQueue_p->size());
        }

        std::string SoftPrint() const;

};


#endif /* !_POLICYPOOLPARTIALJPOLVALPAIR_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
