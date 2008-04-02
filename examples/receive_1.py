import lsst.daf.base as datap
import lsst.ctrl.events as events
import time

if __name__ == "__main__":
    print "starting...\n"
    x = events.EventReceiver("lsst8.ncsa.uiuc.edu", "test_logging")
    print "waiting on receive...\n"
    val = x.receive(8000)
    print "finished!\n"
    print val.get()
    if val.get() != None:
        print val.toString("=", 1)
