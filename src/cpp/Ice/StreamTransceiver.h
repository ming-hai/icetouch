// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// This copy of Ice Touch is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_STREAM_TRANSCEIVER_H
#define ICE_STREAM_TRANSCEIVER_H

#include <Ice/WSTransceiver.h>
#include <Ice/Network.h>
#include <Ice/Selector.h>

struct __CFError;
typedef struct __CFError * CFErrorRef;

struct __CFWriteStream;
typedef struct __CFWriteStream * CFWriteStreamRef;

struct __CFReadStream;
typedef struct __CFReadStream * CFReadStreamRef;

namespace IceObjC
{

class Instance;
typedef IceUtil::Handle<Instance> InstancePtr;

class StreamTransceiver : public IceInternal::Transceiver, public IceInternal::StreamNativeInfo,
                          public IceInternal::WSTransceiverDelegate
{
    enum State
    {
        StateNeedConnect,
        StateConnectPending,
        StateConnected
    };

public:

    StreamTransceiver(const InstancePtr&, CFReadStreamRef, CFWriteStreamRef, const std::string&, Ice::Int);
    StreamTransceiver(const InstancePtr&, CFReadStreamRef, CFWriteStreamRef, SOCKET);
    virtual ~StreamTransceiver();

    virtual IceInternal::NativeInfoPtr getNativeInfo();

    virtual void initStreams(IceInternal::SelectorReadyCallback*);
    virtual IceInternal::SocketOperation registerWithRunLoop(IceInternal::SocketOperation);
    virtual IceInternal::SocketOperation unregisterFromRunLoop(IceInternal::SocketOperation, bool);
    virtual void closeStreams();

    virtual IceInternal::SocketOperation initialize(IceInternal::Buffer&, IceInternal::Buffer&, bool&);
    virtual IceInternal::SocketOperation closing(bool, const Ice::LocalException&);
    virtual void close();

    virtual IceInternal::SocketOperation write(IceInternal::Buffer&);
    virtual IceInternal::SocketOperation read(IceInternal::Buffer&, bool&);

    virtual std::string protocol() const;
    virtual std::string toString() const;
    virtual std::string toDetailedString() const;
    virtual Ice::ConnectionInfoPtr getInfo() const;
    virtual Ice::ConnectionInfoPtr getWSInfo(const Ice::HeaderDict&) const;
    virtual void checkSendSize(const IceInternal::Buffer&);
    virtual void setBufferSize(int, int);

private:

    void checkCertificates();
    void checkError(CFErrorRef, const char*, int);
    void fillConnectionInfo(const Ice::IPConnectionInfoPtr&) const;

    const InstancePtr _instance;
    const std::string _host;
    const Ice::Int _port;
    CFReadStreamRef _readStream;
    CFWriteStreamRef _writeStream;
    bool _readStreamRegistered;
    bool _writeStreamRegistered;
    bool _opening;
    bool _checkCertificates;

    IceUtil::Mutex _mutex;
    bool _error;

    State _state;
    std::string _desc;

    size_t _maxSendPacketSize;
    size_t _maxRecvPacketSize;
};

}

#endif
