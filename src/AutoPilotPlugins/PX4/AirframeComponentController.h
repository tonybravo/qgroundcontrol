/*=====================================================================
 
 QGroundControl Open Source Ground Control Station
 
 (c) 2009, 2015 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 
 This file is part of the QGROUNDCONTROL project
 
 QGROUNDCONTROL is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 QGROUNDCONTROL is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.
 
 ======================================================================*/

/// @file
///     @author Don Gagne <don@thegagnes.com>

#ifndef AIRFRAMECOMPONENTCONTROLLER_H
#define AIRFRAMECOMPONENTCONTROLLER_H

#include <QObject>
#include <QQuickItem>
#include <QList>

#include "UASInterface.h"
#include "AutoPilotPlugin.h"
#include "FactPanelController.h"

/// MVC Controller for AirframeComponent.qml.
class AirframeComponentController : public FactPanelController
{
    Q_OBJECT
    
public:
    AirframeComponentController(void);
    ~AirframeComponentController();
    
    Q_PROPERTY(bool showCustomConfigPanel MEMBER _showCustomConfigPanel NOTIFY showCustomConfigPanelChanged)
    
    Q_PROPERTY(QVariantList airframeTypes MEMBER _airframeTypes CONSTANT)
    
    Q_PROPERTY(QString currentAirframeType MEMBER _currentAirframeType CONSTANT)
    Q_PROPERTY(QString currentVehicleName MEMBER _currentVehicleName CONSTANT)
    Q_PROPERTY(int currentVehicleIndex MEMBER _currentVehicleIndex CONSTANT)
    
    Q_PROPERTY(int autostartId MEMBER _autostartId NOTIFY autostartIdChanged)
    
    Q_INVOKABLE void changeAutostart(void);
    
    int currentAirframeIndex(void);
    void setCurrentAirframeIndex(int newIndex);
    
signals:
    void autostartIdChanged(int newAutostartId);
    void showCustomConfigPanelChanged(bool show);
    
private:
    static bool _typesRegistered;
    
    UASInterface*       _uas;
    QVariantList        _airframeTypes;
    QString             _currentAirframeType;
    QString             _currentVehicleName;
    int                 _currentVehicleIndex;
    int                 _autostartId;
    bool                _showCustomConfigPanel;
};

class Airframe : public QObject
{
    Q_OBJECT
    
public:
    Airframe(const QString& name, int autostartId, QObject* parent = NULL);
    ~Airframe();
    
    Q_PROPERTY(QString text MEMBER _name CONSTANT)
    Q_PROPERTY(int autostartId MEMBER _autostartId CONSTANT)
    
private:
    QString _name;
    int     _autostartId;
};

class AirframeType : public QObject
{
    Q_OBJECT
    
public:
    AirframeType(const QString& name, const QString& imageResource, QObject* parent = NULL);
    ~AirframeType();
    
    Q_PROPERTY(QString name MEMBER _name CONSTANT)
    Q_PROPERTY(QString imageResource MEMBER _imageResource CONSTANT)
    Q_PROPERTY(QVariantList airframes MEMBER _airframes CONSTANT)
    
    void addAirframe(const QString& name, int autostartId);
    
private:
    QString         _name;
    QString         _imageResource;
    QVariantList    _airframes;
};

#endif
