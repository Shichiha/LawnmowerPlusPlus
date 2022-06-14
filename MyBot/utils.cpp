#include <utils.h>

#include <ping.h>
#include <help.h>
#include <purge.h>

bool register_command(std::string name, dpp::cluster& bot, init_cmdptr init, commandptr func)
{
    auto cmd = init(bot);
    if (commands.contains(name))
    {
        return false;
    }
    commands[name] = { cmd, func };
    return true;
}

void init_commands(dpp::cluster& bot)
{
    register_command("ping", bot, ping_cmd_init, ping_cmd);
    register_command("help", bot, help_cmd_init, help_cmd);
    register_command("purge", bot, purge_cmd_init, purge_cmd);
}