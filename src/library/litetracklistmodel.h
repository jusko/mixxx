#pragma once

#include <QAbstractListModel>
#include <QSqlDatabase>

// PROTOTYPE: Write once, throw away
class LiteTrackListModel : public QAbstractListModel {
    Q_OBJECT

  public:
    enum {
        CoverRole = Qt::UserRole,
        TitleRole,
        ArtistRole,
        BpmRole,
        KeyRole,
        DurationRole,
        RatingRole,
        IdRole
    };

    explicit LiteTrackListModel(const QSqlDatabase& db, QObject* parent = nullptr);

    ~LiteTrackListModel() override = default;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

  signals:
    void loadTrack(int row, const QString& group);

  public slots:
    void slotLoadTrack(int row, const QString& group);

  private:
    void loadModel();

    QSqlDatabase m_database;
    QVector<QHash<int, QVariant>> m_rows;
};
