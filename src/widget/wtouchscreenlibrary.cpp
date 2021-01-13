#include "widget/wtouchscreenlibrary.h"

#include <QQmlContext>
#include <QQuickItem>

#include "library/library.h"
#include "library/litetracklistmodel.h"
#include "library/trackcollection.h"
#include "library/trackcollectionmanager.h"
#include "mixer/playermanager.h"

WTouchScreenLibrary::WTouchScreenLibrary(QWidget* pParent,
                                         Library* pLibrary,
                                         PlayerManager* pPlayerManager)
    : QQuickWidget(pParent),
      WBaseWidget(this) {

    initializeView(pLibrary->trackCollections()->internalCollection()->database());
    connectTrackLoading(pLibrary->trackCollections()->internalCollection(), pPlayerManager);
}

void WTouchScreenLibrary::initializeView(const QSqlDatabase& database) {
    m_pLiteTrackListModel = new LiteTrackListModel(database, this);
    rootContext()->setContextProperty("LiteTrackListModel", m_pLiteTrackListModel);
    setSource(QUrl::fromLocalFile("res/qml/view.qml"));
    setResizeMode(QQuickWidget::SizeRootObjectToView);
}

// RnD: Can cutting out all the middle men like this can help clean up later?
void WTouchScreenLibrary::connectTrackLoading(TrackCollection* pTrackCollection,
                                              PlayerManager* pPlayerManager) {

    QObject::connect(m_pLiteTrackListModel, SIGNAL(loadTrack(int, QString)),
                     pTrackCollection, SLOT(slotLoadTrackToPlayer(int, QString))); 

    QObject::connect(pTrackCollection, SIGNAL(loadTrackToPlayer(TrackPointer, QString, bool)),
                     pPlayerManager, SLOT(slotLoadTrackToPlayer(TrackPointer, QString, bool))); 
}

WTouchScreenLibrary::~WTouchScreenLibrary() {
}
