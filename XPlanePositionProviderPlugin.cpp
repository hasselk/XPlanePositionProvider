// Copyright 2012 Ralf Habacker <ralf.habacker@freenet.de>
//
// Hacked by @akeyla420 for X-Plane 10.51 position tracking
// akeyla@protonmail.ch, December 31st, 2016

#include "XPlanePositionProviderPlugin.h"

#include "MarbleDebug.h"
#include <math.h>

#include <QUdpSocket>
#include <QIcon>

using namespace Marble;
/* TRANSLATOR Marble::XPlanePositionProviderPlugin */

using namespace std;

XPlanePositionProviderPlugin::XPlanePositionProviderPlugin()
  : m_socket(0), m_speed( 0.0 ), m_track( 0.0 )
{
}

XPlanePositionProviderPlugin::~XPlanePositionProviderPlugin()
{
    delete m_socket;
}

QString XPlanePositionProviderPlugin::name() const
{
    return tr( "XPlane position provider Plugin" );
}

QString XPlanePositionProviderPlugin::nameId() const
{
    return QStringLiteral("xplane");
}

QString XPlanePositionProviderPlugin::guiString() const
{
    return tr( "X-Plane" );
}

QString XPlanePositionProviderPlugin::version() const
{
    return QStringLiteral(".14");
}

QString XPlanePositionProviderPlugin::description() const
{
    return tr( "Reports the position of running xplane application." );
}

QString XPlanePositionProviderPlugin::copyrightYears() const
{
    return QStringLiteral("2016");
}

QVector<PluginAuthor> XPlanePositionProviderPlugin::pluginAuthors() const
{
    return QVector<PluginAuthor>()
            << PluginAuthor(QStringLiteral("akeyla"), QStringLiteral("akeyla@protonmail.ch"));
}

QIcon XPlanePositionProviderPlugin::icon() const
{
    return QIcon();
}

void XPlanePositionProviderPlugin::initialize()
{
    m_status = PositionProviderStatusAcquiring;
    emit statusChanged( m_status );

    m_socket = new QUdpSocket(this);
    m_socket->bind(QHostAddress::Any, 49003);

    connect(m_socket, SIGNAL(readyRead()),
             this, SLOT(readPendingDatagrams()));
}

