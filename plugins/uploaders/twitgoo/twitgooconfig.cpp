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

#include "twitgooconfig.h"
#include <KPluginFactory>
#include <klocale.h>
#include <qlayout.h>
#include "twitgoosettings.h"
#include <QVBoxLayout>
#include <passwordmanager.h>
#include <accountmanager.h>
#include <KMessageBox>

K_PLUGIN_FACTORY ( TwitgooConfigFactory, registerPlugin < TwitgooConfig > (); )
K_EXPORT_PLUGIN ( TwitgooConfigFactory ( "kcm_choqok_twitgoo" ) )

TwitgooConfig::TwitgooConfig ( QWidget* parent, const QVariantList& ) :
        KCModule ( TwitgooConfigFactory::componentData(), parent )
{
    QVBoxLayout *layout = new QVBoxLayout ( this );
    QWidget *wd = new QWidget ( this );
    wd->setObjectName ( "mTwitgooCtl" );
    ui.setupUi ( wd );
    addConfig ( TwitgooSettings::self(), wd );
    layout->addWidget ( wd );
    connect ( ui.cfg_accountsList, SIGNAL ( currentIndexChanged ( int ) ), SLOT ( emitChanged() ) );
    connect ( ui.cfg_directLink, SIGNAL ( stateChanged ( int ) ), SLOT ( emitChanged() ) );
}

TwitgooConfig::~TwitgooConfig()
{
}

void TwitgooConfig::load()
{
    kDebug();
    KCModule::load();
    QList<Choqok::Account*> list = Choqok::AccountManager::self()->accounts();
    foreach ( Choqok::Account *acc, list ) {
        if ( acc->inherits ( "TwitterAccount" ) ) {
            ui.cfg_accountsList->addItem ( acc->alias() );
        }
    }
    TwitgooSettings::self()->readConfig();
    ui.cfg_accountsList->setCurrentItem ( TwitgooSettings::alias() );
    ui.cfg_directLink->setChecked ( TwitgooSettings::directLink() );
}

void TwitgooConfig::save()
{
    if ( ui.cfg_accountsList->currentIndex() > -1 ) {
        TwitgooSettings::setAlias ( ui.cfg_accountsList->currentText() );
        kDebug() << TwitgooSettings::alias();
    } else {
        TwitgooSettings::setAlias ( QString() );
        KMessageBox::error ( this, i18n ( "You have to configure at least one Twitter account to use this plugin." ) );
    }
    TwitgooSettings::setDirectLink ( ui.cfg_directLink->isChecked() );
    TwitgooSettings::self()->writeConfig();
    KCModule::save();
}

void TwitgooConfig::emitChanged()
{
    emit changed ( true );
}

#include "twitgooconfig.moc"
