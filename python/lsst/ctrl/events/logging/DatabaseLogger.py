#!/usr/bin/env python

# 
# LSST Data Management System
# Copyright 2008, 2009, 2010 LSST Corporation.
# 
# This product includes software developed by the
# LSST Project (http://www.lsst.org/).
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the LSST License Statement and 
# the GNU General Public License along with this program.  If not, 
# see <http://www.lsstcorp.org/LegalNotices/>.
#


from lsst.cat.MySQLBase import MySQLBase
import MySQLdb
import os
import sys
import subprocess

class DatabaseLogger(MySQLBase):

    def __init__(self, dbHostName, portNumber):
        MySQLBase.__init__(self, dbHostName, portNumber)
        self.keywords = ['HOSTID', 'RUNID', 'SLICEID', 'LEVEL', 'LOG', 'DATE', 'NODE', 'TIMESTAMP', 'COMMENT', 'STATUS', 'PIPELINE', 'pipeline', 'EVENTTIME', 'PUBTIME', 'TYPE', 'STAGEID', 'stageId', 'LOOPNUM', 'loopnum']
        self.keywordSet = set(self.keywords)

    def insertRecord(self, dbTable, ps):
        #runId = ps.get("RUNID")
        #dbName = "logs.%s" % runId
        #if self.dbExists(dbName) == False:
        #    self.createDb(self,dbName)
        #self.insertRecord(ps, dbName)
        self._insertRecord(dbTable, ps)

    def _insertRecord(self, dbTable, ps):

        hostId = ps.get("HOSTID")
        hostId = MySQLdb.escape_string(hostId)

        runId = ps.get("RUNID")
        runId = MySQLdb.escape_string(runId)

        sliceId = ps.get("SLICEID")
        level = ps.get("LEVEL")

        log = ps.get("LOG")
        log = MySQLdb.escape_string(log)

        date = ps.get("DATE")
        date = MySQLdb.escape_string(date)
        
        ts = ps.get("TIMESTAMP")
        eventtime = ps.get("EVENTTIME")
        pubtime = ps.get("PUBTIME")
        eventtype = ps.get("TYPE")
        eventtype = MySQLdb.escape_string(eventtype)

        node = -1
        if ps.exists("NODE"):
            node = ps.get("NODE")

        timestamp = ts.nsecs()

        commentList = ps.get("COMMENT")
        comment = ""
        
        if ps.valueCount("COMMENT") == 1:
            comment = commentList
        else:
            for i in commentList:
                if comment == "":
                    comment = i
                else:
                    comment = comment+";"+i


        if (ps.exists("TOPIC")):
            ps.remove("TOPIC")

        status = "NULL"
        if ps.exists("STATUS"):
            status = ps.get("STATUS")
            status = MySQLdb.escape_string(status)

        if ps.exists("pipeline"):
            pipeline = ps.get("pipeline")
            pipeline = MySQLdb.escape_string(pipeline)
        elif ps.exists("PIPELINE"):
            pipeline = ps.get("PIPELINE")
            pipeline = MySQLdb.escape_string(pipeline)
        else:
            pipeline = "NULL"

        stageid = "-1"
        if ps.exists("stageId"):
            stageid = ps.get("stageId")
        elif ps.exists("STAGEID"):
            stageid = ps.get("STAGEID")

        loopnum = "-1"
        if ps.exists("loopnum"):
            loopnum = ps.get("loopnum")
        elif ps.exists("LOOPNUM"):
            loopnum = ps.get("LOOPNUM")



        names = ps.names()
        namesSet = set(names)

        diff = namesSet.difference(self.keywordSet)

        custom = ""
        for name in diff:
            if custom == "":
                custom = "%s : %s;" % (name,ps.get(name))
            else:
                custom = custom+ "%s : %s;" % (name,ps.get(name))
        if custom == "":
            custom = "NULL"
        custom = MySQLdb.escape_string(custom[0:4096])
        comment = MySQLdb.escape_string(comment[0:2048])

        cmd = """INSERT INTO logs.%s(hostId, runId, sliceid, status, level, log, date, node, TIMESTAMP, custom, comment, pipeline, eventtime, pubtime, type, stageid, loopnum) values("%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s")""" % (dbTable, hostId, runId, sliceId, status, level, log, date, node, timestamp, custom, comment, pipeline, eventtime, pubtime, eventtype, stageid, loopnum)


        self.execCommand0(cmd)

