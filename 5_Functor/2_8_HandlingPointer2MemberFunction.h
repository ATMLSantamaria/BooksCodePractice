
#include "2_4_FunctorHandler.h"


template<class ParentFunctor,typename PointerToObj,typename PointerToMemberFn>
class MemberFuncHandler : public FunctorImpl<typename ParentFunctor::ResultType,typename ParentFunctor::ParmList>
{
    public:
        typedef typename ParentFunctor::ResultType ResultType;
        MemberFuncHandler(const PointerToObj &pObj, const PointerToMemberFn & pMemFn ):pObj_(pObj_),pMemFn_(pMemFn)
        {

        }
        
        MemberFuncHandler * Clone() const
        {
            return new MemberFuncHandler(*this);
        } 

        ResultType operator()()
        {
            return ((*pObj_).*pMemFn_)();
        }

        ResultType operator()(typename ParentFunctor::Parm1 p1)
        {
            return ((*pObj_).*pMemFn_)(p1);
        }

        ResultType operator()(typename ParentFunctor::Parm1 p1,typename ParentFunctor::Parm2 p2)
        {
            return ((*pObj_).*pMemFn_)(p1,p2);
        }

    private:
        PointerToObj pObj_;
        PointerToMemberFn pMemFn_; 

};
