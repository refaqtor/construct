// The Construct
//
// Copyright (C) The Construct Developers, Authors & Contributors
// Copyright (C) 2016-2020 Jason Volk <jason@zemos.net>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice is present in all copies. The
// full license for this software is available in the LICENSE file.

#pragma once
#define HAVE_IRCD_M_FED_ROOMS_H

namespace ircd::m::fed::rooms
{
	struct complexity;
};

struct ircd::m::fed::rooms::complexity
:request
{
	explicit operator json::object() const
	{
		return json::object
		{
			in.content
		};
	}

	complexity(const m::id::room &room_id,
	           const mutable_buffer &,
	           opts);

	complexity() = default;
};
