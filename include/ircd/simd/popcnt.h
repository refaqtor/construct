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
#define HAVE_IRCD_SIMD_POPCNT_H

namespace ircd::simd
{
	template<class T> T popmask(const T) noexcept;
	template<class T> T boolmask(const T) noexcept;
	template<class T> uint popcnt(const T) noexcept;
}

/// Convenience template. Unfortunately this drops to scalar until specific
/// targets and specializations are created.
template<class T>
inline uint
ircd::simd::popcnt(const T a)
noexcept
{
	uint ret(0), i(0);
	for(; i < lanes<T>(); ++i)
		if constexpr(sizeof_lane<T>() <= sizeof(int))
			ret += __builtin_popcount(a[i]);
		else if constexpr(sizeof_lane<T>() <= sizeof(long))
			ret += __builtin_popcountl(a[i]);
		else
			ret += __builtin_popcountll(a[i]);

	return ret;
}

/// Convenience template. Extends a bool value where the lsb is 1 or 0 into a
/// mask value like the result of vector comparisons.
template<class T>
inline T
ircd::simd::boolmask(const T a)
noexcept
{
	return ~(popmask(a) - 1);
}

/// Convenience template. Vector compare instructions yield 0xff on equal;
/// sometimes one might need an actual value of 1 for accumulators or maybe
/// some bool-type reason...
template<class T>
inline T
ircd::simd::popmask(const T a)
noexcept
{
	return a & 1;
}
