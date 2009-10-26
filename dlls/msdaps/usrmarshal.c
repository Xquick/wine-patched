/*
 *    Misc marshaling routinues
 *
 * Copyright 2009 Huw Davies
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */
#include <stdarg.h>
#include <string.h>

#define COBJMACROS
#define NONAMELESSUNION
#define NONAMELESSSTRUCT

#include "windef.h"
#include "winbase.h"
#include "wingdi.h"
#include "winuser.h"
#include "winerror.h"
#include "objbase.h"
#include "oleauto.h"
#include "oledb.h"

#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(oledb);

HRESULT CALLBACK IDBCreateCommand_CreateCommand_Proxy(IDBCreateCommand* This, IUnknown *pUnkOuter,
                                                      REFIID riid, IUnknown **ppCommand)
{
    HRESULT hr;
    IErrorInfo *error;

    TRACE("(%p, %p, %s, %p)\n", This, pUnkOuter, debugstr_guid(riid), ppCommand);
    hr = IDBCreateCommand_RemoteCreateCommand_Proxy(This, pUnkOuter, riid, ppCommand, &error);
    if(error)
    {
        SetErrorInfo(0, error);
        IErrorInfo_Release(error);
    }
    return hr;
}

HRESULT __RPC_STUB IDBCreateCommand_CreateCommand_Stub(IDBCreateCommand* This, IUnknown *pUnkOuter,
                                                       REFIID riid, IUnknown **ppCommand, IErrorInfo **ppErrorInfoRem)
{
    HRESULT hr;

    TRACE("(%p, %p, %s, %p, %p)\n", This, pUnkOuter, debugstr_guid(riid), ppCommand, ppErrorInfoRem);

    *ppErrorInfoRem = NULL;
    hr = IDBCreateCommand_CreateCommand(This, pUnkOuter, riid, ppCommand);
    if(FAILED(hr)) GetErrorInfo(0, ppErrorInfoRem);

    return hr;
}

HRESULT CALLBACK IDBCreateSession_CreateSession_Proxy(IDBCreateSession* This, IUnknown *pUnkOuter,
                                                      REFIID riid, IUnknown **ppDBSession)
{
    HRESULT hr;
    IErrorInfo *error;

    TRACE("(%p, %p, %s, %p)\n", This, pUnkOuter, debugstr_guid(riid), ppDBSession);
    hr = IDBCreateSession_RemoteCreateSession_Proxy(This, pUnkOuter, riid, ppDBSession, &error);
    if(error)
    {
        SetErrorInfo(0, error);
        IErrorInfo_Release(error);
    }
    return hr;
}

HRESULT __RPC_STUB IDBCreateSession_CreateSession_Stub(IDBCreateSession* This, IUnknown *pUnkOuter,
                                                       REFIID riid, IUnknown **ppDBSession, IErrorInfo **ppErrorInfoRem)
{
    HRESULT hr;
    TRACE("(%p, %p, %s, %p, %p)\n", This, pUnkOuter, debugstr_guid(riid),
          ppDBSession, ppErrorInfoRem);

    *ppErrorInfoRem = NULL;
    hr = IDBCreateSession_CreateSession(This, pUnkOuter, riid, ppDBSession);
    if(FAILED(hr)) GetErrorInfo(0, ppErrorInfoRem);

    return hr;
}

HRESULT CALLBACK IDBProperties_GetProperties_Proxy(IDBProperties* This, ULONG cPropertyIDSets, const DBPROPIDSET rgPropertyIDSets[],
                                                   ULONG *pcPropertySets, DBPROPSET **prgPropertySets)
{
    FIXME("(%p, %d, %p, %p, %p): stub\n", This, cPropertyIDSets, rgPropertyIDSets, pcPropertySets,
          prgPropertySets);
    return E_NOTIMPL;
}

HRESULT __RPC_STUB IDBProperties_GetProperties_Stub(IDBProperties* This, ULONG cPropertyIDSets, const DBPROPIDSET *rgPropertyIDSets,
                                                    ULONG *pcPropertySets, DBPROPSET **prgPropertySets, IErrorInfo **ppErrorInfoRem)
{
    FIXME("(%p, %d, %p, %p, %p, %p): stub\n", This, cPropertyIDSets, rgPropertyIDSets, pcPropertySets,
          prgPropertySets, ppErrorInfoRem);
    return E_NOTIMPL;
}

