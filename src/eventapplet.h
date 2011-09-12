/*
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 *   Copyright (C) 2008 by Javier Goday <jgoday@gmail.com>
 *   Copyright (C) 2009 by gerdfleischer <gerdfleischer@web.de>
 */

#ifndef EVENTAPPLET_H
#define EVENTAPPLET_H

// kde ui autogenerated file
#include "generalconfig.h"
#include "formatconfig.h"
#include "ui_todoformatconfig.h"
#include "ui_eventappletcolorconfig.h"

// Qt headers
#include <QHash>
#include <QGraphicsSceneHoverEvent>


// Plasma includes
#include <Plasma/PopupApplet>
#include <Plasma/TreeView>
#include <Plasma/Label>
#include <Plasma/BusyWidget>
#include <Plasma/ToolTipManager>

#include <akonadi/agentmanager.h>

class QDateTime;
class QTimer;
class QModelIndex;
class QAction;
class KConfigDialog;
class EventModel;
class PropertyFilterModel;
class EventFilterModel;
class EventItemDelegate;
class QGraphicsLinearLayout;
class QGraphicsProxyWidget;
class QTreeView;
class EventTreeView;
class KDirWatch;
class QDBusServiceWatcher;

class EventApplet : public Plasma::PopupApplet
{
    Q_OBJECT

public:
    EventApplet(QObject *parent, const QVariantList &args);
    ~EventApplet();

    void init();
    QGraphicsWidget *graphicsWidget();
    virtual QList<QAction *> contextualActions();

private slots:
    void slotOpenEvent(const QModelIndex &index);
    void slotUpdateTooltip(QString);
    void openEventFromMenu();
    void slotAddEvent();
    void slotAddTodo();
    void timerExpired();
    void setShownResources();
    void setShownCategories();
    void setupModel();
    void akonadiStatusChanged();
    void plasmaThemeChanged();
    void koConfigChanged();
    void korganizerStartedOpenEvent(const QString &);
    void korganizerStartedAddEvent(const QString &);
    void korganizerStartedAddTodo(const QString &);
    void timedOpenEvent();
    void timedAddEvent();
    void timedAddTodo();

protected slots:
    void configAccepted();

protected:
    void createConfigurationInterface(KConfigDialog *parent);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

private:
    void setupCategoryColors(int opacity);
    void colorizeModel(bool timerTriggered);
    void createToolTip();
    
private:
    QGraphicsWidget *m_graphicsWidget;
    QGraphicsLinearLayout *layout;
    EventModel *m_model;
    PropertyFilterModel *m_propertyFilterModel;
    EventFilterModel *m_filterModel;
    KDirWatch *m_categoryColorWatch;
    QGraphicsProxyWidget *proxyWidget;
    EventTreeView *m_view;
    Plasma::ToolTipContent tooltip;
    Plasma::BusyWidget *busy;
    Plasma::Label *title;
    EventItemDelegate *m_delegate;
    GeneralConfig m_generalConfig;
    FormatConfig m_eventFormatConfig;
    Ui::TodoFormatConfig m_todoFormatConfig;
    Ui::EventAppletColorConfig m_colorConfigUi;
    int m_urgency, m_birthdayUrgency, m_checkInterval, m_period, m_recurringCount;
    QColor m_urgentBg, m_passedFg, m_todoBg, m_finishedTodoBg;
    QHash<QString, QColor> m_categoryColors;
    QMap<QString, QString> m_categoryFormat;
    QList<QColor> m_colors;
    QTimer *m_timer;
    Akonadi::AgentManager *m_agentManager;
    QStringList disabledResources, disabledCategories, m_headerItemsList, m_categories;
    QDateTime lastCheckTime;
    bool m_showFinishedTodos, m_autoGroupHeader;
    QString m_uid, m_appletTitle;
    QDBusServiceWatcher *m_openEventWatcher, *m_addEventWatcher, *m_addTodoWatcher;
};

#endif
