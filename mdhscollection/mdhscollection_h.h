

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Nov 22 14:44:23 2018
 */
/* Compiler settings for mdhscollection.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __mdhscollection_h_h__
#define __mdhscollection_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __Imdhscollection_FWD_DEFINED__
#define __Imdhscollection_FWD_DEFINED__
typedef interface Imdhscollection Imdhscollection;
#endif 	/* __Imdhscollection_FWD_DEFINED__ */


#ifndef __mdhscollection_FWD_DEFINED__
#define __mdhscollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class mdhscollection mdhscollection;
#else
typedef struct mdhscollection mdhscollection;
#endif /* __cplusplus */

#endif 	/* __mdhscollection_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __mdhscollection_LIBRARY_DEFINED__
#define __mdhscollection_LIBRARY_DEFINED__

/* library mdhscollection */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_mdhscollection;

#ifndef __Imdhscollection_DISPINTERFACE_DEFINED__
#define __Imdhscollection_DISPINTERFACE_DEFINED__

/* dispinterface Imdhscollection */
/* [uuid] */ 


EXTERN_C const IID DIID_Imdhscollection;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1D56D1A4-23ED-44E7-886A-E79DE4694C3A")
    Imdhscollection : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ImdhscollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            Imdhscollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            Imdhscollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            Imdhscollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            Imdhscollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            Imdhscollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            Imdhscollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            Imdhscollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ImdhscollectionVtbl;

    interface Imdhscollection
    {
        CONST_VTBL struct ImdhscollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Imdhscollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define Imdhscollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define Imdhscollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define Imdhscollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define Imdhscollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define Imdhscollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define Imdhscollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __Imdhscollection_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_mdhscollection;

#ifdef __cplusplus

class DECLSPEC_UUID("C60DBDED-60A8-4453-808E-D4D6B4DB9C5F")
mdhscollection;
#endif
#endif /* __mdhscollection_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


