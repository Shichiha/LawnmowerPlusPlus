#include <commands/ping.h>

void ping_cmd(dpp::cluster& bot, const dpp::slashcommand_t& event)
{
    event.reply("Pong!");
}

dpp::slashcommand ping_cmd_init(dpp::cluster& bot)
{
    return dpp::slashcommand()
        .set_name("ping")
        .set_description("Just a basic ping command.")
        .set_application_id(bot.me.id);
}
