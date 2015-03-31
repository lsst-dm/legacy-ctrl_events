// -*- lsst-c++ -*-

/* 
 * LSST Data Management System
 * Copyright 2008-2015  AURA/LSST.
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

/** 
 * @file LocationID.h
 *
 * @ingroup ctrl/events
 *
 * @brief defines the LocationID class
 *
 */

#ifndef LSST_CTRL_EVENTS_LOCATIONID_H
#define LSST_CTRL_EVENTS_LOCATIONID_H

#include <stdlib.h>

#include "boost/shared_ptr.hpp"

namespace lsst {
namespace ctrl {
namespace events {

/**
 * @class LocationID
 * @brief Represent process that created an event
 */
class LocationID {
public:

    typedef boost::shared_ptr<LocationID> Ptr;
    typedef boost::shared_ptr<LocationID const> ConstPtr;

    /** 
     * @brief LocationID object. This object represents the originating process
     *        process of an event. This consists of the host name, the process 
     *        id of the process that created this LocationID and a local id 
     *        which is unique for this process. When created, this represents 
     *        a unique location ID.
     */
    LocationID();

    /** 
     * @brief LocationID object. This object represents the originating process
     *        of an event.  When created, this represents a duplicated ID.
     */
    LocationID(LocationID const& id);

    /** 
     * @brief LocationID object. This object represents the originating process
     *        of an event.  When created, this represents a reconstituted ID.
     */
    LocationID(std::string const& hostname, int pid, int localID);


    /** 
     * @brief Retrieve the host name
     * @return a string containing the name of a host
     */
    std::string getHostName() const;

    /** 
     * @brief Retrieve the process id
     * @return an int of the process id
     */
    int getProcessID() const;

    /** 
     * @brief Retrieve the local id
     * @return an int of local id
     */
    int getLocalID() const;

protected:
    static int _localCounter;
    std::string _hostname;
    int _pid;
    int _localID;

};
}
}
}

#endif /*end LSST_CTRL_EVENTS_LOCATIONID_H*/
