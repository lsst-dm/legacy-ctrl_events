// -*- lsst-c++ -*-

/* 
 * LSST Data Management System
 * Copyright 2008-2014  AURA/LSST.
 * 
 * This product includes software developed by the
 * LSST Project (http://www.lsst.org/).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the LSST License Statement and 
 * the GNU General Public License along with this program.  If not, 
 * see <https://www.lsstcorp.org/LegalNotices/>.
 */

/** \file StatusEvent.cc
  *
  * \brief Status Event implementation
  *
  * \ingroup ctrl/events
  *
  * \author Stephen R. Pietrowicz, NCSA
  *
  */
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <cstring>

#include "lsst/ctrl/events/LocationID.h"
#include "lsst/ctrl/events/EventTypes.h"
#include "lsst/ctrl/events/Event.h"
#include "lsst/ctrl/events/StatusEvent.h"
#include "lsst/ctrl/events/EventSystem.h"
#include "lsst/daf/base/DateTime.h"
#include "lsst/daf/base/PropertySet.h"
#include "lsst/pex/exceptions.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <time.h>

#include <activemq/core/ActiveMQConnectionFactory.h>

namespace pexExceptions = lsst::pex::exceptions;
namespace pexLogging = lsst::pex::logging;


using namespace std;
using std::numeric_limits;

namespace lsst {
namespace ctrl {
namespace events {

const std::string StatusEvent::ORIG_HOSTNAME = "ORIG_HOSTNAME";
const std::string StatusEvent::ORIG_PROCESSID = "ORIG_PROCESSID";
const std::string StatusEvent::ORIG_LOCALID = "ORIG_LOCALID";

/** \brief Creates StatusEvent which contains a PropertySet
  *
  */

StatusEvent::StatusEvent() : Event() {
    _init();
}


void StatusEvent::_init() {
    _keywords.insert(ORIG_HOSTNAME);
    _keywords.insert(ORIG_PROCESSID);
    _keywords.insert(ORIG_LOCALID);
}

StatusEvent::StatusEvent(cms::TextMessage *msg) : Event(msg) {
    _init();

    _psp->set(ORIG_HOSTNAME, (std::string)msg->getStringProperty(ORIG_HOSTNAME));
    _psp->set(ORIG_PROCESSID, (int)msg->getIntProperty(ORIG_PROCESSID));
    _psp->set(ORIG_LOCALID, (int)msg->getIntProperty(ORIG_LOCALID));
}

StatusEvent::StatusEvent(const LocationID& originatorID, const PropertySet& ps) : Event(ps) {
    _constructor(originatorID);
}

StatusEvent::StatusEvent(const LocationID& originatorID, const PropertySet& ps, const PropertySet& filterable) : Event(ps, filterable) {
    _constructor(originatorID);
}

StatusEvent::StatusEvent( const std::string& runID, const LocationID& originatorID, const PropertySet::Ptr psp) : Event(runID, *psp) {
    _constructor(originatorID);
}

StatusEvent::StatusEvent( const std::string& runID, const LocationID& originatorID, const PropertySet::Ptr psp, const PropertySet& filterable) : Event(runID, *psp, filterable) {
    _constructor(originatorID);
}

StatusEvent::StatusEvent( const std::string& runID, const LocationID& originatorID, const PropertySet& ps) : Event(runID, ps) {
    _constructor(originatorID);
}

StatusEvent::StatusEvent( const std::string& runID, const LocationID& originatorID, const PropertySet& ps, const PropertySet& filterable) : Event(runID, ps, filterable) {
    _constructor(originatorID);
}

void StatusEvent::_constructor(const LocationID& originatorID) {
    _init();

    _psp->set(ORIG_HOSTNAME, originatorID.getHostName());
    _psp->set(ORIG_PROCESSID, originatorID.getProcessID());
    _psp->set(ORIG_LOCALID, originatorID.getLocalID());
    _psp->set(TYPE, EventTypes::STATUS);

}

void StatusEvent::populateHeader(cms::TextMessage* msg) const {
    Event::populateHeader(msg);

    msg->setStringProperty(ORIG_HOSTNAME, _psp->get<std::string>(ORIG_HOSTNAME));
    msg->setIntProperty(ORIG_PROCESSID, _psp->get<int>(ORIG_PROCESSID));
    msg->setIntProperty(ORIG_LOCALID, _psp->get<int>(ORIG_LOCALID));
}

LocationID *StatusEvent::getOriginator() {
    std::string hostname = _psp->get<std::string>(ORIG_HOSTNAME);
    int pid = _psp->get<int>(ORIG_PROCESSID);
    int local = _psp->get<int>(ORIG_LOCALID);
    return new LocationID(hostname, pid, local);
}

/** \brief destructor
  */
StatusEvent::~StatusEvent() {
}

}
}
}
