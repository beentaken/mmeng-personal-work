#pragma once
#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <list>
#include <functional>

#if defined(_WIN32)
#include <WinSock2.h>
#endif

class NetworkStack
{
    public:
        typedef std::function<void (int)> AcceptListenerFun;
        typedef std::function<void (int)> ConnectListenerFun;
        typedef std::function<void (int, const std::string&)> ReceiveListenerFun;
        typedef std::function<void (int)> DisconnectListenerFun;

        NetworkStack();
        ~NetworkStack();

        void think();

        void listen(const std::string& port);
        void connect(const std::string& address, const std::string& port);

        void registerAcceptListener(AcceptListenerFun fun);
        void registerConnectListener(ConnectListenerFun fun);
        void registerReceiveListener(ReceiveListenerFun fun);
        void registerDisconnectListener(DisconnectListenerFun fun);

        void sendString(int connection, const std::string& message);

        void disconnect(int connection);

    private:
        fd_set myConnections; // List of connections to select.
        int myCurrentConnections; // Max connections.
        int listener; // The specific listener socket.

        std::list<AcceptListenerFun> myAcceptListeners;
        std::list<ConnectListenerFun> myConnectListeners;
        std::list<ReceiveListenerFun> myReceiveListeners;
        std::list<DisconnectListenerFun> myDisconnectListeners;

        void myDisconnectSocket(int socket);
};

#endif // NETWORK_H

