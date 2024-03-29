/*
    This file is part of Choqok, the KDE micro-blogging client

    Copyright (C) 2010-2012 Andrey Esin <gmlastik@gmail.com>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License or (at your option) version 3 or any later version
    accepted by the membership of KDE e.V. (or its successor approved
    by the membership of KDE e.V.), which shall act as a proxy
    defined in Section 14 of version 3 of the license.


    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, see http://www.gnu.org/licenses/
*/

#include "bit_ly.h"
#include <QString>
#include <KIO/Job>
#include <KDebug>
#include <kio/netaccess.h>
#include <KAboutData>
#include <KGenericFactory>
#include "notifymanager.h"
#include "bit_ly_settings.h"
#include <passwordmanager.h>

K_PLUGIN_FACTORY( MyPluginFactory, registerPlugin < Bit_ly > (); )
K_EXPORT_PLUGIN( MyPluginFactory( "choqok_bit_ly" ) )

Bit_ly::Bit_ly( QObject* parent, const QVariantList& )
    : Choqok::Shortener( MyPluginFactory::componentData(), parent )
{
}

Bit_ly::~Bit_ly()
{
}

QString Bit_ly::shorten( const QString& url )
{
    kDebug() << "Using bit.ly";
    QByteArray data;
    QString login = "choqok";
    QString apiKey = "R_bdd1ae8b6191dd36e13fc77ca1d4f27f";
    KUrl reqUrl( "http://api.bit.ly/v3/shorten" );
    Bit_ly_Settings::self()->readConfig();
    QString userApiKey = Choqok::PasswordManager::self()->readPassword( QString("bitly_%1")
                                                       .arg( Bit_ly_Settings::login() ) );
    if( !Bit_ly_Settings::login().isEmpty() && !userApiKey.isEmpty() ){
        reqUrl.addQueryItem( "x_login", Bit_ly_Settings::login() );
        reqUrl.addQueryItem( "x_apiKey", userApiKey );
    }

    if( Bit_ly_Settings::domain() == "j.mp" ) //bit.ly is default domain
        reqUrl.addQueryItem( "domain", "j.mp" );

    reqUrl.addQueryItem( "login", login.toUtf8() );
    reqUrl.addQueryItem( "apiKey", apiKey.toUtf8() );
    reqUrl.addQueryItem( "longUrl", KUrl( url ).url() );
    reqUrl.addQueryItem( "format", "txt" );

    KIO::Job* job = KIO::get( reqUrl, KIO::Reload, KIO::HideProgressInfo );

    if( KIO::NetAccess::synchronousRun( job, 0, &data ) ) {
        QString output(data);
        kDebug() << "Short url is: " << output;
        QRegExp rx( QString( "(http://((.*)+)/([a-zA-Z0-9])+)" ) );
        rx.indexIn( output );
        QString bitlyUrl = rx.cap( 0 );
        if( !bitlyUrl.isEmpty() )
            return bitlyUrl;

        QString err = QString( data );
        if ( output.startsWith( QString( "INVALID_X_APIKEY" ) ) )
             err = i18n( "API key is invalid" );
        if ( output.startsWith( QString( "INVALID_X_LOGIN" ) ) )
             err = i18n( "Login is invalid" );
        if ( output.startsWith( QString( "RATE_LIMIT_EXCEEDED" ) ) )
             err = i18n( "Rate limit exceeded. Try another shortener." );

        Choqok::NotifyManager::error( err, i18n( "bit.ly Error" ) );
    }
    else {
        Choqok::NotifyManager::error( job->errorString(), i18n( "bit.ly Error" ) );
    }
    return url;
}