HRESULT CALLBACK IDBProperties_GetPropertyInfo_Proxy(IDBProperties* This, ULONG cPropertyIDSets, const DBPROPIDSET rgPropertyIDSets[],
                                                     ULONG *pcPropertyInfoSets, DBPROPINFOSET **prgPropertyInfoSets,
                                                     OLECHAR **ppDescBuffer)
{
    FIXME("(%p, %d, %p, %p, %p, %p): stub\n", This, cPropertyIDSets, rgPropertyIDSets, pcPropertyInfoSets,
          prgPropertyInfoSets, ppDescBuffer);
    return E_NOTIMPL;
}

HRESULT __RPC_STUB IDBProperties_GetPropertyInfo_Stub(IDBProperties* This, ULONG cPropertyIDSets, const DBPROPIDSET *rgPropertyIDSets,
                                                      ULONG *pcPropertyInfoSets, DBPROPINFOSET **prgPropertyInfoSets,
                                                      ULONG *pcOffsets, DBBYTEOFFSET **prgDescOffsets, ULONG *pcbDescBuffer,
                                                      OLECHAR **ppDescBuffer, IErrorInfo **ppErrorInfoRem)
{
    FIXME("(%p, %d, %p, %p, %p, %p, %p, %p, %p, %p): stub\n", This, cPropertyIDSets, rgPropertyIDSets, pcPropertyInfoSets,
          prgPropertyInfoSets, pcOffsets, prgDescOffsets, pcbDescBuffer, ppDescBuffer, ppErrorInfoRem);
    return E_NOTIMPL;
}

HRESULT CALLBACK IDBProperties_SetProperties_Proxy(IDBProperties* This, ULONG cPropertySets, DBPROPSET rgPropertySets[])
{
    ULONG prop_set, prop, total_props = 0;
    HRESULT hr;
    IErrorInfo *error;
    DBPROPSTATUS *status;

    TRACE("(%p, %d, %p)\n", This, cPropertySets, rgPropertySets);

    for(prop_set = 0; prop_set < cPropertySets; prop_set++)
        total_props += rgPropertySets[prop_set].cProperties;

    if(total_props == 0) return S_OK;

    status = CoTaskMemAlloc(total_props * sizeof(*status));
    if(!status) return E_OUTOFMEMORY;

    hr = IDBProperties_RemoteSetProperties_Proxy(This, cPropertySets, rgPropertySets,
                                                 total_props, status, &error);
    if(error)
    {
        SetErrorInfo(0, error);
        IErrorInfo_Release(error);
    }

    total_props = 0;
    for(prop_set = 0; prop_set < cPropertySets; prop_set++)
        for(prop = 0; prop < rgPropertySets[prop_set].cProperties; prop++)
            rgPropertySets[prop_set].rgProperties[prop].dwStatus = status[total_props++];

    CoTaskMemFree(status);
    return hr;
}

HRESULT __RPC_STUB IDBProperties_SetProperties_Stub(IDBProperties* This, ULONG cPropertySets, DBPROPSET *rgPropertySets,
                                                    ULONG cTotalProps, DBPROPSTATUS *rgPropStatus, IErrorInfo **ppErrorInfoRem)
{
    ULONG prop_set, prop, total_props = 0;
    HRESULT hr;

    TRACE("(%p, %d, %p, %d, %p, %p)\n", This, cPropertySets, rgPropertySets, cTotalProps,
          rgPropStatus, ppErrorInfoRem);

    *ppErrorInfoRem = NULL;
    hr = IDBProperties_SetProperties(This, cPropertySets, rgPropertySets);
    if(FAILED(hr)) GetErrorInfo(0, ppErrorInfoRem);

    for(prop_set = 0; prop_set < cPropertySets; prop_set++)
        for(prop = 0; prop < rgPropertySets[prop_set].cProperties; prop++)
            rgPropStatus[total_props++] = rgPropertySets[prop_set].rgProperties[prop].dwStatus;

    return hr;
}

HRESULT CALLBACK IDBInitialize_Initialize_Proxy(IDBInitialize* This)
{
    HRESULT hr;
    IErrorInfo *error;

    TRACE("(%p)\n", This);
    hr = IDBInitialize_RemoteInitialize_Proxy(This, &error);
    if(error)
    {
        SetErrorInfo(0, error);
        IErrorInfo_Release(error);
    }
    return hr;
}

