#ifndef _HELP_H_
#define _HELP_H_

#include <dpp/dpp.h>

void help_cmd(dpp::cluster& bot, const dpp::slashcommand_t& event);
dpp::slashcommand help_cmd_init(dpp::cluster& bot);

#endif // _HELP_H_
