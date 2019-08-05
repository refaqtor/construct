// Matrix Construct
//
// Copyright (C) Matrix Construct Developers, Authors & Contributors
// Copyright (C) 2016-2019 Jason Volk <jason@zemos.net>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice is present in all copies. The
// full license for this software is available in the LICENSE file.

#pragma once
#define HAVE_IRCD_PROF_H

namespace ircd::prof
{
	struct init;
	struct type;
	struct event;
	enum dpl :uint8_t;
	using group = std::vector<std::unique_ptr<event>>;
	IRCD_EXCEPTION(ircd::error, error)
	IRCD_OVERLOAD(sample)

	// Samples
	uint64_t cycles() noexcept;     ///< Monotonic reference cycles (since system boot)
	uint64_t time_user() noexcept;  ///< Nanoseconds of CPU time in userspace.
	uint64_t time_kern() noexcept;  ///< Nanoseconds of CPU time in kernelland.
	uint64_t time_real() noexcept;  ///< Nanoseconds of CPU time real.
	uint64_t time_proc();           ///< Nanoseconds of CPU time for process.
	uint64_t time_thrd();           ///< Nanoseconds of CPU time for thread.

	// Control panel
	void stop(group &);
	void start(group &);
	void reset(group &);

	// Config
	extern conf::item<bool> enable;
}

#include "x86.h"
#include "vg.h"
#include "syscall_timer.h"
#include "instructions.h"
#include "resource.h"
#include "times.h"
#include "system.h"

// Exports to ircd::
namespace ircd
{
	using prof::cycles;
}

/// Type descriptor for prof events. This structure is used to aggregate
/// information that describes a profiling event type, including whether
/// the kernel or the user is being profiled (dpl), the principal counter
/// type being profiled (counter) and any other contextual attributes.
struct ircd::prof::type
{
	enum dpl dpl {0};
	uint8_t type_id {0};
	uint8_t counter {0};
	uint8_t cacheop {0};
	uint8_t cacheres {0};

	type(const event &);
	type(const enum dpl & = (enum dpl)0,
	     const uint8_t &attr_type = 0,
	     const uint8_t &counter = 0,
	     const uint8_t &cacheop = 0,
	     const uint8_t &cacheres = 0);
};

enum ircd::prof::dpl
:std::underlying_type<ircd::prof::dpl>::type
{
	KERNEL  = 0,
	USER    = 1,
};

struct ircd::prof::init
{
	init();
	~init() noexcept;
};

#if defined(__x86_64__) || defined(__i386__)
extern inline uint64_t
__attribute__((flatten, always_inline, gnu_inline, artificial))
ircd::prof::cycles()
noexcept
{
	return x86::rdtsc();
}
#else
ircd::prof::cycles()
noexcept
{
	static_assert(false, "Select reference cycle counter for platform.");
	return 0;
}
#endif