HRESULT __RPC_STUB IDBInitialize_Initialize_Stub(IDBInitialize* This, IErrorInfo **ppErrorInfoRem)
{
    HRESULT hr;
    TRACE("(%p, %p)\n", This, ppErrorInfoRem);

    *ppErrorInfoRem = NULL;
    hr = IDBInitialize_Initialize(This);
    if(FAILED(hr)) GetErrorInfo(0, ppErrorInfoRem);

    return hr;
}

HRESULT CALLBACK IDBInitialize_Uninitialize_Proxy(IDBInitialize* This)
{
    FIXME("(%p): stub\n", This);
    return E_NOTIMPL;
}

HRESULT __RPC_STUB IDBInitialize_Uninitialize_Stub(IDBInitialize* This, IErrorInfo **ppErrorInfoRem)
{
    FIXME("(%p, %p): stub\n", This, ppErrorInfoRem);
    return E_NOTIMPL;
}

HRESULT CALLBACK IDBDataSourceAdmin_CreateDataSource_Proxy(IDBDataSourceAdmin* This, ULONG cPropertySets,
                                                           DBPROPSET rgPropertySets[], IUnknown *pUnkOuter,
                                                           REFIID riid, IUnknown **ppDBSession)
{
    ULONG prop_set, prop, total_props = 0;
    HRESULT hr;
    IErrorInfo *error;
    DBPROPSTATUS *status;

    TRACE("(%p, %d, %p, %p, %s, %p)\n", This, cPropertySets, rgPropertySets, pUnkOuter,
          debugstr_guid(riid), ppDBSession);

    for(prop_set = 0; prop_set < cPropertySets; prop_set++)
        total_props += rgPropertySets[prop_set].cProperties;

    if(total_props == 0) return S_OK;

    status = CoTaskMemAlloc(total_props * sizeof(*status));
    if(!status) return E_OUTOFMEMORY;

    hr = IDBDataSourceAdmin_RemoteCreateDataSource_Proxy(This, cPropertySets, rgPropertySets, pUnkOuter,
                                                         riid, ppDBSession, total_props, status, &error);
    if(error)
    {
        SetErrorInfo(0, error);
        IErrorInfo_Release(error);
    }

    total_props = 0;
    for(prop_set = 0; prop_set < cPropertySets; prop_set++)
        for(prop = 0; prop < rgPropertySets[prop_set].cProperties; prop++)
            rgPropertySets[prop_set].rgProperties[prop].dwStatus = status[total_props++];

    CoTaskMemFree(status);
    return hr;
}

HRESULT __RPC_STUB IDBDataSourceAdmin_CreateDataSource_Stub(IDBDataSourceAdmin* This, ULONG cPropertySets,
                                                            DBPROPSET *rgPropertySets, IUnknown *pUnkOuter,
                                                            REFIID riid, IUnknown **ppDBSession, ULONG cTotalProps,
                                                            DBPROPSTATUS *rgPropStatus, IErrorInfo **ppErrorInfoRem)
{
    ULONG prop_set, prop, total_props = 0;
    HRESULT hr;

    TRACE("(%p, %d, %p, %p, %s, %p, %d, %p, %p)\n", This, cPropertySets, rgPropertySets, pUnkOuter,
          debugstr_guid(riid), ppDBSession, cTotalProps, rgPropStatus, ppErrorInfoRem);

    *ppErrorInfoRem = NULL;
    hr = IDBDataSourceAdmin_CreateDataSource(This, cPropertySets, rgPropertySets, pUnkOuter, riid, ppDBSession);
    if(FAILED(hr)) GetErrorInfo(0, ppErrorInfoRem);

    for(prop_set = 0; prop_set < cPropertySets; prop_set++)
        for(prop = 0; prop < rgPropertySets[prop_set].cProperties; prop++)
            rgPropStatus[total_props++] = rgPropertySets[prop_set].rgProperties[prop].dwStatus;

    return hr;
}

HRESULT CALLBACK IDBDataSourceAdmin_DestroyDataSource_Proxy(IDBDataSourceAdmin* This)
{
    FIXME("(%p): stub\n", This);
    return E_NOTIMPL;
}

HRESULT __RPC_STUB IDBDataSourceAdmin_DestroyDataSource_Stub(IDBDataSourceAdmin* This, IErrorInfo **ppErrorInfoRem)
{
    FIXME("(%p, %p): stub\n", This, ppErrorInfoRem);
    return E_NOTIMPL;
}

