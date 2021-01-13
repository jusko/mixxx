#pragma once

#include <QQuickWidget>

#include "widget/wbasewidget.h"

class QSqlDatabase;
class Library;
class TrackCollection;
class PlayerManager;
class LiteTrackListModel;

class WTouchScreenLibrary : public QQuickWidget, public WBaseWidget {
  public:
    explicit WTouchScreenLibrary(QWidget* parent,
                                 Library*,
                                 PlayerManager*);

    virtual ~WTouchScreenLibrary();

  private:
    void initializeView(const QSqlDatabase&);
    void connectTrackLoading(TrackCollection*, PlayerManager*);

    LiteTrackListModel* m_pLiteTrackListModel;
};
