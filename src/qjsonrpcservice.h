#ifndef QJSONRPCSERVICE_H
#define QJSONRPCSERVICE_H

#include <QObject>
#include <QHostAddress>

#include "qjsonrpcmessage.h"

class QJsonRpcServiceProvider;
class Q_JSONRPC_EXPORT QJsonRpcService : public QObject
{
    Q_OBJECT
public:
    explicit QJsonRpcService(QObject *parent = 0);

private:
    QJsonRpcMessage dispatch(const QJsonRpcMessage &request) const;
    void cacheInvokableInfo();
    QMultiHash<QByteArray, int> m_invokableMethodHash;
    QHash<int, QList<int> > m_parameterTypeHash;
    friend class QJsonRpcServiceProvider;
};

class Q_JSONRPC_EXPORT QJsonRpcServiceReply : public QObject
{
    Q_OBJECT
public:
    explicit QJsonRpcServiceReply(QObject *parent = 0);
    QJsonRpcMessage response() const;

Q_SIGNALS:
    void finished();

private:
    QJsonRpcMessage m_response;
    friend class QJsonRpcSocket;
    friend class QJsonRpcServerSocket;
};

// IDEA: QJsonRpcServiceSocket inherit from QJsonRpcServiceProvider
//       QJsonRpcServiceProvider just has addService, process message
//       QJsonRpcLocalServer/QJsonRpcTcpServer inherit from QJsonRpcServiceProvider + QJsonRpcServer

class QJsonRpcServerSocket;
class QJsonRpcServiceProviderPrivate;
class Q_JSONRPC_EXPORT QJsonRpcServiceProvider
{
public:
    ~QJsonRpcServiceProvider();
    void addService(QJsonRpcService *service);

protected:
    QJsonRpcServiceProvider();
    void processMessage(QJsonRpcServerSocket *socket, const QJsonRpcMessage &message);
    QHash<QString, QJsonRpcService*> m_services;

};

class QJsonRpcServerSocketPrivate;
class Q_JSONRPC_EXPORT QJsonRpcServerSocket : public QObject
{
    Q_OBJECT
public:
    explicit QJsonRpcServerSocket(QIODevice *device, QObject *parent = 0);
    ~QJsonRpcServerSocket();

    bool isValid() const;

    void notify(const QJsonRpcMessage &message);
    QJsonRpcMessage sendMessageBlocking(const QJsonRpcMessage &message, int msecs = 30000);
    QJsonRpcServiceReply *sendMessage(const QJsonRpcMessage &message);
//  void sendMessage(const QList<QJsonRpcMessage> &bulk);
    QJsonRpcServiceReply *invokeRemoteMethod(const QString &method, const QVariant &arg1 = QVariant(),
                                             const QVariant &arg2 = QVariant(), const QVariant &arg3 = QVariant(),
                                             const QVariant &arg4 = QVariant(), const QVariant &arg5 = QVariant(),
                                             const QVariant &arg6 = QVariant(), const QVariant &arg7 = QVariant(),
                                             const QVariant &arg8 = QVariant(), const QVariant &arg9 = QVariant(),
                                             const QVariant &arg10 = QVariant());

Q_SIGNALS:
    void messageReceived(const QJsonRpcMessage &message);

private Q_SLOTS:
    void processIncomingData();

protected:
    virtual void processRequestMessage(const QJsonRpcMessage &message);

private:
    Q_DECLARE_PRIVATE(QJsonRpcServerSocket)
    QScopedPointer<QJsonRpcServerSocketPrivate> d_ptr;

};

class Q_JSONRPC_EXPORT QJsonRpcSocket : public QJsonRpcServerSocket,
                                        public QJsonRpcServiceProvider
{
    Q_OBJECT
public:
    explicit QJsonRpcSocket(QIODevice *device, QObject *parent = 0);
    ~QJsonRpcSocket();

private:
    virtual void processRequestMessage(const QJsonRpcMessage &message);

};

class QJsonRpcServerPrivate;
class Q_JSONRPC_EXPORT QJsonRpcServer : public QObject,
                                        public QJsonRpcServiceProvider
{
    Q_OBJECT
public:
    virtual ~QJsonRpcServer();
    virtual QString errorString() const = 0;

public Q_SLOTS:
    void notifyConnectedClients(const QJsonRpcMessage &message);
    void notifyConnectedClients(const QString &method, const QVariantList &params = QVariantList());

private Q_SLOTS:
    virtual void processIncomingConnection() = 0;
    virtual void clientDisconnected() = 0;
    void processMessage(const QJsonRpcMessage &message);

protected:
    explicit QJsonRpcServer(QJsonRpcServerPrivate *dd, QObject *parent);
    Q_DECLARE_PRIVATE(QJsonRpcServer)
    QScopedPointer<QJsonRpcServerPrivate> d_ptr;

};

class QJsonRpcLocalServerPrivate;
class QJsonRpcLocalServer : public QJsonRpcServer
{
    Q_OBJECT
public:
    explicit QJsonRpcLocalServer(QObject *parent = 0);
    ~QJsonRpcLocalServer();

    QString errorString() const;
    bool listen(const QString &service);

private Q_SLOTS:
    void processIncomingConnection();
    void clientDisconnected();

private:
    Q_DECLARE_PRIVATE(QJsonRpcLocalServer)

};

class QJsonRpcTcpServerPrivate;
class QJsonRpcTcpServer : public QJsonRpcServer
{
    Q_OBJECT
public:
    explicit QJsonRpcTcpServer(QObject *parent = 0);
    ~QJsonRpcTcpServer();

    QString errorString() const;
    bool listen(const QHostAddress &address, quint16 port);

private Q_SLOTS:
    void processIncomingConnection();
    void clientDisconnected();

private:
    Q_DECLARE_PRIVATE(QJsonRpcTcpServer)

};

#endif

