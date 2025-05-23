#pragma once

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <atomic>
#include <mutex>
#include <thread>
#include <functional>
using namespace std;

#include <mysqlx/xdevapi.h>

#include <tbb/tbb.h>
#include <concurrent_vector.h>
#include <concurrent_queue.h>
#include <concurrent_priority_queue.h>
#include <concurrent_unordered_map.h>
#include <concurrent_unordered_set.h>
using namespace tbb;

#include "socket.h"
#include "context.h"
using namespace cppx;

#include "Thread/CoreTLS.h"
#include "Thread/Job.h"
#include "Memory/Memory.h"
#include "Memory/ObjectPool.h"
#include "System/Engine.h"

#define _STOMP