HRESULT CALLBACK IDBDataSourceAdmin_GetCreationProperties_Proxy(IDBDataSourceAdmin* This, ULONG cPropertyIDSets,
                                                                const DBPROPIDSET rgPropertyIDSets[], ULONG *pcPropertyInfoSets,
                                                                DBPROPINFOSET **prgPropertyInfoSets, OLECHAR **ppDescBuffer)
{
    FIXME("(%p, %d, %p, %p, %p, %p): stub\n", This, cPropertyIDSets, rgPropertyIDSets, pcPropertyInfoSets,
          prgPropertyInfoSets, ppDescBuffer);
    return E_NOTIMPL;
}

HRESULT __RPC_STUB IDBDataSourceAdmin_GetCreationProperties_Stub(IDBDataSourceAdmin* This, ULONG cPropertyIDSets,
                                                                 const DBPROPIDSET *rgPropertyIDSets, ULONG *pcPropertyInfoSets,
                                                                 DBPROPINFOSET **prgPropertyInfoSets, DBCOUNTITEM *pcOffsets,
                                                                 DBBYTEOFFSET **prgDescOffsets, ULONG *pcbDescBuffer,
                                                                 OLECHAR **ppDescBuffer, IErrorInfo **ppErrorInfoRem)
{
    FIXME("(%p, %d, %p, %p, %p, %p, %p, %p, %p, %p): stub\n", This, cPropertyIDSets, rgPropertyIDSets, pcPropertyInfoSets,
          prgPropertyInfoSets, pcOffsets, prgDescOffsets, pcbDescBuffer, ppDescBuffer, ppErrorInfoRem);
    return E_NOTIMPL;
}

HRESULT CALLBACK IDBDataSourceAdmin_ModifyDataSource_Proxy(IDBDataSourceAdmin* This, ULONG cPropertySets, DBPROPSET rgPropertySets[])
{
    FIXME("(%p, %d, %p): stub\n", This, cPropertySets, rgPropertySets);
    return E_NOTIMPL;
}

HRESULT __RPC_STUB IDBDataSourceAdmin_ModifyDataSource_Stub(IDBDataSourceAdmin* This, ULONG cPropertySets,
                                                            DBPROPSET *rgPropertySets, IErrorInfo **ppErrorInfoRem)
{
    FIXME("(%p, %d, %p, %p): stub\n", This, cPropertySets, rgPropertySets, ppErrorInfoRem);
    return E_NOTIMPL;
}

HRESULT CALLBACK ISessionProperties_GetProperties_Proxy(ISessionProperties* This, ULONG cPropertyIDSets,
                                                        const DBPROPIDSET rgPropertyIDSets[], ULONG *pcPropertySets,
                                                        DBPROPSET **prgPropertySets)
{
    FIXME("(%p, %d, %p, %p, %p): stub\n", This, cPropertyIDSets, rgPropertyIDSets,
          pcPropertySets, prgPropertySets);
    return E_NOTIMPL;
}

HRESULT __RPC_STUB ISessionProperties_GetProperties_Stub(ISessionProperties* This, ULONG cPropertyIDSets,
                                                         const DBPROPIDSET *rgPropertyIDSets, ULONG *pcPropertySets,
                                                         DBPROPSET **prgPropertySets, IErrorInfo **ppErrorInfoRem)
{
    FIXME("(%p, %d, %p, %p, %p, %p): stub\n", This, cPropertyIDSets, rgPropertyIDSets,
          pcPropertySets, prgPropertySets, ppErrorInfoRem);
    return E_NOTIMPL;
}

HRESULT CALLBACK ISessionProperties_SetProperties_Proxy(ISessionProperties* This, ULONG cPropertySets, DBPROPSET rgPropertySets[])
{
    ULONG prop_set, prop, total_props = 0;
    HRESULT hr;
    IErrorInfo *error;
    DBPROPSTATUS *status;

    TRACE("(%p, %d, %p)\n", This, cPropertySets, rgPropertySets);

    for(prop_set = 0; prop_set < cPropertySets; prop_set++)
        total_props += rgPropertySets[prop_set].cProperties;

    if(total_props == 0) return S_OK;

    status = CoTaskMemAlloc(total_props * sizeof(*status));
    if(!status) return E_OUTOFMEMORY;

    hr = ISessionProperties_RemoteSetProperties_Proxy(This, cPropertySets, rgPropertySets,
                                                      total_props, status, &error);
    if(error)
    {
        SetErrorInfo(0, error);
        IErrorInfo_Release(error);
    }

    total_props = 0;
    for(prop_set = 0; prop_set < cPropertySets; prop_set++)
        for(prop = 0; prop < rgPropertySets[prop_set].cProperties; prop++)
            rgPropertySets[prop_set].rgProperties[prop].dwStatus = status[total_props++];

    CoTaskMemFree(status);
    return hr;
}

