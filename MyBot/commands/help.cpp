#include <commands/help.h>

void help_cmd(dpp::cluster& bot, const dpp::slashcommand_t& event)
{
    dpp::embed embed = dpp::embed().
        set_color(0x03fc41).
        set_title("Grasscutters").
        set_description("An unofficial community for the Grasscutter server.\n\n**Permanent Invite Link**: https://discord.gg/T5vZU6UyeG\n**GitHub Repository**: https://github.com/Melledy/Grasscutter\n**Trello Board**: https://trello.com/b/ij3ICC8K/features");

    event.reply(dpp::message(0,embed)
        .set_flags(dpp::message_flags::m_ephemeral));
}

dpp::slashcommand help_cmd_init(dpp::cluster& bot)
{
    return dpp::slashcommand()
        .set_name("help")
        .set_description("Shows the help.")
        .set_application_id(bot.me.id);
}
