#include "llvm/ADT/SCCIterator.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/CFG.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace{    
    struct callinfo : public ModulePass
    {
	static char ID;
	callinfo() : ModulePass(ID) {}
	
	bool runOnModule(Module &M);

	void print(raw_ostream &o, const Module * = 0) const {}

	virtual void getAnalysisUsage(AnalysisUsage &AU) const
	{
	    AU.setPreservesAll();
	    AU.addRequired<CallGraphWrapperPass>();
	}
    };
}


bool callinfo::runOnModule(Module &M)
{
    //get cg of special module	
    CallGraph &CG = getAnalysis<CallGraphWrapperPass>().getCallGraph();
	
	//unsigned callNum = 0;
	//errs() << "CallGraph Information(include callsite and so on):";
	//getAnalysis<CallGraphWrapperPass>().print( errs(), &M);
    

    //loop module to get cfg information of every function  
    //use callsite info to get every function's next succ and then add the function to
    //rule as main,then other functions will be added to the main function(just for graph more easy)
    //
/*    for ( scc_iterator<CallGraph*> SCCI = scc_begin(&CG), SE = scc_end(&CG); SCCI != SE ; SCCI++)
    {
	const std::vector<CallGraph*> &nextSCC = *SCCI;
	for( std::vector<CallGraphNode*>::const_iterator II = nextSCC.begin(), EE = nextSCC.end(); II != EE; II++)
	{
	    if( (*II)->getFunction())
	    {
		mainFunName.push_back((*II)->getFunction()->getName());
	    }
	}
    }
*/

    //get main's next funtion and store it in vector
    std::vector<std::string> mainFuncName;
    if ( CG->Root->getFunction() )
    {
	 if( CG->Root->getFunction()->getName() == "main" )
	 {
		for ( const_iterator<CallGraph*> I = CG.begin(), E = CG.end() ; I != E; I++ )
		{
		    if ( I->first->getName() ==  "main")
		    {
			for ( const_iterator<CallGraphNode*> II = I->second.begin(), EE = I->second.end() ; II != EE ;  II++ )
			{
				if ( Function * FI = II->second->getFunction() )
				    mainFuncName.push_back(FI->getName);
			}
		    }
		}
	 }
	 errs() << "main is not the root ,sorry ,cannot analysis!" << "\n";
    }
    else
    {
	errs() << "there  is no  root!!!"  << "\n";
	return false;
    }



    for( Module::iterator I = M.begin(), E = M.end(); I != E; I++ )
    {
	if ( I->getName() == "main" )
	{
	    //add every function into main function
	    for ( Module::iterator II =  M.begin(), EE = M.end(); II != EE; II++ )
	    {
		//check vectot
		for ( std::vector<std::string > V = mainFuncName.begin(), Z = mainFuncName.end(); V != Z; V++)
		{
		    if ( II->getName() == (*V) )
		    {
			// add to function main
			// analysis function main(I) to get every basic block ,if the block has called the function then add succ_iterator(bb)
			
			// get entry block of function II
			const BasicBlock *B = II->getEntryBlock();


			for ( BasicBlock::iterator BB = I.begin(), BE = I.end(); BB != BE; BB++)
			{
				// at last we need it here:succ_iterator(BB) = B;
			    if (  IN = BB.begin(), IE = BB.end(); IN != IE ; IN++ )
			    {
				if( Instruction::iterator IB = IN.begin(), ID = IN.end() ; IB != IN ; IB++ )	
				    
			    }
			}

		    }
		}
	    }
	}
    }
    
	
	return false;

		
}


char callinfo::ID=0;
static RegisterPass<callinfo>X ("mycfg" , "combile callgraph && cfg");

