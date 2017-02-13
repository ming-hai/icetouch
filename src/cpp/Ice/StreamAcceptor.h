// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// This copy of Ice Touch is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_STREAM_ACCEPTOR_H
#define ICE_STREAM_ACCEPTOR_H

#include <Ice/TransceiverF.h>
#include <Ice/Acceptor.h>

namespace IceObjC
{

class StreamEndpointI;
typedef IceUtil::Handle<StreamEndpointI> StreamEndpointIPtr;

class Instance;
typedef IceUtil::Handle<Instance> InstancePtr;

class StreamAcceptor : public IceInternal::Acceptor, public IceInternal::NativeInfo
{
public:

    virtual IceInternal::NativeInfoPtr getNativeInfo();
    virtual void close();
    virtual IceInternal::EndpointIPtr listen();
    virtual IceInternal::TransceiverPtr accept();
    virtual std::string protocol() const;
    virtual std::string toString() const;
    virtual std::string toDetailedString() const;

    int effectivePort() const;

private:

    StreamAcceptor(const StreamEndpointIPtr&, const InstancePtr&, const std::string&, int);
    virtual ~StreamAcceptor();
    friend class StreamEndpointI;

    StreamEndpointIPtr _endpoint;
    InstancePtr _instance;
    int _backlog;
    IceInternal::Address _addr;
};

}

#endif
