/*
    This file is part of Choqok, the KDE micro-blogging client

    Copyright (C) 2010 Mehrdad Momeny <mehrdad.momeny@gmail.com>

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

#include "filter.h"
#include <KConfigGroup>
#include <KGlobal>
#include <KSharedConfig>

class Filter::Private{
public:
    Private(const QString& text, Filter::FilterField field, Filter::FilterType type)
    :filterField(field), filterText(text), filterType(type)
    {
        config = new KConfigGroup(KGlobal::config(), QString::fromLatin1( "Filter_%1%2%3" ).arg( text )
                                                                                           .arg( field )
                                                                                           .arg( type ));
    }

    Private(KConfigGroup *configGroup)
    :config(configGroup)
    {
        filterText = config->readEntry("Text", QString());
        filterField = (FilterField) config->readEntry("Field", 0);
        filterType = (FilterType) config->readEntry("Type", 0);
    }

    FilterField filterField;
    QString filterText;
    FilterType filterType;
    KConfigGroup *config;
};

Filter::Filter(const QString& filterText, Filter::FilterField field, Filter::FilterType type,
               QObject* parent)
               : QObject(parent), d(new Private(filterText, field, type))
{

}

Filter::Filter(KConfigGroup* config, QObject* parent)
    : QObject(parent), d(new Private(config))
{

}

Filter::~Filter()
{

}

Filter::FilterField Filter::filterField() const
{
    return d->filterField;
}

void Filter::setFilterField(Filter::FilterField field)
{
    d->filterField = field;
}

QString Filter::filterText() const
{
    return d->filterText;
}

void Filter::setFilterText(const QString& text)
{
    d->filterText = text;
}

Filter::FilterType Filter::filterType() const
{
    return d->filterType;
}

void Filter::setFilterType(Filter::FilterType type)
{
    d->filterType = type;
}

void Filter::writeConfig()
{
    d->config->writeEntry("Text", filterText());
    d->config->writeEntry("Field", (int)filterField());
    d->config->writeEntry("Type", (int)filterType());
}
