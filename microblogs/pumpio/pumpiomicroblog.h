/*
    This file is part of Choqok, the KDE micro-blogging client

    Copyright (C) 2013 Andrea Scarpino <scarpino@kde.org>

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

#ifndef PUMPIOMICROBLOG_H
#define PUMPIOMICROBLOG_H

#include "QtOAuth/qoauth_namespace.h"

#include "microblog.h"

class KJob;
class KUrl;
class PumpIOAccount;

class PumpIOMicroBlog : public Choqok::MicroBlog
{
    Q_OBJECT
public:
    explicit PumpIOMicroBlog(QObject* parent, const QVariantList& args);
    virtual ~PumpIOMicroBlog();

    virtual void abortAllJobs(Choqok::Account* theAccount);

    virtual void abortCreatePost(Choqok::Account* theAccount, Choqok::Post* post = 0);

    virtual void aboutToUnload();

    virtual QMenu* createActionsMenu(Choqok::Account* theAccount,
                                     QWidget* parent = Choqok::UI::Global::mainWindow());

    virtual Choqok::UI::ComposerWidget* createComposerWidget(Choqok::Account* account,
                                                             QWidget* parent);

    virtual ChoqokEditAccountWidget* createEditAccountWidget(Choqok::Account* account,
                                                             QWidget* parent);

    virtual Choqok::Account* createNewAccount(const QString& alias);

    virtual void createPost(Choqok::Account* theAccount, Choqok::Post* post);

    virtual Choqok::UI::PostWidget* createPostWidget(Choqok::Account* account,
                                                     Choqok::Post* post,
                                                     QWidget* parent);

    virtual void fetchPost(Choqok::Account* theAccount, Choqok::Post* post);

    virtual QList<Choqok::Post* > loadTimeline(Choqok::Account* account,
                                               const QString& timelineName);

    virtual void removePost(Choqok::Account* theAccount, Choqok::Post* post);

    virtual QString postUrl(Choqok::Account* account, const QString& username,
                            const QString& postId) const;

    virtual QString profileUrl(Choqok::Account* account, const QString& username) const;

    virtual void saveTimeline(Choqok::Account* account, const QString& timelineName,
                              const QList< Choqok::UI::PostWidget* >& timeline);

    virtual Choqok::TimelineInfo* timelineInfo(const QString& timelineName);

    virtual void updateTimelines(Choqok::Account* theAccount);

    void createPost(Choqok::Account* theAccount, Choqok::Post* post,
                    const QVariantList& to, const QVariantList& cc = QVariantList());

    void createPostWithMedia(Choqok::Account* theAccount, Choqok::Post* post,
                             const QString& filePath);

    void fetchFollowing(Choqok::Account* theAccount);

    void fetchLists(Choqok::Account* theAccount);

    void share(Choqok::Account* theAccount, Choqok::Post* post);

    void toggleFavorite(Choqok::Account* theAccount, Choqok::Post* post);

    void fetchReplies(Choqok::Account* theAccount, const QString& url);

    static QString userNameFromAcct(const QString& acct);
    static QString hostFromAcct(const QString& acct);

Q_SIGNALS:
    void favorite(Choqok::Account*, Choqok::Post*);
    void followingFetched(Choqok::Account*);
    void listsFetched(Choqok::Account*);

protected Q_SLOTS:
    void showDirectMessageDialog();
    void slotCreatePost(KJob* job);
    void slotFavorite(KJob* job);
    void slotFetchPost(KJob* job);
    void slotFetchReplies(KJob* job);
    void slotFollowing(KJob* job);
    void slotLists(KJob* job);
    void slotRemovePost(KJob* job);
    void slotShare(KJob* job);
    void slotUpdatePost(KJob* job);
    void slotUpdateTimeline(KJob* job);
    void slotUpload(KJob* job);

protected:
    static const QString inboxActivity;
    static const QString outboxActivity;

    QString authorizationMetaData(PumpIOAccount* account, const KUrl& url,
                                  const QOAuth::HttpMethod& method,
                                  const QOAuth::ParamMap& map = QOAuth::ParamMap()) const;

    ChoqokId lastTimelineId(Choqok::Account* theAccount, const QString& timeline) const;

    Choqok::Post* readPost(const QVariantMap& var, Choqok::Post* post);

    QList<Choqok::Post* > readTimeline(const QByteArray& buffer);

    void setLastTimelineId(Choqok::Account* theAccount, const QString& timeline,
                           const ChoqokId& id);

    void setTimelinesInfo();

    void updatePost(Choqok::Account* theAccount, Choqok::Post* post);

    QMap<KJob*, Choqok::Account* > m_accountJobs;
    QMap<KJob*, Choqok::Post* > m_createPostJobs;
    QMap<KJob*, Choqok::Post* > m_favoriteJobs;
    QMap<KJob*, Choqok::Post* > m_removePostJobs;
    QMap<KJob*, Choqok::Post* > m_shareJobs;
    QMap<KJob*, Choqok::Post* > m_uploadJobs;
    QMap<KJob*, Choqok::Post* > m_updateJobs;
    QMap<QString, Choqok::TimelineInfo* > m_timelinesInfos;
    QHash<Choqok::Account*, QMap<QString, ChoqokId> > m_timelinesLatestIds;
    QHash<QString, QString> m_timelinesPaths;
    QMap<KJob*, QString> m_timelinesRequests;

private:
    class Private;
    Private * const d;

};

#endif // PUMPIOMICROBLOG_H