#ifndef _PING_H_
#define _PING_H_

#include <dpp/dpp.h>

void ping_cmd(dpp::cluster& bot, const dpp::slashcommand_t& event);
dpp::slashcommand ping_cmd_init(dpp::cluster& bot);

#endif // _PING_H_
