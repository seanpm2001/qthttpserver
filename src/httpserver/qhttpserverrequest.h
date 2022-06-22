// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QHTTPSERVERREQUEST_H
#define QHTTPSERVERREQUEST_H

#include <QtHttpServer/qthttpserverglobal.h>

#include <QtCore/qglobal.h>
#include <QtCore/qurl.h>
#include <QtCore/qurlquery.h>
#include <QtNetwork/qhostaddress.h>

QT_BEGIN_NAMESPACE

class QRegularExpression;
class QString;
class QTcpSocket;

class QHttpServerRequestPrivate;
class QHttpServerRequest final
{
    friend class QAbstractHttpServerPrivate;
    friend class QHttpServerResponse;

    Q_GADGET_EXPORT(Q_HTTPSERVER_EXPORT)

public:
    Q_HTTPSERVER_EXPORT ~QHttpServerRequest();

    enum class Method
    {
        Unknown = 0x0000,
        Get     = 0x0001,
        Put     = 0x0002,
        Delete  = 0x0004,
        Post    = 0x0008,
        Head    = 0x0010,
        Options = 0x0020,
        Patch   = 0x0040,
        Connect = 0x0080,

        All = Get | Put | Delete | Post | Head | Options | Patch | Connect,

        // Include upper-case aliases for the sake of parsing from strings:
        GET     = Get,
        PUT     = Put,
        DELETE  = Delete,
        POST    = Post,
        HEAD    = Head,
        OPTIONS = Options,
        PATCH   = Patch,
        CONNECT = Connect
    };
    Q_ENUM(Method)
    Q_DECLARE_FLAGS(Methods, Method)
    Q_FLAG(Methods)

    Q_HTTPSERVER_EXPORT QByteArray value(const QByteArray &key) const;
    Q_HTTPSERVER_EXPORT QUrl url() const;
    Q_HTTPSERVER_EXPORT QUrlQuery query() const;
    Q_HTTPSERVER_EXPORT Method method() const;
    Q_HTTPSERVER_EXPORT QVariantMap headers() const;
    Q_HTTPSERVER_EXPORT QByteArray body() const;
    Q_HTTPSERVER_EXPORT QHostAddress remoteAddress() const;

private:
    Q_DISABLE_COPY(QHttpServerRequest)

#if !defined(QT_NO_DEBUG_STREAM)
    friend Q_HTTPSERVER_EXPORT QDebug operator<<(QDebug debug, const QHttpServerRequest &request);
#endif

    Q_HTTPSERVER_EXPORT explicit QHttpServerRequest(const QHostAddress &remoteAddress);

    QScopedPointer<QHttpServerRequestPrivate> d;
};

QT_END_NAMESPACE

#endif // QHTTPSERVERREQUEST_H
