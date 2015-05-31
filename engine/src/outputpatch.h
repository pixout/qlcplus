/*
  Q Light Controller
  outputpatch.h

  Copyright (c) Heikki Junnila

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef OUTPUTPATCH_H
#define OUTPUTPATCH_H

#include <QObject>

class QLCIOPlugin;

/** @addtogroup engine Engine
 * @{
 */

#define KOutputNone QObject::tr("None")

#define KXMLQLCOutputPatch "Patch"
#define KXMLQLCOutputPatchUniverse "Universe"
#define KXMLQLCOutputPatchPlugin "Plugin"
#define KXMLQLCOutputPatchOutput "Output"

class OutputPatch : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(OutputPatch)

    Q_PROPERTY(QString outputName READ outputName CONSTANT)
    Q_PROPERTY(QString pluginName READ pluginName CONSTANT)

    /********************************************************************
     * Initialization
     ********************************************************************/
public:
    OutputPatch(QObject* parent = 0);
    OutputPatch(quint32 universe, QObject* parent = 0);
    virtual ~OutputPatch();

    /********************************************************************
     * Plugin & output
     ********************************************************************/
public:
    /**
     * Set the plugin to use and the plugin line number to output data on
     */
    bool set(QLCIOPlugin* plugin, quint32 output);

    /**
     * If a valid plugin and line have been set, close
     * the output line and re-open it again
     */
    bool reconnect();

    /** The plugin instance that has been assigned to a patch */
    QLCIOPlugin* plugin() const;

    /** Friendly name of the plugin assigned to a patch ("None" if none) */
    QString pluginName() const;

    /** An output line provided by the assigned plugin */
    quint32 output() const;

    /** Friendly name of the assigned output line */
    QString outputName() const;

    /** Returns true if a valid plugin line has been set */
    bool isPatched() const;

    /** Set a parameter specific to the patched plugin */
    void setPluginParameter(QString prop, QVariant value);

    /** Retrieve the map of custom parameters set to the patched plugin */
    QMap<QString, QVariant> getPluginParameters();

private:
    /** The reference of the plugin associated by this Output patch */
    QLCIOPlugin* m_plugin;
    /** The plugin line open by this Output patch */
    quint32 m_pluginLine;
    /** The universe that this Output patch is attached to */
    quint32 m_universe;

    /********************************************************************
     * Value dump
     ********************************************************************/
public:
    /** Write the contents of a 512 channel value buffer to the plugin.
      * Called periodically by OutputMap. No need to call manually. */
    void dump(quint32 universe, const QByteArray &data);
};

/** @} */

#endif
