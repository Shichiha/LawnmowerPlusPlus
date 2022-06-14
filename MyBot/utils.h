#pragma once

#include <dpp/dpp.h>
#include <string>

typedef void (*commandptr) (dpp::cluster& bot, const dpp::slashcommand_t& event);
typedef dpp::slashcommand (*init_cmdptr) (dpp::cluster& bot);

typedef struct
{
    dpp::slashcommand cmd;
    commandptr cb;
} command_entry;

extern std::unordered_map<std::string, command_entry> commands;

bool register_command(std::string name, dpp::cluster& bot, init_cmdptr init, commandptr func);
void init_commands(dpp::cluster& bot);