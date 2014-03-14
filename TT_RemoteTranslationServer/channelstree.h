/*
 * Copyright (c) 2005-2013, BearWare.dk
 *
 * Contact Information:
 *
 * Bjoern D. Rasmussen
 * Bedelundvej 79
 * DK-9830 Taars
 * Denmark
 * Email: contact@bearware.dk
 * Phone: +45 20 20 54 59
 * Web: http://www.bearware.dk
 *
 * This source code is part of the TeamTalk 4 SDK owned by
 * BearWare.dk. All copyright statements may not be removed
 * or altered from any source distribution. If you use this
 * software in a product, an acknowledgment in the product
 * documentation is required.
 *
 */

#ifndef CHANNELSTREE_H
#define CHANNELSTREE_H

#include <QMap>
#include <QSet>
#include <QVector>
#include <QTreeWidget>

#include "common.h"

typedef QVector<int> userids_t;

bool userCanVoiceTx(int userid, const Channel& chan);
bool userCanVideoTx(int userid, const Channel& chan);
bool userCanDesktopTx(int userid, const Channel& chan);

class ChannelsTree : public QTreeWidget
{
    Q_OBJECT

public:
    ChannelsTree(QWidget* parent);

    int selectedChannel(bool include_user = false) const;
    QVector<int> selectedChannels() const;

    int selectedUser() const;
    QVector<int> selectedUsers() const;

    bool getChannel(int channelid, Channel& chan) const;
    bool getSelectedChannel(Channel& chan) const;
    bool getUser(int userid, User& user) const;
    bool getSelectedUser(User& user) const;

    QVector<int> getUsersInChannel(int channelid) const;
    QVector<int> getUsers() const;

    void getClassRoomUsers(int channelid, QSet<int>& voiceUsers,
                           QSet<int>& videoUsers, QSet<int>& desktopUsers);

    void reset();

    void setChannelMessaged(int channelid, bool messaged);
    void setUserMessaged(int userid, bool messaged);
    void setShowUserCount(bool show);

signals:
    void userDoubleClicked(int);
    void channelDoubleClicked(int);
    void fileDropped(const QString&);

    //chanid, voiceUsers, videoUsers, desktopUsers
    void classroomChanged(int, const QSet<int>&, const QSet<int>&,
                          const QSet<int>&);

protected:
    void timerEvent(QTimerEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent * event);

private:
    typedef QMap<int, Channel> channels_t;
    typedef QMap<int, User> users_t;
    typedef QMap<int, UserStatistics> statistics_t;
    typedef QSet<int> uservideo_t;
    channels_t m_channels;
    users_t m_users;
    bool m_showusercount;
    statistics_t m_stats;
    uservideo_t m_videousers;
    //users who are blinking
    QSet<int> m_blinkusers;

    int m_statTimerId, m_questionTimerId;

    QPoint m_dragStartPos;

    QTreeWidgetItem* getChannelItem(int channelid);
    QTreeWidgetItem* getUserItem(int userid);
    int getUserIndex(const QTreeWidgetItem* parent, const QString& nick);
    void updateChannelItem(int channelid);

    bool m_ignore_item_changes;

private slots:
    void slotItemDoubleClicked(QTreeWidgetItem* item, int column);
    void slotItemChanged(QTreeWidgetItem* item, int column);
    void slotUpdateTreeWidgetItem(QTreeWidgetItem* item);

public slots:
    void slotServerUpdate();
    void slotAddChannel(int channelid);
    void slotUpdateChannel(int channelid);
    void slotRemoveChannel(int channelid);
    void slotUserJoin(int userid, int channelid);
    void slotUserUpdate(int userid, int channelid);
    void slotUserRemove(int userid, int channelid);
    void slotUserTalking(int userid, bool talking);
    void slotUserVideoFrame(int userid, int frame_count);
};

#endif
