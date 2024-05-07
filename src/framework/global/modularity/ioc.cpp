/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2024 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ioc.h"

#include "log.h"

#ifndef NO_QT_SUPPORT
#include <QtQml>

muse::Injectable::GetContext muse::iocCtxForQmlObject(const QObject* o)
{
    return [o]() {
        QQmlEngine* engine = qmlEngine(o);
        if (!engine) {
            engine = qmlEngine(o->parent());
        }

        IF_ASSERT_FAILED(engine) {
            return modularity::ContextPtr();
        }

        QmlIoCContext* qmlIoc = engine->property("ioc_context").value<QmlIoCContext*>();
        IF_ASSERT_FAILED(qmlIoc) {
            return modularity::ContextPtr();
        }

        return qmlIoc->ctx;
    };
}

#endif