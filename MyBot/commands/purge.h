#ifndef _PURGE_H_
#define _PURGE_H_

#include <dpp/dpp.h>

void purge_cmd(dpp::cluster& bot, const dpp::slashcommand_t& event);
dpp::slashcommand purge_cmd_init(dpp::cluster& bot);


#endif // _PURGE_H_
