#include "litetracklistmodel.h"

#include <QSqlQuery>
#include <QSqlRecord>

#include "util/compatibility.h"
#include "util/duration.h"
#include "library/queryutil.h"

inline bool unsupported(int role) {
    return role < LiteTrackListModel::CoverRole || role > LiteTrackListModel::RatingRole;
}

inline QVariant formattedValue(const QVariant& data, int role) {
    if (role != LiteTrackListModel::DurationRole) {
        return data;
    }
    return mixxx::Duration::formatTime(data.toDouble());
}

LiteTrackListModel::LiteTrackListModel(const QSqlDatabase& database, QObject* parent)
        : QAbstractListModel(parent),
          m_database(database) {

    loadModel();
}

void LiteTrackListModel::loadModel() {
    QSqlQuery query(m_database);
    query.prepare(
        "SELECT coverart_type, title, artist, bpm, key, duration, rating, id "
        "FROM library "
        "WHERE mixxx_deleted=0"
    );
    if (!query.exec()) {
        LOG_FAILED_QUERY(query);
    }

    while (query.next()) {
        QSqlRecord record = query.record();
        QHash<int, QVariant> row;
        for (int i = CoverRole; i <= IdRole; ++i) {
            row[i] = formattedValue(record.value(i - CoverRole), i);
        }
        m_rows.push_back(row);
    }
}

int LiteTrackListModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_rows.size();
}

QVariant LiteTrackListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() > m_rows.size() || unsupported(role)) {
        return QVariant();
    }
    return m_rows[index.row()][role];
}

QHash<int, QByteArray> LiteTrackListModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[CoverRole] = "cover";
    names[TitleRole] = "title";
    names[ArtistRole] = "artist";
    names[BpmRole] = "bpm";
    names[KeyRole] = "key";
    names[DurationRole] = "duration";
    names[RatingRole] = "rating";
    names[IdRole] = "id";
    return names;
}

void LiteTrackListModel::slotLoadTrack(int row, const QString& group) {
    emit loadTrack(m_rows[row][IdRole].toInt(), group);
}