HRESULT __RPC_STUB ISessionProperties_SetProperties_Stub(ISessionProperties* This, ULONG cPropertySets, DBPROPSET *rgPropertySets,
                                                         ULONG cTotalProps, DBPROPSTATUS *rgPropStatus, IErrorInfo **ppErrorInfoRem)
{
    ULONG prop_set, prop, total_props = 0;
    HRESULT hr;

    TRACE("(%p, %d, %p, %d, %p, %p)\n", This, cPropertySets, rgPropertySets, cTotalProps,
          rgPropStatus, ppErrorInfoRem);

    *ppErrorInfoRem = NULL;
    hr = ISessionProperties_SetProperties(This, cPropertySets, rgPropertySets);
    if(FAILED(hr)) GetErrorInfo(0, ppErrorInfoRem);

    for(prop_set = 0; prop_set < cPropertySets; prop_set++)
        for(prop = 0; prop < rgPropertySets[prop_set].cProperties; prop++)
            rgPropStatus[total_props++] = rgPropertySets[prop_set].rgProperties[prop].dwStatus;

    return hr;
}

HRESULT CALLBACK IOpenRowset_OpenRowset_Proxy(IOpenRowset* This, IUnknown *pUnkOuter, DBID *pTableID, DBID *pIndexID,
                                              REFIID riid, ULONG cPropertySets, DBPROPSET rgPropertySets[], IUnknown **ppRowset)
{
    FIXME("(%p, %p, %p, %p, %s, %d, %p, %p): stub\n", This, pUnkOuter, pTableID, pIndexID, debugstr_guid(riid),
          cPropertySets, rgPropertySets, ppRowset);
    return E_NOTIMPL;
}

HRESULT __RPC_STUB IOpenRowset_OpenRowset_Stub(IOpenRowset* This, IUnknown *pUnkOuter, DBID *pTableID, DBID *pIndexID,
                                               REFIID riid, ULONG cPropertySets, DBPROPSET *rgPropertySets,
                                               IUnknown **ppRowset, ULONG cTotalProps, DBPROPSTATUS *rgPropStatus,
                                               IErrorInfo **ppErrorInfoRem)
{
    FIXME("(%p, %p, %p, %p, %s, %d, %p, %p, %d, %p, %p): stub\n", This, pUnkOuter, pTableID, pIndexID, debugstr_guid(riid),
          cPropertySets, rgPropertySets, ppRowset, cTotalProps, rgPropStatus, ppErrorInfoRem);
    return E_NOTIMPL;
}

HRESULT CALLBACK IBindResource_Bind_Proxy(IBindResource* This, IUnknown *pUnkOuter, LPCOLESTR pwszURL, DBBINDURLFLAG dwBindURLFlags,
                                          REFGUID rguid, REFIID riid, IAuthenticate *pAuthenticate, DBIMPLICITSESSION *pImplSession,
                                          DBBINDURLSTATUS *pdwBindStatus, IUnknown **ppUnk)
{
    HRESULT hr;

    TRACE("(%p, %p, %s, %08x, %s, %s, %p, %p, %p, %p)\n", This, pUnkOuter, debugstr_w(pwszURL), dwBindURLFlags,
          debugstr_guid(rguid), debugstr_guid(riid), pAuthenticate, pImplSession, pdwBindStatus, ppUnk);

    hr = IBindResource_RemoteBind_Proxy(This, pUnkOuter, pwszURL, dwBindURLFlags, rguid, riid, pAuthenticate,
                                        pImplSession ? pImplSession->pUnkOuter : NULL, pImplSession ? pImplSession->piid : NULL,
                                        pImplSession ? &pImplSession->pSession : NULL, pdwBindStatus, ppUnk);
    return hr;
}

