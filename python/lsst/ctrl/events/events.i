/* Events.i */
%module("directors=1") events

%{
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include "lsst/daf/data/Citizen.h"
#include "lsst/pex/exceptions.h"
#include "lsst/pex/policy/Policy.h"
#include "lsst/daf/base/DataProperty.h"
#include "lsst/ctrl/events/EventTransmitter.h"
#include "lsst/ctrl/events/EventReceiver.h"
#include "lsst/ctrl/events/EventSystem.h"
#include "lsst/pex/logging/Log.h"
#include "lsst/pex/logging/LogRecord.h"
#include "lsst/ctrl/events/EventLog.h"
#include "lsst/ctrl/events/EventFormatter.h"
%}

%inline %{
namespace lsst { namespace daf { namespace base { } } } 
namespace lsst { namespace pex { namespace policy { } } } 
namespace activemq { namespace core { } } 
namespace activemq { namespace util { } } 
namespace activemq { namespace concurrent { } } 
namespace cms { } 
namespace boost { namespace filesystem {} }

using namespace lsst;
using namespace lsst::daf::base;
using namespace lsst::pex::policy;
%}

%init %{
%}
%pythoncode %{
import lsst.daf.base
import lsst.pex.policy
%}

%include "std_string.i"
%include "std_set.i"
%include "lsst/utils/p_lsstSwig.i"
%include "lsst/utils/Utils.h"
%import "lsst/daf/base/Citizen.h"
%import "lsst/pex/policy/Policy.h"
%import "lsst/daf/base/DataProperty.h"
%import "lsst/pex/exceptions.h"
%import "lsst/pex/logging/Log.h"
%import "lsst/pex/logging/LogRecord.h"
%include "lsst/ctrl/events/EventTransmitter.h"
%include "lsst/ctrl/events/EventReceiver.h"
%include "lsst/ctrl/events/EventLog.h"
%include "lsst/ctrl/events/EventFormatter.h"
%include "lsst/ctrl/events/EventSystem.h"