void XPlanePositionProviderPlugin::readPendingDatagrams()
{
	PositionProviderStatus oldStatus = m_status;
	GeoDataCoordinates oldPosition = m_position;
	
	int	__debug = 0;

	int	__offset = 0;

	float   _Vind_kias, //Block 3
                _Vind_keas,
                Vtrue_ktas,
                Vtrue_ktgs,
                _Vind__mph,
                Vtruemphas,
                Vtruemphgs;

	float	pitch__deg, //Block 17
		_roll__deg,
		hding_true,
		hding__mag;


	float   __lat__deg, //Block 20
                __lon__deg,
                __altftmsl,
                __altftagl,
                ___onrunwy,
                __alt__ind,
                __latsouth,
                __lat_west;


	while (m_socket->hasPendingDatagrams()) {
		__offset = 5;
		QByteArray datagram;
		datagram.resize(m_socket->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;

		m_socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        
		char *data = datagram.data();

		if ( data[__offset] == 0x00 ) __offset += 36;
		if ( data[__offset] == 0x01 ) __offset += 36;
		if ( data[__offset] == 0x02 ) __offset += 36;
		if ( data[__offset] == 0x03 ) {
			memcpy(&_Vind_kias, &data[__offset+4], sizeof(float));
			if (__debug) printf ("_Vind,_kias : %f\n", _Vind_kias);
			memcpy(&_Vind_keas, &data[__offset+8], sizeof(float));
			if (__debug) printf ("_Vind,_keas : %f\n", _Vind_keas);
			memcpy(&Vtrue_ktas, &data[__offset+12], sizeof(float));
			if (__debug) printf ("Vtrue,_ktas : %f\n", Vtrue_ktas);
			memcpy(&Vtrue_ktgs, &data[__offset+16], sizeof(float));
			if (__debug) printf ("Vtrue,_ktgs : %f\n", Vtrue_ktgs);
			memcpy(&_Vind__mph, &data[__offset+20], sizeof(float));
			if (__debug) printf ("_Vind,__mph : %f\n", _Vind__mph);
			memcpy(&Vtruemphas, &data[__offset+24], sizeof(float));
			if (__debug) printf ("Vtrue,mphas : %f\n", Vtruemphas);
			memcpy(&Vtruemphgs, &data[__offset+28], sizeof(float));
			if (__debug) printf ("Vtrue,mphgs : %f\n", Vtruemphgs);
			__offset += 36;
		}
		if ( data[__offset] == 0x04 ) __offset += 36;
		if ( data[__offset] == 0x05 ) __offset += 36;
		if ( data[__offset] == 0x06 ) __offset += 36;
		if ( data[__offset] == 0x07 ) __offset += 36;
		if ( data[__offset] == 0x08 ) __offset += 36;
		if ( data[__offset] == 0x09 ) __offset += 36;
		if ( data[__offset] == 0x0a ) __offset += 36;
		if ( data[__offset] == 0x0b ) __offset += 36;
		if ( data[__offset] == 0x0c ) __offset += 36;
		if ( data[__offset] == 0x0d ) __offset += 36;
		if ( data[__offset] == 0x0e ) __offset += 36;
		if ( data[__offset] == 0x0f ) __offset += 36;
		if ( data[__offset] == 0x10 ) __offset += 36;
		if ( data[__offset] == 0x11 ) {
			memcpy(&pitch__deg, &data[__offset+4], sizeof(float));
			if (__debug) printf ("pitch,__deg : %f\n", pitch__deg);
			memcpy(&_roll__deg, &data[__offset+8], sizeof(float));
			if (__debug) printf ("_roll,__del : %f\n", _roll__deg);
			memcpy(&hding_true, &data[__offset+12], sizeof(float));
			if (__debug) printf ("hding,_true : %f\n", hding_true);
			memcpy(&hding__mag, &data[__offset+16], sizeof(float));
			if (__debug) printf ("hding,__mag : %f\n", hding__mag);
			__offset += 36;
		}
		if ( data[__offset] == 0x12 ) __offset += 36;
		if ( data[__offset] == 0x13 ) __offset += 36;
		if ( data[__offset] == 0x14 ) {
			memcpy(&__lat__deg, &data[__offset+4], sizeof(float));
			if (__debug) printf("__lat,__deg : %f\n", __lat__deg);
			memcpy(&__lon__deg, &data[__offset+8], sizeof(float));
			if (__debug) printf("__lon,__deg : %f\n", __lon__deg);
			memcpy(&__altftmsl, &data[__offset+12], sizeof(float));
			if (__debug) printf("__alt,ftmsl : %f\n", __altftmsl);
			memcpy(&__altftagl, &data[__offset+16], sizeof(float));
			if (__debug) printf("__alt,ftagl : %f\n", __altftmsl);
			memcpy(&___onrunwy, &data[__offset+20], sizeof(float));
			if (__debug) printf("___on,runwy : %f\n", ___onrunwy);
			memcpy(&__alt__ind, &data[__offset+24], sizeof(float));
			if (__debug) printf("__alt,__ind : %f\n", __alt__ind);
			memcpy(&__latsouth, &data[__offset+28], sizeof(float));
			if (__debug) printf("__lat,south : %f\n", __latsouth);
			memcpy(&__lat_west, &data[__offset+32], sizeof(float));
			if (__debug) printf("__lat,_west : %f\n", __lat_west);
			__offset += 36;
		}

		m_speed = _Vind_kias * .514444; // Cause speed math
		m_position.set( __lon__deg, __lat__deg, __altftmsl/3.2808399, GeoDataCoordinates::Degree );
		m_accuracy.level = GeoDataAccuracy::Detailed;
		m_status = PositionProviderStatusAvailable;
		m_track = hding__mag;
	}
	if ( m_status != oldStatus ) {
		emit statusChanged( m_status );
	}
	if ( m_position != oldPosition && m_status == PositionProviderStatusAvailable ) {
		emit positionChanged( m_position, m_accuracy );
	}
}
 
bool XPlanePositionProviderPlugin::isInitialized() const
{
    return m_socket;
}

PositionProviderPlugin* XPlanePositionProviderPlugin::newInstance() const
{
    return new XPlanePositionProviderPlugin;
}

PositionProviderStatus XPlanePositionProviderPlugin::status() const
{
    return m_status;
}

GeoDataCoordinates XPlanePositionProviderPlugin::position() const
{
    return m_position;
}

GeoDataAccuracy XPlanePositionProviderPlugin::accuracy() const
{
    return m_accuracy;
}

qreal XPlanePositionProviderPlugin::speed() const
{
    return m_speed;
}

qreal XPlanePositionProviderPlugin::direction() const
{
    return m_track;
}

QString XPlanePositionProviderPlugin::error() const
{
    return QString();
}

QDateTime XPlanePositionProviderPlugin::timestamp() const
{
    return m_timestamp;
}
