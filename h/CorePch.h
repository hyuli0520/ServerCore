#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <atomic>
#include <mutex>
using namespace std;

#include "socket.h"
#include "context.h"
using namespace cppx;

#include "Thread/CoreTLS.h"
#include "Thread/ThreadManager.h"
#include "Memory/Memory.h"
#include "Memory/ObjectPool.h"

#define _STOMP