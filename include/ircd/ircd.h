/*
 *  ircd-ratbox: A slightly useful ircd.
 *  ircd.h: A header for the ircd startup routines.
 *
 *  Copyright (C) 1990 Jarkko Oikarinen and University of Oulu, Co Center
 *  Copyright (C) 1996-2002 Hybrid Development Team
 *  Copyright (C) 2002-2004 ircd-ratbox development team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
 *  USA
 */

#pragma once
#define HAVE_IRCD_H

#if defined(PIC) && defined(PCH)
	#include "stdinc.pic.h"
#else
	#include "stdinc.h"
#endif

namespace ircd {

extern bool debugmode;                           // Set by command line to indicate debug behavior
extern bool main_exited;                         // Set when main context has finished.

// Set callback for when IRCd's main context has completed.
using main_exit_cb = std::function<void ()>;
void at_main_exit(main_exit_cb);

//
// Sets up the IRCd, handlers (main context), and then returns without blocking.
// Pass your io_service instance, it will share it with the rest of your program.
// An exception will be thrown on error.
//
void init(boost::asio::io_service &ios, const std::string &newconf_path, main_exit_cb = nullptr);

//
// Notifies IRCd to shutdown. A shutdown will occur asynchronously and this function will return
// immediately. main_exit_cb will be called when IRCd has no more work for the ios (main_exit_cb
// will be the last operation from IRCd posted to the ios).
//
void stop();

} // namespace ircd




/*

#ifdef __cplusplus
namespace ircd {


struct SetOptions
{
	int maxclients;		// max clients allowed
	int autoconn;		// autoconn enabled for all servers?

	int floodcount;		// Number of messages in 1 second
	int ident_timeout;	// timeout for identd lookups

	int spam_num;
	int spam_time;

	char operstring[REALLEN];
	char adminstring[REALLEN];
};

struct Counter
{
	int oper;		// Opers
	int total;		// total clients
	int invisi;		// invisible clients
	int max_loc;	// MAX local clients
	int max_tot;	// MAX global clients
	unsigned long totalrestartcount;	// Total client count ever
};

extern struct SetOptions GlobalSetOptions;

extern volatile sig_atomic_t dorehash;
extern volatile sig_atomic_t dorehashbans;
extern volatile sig_atomic_t doremotd;
extern bool kline_queued;
extern bool server_state_foreground;
extern bool opers_see_all_users; // sno_farconnect.so loaded, operspy without accountability, etc

extern rb_dlink_list global_client_list;
extern client::client *local[];
extern struct Counter Count;
extern int default_server_capabs;

extern int splitmode;
extern int splitchecking;
extern int split_users;
extern int split_servers;
extern int eob_count;

extern rb_dlink_list unknown_list;
extern rb_dlink_list lclient_list;
extern rb_dlink_list serv_list;
extern rb_dlink_list global_serv_list;
extern rb_dlink_list local_oper_list;
extern rb_dlink_list oper_list;
extern rb_dlink_list dead_list;

extern int testing_conf;

extern struct ev_entry *check_splitmode_ev;

extern bool ircd_ssl_ok;
extern bool ircd_zlib_ok;
extern int maxconnections;

void restart(const char *) __attribute__((noreturn));
void ircd_shutdown() __attribute__((noreturn));
void server_reboot(void) __attribute__((noreturn));

}      // namespace ircd
#endif // __cplusplus

*/
