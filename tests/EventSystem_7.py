#!/usr/bin/env python


import threading
import lsst.ctrl.events as events
import lsst.daf.base as base
import lsst.pex.exceptions as ex
import time


#
# Send an event; if this fails, remove /tmp/test_events_3 and retry.
#
def sendEvent(topicName):
    
    root = base.PropertySet()
    root.add("DATE","2007-07-01T14:28:32.546012")
    root.addInt("PID",200)
    root.add("HOST","fester.ncsa.uiuc.edu")
    root.add("IP","141.142.220.44")
    root.add("EVNT","test")
    root.add("misc1","data 1")
    root.add("misc2","data 2")
    root.addFloat("float_value", 3.14)
    
    eventSystem = events.EventSystem.getDefaultEventSystem()
    eventSystem.publish(topicName, root)

if __name__ == "__main__":
    topic1 = "test_events_3"
    eventSystem = events.EventSystem.getDefaultEventSystem()

    #
    # create a transmitter that has no receiver 
    # 
    try:
        eventSystem.createLocalTransmitter("moo")
    except ex.LsstCppException, e:
        pass
    #
    # Create a local receiver and sender
    #
    eventSystem.createLocalReceiver(topic1)
    eventSystem.createLocalTransmitter(topic1)

    #
    # send a test event on both topics at once, and have each receiver wait to
    # receive it
    #
    sendEvent(topic1)

    val = eventSystem.receive(topic1)
    assert val != None