HRESULT __RPC_STUB IBindResource_Bind_Stub(IBindResource* This, IUnknown *pUnkOuter, LPCOLESTR pwszURL, DBBINDURLFLAG dwBindURLFlags,
                                           REFGUID rguid, REFIID riid, IAuthenticate *pAuthenticate, IUnknown *pSessionUnkOuter,
                                           IID *piid, IUnknown **ppSession, DBBINDURLSTATUS *pdwBindStatus, IUnknown **ppUnk)
{
    HRESULT hr;
    DBIMPLICITSESSION impl_session;

    TRACE("(%p, %p, %s, %08x, %s, %s, %p, %p, %p, %p, %p, %p)\n", This, pUnkOuter, debugstr_w(pwszURL), dwBindURLFlags,
          debugstr_guid(rguid), debugstr_guid(riid), pAuthenticate, pSessionUnkOuter, piid, ppSession, pdwBindStatus, ppUnk);

    impl_session.pUnkOuter = pSessionUnkOuter;
    impl_session.piid = piid;
    impl_session.pSession = NULL;

    hr = IBindResource_Bind(This, pUnkOuter, pwszURL, dwBindURLFlags, rguid, riid, pAuthenticate,
                            ppSession ? &impl_session : NULL, pdwBindStatus, ppUnk);

    if(ppSession) *ppSession = impl_session.pSession;
    return hr;
}

HRESULT CALLBACK ICreateRow_CreateRow_Proxy(ICreateRow* This, IUnknown *pUnkOuter, LPCOLESTR pwszURL, DBBINDURLFLAG dwBindURLFlags,
                                            REFGUID rguid, REFIID riid, IAuthenticate *pAuthenticate, DBIMPLICITSESSION *pImplSession,
                                            DBBINDURLSTATUS *pdwBindStatus, LPOLESTR *ppwszNewURL, IUnknown **ppUnk)
{
    HRESULT hr;

    TRACE("(%p, %p, %s, %08x, %s, %s, %p, %p, %p, %p, %p)\n", This, pUnkOuter, debugstr_w(pwszURL), dwBindURLFlags,
          debugstr_guid(rguid), debugstr_guid(riid), pAuthenticate, pImplSession, pdwBindStatus, ppwszNewURL, ppUnk);

    hr = ICreateRow_RemoteCreateRow_Proxy(This, pUnkOuter, pwszURL, dwBindURLFlags, rguid, riid, pAuthenticate,
                                          pImplSession ? pImplSession->pUnkOuter : NULL, pImplSession ? pImplSession->piid : NULL,
                                          pImplSession ? &pImplSession->pSession : NULL, pdwBindStatus, ppwszNewURL, ppUnk);
    return hr;
}

HRESULT __RPC_STUB ICreateRow_CreateRow_Stub(ICreateRow* This, IUnknown *pUnkOuter, LPCOLESTR pwszURL, DBBINDURLFLAG dwBindURLFlags,
                                             REFGUID rguid, REFIID riid, IAuthenticate *pAuthenticate, IUnknown *pSessionUnkOuter,
                                             IID *piid, IUnknown **ppSession, DBBINDURLSTATUS *pdwBindStatus,
                                             LPOLESTR *ppwszNewURL, IUnknown **ppUnk)
{
    HRESULT hr;
    DBIMPLICITSESSION impl_session;

    TRACE("(%p, %p, %s, %08x, %s, %s, %p, %p, %p, %p, %p, %p, %p)\n", This, pUnkOuter, debugstr_w(pwszURL), dwBindURLFlags,
          debugstr_guid(rguid), debugstr_guid(riid), pAuthenticate, pSessionUnkOuter, piid, ppSession, pdwBindStatus, ppwszNewURL,
          ppUnk);

    impl_session.pUnkOuter = pSessionUnkOuter;
    impl_session.piid = piid;
    impl_session.pSession = NULL;

    hr = ICreateRow_CreateRow(This, pUnkOuter, pwszURL, dwBindURLFlags, rguid, riid, pAuthenticate,
                              ppSession ? &impl_session : NULL, pdwBindStatus, ppwszNewURL, ppUnk);

    if(ppSession) *ppSession = impl_session.pSession;
    return hr;
}

HRESULT CALLBACK IAccessor_AddRefAccessor_Proxy(IAccessor* This, HACCESSOR hAccessor, DBREFCOUNT *pcRefCount)
{
    FIXME("(%p)->(%08lx, %p): stub\n", This, hAccessor, pcRefCount);
    return E_NOTIMPL;
}

HRESULT __RPC_STUB IAccessor_AddRefAccessor_Stub(IAccessor* This, HACCESSOR hAccessor, DBREFCOUNT *pcRefCount,
                                                 IErrorInfo **ppErrorInfoRem)
{
    FIXME("(%p)->(%08lx, %p, %p): stub\n", This, hAccessor, pcRefCount, ppErrorInfoRem);
    return E_NOTIMPL;
}

