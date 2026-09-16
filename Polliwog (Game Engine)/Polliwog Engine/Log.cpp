#include "Log.h"

#include "NoLog.h"
#include "RenderLog.h"


// Set up all the unique copies of states
NoLog Log::Null;
RenderLog Log::Action;
