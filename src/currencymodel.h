/*
    This file is part of shiftwallet.
    shiftwallet is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    shiftwallet is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with shiftwallet. If not, see <http://www.gnu.org/licenses/>.
*/
/** @file currencymodel.h
 * @author Ales Katona <almindor@gmail.com>
 * @date 2016
 *
 * Currency model header
 */

#ifndef CURRENCYMODEL_H
#define CURRENCYMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include "etherlog.h"
#include "types.h"

namespace ShiftWallet {

    class CurrencyModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(QString currencyName READ getCurrencyName() NOTIFY currencyChanged FINAL)
        Q_PROPERTY(int count READ getCount NOTIFY currencyChanged FINAL)
    public:
        CurrencyModel();
        QHash<int, QByteArray> roleNames() const;
        int rowCount(const QModelIndex & parent = QModelIndex()) const;
        QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
        QVariant recalculate(const QVariant ether) const;
        int getCount() const;
        Q_INVOKABLE QString getCurrencyName(int index = -1) const;
        Q_INVOKABLE void loadCurrencies();
        Q_INVOKABLE void setCurrencyIndex(int index);
        Q_INVOKABLE int getCurrencyIndex() const;
        Q_INVOKABLE double getCurrencyPrice(int index) const;
    public slots:
        void loadCurrenciesDone(QNetworkReply *reply);
    signals:
        void currencyChanged();
    private:
        CurrencyInfos fCurrencies;
        QNetworkAccessManager fNetManager;
        int fIndex;
        QTimer fTimer;
    };

}

#endif // CURRENCYMODEL_H
