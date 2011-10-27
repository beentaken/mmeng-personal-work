#pragma once
#ifndef NETWORK_EXCEPTION_H
#define NETWORK_EXCEPTION_H

#include <stdexcept>

class NetworkException : public std::runtime_error
{
    public:
        NetworkException(const std::string& error)
            :std::runtime_error(error)
        {
        }
};

class BindException : public NetworkException
{
    public:
        BindException(const std::string& error)
            :NetworkException(error)
        {
        }
};

class ListenException : public NetworkException
{
    public:
        ListenException(const std::string& error)
            :NetworkException(error)
        {
        }
};

class ShutdownException : public NetworkException
{
    public:
        ShutdownException(const std::string& error)
            :NetworkException(error)
        {
        }
};

class CloseException : public NetworkException
{
    public:
        CloseException(const std::string& error)
            :NetworkException(error)
        {
        }
};

class SendException : public NetworkException
{
    public:
        SendException(const std::string& error)
            :NetworkException(error)
        {
        }
};

class SocketException : public NetworkException
{
    public:
        SocketException(const std::string& error)
            :NetworkException(error)
        {
        }
};

class ConnectException : public NetworkException
{
    public:
        ConnectException(const std::string& error)
            :NetworkException(error)
        {
        }
};

#endif // NETWORK_EXCEPTION_H