HRESULT CALLBACK IAccessor_CreateAccessor_Proxy(IAccessor* This, DBACCESSORFLAGS dwAccessorFlags, DBCOUNTITEM cBindings,
                                                const DBBINDING rgBindings[], DBLENGTH cbRowSize, HACCESSOR *phAccessor,
                                                DBBINDSTATUS rgStatus[])
{
    HRESULT hr;
    IErrorInfo *error;
    DBCOUNTITEM i;

    TRACE("(%p)->(%08x, %d, %p, %d, %p, %p)\n", This, dwAccessorFlags, cBindings, rgBindings,
          cbRowSize, phAccessor, rgStatus);

    for(i = 0; i < cBindings; i++)
    {
        TRACE("%d: ord %d val off %d len off %d stat off %d part %04x mem_owner %d max_len %d type %04x\n",
              i, rgBindings[i].iOrdinal, rgBindings[i].obValue, rgBindings[i].obLength, rgBindings[i].obStatus,
              rgBindings[i].dwPart, rgBindings[i].dwMemOwner, rgBindings[i].cbMaxLen, rgBindings[i].wType);
    }

    hr = IAccessor_RemoteCreateAccessor_Proxy(This, dwAccessorFlags, cBindings, (DBBINDING *)rgBindings,
                                              cbRowSize, phAccessor, rgStatus, &error);
    if(error)
    {
        SetErrorInfo(0, error);
        IErrorInfo_Release(error);
    }

    TRACE("returning %08x accessor %lx\n", hr, *phAccessor);
    return hr;
}

HRESULT __RPC_STUB IAccessor_CreateAccessor_Stub(IAccessor* This, DBACCESSORFLAGS dwAccessorFlags, DBCOUNTITEM cBindings,
                                                 DBBINDING *rgBindings, DBLENGTH cbRowSize, HACCESSOR *phAccessor,
                                                 DBBINDSTATUS *rgStatus, IErrorInfo **ppErrorInfoRem)
{
    HRESULT hr;

    TRACE("(%p)->(%08x, %d, %p, %d, %p, %p, %p)\n", This, dwAccessorFlags, cBindings, rgBindings,
          cbRowSize, phAccessor, rgStatus, ppErrorInfoRem);

    *ppErrorInfoRem = NULL;
    hr = IAccessor_CreateAccessor(This, dwAccessorFlags, cBindings, rgBindings,
                                  cbRowSize, phAccessor, rgStatus);
    if(FAILED(hr)) GetErrorInfo(0, ppErrorInfoRem);

    return hr;
}

HRESULT CALLBACK IAccessor_GetBindings_Proxy(IAccessor* This, HACCESSOR hAccessor, DBACCESSORFLAGS *pdwAccessorFlags,
                                             DBCOUNTITEM *pcBindings, DBBINDING **prgBindings)
{
    FIXME("(%p): stub\n", This);
    return E_NOTIMPL;
}

HRESULT __RPC_STUB IAccessor_GetBindings_Stub(IAccessor* This, HACCESSOR hAccessor, DBACCESSORFLAGS *pdwAccessorFlags,
                                              DBCOUNTITEM *pcBindings, DBBINDING **prgBindings, IErrorInfo **ppErrorInfoRem)
{
    FIXME("(%p): stub\n", This);
    return E_NOTIMPL;
}

HRESULT CALLBACK IAccessor_ReleaseAccessor_Proxy(IAccessor* This, HACCESSOR hAccessor, DBREFCOUNT *pcRefCount)
{
    HRESULT hr;
    IErrorInfo *error;
    DBREFCOUNT ref;

    TRACE("(%p)->(%lx, %p)\n", This, hAccessor, pcRefCount);

    hr = IAccessor_RemoteReleaseAccessor_Proxy(This, hAccessor, &ref, &error);

    if(pcRefCount) *pcRefCount = ref;
    if(error)
    {
        SetErrorInfo(0, error);
        IErrorInfo_Release(error);
    }
    return hr;
}

HRESULT __RPC_STUB IAccessor_ReleaseAccessor_Stub(IAccessor* This, HACCESSOR hAccessor, DBREFCOUNT *pcRefCount,
                                                  IErrorInfo **ppErrorInfoRem)
{
    HRESULT hr;

    TRACE("(%p)->(%lx, %p, %p)\n", This, hAccessor, pcRefCount, ppErrorInfoRem);

    *ppErrorInfoRem = NULL;

    hr = IAccessor_ReleaseAccessor(This, hAccessor, pcRefCount);

    if(FAILED(hr)) GetErrorInfo(0, ppErrorInfoRem);
    return hr;
}

