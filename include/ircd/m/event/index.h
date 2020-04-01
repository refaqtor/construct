// Matrix Construct
//
// Copyright (C) Matrix Construct Developers, Authors & Contributors
// Copyright (C) 2016-2018 Jason Volk <jason@zemos.net>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice is present in all copies. The
// full license for this software is available in the LICENSE file.

#pragma once
#define HAVE_IRCD_M_EVENT_INDEX_H

namespace ircd::m
{
	bool index(std::nothrow_t, const event::id &, const event::closure_idx &);

	[[gnu::warn_unused_result]] event::idx index(std::nothrow_t, const event::id &);
	event::idx index(const event::id &);

	[[gnu::warn_unused_result]] event::idx index(std::nothrow_t, const event &);
	event::idx index(const event &);
}
