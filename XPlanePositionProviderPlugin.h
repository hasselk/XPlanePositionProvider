// Copyright 2012 Ralf Habacker <ralf.habacker@freenet.de>
//
// Hacked by @akeyla420 for X-Plane 10.51 position tracking
// akeyla@protonmail.ch, December 31st, 2016

#ifndef XPLANEPOSITIONPROVIDERPLUGIN_H
#define XPLANEPOSITIONPROVIDERPLUGIN_H

#include "PositionProviderPlugin.h"

#include "GeoDataAccuracy.h"
#include "GeoDataCoordinates.h"
#include <QDateTime>

class QUdpSocket;

namespace Marble
{

class XPlanePositionProviderPlugin : public PositionProviderPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.marble.XPlanePositionProviderPlugin")
    Q_INTERFACES( Marble::PositionProviderPluginInterface )

 public:
    XPlanePositionProviderPlugin();
    ~XPlanePositionProviderPlugin() override;

    QString name() const override;
    QString nameId() const override;
    QString guiString() const override;
    QString version() const override;
    QString description() const override;
    QString copyrightYears() const override;
    QVector<PluginAuthor> pluginAuthors() const override;
    QIcon icon() const override;
    void initialize() override;
    bool isInitialized() const override;

    PositionProviderPlugin * newInstance() const override;

    PositionProviderStatus status() const override;
    GeoDataCoordinates position() const override;
    GeoDataAccuracy accuracy() const override;
    QString error() const override;
    qreal speed() const override;
    qreal direction() const override;
    QDateTime timestamp() const override;

private Q_SLOTS:
   void readPendingDatagrams();

 private:
    QUdpSocket* m_socket;
    PositionProviderStatus m_status;
    GeoDataCoordinates m_position;
    GeoDataAccuracy m_accuracy;
    qreal m_speed;
    qreal m_track;
    //QDateTime m_timestamp;
};

}
#endif // XPLANEPOSITIONPROVIDERPLUGIN_H