HRESULT CALLBACK ICommand_Cancel_Proxy(ICommand* This)
{
    FIXME("(%p): stub\n", This);
    return E_NOTIMPL;
}

HRESULT __RPC_STUB ICommand_Cancel_Stub(ICommand* This, IErrorInfo **ppErrorInfoRem)
{
    FIXME("(%p)->(%p): stub\n", This, ppErrorInfoRem);
    return E_NOTIMPL;
}

HRESULT CALLBACK ICommand_Execute_Proxy(ICommand* This, IUnknown *pUnkOuter, REFIID riid,
                                        DBPARAMS *pParams, DBROWCOUNT *pcRowsAffected, IUnknown **ppRowset)
{
    FIXME("(%p)->(%p, %s, %p, %p, %p): stub\n", This, pUnkOuter, debugstr_guid(riid), pParams,
          pcRowsAffected, ppRowset);
    if(pParams) TRACE("params {%p, %d, %08lx}\n", pParams->pData, pParams->cParamSets, pParams->hAccessor);

    return E_NOTIMPL;
}

HRESULT __RPC_STUB ICommand_Execute_Stub(ICommand* This, IUnknown *pUnkOuter, REFIID riid, HACCESSOR hAccessor,
                                         DB_UPARAMS cParamSets, GUID *pGuid, ULONG ulGuidOffset, RMTPACK *pInputParams,
                                         RMTPACK *pOutputParams, DBCOUNTITEM cBindings, DBBINDING *rgBindings,
                                         DBSTATUS *rgStatus, DBROWCOUNT *pcRowsAffected, IUnknown **ppRowset)
{
    FIXME("(%p)->(%p, %s, %08lx, %d, %p, %d, %p, %p, %d, %p, %p, %p, %p): stub\n", This, pUnkOuter, debugstr_guid(riid),
          hAccessor, cParamSets, pGuid, ulGuidOffset, pInputParams, pOutputParams, cBindings, rgBindings, rgStatus,
          pcRowsAffected, ppRowset);
    return E_NOTIMPL;
}

HRESULT CALLBACK ICommand_GetDBSession_Proxy(ICommand* This, REFIID riid, IUnknown **ppSession)
{
    FIXME("(%p)->(%s, %p): stub\n", This, debugstr_guid(riid), ppSession);
    return E_NOTIMPL;
}

HRESULT __RPC_STUB ICommand_GetDBSession_Stub(ICommand* This, REFIID riid, IUnknown **ppSession, IErrorInfo **ppErrorInfoRem)
{
    FIXME("(%p)->(%s, %p, %p): stub\n", This, debugstr_guid(riid), ppSession, ppErrorInfoRem);
    return E_NOTIMPL;
}

HRESULT CALLBACK ICommandText_GetCommandText_Proxy(ICommandText* This, GUID *pguidDialect, LPOLESTR *ppwszCommand)
{
    FIXME("(%p)->(%p, %p): stub\n", This, pguidDialect, ppwszCommand);
    return E_NOTIMPL;
}

HRESULT __RPC_STUB ICommandText_GetCommandText_Stub(ICommandText* This, GUID *pguidDialect,
                                                    LPOLESTR *ppwszCommand, IErrorInfo **ppErrorInfoRem)
{
    FIXME("(%p)->(%p, %p, %p): stub\n", This, pguidDialect, ppwszCommand, ppErrorInfoRem);
    return E_NOTIMPL;
}

HRESULT CALLBACK ICommandText_SetCommandText_Proxy(ICommandText* This, REFGUID rguidDialect, LPCOLESTR pwszCommand)
{
    FIXME("(%p)->(%s, %s): stub\n", This, debugstr_guid(rguidDialect), debugstr_w(pwszCommand));
    return E_NOTIMPL;
}

HRESULT __RPC_STUB ICommandText_SetCommandText_Stub(ICommandText* This, REFGUID rguidDialect, LPCOLESTR pwszCommand,
                                                    IErrorInfo **ppErrorInfoRem)
{
    FIXME("(%p)->(%s, %s, %p): stub\n", This, debugstr_guid(rguidDialect), debugstr_w(pwszCommand),
          ppErrorInfoRem);
    return E_NOTIMPL;
}
